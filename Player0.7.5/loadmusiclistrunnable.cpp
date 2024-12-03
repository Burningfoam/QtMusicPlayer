#include "loadmusiclistrunnable.h"
#include "widget.h"

loadMusicListRunnable::loadMusicListRunnable(const QString &userid, const QString &listname, const QString& tempPath, QObject *parent)
    : userId(userid),
      listName(listname),
      tempPath(tempPath)
{
    setAutoDelete(true);
}

void loadMusicListRunnable::run()
{
    qDebug()<<"进入歌单子线程！";
    QList<SongInfo> songList;  // 用于存储查询到的歌曲信息

    // 每个子线程都使用独立的数据库连接
    QSqlDatabase db;

    // 检查是否已经存在连接
    if (!QSqlDatabase::contains("MusiclistLoaderConnection"))
    {
        qDebug() << "新建歌单子线程数据库连接";
        db = QSqlDatabase::addDatabase("QMYSQL", "MusiclistLoaderConnection"); // 使用独立连接名称
//        db.setHostName("192.168.109.128");
        db.setHostName("121.40.108.31");
        db.setUserName("root");
        db.setPassword("1");
        db.setPort(3306);
        db.setDatabaseName("musicDB");
    }
    else
    {
        // 如果连接已经存在，获取该连接对象
        db = QSqlDatabase::database("MusiclistLoaderConnection");
        qDebug() << "已经存在歌单子线程数据库连接";
    }

    // 打开数据库连接
    if (!db.isOpen() && !db.open())
    {
        qDebug() << "歌单子线程数据库打开失败:" << db.lastError().text();
        return;  // 如果数据库无法打开，直接返回
    }
    else
    {
        qDebug() << "歌单子线程数据库连接成功";
    }

    QSqlQuery query(db);
    // 获取歌单 ID
    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = :playlist_name");
    query.bindValue(":userId", userId);
    query.bindValue(":playlist_name", listName);

    if (!query.exec() || !query.next())
    {
        emit loadFailed("Playlist not found: " + listName);
        return;
    }

    int playlistId = query.value("playlist_id").toInt();

    // 查询歌单中的歌曲
    query.prepare("SELECT S.music_id, S.title, S.artist, S.album, S.coverPath "
                  "FROM SongInfo S "
                  "JOIN PlaylistSong PS ON S.music_id = PS.music_id "
                  "WHERE PS.playlist_id = :playlistId");
    query.bindValue(":playlistId", playlistId);

    if (!query.exec())
    {
        emit loadFailed("Database query failed: " + query.lastError().text());
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

        songList.append(song);
    }

    emit loadCompleted(songList);  // 将结果发送到主线程

    // 子线程完成数据库操作后关闭连接
    db.close();
}
