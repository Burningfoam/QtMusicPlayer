#include "likestateschangerunnable.h"
#include "databaseconnectionpool.h"

LikeStatesChangeRunnable::LikeStatesChangeRunnable(const QString &userId, const QString &musicId, bool like, QObject *parent)
    : QObject(parent),
      userId(userId),
      musicId(musicId),
      like(like)
{
    setAutoDelete(true);
}

void LikeStatesChangeRunnable::run()
{
    QSqlDatabase db = DatabaseConnectionPool::instance().getConnection();

    if (!db.isOpen())
    {
        emit operationFailed("数据库连接失败");
        return;
    }

    QSqlQuery query(db);
    int playlistId;

    // 查找或创建用户的 'user_likelist'
    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_likelist'");
    query.bindValue(":userId", userId);

    if (!query.exec() || !query.next())
    {
        // 创建 'user_likelist'
        query.prepare("INSERT INTO Playlist (user_id, playlist_name) VALUES (:userId, 'user_likelist')");
        query.bindValue(":userId", userId);

        if (!query.exec())
        {
            emit operationFailed("创建歌单失败: " + query.lastError().text());
            DatabaseConnectionPool::instance().releaseConnection(db);
            return;
        }

        playlistId = query.lastInsertId().toInt();
    }
    else
    {
        playlistId = query.value("playlist_id").toInt();
    }

    // 根据操作进行插入或删除
    if (like)
    {
        query.prepare("INSERT INTO PlaylistSong (playlist_id, music_id) VALUES (:playlistId, :musicId)");
    }
    else
    {
        query.prepare("DELETE FROM PlaylistSong WHERE playlist_id = :playlistId AND music_id = :musicId");
    }
    query.bindValue(":playlistId", playlistId);
    query.bindValue(":musicId", musicId);

    if (!query.exec())
    {
        emit operationFailed("数据库操作失败: " + query.lastError().text());
    }
    else
    {
        emit operationCompleted(true, like);
    }

    DatabaseConnectionPool::instance().releaseConnection(db);
}
