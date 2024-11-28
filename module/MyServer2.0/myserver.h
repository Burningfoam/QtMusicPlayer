#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer> // QT服务器类


struct SongInfo
{
    QString title;       // 歌曲标题
    QString artist;      // 艺术家
    QString album;       // 专辑
    QString filePath;    // 歌曲文件路径
    QString lyricsPath;  // 歌词文件路径
    QString coverPath;   // 封面图片路径
    QString id;          // 唯一标识符
//    int duration;        // 歌曲时长
};

class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    MyServer(QTcpServer *parent = 0);
    ~MyServer();
    // 启动服务器监听
    void StartServer(int port);
    // 重写新连接的虚函数
    void incomingConnection(qintptr handle);
    // 生成所有音乐文件的元数据
    void generateMetadataJson(const QString &musicDirectory, const QString &outputFile);
    void generateMetadataSQL(const QString &musicDirectory);
    // 使用 QMap 存储歌曲，键为歌曲ID
    QMap<QString, SongInfo> songMap;
private:
    // 加载json文件中的所有歌曲信息
    void loadMetadata(const QString& metadataPath);
    // 生成歌单json
    void generateMusicListJson();
    // 初始化注册机
    void initializeHandlers();
private:


};

#endif // MYSERVER_H
