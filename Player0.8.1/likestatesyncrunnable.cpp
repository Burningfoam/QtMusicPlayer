#include "likestatesyncrunnable.h"
#include "databaseconnectionpool.h"

LikeStateSyncRunnable::LikeStateSyncRunnable(const QString &userId,  const QString &musicId, QObject *parent)
    : userId(userId),
      musicId(musicId)
{
    setAutoDelete(true);
}

void LikeStateSyncRunnable::run()
{
    bool isLiked = false;

    // 从连接池获取数据库连接
    QSqlDatabase db = DatabaseConnectionPool::instance().getConnection();
    if (!db.isOpen())
    {
        emit checkFailed("数据库连接失败: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM Playlist P "
                  "JOIN PlaylistSong PS ON P.playlist_id = PS.playlist_id "
                  "WHERE P.user_id = :userId AND P.playlist_name = 'user_likelist' AND PS.music_id = :musicId");
    query.bindValue(":userId", userId);
    query.bindValue(":musicId", musicId);

    if (!query.exec())
    {
        emit checkFailed("查询执行失败: " + query.lastError().text());
        return;
    }

    if (query.next())
    {
        isLiked = query.value(0).toInt() > 0;
    }

    // 发射信号将结果返回主线程
    emit checkCompleted(isLiked);

    // 释放数据库连接
    DatabaseConnectionPool::instance().releaseConnection(db);
}
