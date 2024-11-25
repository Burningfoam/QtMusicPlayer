#include "widget.h"
#include "ui_widget.h"
#include <QIcon>
#include <QSize>
#include <QPushButton>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QMessageBox>
#include <QTime>
#include <QSlider>
#include <QPixmap>
#include <QFile>
#include "loginsignup.h"
#include "bubbleplaylist.h"
#define BUFFER_SIZE 128

struct WidgetPrivate
{
    QImage image; // 背景图
//    loginSignUp loginWidget; // 用户登录组件
    bubblePlayList bubbleWidget;// 播放列表气泡
};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    p(new WidgetPrivate),
    m_player(new QMediaPlayer),
    m_playingState(false),
    m_playMode(ORDER_PLAY),
    m_timer(new QTimer(this))
{
    ui->setupUi(this);

    // 设置背景图
    p->image = QImage(this->width(),this->height(),QImage::Format_RGB32);
    p->image.load(":/img/background_main.png");
    setFixedSize(1500,1068);
    setWindowTitle("网易云音乐");

    // 初始化按钮图标
    initButtonIcon();

    leftBarConnect();
    loginBarConnect();
    playerBarConnect();
    mediaConnect();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    m_lyricInfo.clear();
    lastIter = m_lyricInfo.end();


    // 双击切换歌曲
    connect(ui->musicList,&QListWidget::itemDoubleClicked,this,&Widget::handleDoubleClickList);

    // 定时器
    m_timer->setInterval(300);
    connect(m_timer, &QTimer::timeout, this, &Widget::handleTimeoutSlot);


    // 设置多媒体路径
    m_musicPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\artists\\artist_test\\album_test\\";
    loadAppointMusicDir(m_musicPath);

    // 打开时播放列表第一首歌
    ui->musicList->setCurrentRow(0);
    playAppointMusic();
    handlePlaySlot();
}

void Widget::leftBarConnect()
{
    connect(ui->pushButton_page_home,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_home);
    });
    connect(ui->pushButton_page_music,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_music);
    });
    connect(ui->pushButton_page_love,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_love);
    });
    connect(ui->pushButton_page_download,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_download);
    });
    connect(ui->pushButton_page_local,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_local);
    });
}

void Widget::loginBarConnect()
{
    connect(ui->pushButton_login,&QPushButton::clicked,[this]()
    {
//        ui->stackedWidget->setCurrentIndex(1);
//        p->loginWidget.show();
    });
}

void Widget::playerBarConnect()
{
    connect(ui->prevBtn, &QPushButton::clicked, this, &Widget::handlePrevSlot);
    connect(ui->playerBtn, &QPushButton::clicked, this, &Widget::handlePlaySlot);
    connect(ui->nextBtn, &QPushButton::clicked, this, &Widget::handleNextSlot);
    connect(ui->modeBtn, &QPushButton::clicked, this, &Widget::handleModeSlot);
    connect(ui->toolButton_playlist, &QToolButton::clicked,[this]()
    {
        p->bubbleWidget.showBubble(ui->toolButton_playlist);
    });
}

void Widget::mediaConnect()
{
    // 多媒体相关
    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::handleDurationSlot);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::handlePositionSlot);// 信号传入position形参，并触发槽函数
    // 进度条
    connect(ui->processBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
    connect(ui->soundBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setVolume);
    // 播放完毕
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Widget::handlePlayFinish);
}

void Widget::handleTimeoutSlot()
{
    RefreshLyric();
}

void Widget::handleDoubleClickList()
{
    playAppointMusic();
}

void Widget::handlePlayFinish(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        int currentRow = ui->musicList->currentRow();
        int nextRow = 0;

        if(m_playMode == ORDER_PLAY)
        {
            nextRow = (currentRow + 1) % ui->musicList->count();
        }
        else if(m_playMode == RANDOM_PLAY)
        {
            do
            {
                nextRow = qrand() % ui->musicList->count();
            } while(currentRow == nextRow);
        }
        else if(m_playMode == CIRCLE_PLAY)
        {
            nextRow = currentRow;
        }
        ui->musicList->setCurrentRow(nextRow);
        playAppointMusic();
    }
}

QString Widget::formatMilliseconds(int milliseconds)
{
    // 将毫秒数转换为 QTime 对象（从 00:00:00 开始）
    QTime time = QTime(0, 0, 0).addMSecs(milliseconds);
    // 格式化为 "mm:ss"
    return time.toString("mm:ss");
}

void Widget::handlePositionSlot(qint64 position)
{
    QString currentTime = formatMilliseconds(position);
    currentTime += "/";
    ui->currentTime->setText(currentTime); // 显示当前时长

    ui->processBar->setValue(position); // 设置进度条当前时长
}

// 解析时间转换成毫秒级别
int Widget::parseTime(const QString& time)
{
    int minutes = time.split(":")[0].toInt();
    int seconds = time.split(":")[1].split(".")[0].toInt();
    int millSeconds = time.split(".")[1].toInt();

    int totalMills = minutes *60 *1000 + seconds * 1000 + millSeconds;
    return totalMills;
}

void Widget::RefreshLyric()
{
    int currentPos = m_player->position();

    QMap<int, QString>::iterator currentIter = m_lyricInfo.lowerBound(currentPos); // 获取第一个大于等于 currentPos 的位置
    if(currentPos != currentIter.key() && currentIter != m_lyricInfo.begin())
    {
        currentIter--;
        if(currentIter == lastIter)
            return;
    }

    QStringList lyrics;

    // 向前添加 2 条歌词（当前歌词在 lyricLabel_3，所以向前获取两行）
    QMap<int, QString>::iterator prevIter = currentIter;
    for (int i = 0; i < 2; ++i)
    {
        if (prevIter != m_lyricInfo.begin())
        {
            --prevIter;  // 向前移动迭代器
            lyrics.prepend(prevIter.value());
        }
        else
        {
            lyrics.prepend("");  // 如果已经到达最前面，插入空字符串
        }
    }

    // 当前歌词
    lyrics.append(currentIter.value());
    ui->currentLyric->setText(currentIter.value());

    // 向后添加 4 条歌词
    QMap<int, QString>::iterator nextIter = currentIter;
    for (int i = 0; i < 4; ++i)
    {
        ++nextIter;  // 向后移动迭代器
        if (nextIter != m_lyricInfo.end())
        {
            lyrics.append(nextIter.value());
        }
        else
        {
            lyrics.append("");  // 如果已到达最后，插入空字符串
            break;  // 到达最后，停止添加后续歌词
        }
    }

    // 确保歌词列表大小为 7
    while (lyrics.size() < 7)
    {
        lyrics.append("");  // 补充空歌词，防止UI访问越界
    }

    // 更新 UI
    ui->lyricLabel_1->setText(lyrics[0]);
    ui->lyricLabel_2->setText(lyrics[1]);
    ui->lyricLabel_3->setText(lyrics[2]); // 当前歌词
    ui->lyricLabel_4->setText(lyrics[3]);
    ui->lyricLabel_5->setText(lyrics[4]);
    ui->lyricLabel_6->setText(lyrics[5]);
    ui->lyricLabel_7->setText(lyrics[6]);

    lastIter = currentIter;
}



// 加载歌词
void Widget::loadAppointLyric(const QString& filepath)
{
    // 清除上一首歌词
    m_lyricInfo.clear();

    QFile file(filepath);

    if(file.open(QIODevice::ReadOnly) == false)
    {
        QMessageBox::warning(this, "歌词文件", "文件不存在");
        return;
    }
    char buffer[BUFFER_SIZE] = {0};
    while(file.atEnd()!= true)
    {
        file.readLine(buffer, sizeof(buffer)- 1);

        QString lineData = buffer;

        QStringList listInfo = lineData.split("]");

        int time = parseTime( listInfo[0].split("[")[1] );
        QString lyric = listInfo[1].split("\n")[0];

        // 插入哈希表
        m_lyricInfo[time] = lyric;

        memset(buffer,0,sizeof(buffer));
    }
}

void Widget::handleDurationSlot(qint64 duration)
{
    if(duration != 0)
    {
        QString totalTime = formatMilliseconds(duration);
        ui->totalTime->setText(totalTime); // 显示总时长

        ui->processBar->setRange(0, duration); // 设置进度条总时长
    }
}

// 初始化按钮图标
void Widget::initButtonIcon()
{
    setWindowIcon(QIcon(":/img/netease.png"));

    QIcon prevIcon(":/img/last.png");
    ui->prevBtn->setIcon(prevIcon);
    ui->prevBtn->setIconSize(QSize(ui->prevBtn->width(), ui->prevBtn->height()));
    // 设置样式表
    ui->prevBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    QIcon nextIcon(":/img/next.png");
    ui->nextBtn->setIcon(nextIcon);
    ui->nextBtn->setIconSize(QSize(ui->nextBtn->width(), ui->nextBtn->height()));
    ui->nextBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    QIcon playerIcon(":/img/play.png");
    ui->playerBtn->setIcon(playerIcon);
    ui->playerBtn->setIconSize(QSize(ui->playerBtn->width()-5, ui->playerBtn->height()-5));
    ui->playerBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    QIcon modeIcon(":/img/sequenceCycle.png");
    ui->modeBtn->setIcon(modeIcon);
    ui->modeBtn->setIconSize(QSize(ui->modeBtn->width()-20, ui->modeBtn->height()-20));
    ui->modeBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    QIcon soundIcon(":/img/icon_volume.png");
    ui->soundBtn->setIcon(soundIcon);
    ui->soundBtn->setIconSize(QSize(ui->soundBtn->width(), ui->soundBtn->height()));
    ui->soundBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");
}

void Widget::handlePrevSlot()
{
    int currentRow = ui->musicList->currentRow();
    int prevRow = 0;

    if(m_playMode == ORDER_PLAY || m_playMode == CIRCLE_PLAY)
    {
        prevRow = (currentRow - 1 + ui->musicList->count()) % ui->musicList->count();
    }
    else if(m_playMode == RANDOM_PLAY)
    {
        do
        {
            prevRow = qrand() % ui->musicList->count();
        } while(currentRow == prevRow);
    }
    ui->musicList->setCurrentRow(prevRow);
    playAppointMusic();
}

void Widget::handlePlaySlot()
{
    if(m_player->state() == QMediaPlayer::PlayingState)
    {
        QIcon playerIcon(":/img/play.png");
        ui->playerBtn->setIcon(playerIcon);

        m_player->pause();

        // 定时器停止
        m_timer->stop();
        ui->PostWidget->stop();
    }
    else
    {
        qDebug()<<"播放";

        QIcon suspendIcon(":/img/suspend.png");
        ui->playerBtn->setIcon(suspendIcon);

        m_player->play();

        m_timer->start();
        ui->PostWidget->start();
    }
}

void Widget::loadAppointMusicDir(const QString& filepath)
{
    QDir dir(filepath);

    if(dir.exists() == false)
    {
        QMessageBox::warning(this,"打开文件夹", "文件夹不存在");
        return;
    }

    const QFileInfoList& fileInfos = dir.entryInfoList(QDir::Files);
    for (const QFileInfo& info : fileInfos)
    {
        // if(info.suffix() == "mp3" || info.suffix() == "flac")
        if(info.suffix() == "mp3")
        // 文件名
            ui->musicList->addItem(info.baseName());
    }
}

// 播放指定的歌曲
void Widget::playAppointMusic(const QString& filepath)
{
    // 暂不使用此参数
    Q_UNUSED(filepath);

    QString musicName = ui->musicList->currentItem()->text();
    // 歌曲名
    ui->songName->setText(musicName);
    // 专辑照片
    QString albumPath = m_musicPath + musicName + ".jpg";
    QPixmap albumPix(albumPath);
    if(albumPix.isNull())
    {
        albumPath = m_musicPath + musicName + ".png";
        albumPix = QPixmap(albumPath);
    }
    ui->albumPic->setPixmap(albumPix.scaled(ui->albumPic->width(),ui->albumPic->height()));
    ui->PostWidget->SetPixmap(albumPix);
    // 歌曲
    QString absoluteName = m_musicPath + musicName + ".mp3";
    m_player->setMedia(QUrl::fromLocalFile(absoluteName));

    // 歌词
    QString lyricPath = m_musicPath + musicName + ".lrc";
    // 加载歌词
    loadAppointLyric(lyricPath);

    handlePlaySlot();
    m_player->play();
}

void Widget::handleNextSlot()
{
    int currentRow = ui->musicList->currentRow();
    int nextRow = 0;

    if(m_playMode == ORDER_PLAY | m_playMode == CIRCLE_PLAY)
    {
        nextRow = (currentRow + 1) % ui->musicList->count();
    }
    else if(m_playMode == RANDOM_PLAY)
    {
        do
        {
            nextRow = qrand() % ui->musicList->count();
        } while(currentRow == nextRow);
    }
    ui->musicList->setCurrentRow(nextRow);
    playAppointMusic();
}

// 播放模式切换
void Widget::handleModeSlot()
{
    // 播放模式
    m_playMode = (m_playMode + 1)% MAXNUM_PLAY;

    switch(m_playMode)
    {
        case ORDER_PLAY:
        {
            QIcon modeIcon(":/img/sequenceCycle.png");
            ui->modeBtn->setIcon(modeIcon);
            break;
        }
        case RANDOM_PLAY:
        {
            QIcon modeIcon(":/img/random.png");
            ui->modeBtn->setIcon(modeIcon);
            break;
        }
        case CIRCLE_PLAY:
        {
            QIcon modeIcon(":/img/single.png");
            ui->modeBtn->setIcon(modeIcon);
            break;
        }
    }
}

Widget::~Widget()
{
    delete m_player;
    delete p;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 将背景图绘制到整个窗口
    painter.drawImage(0, 0, p->image);
}
