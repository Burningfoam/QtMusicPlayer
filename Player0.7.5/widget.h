#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QString>
#include <QMap>
#include <QTimer>
#include <QPainter>
#include <QListWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QQueue>
#include <QLabel>
#include "bubbleplaylist.h"
#include "loginsignup.h"

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

struct WidgetPrivate;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *event)override;
    // 函数：解析 JSON 数据
    void parseMusicList(const QString &jsonStr,QMap<QString, SongInfo>& songMap,const QString& listName);
    void displayMusicList(QListWidget *listWidget,const QMap<QString, SongInfo>& songMap);
    void displayMusicListForPlaylist(bubblePlayList* list,const QMap<QString, SongInfo>& songMap);
    void showBigCover(QListWidget* list,QLabel* label);

    // 鼠标点击进入歌单
    void mousePressEvent(QMouseEvent* e)override;
public:
    // 临时文件路径
    QString tempPath;

    QMap<QString, SongInfo> map_hotList;

    QString requestedMusicId;
    QString requestedLyricId;
    QString requestedCoverId;
    bool IsRequestMusicReceived;
    bool IsRequestCoverReceived;
    bool IsRequestLyricReceived;
    // 封面下载等待队列
    QQueue<QString> downloadCoverQueue;

//    QString currentMusicId;

signals:
    void downloadSuccess_music();  // 下载成功信号
    void downloadSuccess_lyric();  // 下载成功信号
    void downloadSuccess_cover();  // 下载成功信号
    void playListDoubleClicked(QListWidgetItem *item); // 气泡播放列表双击信号
    void hotlistClicked(); // 点击热门歌单信号
    void newlistClicked(); // 点击新歌歌单信号
    void uplistClicked(); // 点击飙升歌单信号
    void goldlistClicked(); // 点击金曲歌单信号
    void jaylistClicked(); // 点击杰伦歌单信号
    void userLoginSuccess();
public slots:
    // 槽函数
    void handlePrevSlot();// 上一首按钮
    void handlePlaySlot();// 播放按钮
    void handleNextSlot();// 下一首按钮
    void handleModeSlot();// 播放模式切换按钮
    // 处理音乐播放位置
    void handleDurationSlot(qint64 duration);
    void handlePositionSlot(qint64 position);
    // 处理定时器超时
    void handleTimeoutSlot();
    void handleDoubleClickList();
    // 歌曲播放完毕
    void handlePlayFinish(QMediaPlayer::MediaStatus status);
//    void handlePlayList(QListWidgetItem *item);
private:
    // 初始化按钮图标
    void initButtonIcon();
    void initHomeListLabel();
    // 加载指定文件路径
    void loadAppointMusicDir(const QString& filepath);
    // 加载本地播放列表
    void loadLocalPlayList();
    // 播放指定的歌曲
    void playAppointMusic(QListWidgetItem *item = nullptr);
    // 设置指定的歌曲，不播放
    void setAppointMusic(QListWidgetItem *item = nullptr);
    // 格式化毫秒成 mm:ss
    QString formatMilliseconds(int milliseconds);
    // 加载歌词
    void loadAppointLyric(const QString& filepath);
    // 解析时间转换成毫秒级别
    int parseTime(const QString& time);
    // 刷新歌词(滚动歌词)
    void RefreshLyric();
    // 清除歌词界面
    void ClearLyric();
    // 向服务器发送json通用函数
    void sendJsonToServer(const QJsonObject &jsonObj);
    // 左栏的信号与槽连接函数
    void leftBarConnect();
    // 登录栏连接函数
    void loginConnect();
    // 搜索栏连接函数
    void searchBarConnect();
    // 播放栏连接函数
    void playerBarConnect();
    // 音乐播放媒体相关连接函数
    void mediaConnect();
    // 歌单列表、播放列表连接函数
    void musicListWidgetConnect();
    // 首页歌单点击连接函数
    void musicListHomeConnect();
    // 下载当前资源成功连接函数
    void downloadSuccessConnect();
    void serverReceiveConnect();
    void timerConnect();

    QString getFilePathFromDatabase(const QString & musicId, const QString &fileType);
    // 判断歌曲是否被喜欢过
    bool isSongLiked();
    void refreshLikeButton(bool status);
    void loadLikeList();
    void loadMusicList(const QString& userid,const QString& listname);

    void playMusicList(QListWidget* list,const QString& id);
    void setFadeInEffect(QLabel* label);
    void setRoundCornerLabel(const QPixmap &Image,QLabel* label,int radius = 15);
    void loadHomelistCover();

private:
    Ui::Widget *ui;
    WidgetPrivate* p;

    loginSignUp* userProcess; // 用户登录组件
    bubblePlayList* bubble;// 播放列表气泡
    // 音乐路径
    QString m_musicPath;


};

#endif // WIDGET_H
