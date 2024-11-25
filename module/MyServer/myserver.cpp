#include "myserver.h"
#include <QThreadPool>
#include "clientrunnable.h"
#include "requesthandler.h"
#include <QDebug>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

MyServer::MyServer(QTcpServer *parent)
    : QTcpServer(parent)
{
}

void MyServer::StartServer(int port)
{
    if(this->listen(QHostAddress::Any,port))
    {
        qDebug()<<"server listen!"<<endl;
    }
    else
    {
        qDebug()<<"server listen failed!"<<endl;
    }
//    QString musicDirectory = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\artists\\"; // 替换为实际的音乐文件夹路径
//    QString outputFile = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\metadata.json";
//    generateMetadataJson(musicDirectory, outputFile);
    loadMetadata("D:/File/Documents/QtProjects/MusicPlayer/music/metadata.json");
    generateMusicListJson();
    initializeHandlers();
}

void MyServer::incomingConnection(qintptr handle)
{
    ClientRunnable* c = new ClientRunnable(handle,this);
    QThreadPool::globalInstance()->start(c);
}

void MyServer::generateMetadataJson(const QString &musicDirectory, const QString &outputFile)
{
    QDir dir(musicDirectory);
    if (!dir.exists())
    {
        qDebug() << "Directory does not exist:" << musicDirectory;
        return;
    }

    QJsonArray songsArray;

    // 遍历艺术家目录
    foreach (const QString &artistDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QDir artistPath(dir.filePath(artistDir));

        // 遍历专辑目录
        foreach (const QString &albumDir, artistPath.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QDir albumPath(artistPath.filePath(albumDir));

            // 查找封面文件
            QString coverFile;
            foreach (const QString &file, albumPath.entryList({"*.jpg", "*.png"}, QDir::Files))
            {
                if (file.startsWith("cover"))
                {
                    coverFile = albumPath.filePath(file);
                    break;
                }
            }

            // 遍历音乐文件
            foreach (const QString &file, albumPath.entryList({"*.mp3", "*.flac", "*.wav"}, QDir::Files))
            {
                QFileInfo fileInfo(albumPath.filePath(file));
                QString songPath = fileInfo.filePath();
                QString songName = fileInfo.baseName();

                // 查找歌词文件
                QString lyricsFile = albumPath.filePath(songName + ".lrc");
                if (!QFile::exists(lyricsFile))
                {
                    lyricsFile.clear();
                }

                // 使用目录信息生成元数据
                QJsonObject songObject;
                songObject["id"] = QString::number(qHash(songPath,0));
                songObject["title"] = songName.isEmpty() ? "Unknown Title" : songName;
                songObject["artist"] = artistDir.isEmpty() ? "Unknown Artist" : artistDir;
                songObject["album"] = albumDir.isEmpty() ? "Unknown Album" : albumDir;
//                songObject["duration"] = 0; // 如果需要时长，需额外处理
                songObject["file_path"] = songPath;
                songObject["lyrics_path"] = lyricsFile.isEmpty() ? "N/A" : lyricsFile;
                songObject["cover_path"] = coverFile.isEmpty() ? "N/A" : coverFile;

                songsArray.append(songObject);
            }
        }
    }

    // 构建 JSON 对象并写入文件
    QJsonObject rootObject;
    rootObject["songs"] = songsArray;

    QJsonDocument jsonDoc(rootObject);
    QFile outFile(outputFile);
    if (outFile.open(QIODevice::WriteOnly))
    {
        outFile.write(jsonDoc.toJson(QJsonDocument::Indented));
        outFile.close();
        qDebug() << "Metadata.json generated successfully!";
    }
    else
    {
        qDebug() << "Failed to write metadata.json!";
    }
}

void MyServer::loadMetadata(const QString &metadataPath)
{
    QFile file(metadataPath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isNull())
        {
            QJsonArray songsArray = doc.object()["songs"].toArray();
            for (const QJsonValue& value : songsArray)
            {
                QJsonObject songObj = value.toObject();
                SongInfo song;
                song.title = songObj["title"].toString();
                song.artist = songObj["artist"].toString();
                song.album = songObj["album"].toString();
                song.filePath = songObj["file_path"].toString();
                song.lyricsPath = songObj["lyrics_path"].toString();
                song.coverPath = songObj["cover_path"].toString();
                song.id = songObj["id"].toString();
//                song.duration = songObj["duration"].toInt();
                songMap[song.id] = song;
            }
        }
    }
}

void MyServer::generateMusicListJson()
{
    // 分割输入字符串，获取ID列表
    QString idString = "431352237,2480320881,3038060749,972864246,2561447689,2775921610";
    QStringList idList = idString.split(",", QString::SkipEmptyParts);

    // 创建一个JSON数组存储歌曲信息
    QJsonArray hotListArray;

    for (const QString &id : idList)
    {
        if (songMap.contains(id.trimmed())) // 确保歌曲ID在map中存在
        {
            const SongInfo &song = songMap[id.trimmed()];

            // 构造JSON对象存储歌曲信息
            QJsonObject songObj;
            songObj["title"] = song.title;
            songObj["artist"] = song.artist;
            songObj["album"] = song.album;
            songObj["id"] = song.id;

            hotListArray.append(songObj);
        }
    }

    // 构造JSON对象结构
    QJsonObject rootObj;
    QJsonObject musicListObj;
    musicListObj["hotlist"] = hotListArray;
    rootObj["musiclist"] = musicListObj;

    // 将JSON对象写入文件
    QFile file("D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\hotlist.json");
    if (file.open(QIODevice::WriteOnly))
    {
        QJsonDocument doc(rootObj);
        file.write(doc.toJson(QJsonDocument::Indented)); // 美化格式化输出
        file.close();
    }
}

void MyServer::initializeHandlers()
{
    RequestHandlerRegistry::instance().registerHandler("DOWNLOAD_MUSIC", new DownloadMusicHandler());
    RequestHandlerRegistry::instance().registerHandler("DOWNLOAD_COVER", new DownloadCoverHandler());
    RequestHandlerRegistry::instance().registerHandler("DOWNLOAD_LYRIC", new DownloadLyricHandler());
    RequestHandlerRegistry::instance().registerHandler("GET_MUSICLIST", new GetMusicListHandler());
}

MyServer::~MyServer()
{

}
