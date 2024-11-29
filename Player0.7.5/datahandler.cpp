#include "datahandler.h"
#include "widget.h"
#include <QFile>

void JsonDataHandler::handleData(const QByteArray &data,Widget* w)
{
    // 解析 JSON 数据
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isObject())
        {
            qDebug() << "Invalid JSON format!";
            return;
        }

        QJsonObject rootObj = doc.object();

        // 检查是否包含 "musiclist" 字段
        if (rootObj.contains("musiclist"))
        {
            QJsonObject musiclistObj = rootObj.value("musiclist").toObject();

            // 检查是否包含 "hotlist" 字段
            if (musiclistObj.contains("hotlist"))
            {
                w->parseMusicList(data,w->map_hotList,"11");

            }
        }

}

void AudioDataHandler::handleData(const QByteArray &data,Widget* w)
{
    qDebug()<<"开始保存音乐";
    // 处理音频数据
//    QString location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
    QString location = w->tempPath + "music\\";
    QString musicid = w->requestedMusicId;
    QFile file(location + musicid + ".mp3");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
        w->requestedMusicId.clear();
        w->IsRequestMusicReceived = true;
        qDebug() << "音乐保存成功！";
        // 下载成功后发射信号
        emit w->downloadSuccess_music();  // 触发 downloadSuccess 信号
    }
    else
    {
        qDebug() << "无法保存文件！";
    }
}

void LyricDataHandler::handleData(const QByteArray &data,Widget* w)
{
    // 处理音频数据
//    QString location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
    QString location = w->tempPath + "music\\";
    QString musicid = w->requestedLyricId;
    QFile file(location + musicid + ".lrc");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
        w->IsRequestLyricReceived = true;
        qDebug() << "歌词保存成功！";
        emit w->downloadSuccess_lyric();
    }
    else
    {
        qDebug() << "无法保存文件！";
    }
}

void CoverDataHandler::handleData(const QByteArray &data,Widget* w)
{
    // 处理音频数据
//    QString location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
    QString location = w->tempPath + "music\\";
//    QString musicid = w->requestedCoverId;
    QString musicid = w->downloadCoverQueue.dequeue();
    QFile file(location + musicid + ".png");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
        w->IsRequestCoverReceived = true;
        qDebug() << "封面保存成功！";
        emit w->downloadSuccess_cover();
    }
    else
    {
        qDebug() << "无法保存文件！";
    }
}
