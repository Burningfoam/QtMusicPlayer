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
#include <QPushButton>
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

    QString coverPath;   // 封面图片路径
    bool coverExists;
};
// 添加 Q_DECLARE_METATYPE
Q_DECLARE_METATYPE(SongInfo) // 声明为元类型，方便跨线程使用

struct WidgetPrivate;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 函数：解析 JSON 数据
    void parseMusicList(const QString &jsonStr,QMap<QString, SongInfo>& songMap,const QString& listName);
    void displayMusicList(QListWidget *listWidget,const QMap<QString, SongInfo>& songMap);

    // 重写事件
    void paintEvent(QPaintEvent *event)override;
    void mousePressEvent(QMouseEvent* e)override;
    void keyPressEvent(QKeyEvent *event)override;
    void closeEvent(QCloseEvent *event)override;
public:
    // 临时文件路径
    QString tempPath;

    QString requestedMusicId;
    QString requestedLyricId;
    QString requestedCoverId;
    bool IsRequestMusicReceived;
    bool IsRequestCoverReceived;
    bool IsRequestLyricReceived;
    // 封面下载等待队列
    QQueue<QString> downloadCoverQueue;

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
    void userLoginSuccess();// 用户登录成功信号
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
    // 歌曲播放完毕
    void handlePlayFinish(QMediaPlayer::MediaStatus status);
private:
    // 左栏的信号与槽连接函数
    void leftBarConnect();
    // 登录连接函数
    void loginConnect();
    // 搜索栏连接函数
    void topBarConnect();
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
    // 服务器数据解释处理函数
    void serverReceiveConnect();
    // 定时器连接函数
    void timerConnect();
    // 文件夹按钮连接函数
    void folderConnect();

    // 初始化缓存文件夹
    void initTempFolder();
    // 初始化按钮图标
    void initButtonIcon();
    void initHomeListLabel();
    // 加载保存在本地的播放列表文件
    void initLocalPlayList();
    // 播放指定的歌曲
    void playAppointMusic(QListWidgetItem *item = nullptr);
    // 播放本地歌曲
    void playLocalMusic();
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

    // 从数据库获取文件服务器的存储路径
    QString getFilePathFromDatabase(const QString & musicId, const QString &fileType);
    // 刷新歌曲喜欢按钮状态
    void refreshLikeButton(bool status);
    // 加载音乐列表
    void loadLikeList();
    void loadMusicList(const QString& userid,const QString& listname);
    void loadSearchList(const QString &keyword);
    void loadLocalList();
    // 播放整个歌单
    void playMusicList(QListWidget* list,const QString& id);
    // 播放歌单列表中的单个歌曲(搜索页面使用)
    void insertMusicToFront(QListWidget *list,QListWidgetItem* item);
    // 从Map读取音乐并加入播放列表
    void displayMusicListForPlaylist(bubblePlayList* list,const QMap<QString, SongInfo>& songMap);
    // 展示歌单页面的封面大图
    void showBigCover(QListWidget* list,QLabel* label);
    // 设置QLabel特殊效果
    void setFadeInEffect(QLabel* label);
    void setRoundCornerLabel(const QPixmap &Image,QLabel* label,int radius = 15);
    // 加载主页歌单大图
    void loadHomelistCover();
    // 左栏按钮样式处理函数
    void initLeftButtonStyle();
    void selectLeftButtonStyle(QPushButton* button);

private:
    Ui::Widget *ui;
    WidgetPrivate* p;

    loginSignUp* userProcess; // 用户登录组件
    bubblePlayList* bubble;// 播放列表气泡
};

#endif // WIDGET_H
