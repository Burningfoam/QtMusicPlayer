#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QString>
#include <QMap>
#include <QTimer>

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

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

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
private:
    // 初始化按钮图标
    void initButtonIcon();
    // 加载指定文件路径
    void loadAppointMusicDir(const QString& filepath);
    // 播放指定的歌曲
    void playAppointMusic(const QString& filepath = "");
    // 格式化毫秒成 mm:ss
    QString formatMilliseconds(int milliseconds);
    // 加载歌词
    void loadAppointLyric(const QString& filepath);
    // 解析时间转换成毫秒级别
    int parseTime(const QString& time);
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

    // 定时器
    QTimer* m_timer;

};

#endif // WIDGET_H
