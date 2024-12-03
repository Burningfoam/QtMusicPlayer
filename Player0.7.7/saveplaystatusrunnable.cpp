#include "saveplaystatusrunnable.h"
#include "databaseconnectionpool.h"

SavePlayStatusRunnable::SavePlayStatusRunnable(const QString &userId, int currentSongId, int currentDuration, const QStringList &playlist, QObject *parent)
    : userId(userId),
      currentSongId(currentSongId),
      currentDuration(currentDuration),
      playlist(playlist)
{
    setAutoDelete(true);
}

void SavePlayStatusRunnable::run()
{
    QSqlDatabase db = DatabaseConnectionPool::instance().getConnection();
    if (!db.isOpen())
    {
        qWarning() << "数据库连接失败：" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);

    // 保存当前播放歌曲信息
    query.prepare("UPDATE UserInfo SET last_played_song_id = :songId, last_played_song_duration = :duration WHERE user_id = :userId");
    query.bindValue(":songId", currentSongId);
    query.bindValue(":duration", currentDuration);
    query.bindValue(":userId", userId);
    if (!query.exec())
    {
        qWarning() << "保存当前播放歌曲失败：" << query.lastError().text();
    }

    // 获取或创建播放列表
    int playlistId = 0;
    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_playlist'");
    query.bindValue(":userId", userId);
    if (query.exec() && query.next())
    {
        playlistId = query.value(0).toInt();
    }
    else
    {
        query.prepare("INSERT INTO Playlist (user_id, playlist_name) VALUES (:userId, 'user_playlist')");
        query.bindValue(":userId", userId);
        if (query.exec())
        {
            playlistId = query.lastInsertId().toInt();
        }
        else
        {
            qWarning() << "创建播放列表失败：" << query.lastError().text();
            return;
        }
    }

    // 清空播放列表
    query.prepare("DELETE FROM PlaylistSong WHERE playlist_id = :playlistId");
    query.bindValue(":playlistId", playlistId);
    if (!query.exec())
    {
        qWarning() << "清空播放列表失败：" << query.lastError().text();
    }

    // 插入播放列表中的歌曲
    query.prepare("INSERT INTO PlaylistSong (playlist_id, music_id) VALUES (:playlistId, :musicId)");
    foreach (const QString& musicId, playlist)
    {
        query.bindValue(":playlistId", playlistId);
        query.bindValue(":musicId", musicId.toInt());
        if (!query.exec())
        {
            qWarning() << "插入歌曲失败：" << query.lastError().text();
        }
    }

    DatabaseConnectionPool::instance().releaseConnection(db);
}
