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

#define BUFFER_SIZE 128

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_player(new QMediaPlayer),
    m_playingState(false),
    m_playMode(ORDER_PLAY),
    m_timer(new QTimer(this))
{
    ui->setupUi(this);

    // 初始化按钮图标
    initButtonIcon();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    m_lyricInfo.clear();

    // 信号和槽
    // 按钮
    connect(ui->prevBtn, &QPushButton::clicked, this, &Widget::handlePrevSlot);
    connect(ui->playerBtn, &QPushButton::clicked, this, &Widget::handlePlaySlot);
    connect(ui->nextBtn, &QPushButton::clicked, this, &Widget::handleNextSlot);
    connect(ui->modeBtn, &QPushButton::clicked, this, &Widget::handleModeSlot);
    // 多媒体相关
    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::handleDurationSlot);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::handlePositionSlot);// 信号传入position形参，并触发槽函数
    // 进度条
    connect(ui->processBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
    connect(ui->soundBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setVolume);

    // 定时器
    m_timer->setInterval(300);
    connect(m_timer, &QTimer::timeout, this, &Widget::handleTimeoutSlot);

    // 设置多媒体路径
    m_musicPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\";
    QString musicname = "一念之间.mp3";
    // QString musicname = "小镇姑娘.mp3";
    QString testPath = m_musicPath + musicname;
    m_player->setMedia(QUrl::fromLocalFile(testPath));
//    m_player->setVm_olume(50);

    loadAppointMusicDir(m_musicPath);

    ui->musicList->setCurrentRow(0);
    playAppointMusic();
    connect(ui->musicList,&QListWidget::itemDoubleClicked,this,&Widget::handleDoubleClickList);
}

void Widget::handleTimeoutSlot()
{
    int currentPos = m_player->position();

    for(auto iter = m_lyricInfo.begin(); iter != m_lyricInfo.end(); iter++)
    {
        int prevPos = iter.key();
        int nextPos = (iter + 1).key();

        if(prevPos < currentPos && currentPos <nextPos)
        {
            ui->currentLyric->setText(iter.value());
            break;
        }
    }
}

void Widget::handleDoubleClickList()
{
    playAppointMusic();
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

    QIcon modeIcon(":/img/sequence.png");
    ui->modeBtn->setIcon(modeIcon);
    ui->modeBtn->setIconSize(QSize(ui->modeBtn->width()-20, ui->modeBtn->height()-20));
    ui->modeBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    QIcon soundIcon(":/img/sound.png");
    ui->soundBtn->setIcon(soundIcon);
    ui->soundBtn->setIconSize(QSize(ui->soundBtn->width(), ui->soundBtn->height()));
    ui->soundBtn->setStyleSheet("QPushButton {background-color:rgba(255,255,255,0);}");

    // ui->processBar->setStyleSheet();

}

void Widget::handlePrevSlot()
{
    int currentRow = ui->musicList->currentRow();
    int prevRow = 0;

    if(m_playMode == ORDER_PLAY)
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
    else if(m_playMode == CIRCLE_PLAY)
    {
        prevRow = currentRow;
    }
    ui->musicList->setCurrentRow(prevRow);
    playAppointMusic();
}

void Widget::handlePlaySlot()
{
    // if(m_playingState == false)
    // {
    //     qDebug()<<"播放";
    //     m_playingState = true;
    //     QIcon suspendIcon(":/img/suspend.png");
    //     ui->playerBtn->setIcon(suspendIcon);

    //     m_player->play();
    // }
    // else
    // {
    //     qDebug()<<"暂停";
    //     m_playingState = false;
    //     QIcon playerIcon(":/img/play.png");
    //     ui->playerBtn->setIcon(playerIcon);

    //     // 音乐暂停
    //     m_player->pause();
    // }
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

// 播放模式切换
void Widget::handleModeSlot()
{
    // 播放模式
    m_playMode = (m_playMode + 1)% MAXNUM_PLAY;

    switch(m_playMode)
    {
        case ORDER_PLAY:
        {
            QIcon modeIcon(":/img/sequence.png");
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

    delete ui;
}
