#include "requesthandler.h"
//#include "clientrunnable.h"
#include "myserver.h"
#include <QFile>

void DownloadMusicHandler::handleRequest(const QJsonObject &request,QTcpSocket &socket,QMap<QString, SongInfo>& songMap)
{
    QString musicId = request["musicid"].toString();

    QFile file(songMap[musicId].filePath); // 打开要发送的 MP3 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<songMap[musicId].filePath;
        qDebug() << "无法打开音乐文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();

    size_t fileSize = fileContent.size(); // 获取文件大小
    auto Type = QString("audio").toUtf8();
    qDebug()<<"开始发送："<<songMap[musicId].title;
    // 发送包头（文件大小）
    socket.write((const char*)&fileSize, sizeof(size_t));
    socket.write(Type);
    // 发送文件内容
    socket.write(fileContent);
}

void DownloadCoverHandler::handleRequest(const QJsonObject &request, QTcpSocket &socket, QMap<QString, SongInfo> &songMap)
{
    QString musicId = request["musicid"].toString();

    QFile file(songMap[musicId].coverPath); // 打开要发送的 封面 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<songMap[musicId].coverPath;
        qDebug() << "无法打开封面文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();

    size_t fileSize = fileContent.size(); // 获取文件大小
    auto Type = QString("cover").toUtf8();

    // 发送包头（文件大小）
    socket.write((const char*)&fileSize, sizeof(size_t));
    socket.write(Type);
    // 发送文件内容
    socket.write(fileContent);
}

void DownloadLyricHandler::handleRequest(const QJsonObject &request,QTcpSocket &socket,QMap<QString, SongInfo>& songMap)
{
    QString musicId = request["musicid"].toString();

    QFile file(songMap[musicId].lyricsPath); // 打开要发送的 lrc 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<songMap[musicId].lyricsPath;
        qDebug() << "无法打开歌词文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();

    size_t fileSize = fileContent.size(); // 获取文件大小
    auto Type = QString("lyric").toUtf8();

    // 发送包头（文件大小）
    socket.write((const char*)&fileSize, sizeof(size_t));
    socket.write(Type);
    // 发送文件内容
    socket.write(fileContent);
}

void GetMusicListHandler::handleRequest(const QJsonObject &request,QTcpSocket &socket,QMap<QString, SongInfo>& songMap)
{
    QString Location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\";
    QString ListName = request["listtype"].toString() + ".json";

    qDebug()<<"歌单名："<<ListName;

    QFile file(Location + ListName); // 打开要发送的 json 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<Location + ListName;
        qDebug() << "无法打开歌单文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();

    size_t fileSize = fileContent.size(); // 获取文件大小
    auto Type = QString("json ").toUtf8();

    // 发送包头（文件大小）
    socket.write((const char*)&fileSize, sizeof(size_t));
    socket.write(Type);
    // 发送文件内容
    socket.write(fileContent);
}
