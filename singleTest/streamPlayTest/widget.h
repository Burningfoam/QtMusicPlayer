#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QString>
#include <QMap>
#include <QTimer>
#include <QTcpSocket>
#include <QListWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

// 播放模式
enum PLAYERMODE
{
    ORDER_PLAY, // 顺序播放
    RANDOM_PLAY, // 随机播放
    CIRCLE_PLAY, // 单曲循环
    MAXNUM_PLAY,
};

struct SongInfo
{
    QString title;       // 歌曲标题
    QString artist;      // 艺术家
    QString album;       // 专辑
    QString id;          // 唯一标识符
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    QMap<QString, SongInfo> map_hotList;

    QString requestedMusicId;
    QString requestedLyricId;
    bool IsRequestMusicReceived;
    bool IsRequestLyricReceived;

    // 函数：解析 JSON 数据
    void parseMusicList(const QString &jsonStr,QMap<QString, SongInfo>& songMap,const QString& listName);
    void displayMusicList(QListWidget *listWidget,const QMap<QString, SongInfo>& songMap);
signals:
    void downloadSuccess_music();  // 下载成功信号
    void downloadSuccess_lyric();  // 下载成功信号
    void downloadSuccess_cover();  // 下载成功信号
public slots:
    // 槽函数
    void handlePrevSlot();// 上一首按钮
    void handlePlaySlot();// 播放按钮
    void handleNextSlot();// 下一首按钮
    void handleModeSlot();// 播放模式切换按钮
    // 处理音乐播放位置
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void handlePositionSlot(qint64 position);
    // 处理定时器超时
    void handleTimeoutSlot();
    void handleDoubleClickList();
    // 歌曲播放完毕
    void handlePlayFinish(QMediaPlayer::MediaStatus status);
    void handleStateChanged(QMediaPlayer::State state);
    void handleBufferStatusChanged(int percent);
private:
    // 初始化按钮图标
    void initButtonIcon();
    // 加载指定文件路径
    void loadAppointMusicDir(const QString& filepath);
    // 播放指定的歌曲
    void playAppointMusic();
    // 格式化毫秒成 mm:ss
    QString formatMilliseconds(int milliseconds);
    // 加载歌词
    void loadAppointLyric(const QString& filepath);
    // 解析时间转换成毫秒级别
    int parseTime(const QString& time);
    // 刷新歌词(滚动歌词)
    void RefreshLyric();

    void sendJsonToServer(const QJsonObject &jsonObj);
private:
    Ui::Widget *ui;
    QMediaPlayer* m_player;

    // 播放的状态
    bool m_playingState;
    // 播放模式
    int m_playMode;
    // 音乐路径
    QString m_musicPath;

    // 歌词信息 <key:value> : <时间:歌词>
    QMap<int, QString> m_lyricInfo;
    QMap<int, QString>::iterator lastIter;

    // 定时器
    QTimer* m_timer;


    QTcpSocket socket;
    QByteArray buffer; // 人造缓冲区
    QByteArray dataType; // 数据类型
    size_t expectedSize; // 存储期望的数据包大小

    QMap<QString, SongInfo> map_playList;



};

#endif // WIDGET_H
