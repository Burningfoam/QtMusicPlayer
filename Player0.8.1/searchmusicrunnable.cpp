#include "searchmusicrunnable.h"
#include "databaseconnectionpool.h"
#include <QFile>
#include <QDebug>
#include "widget.h"

SearchMusicRunnable::SearchMusicRunnable(const QString &keyword, const QString &tempPath, QObject *parent)
    : QObject(parent),
      searchKeyword(keyword),
      tempPath(tempPath)
{
    setAutoDelete(true);
}

void SearchMusicRunnable::run()
{
    qDebug() << "进入搜索子线程！";
    QList<SongInfo> searchResults; // 用于存储查询到的歌曲信息

    // 从连接池获取数据库连接
    QSqlDatabase db = DatabaseConnectionPool::instance().getConnection();

    if (!db.isOpen())
    {
        emit searchFailed("数据库连接失败: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    // 模糊查询音乐信息
    query.prepare(R"(
        SELECT music_id, title, artist, album, coverPath
        FROM SongInfo
        WHERE title LIKE :keyword OR artist LIKE :keyword OR album LIKE :keyword
    )");
    query.bindValue(":keyword", "%" + searchKeyword + "%");

    if (!query.exec())
    {
        emit searchFailed("数据库查询失败: " + query.lastError().text());
        DatabaseConnectionPool::instance().releaseConnection(db);
        return;
    }

    // 遍历查询结果，收集数据
    while (query.next())
    {
        SongInfo song;
        song.id = QString::asprintf("%010d", query.value("music_id").toInt());
        song.title = query.value("title").toString();
        song.artist = query.value("artist").toString();
        song.album = query.value("album").toString();
        song.coverPath = query.value("coverPath").toString();
        song.coverExists = QFile::exists(tempPath + "music\\" + song.id + ".png");

        searchResults.append(song);
    }

    emit searchCompleted(searchResults); // 将结果发送到主线程

    // 释放数据库连接
    DatabaseConnectionPool::instance().releaseConnection(db);
}
