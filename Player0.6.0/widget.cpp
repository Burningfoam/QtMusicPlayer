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
#include <QTcpSocket>
#include "loginsignup.h"
#include "datahandler.h"
#define BUFFER_SIZE 128

struct WidgetPrivate
{
    QImage image; // 背景图
//    loginSignUp loginWidget; // 用户登录组件

    QMediaPlayer* m_player; // 媒体播放器
    // 播放模式
    int m_playMode;
//    // 播放的状态
//    bool m_playingState;


    // 定时器
    QTimer* m_timer;

    // 歌词信息 <key:value> : <时间:歌词>
    QMap<int, QString> m_lyricInfo;
    QMap<int, QString>::iterator lastIter;

    QTcpSocket socket;
    QByteArray buffer; // 人造缓冲区
    QByteArray dataType; // 数据类型
    size_t expectedSize; // 存储期望的数据包大小

//    QListWidgetItem *CurrentItem;

    QMap<QString, SongInfo> map_playList;

};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    p(new WidgetPrivate),
    bubble(new bubblePlayList(this))
//    m_playingState(false)
{
    ui->setupUi(this);

    p->socket.connectToHost("192.168.5.12",8080);
    connect(&p->socket,&QTcpSocket::connected,[]()
    {
        qDebug()<<"连接服务器成功!"<<endl;
    });
    // 设置背景图
    p->image = QImage(this->width(),this->height(),QImage::Format_RGB32);
    p->image.load(":/img/background_main.png");
    setFixedSize(1500,1068);
    setWindowTitle("网易云音乐");
    p->m_player = new QMediaPlayer;
    p->m_timer = new QTimer(this);
    p->m_playMode = ORDER_PLAY;
    p->expectedSize = 0;
    tempPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\ClientTemp\\";
    map_hotList.clear();
    p->map_playList.clear();
    IsRequestMusicReceived = true;
    IsRequestLyricReceived = true;
    IsRequestCoverReceived = true;


    // 初始化按钮图标
    initButtonIcon();

    leftBarConnect();
    loginBarConnect();
    playerBarConnect();
    mediaConnect();
    downloadSuccessConnect();
    serverReceiveConnect();
    musicListConnect();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    p->m_lyricInfo.clear();
    p->lastIter = p->m_lyricInfo.end();


    // 双击切换歌曲
    connect(ui->musicList,&QListWidget::itemDoubleClicked,this,&Widget::handleDoubleClickList);

    // 定时器
    p->m_timer->setInterval(300);
    connect(p->m_timer, &QTimer::timeout, this, &Widget::handleTimeoutSlot);


    // 设置多媒体路径
    m_musicPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\artists\\artist_test\\album_test\\";
    loadAppointMusicDir(m_musicPath);
    loadLocalPlayList();

    // 打开时播放列表第一首歌
    bubble->setCurrentRow(0);
    playAppointMusic(bubble->currentItem());
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
        bubble->showBubble(ui->toolButton_playlist);
    });
}

void Widget::mediaConnect()
{
    // 多媒体相关
    connect(p->m_player, &QMediaPlayer::durationChanged, this, &Widget::handleDurationSlot);
    connect(p->m_player, &QMediaPlayer::positionChanged, this, &Widget::handlePositionSlot);// 信号传入position形参，并触发槽函数
    // 进度条
    connect(ui->processBar, &QSlider::sliderMoved, p->m_player, &QMediaPlayer::setPosition);
    connect(ui->soundBar, &QSlider::sliderMoved, p->m_player, &QMediaPlayer::setVolume);
    // 播放完毕
    connect(p->m_player, &QMediaPlayer::mediaStatusChanged, this, &Widget::handlePlayFinish);
}

void Widget::musicListConnect()
{
    // 双击切换歌曲
    connect(ui->musicList,&QListWidget::itemDoubleClicked,this,&Widget::handleDoubleClickList);
    connect(this,&Widget::playListDoubleClicked,[this](QListWidgetItem *item)
    {
//        qDebug()<<"音乐列表连接："<<item->data(Qt::UserRole).toString();
//        p->CurrentItem = item;
        playAppointMusic(bubble->currentItem());
    });
}

void Widget::downloadSuccessConnect()
{
    connect(this, &Widget::downloadSuccess_music, [this]()
    {
        // 下载成功后的操作
        qDebug()<<"下载成功,开始播放！";
        playAppointMusic(bubble->currentItem());
    });
    connect(this, &Widget::downloadSuccess_lyric, [this]()
    {
        // 下载成功后的操作
        QString lyricPath = tempPath + "music\\" + requestedLyricId + ".lrc";
        qDebug()<<"下载成功,加载歌词！";
        // 加载歌词
        loadAppointLyric(lyricPath);
    });
    connect(this, &Widget::downloadSuccess_cover, [this]()
    {
        qDebug()<<"下载成功,加载封面！";
        QString albumPath = tempPath + "music\\" + requestedCoverId + ".png";
        QPixmap albumPix(albumPath);
        ui->albumPic->setPixmap(albumPix.scaled(ui->albumPic->width(),ui->albumPic->height()));
        ui->PostWidget->SetPixmap(albumPix);
    });
}

void Widget::serverReceiveConnect()
{
    connect(&p->socket, &QTcpSocket::readyRead, [this]()
    {
        auto Content = p->socket.readAll();  // 读取套接字缓冲区的数据
        p->buffer.append(Content);           // 追加到自定义缓冲区

        // 解析缓冲区的数据包
        while (p->buffer.size() > sizeof(size_t) + 5)
        {
            if (p->expectedSize == 0)
            {
                // 提取包头，获取数据包大小
                memcpy(&p->expectedSize, p->buffer.data(), sizeof(size_t));
            }

            // 如果缓冲区中的数据不足以构成完整包，退出循环
            if (p->buffer.size() < p->expectedSize + sizeof(size_t) + 5) {
                break;
            }

            // 提取包头（数据类型）
            auto type = p->buffer.mid(sizeof(size_t), 5); // 类型长度为5字节（例如："audio" 或 "json "）
            // 提取完整数据包内容
            auto data = p->buffer.mid(sizeof(size_t) + 5, p->expectedSize);
            qDebug()<<"数据下载成功，类型："<<type;
            // 使用工厂方法创建对应的处理策略
            auto handler = DataHandlerFactory::createHandler(type);
            if (handler)
            {
                handler->handleData(data,this);  // 执行数据处理
                delete handler;
            }

            // 移除已处理的数据包
            p->buffer.remove(0, p->expectedSize + sizeof(size_t) + 5);

            // 重置期望大小
            p->expectedSize = 0;
            p->dataType.clear();
        }
    });
}

void Widget::handleTimeoutSlot()
{
    RefreshLyric();
}

void Widget::handleDoubleClickList()
{
//    playAppointMusic(p->CurrentItem);
}

void Widget::handlePlayFinish(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
    {
        int currentRow = bubble->currentRow();
        int nextRow = 0;

        if(p->m_playMode == ORDER_PLAY)
        {
            nextRow = (currentRow + 1) % bubble->count();
        }
        else if(p->m_playMode == RANDOM_PLAY)
        {
            do
            {
                nextRow = qrand() % bubble->count();
            } while(currentRow == nextRow);
        }
        else if(p->m_playMode == CIRCLE_PLAY)
        {
            nextRow = currentRow;
        }
        bubble->setCurrentRow(nextRow);
        playAppointMusic(bubble->currentItem());
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
    if(p->m_lyricInfo.isEmpty())
            return;
    int currentPos = p->m_player->position();

    QMap<int, QString>::iterator currentIter = p->m_lyricInfo.lowerBound(currentPos); // 获取第一个大于等于 currentPos 的位置
    if(currentPos != currentIter.key() && currentIter != p->m_lyricInfo.begin())
    {
        currentIter--;
        if(currentIter == p->lastIter)
            return;
    }

    QStringList lyrics;

    // 向前添加 2 条歌词（当前歌词在 lyricLabel_3，所以向前获取两行）
    QMap<int, QString>::iterator prevIter = currentIter;
    for (int i = 0; i < 2; ++i)
    {
        if (prevIter != p->m_lyricInfo.begin())
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
        if (nextIter != p->m_lyricInfo.end())
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

    p->lastIter = currentIter;
}

void Widget::sendJsonToServer(const QJsonObject &jsonObj)
{
    // 将 JSON 对象转换为 JSON 文档
    QJsonDocument jsonDocument(jsonObj);
    QByteArray json = jsonDocument.toJson();

    size_t fileSize = json.size(); // 获取文件大小
    auto Type = QString("json ").toUtf8();

    // 发送包头（文件大小）
    p->socket.write((const char*)&fileSize, sizeof(size_t));
    p->socket.write(Type);
    // 发送文件内容
    p->socket.write(json);
}

// 加载歌词
void Widget::loadAppointLyric(const QString& filepath)
{
    // 清除上一首歌词
    p->m_lyricInfo.clear();

    QFile file(filepath);

    if(file.open(QIODevice::ReadOnly) == false)
    {
//        QMessageBox::warning(this, "歌词文件", "文件不存在");
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
        p->m_lyricInfo[time] = lyric;

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
    int currentRow = bubble->currentRow();
    int prevRow = 0;

    if(p->m_playMode == ORDER_PLAY || p->m_playMode == CIRCLE_PLAY)
    {
        prevRow = (currentRow - 1 + bubble->count()) % bubble->count();
    }
    else if(p->m_playMode == RANDOM_PLAY)
    {
        do
        {
            prevRow = qrand() % bubble->count();
        } while(currentRow == prevRow);
    }
    bubble->setCurrentRow(prevRow);
    playAppointMusic(bubble->currentItem());
}

void Widget::handlePlaySlot()
{
    if(p->m_player->state() == QMediaPlayer::PlayingState)
    {
        QIcon playerIcon(":/img/play.png");
        ui->playerBtn->setIcon(playerIcon);

        p->m_player->pause();

        // 定时器停止
        p->m_timer->stop();
        ui->PostWidget->stop();
    }
    else
    {
        qDebug()<<"播放";

        QIcon suspendIcon(":/img/suspend.png");
        ui->playerBtn->setIcon(suspendIcon);

        p->m_player->play();

        p->m_timer->start();
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

void Widget::loadLocalPlayList()
{
    QFile file(tempPath + "playlist.json"); // 打开 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "无法打开播放列表文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();
//    qDebug()<<QString(fileContent);
    parseMusicList(fileContent,p->map_playList,"playlist");
    displayMusicListForPlaylist(bubble,p->map_playList);
}

// 播放指定的歌曲
void Widget::playAppointMusic(QListWidgetItem *item)
{
    // 处理音频数据
//    QString location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
//    QString musicid = ui->musicList->currentItem()->data(Qt::UserRole).toString();
    QString location = tempPath + "music\\";
    QString musicid = item->data(Qt::UserRole).toString();

    if(!QFile::exists(location + musicid + ".mp3") && IsRequestMusicReceived == true)
    {
        qDebug() << "没有这首歌，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_MUSIC";
        jsonObject["musicid"] = musicid;

        requestedMusicId = musicid;
        IsRequestMusicReceived = false;

        sendJsonToServer(jsonObject);
    }
    if(!QFile::exists(location + musicid + ".lrc") && IsRequestLyricReceived == true)
    {
        qDebug() << "没有歌词，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_LYRIC";
        jsonObject["musicid"] = musicid;

        requestedLyricId = musicid;
        qDebug()<<requestedLyricId;
        IsRequestLyricReceived = false;

        sendJsonToServer(jsonObject);
    }
    if(!QFile::exists(location + musicid + ".png") && IsRequestCoverReceived == true)
    {
        qDebug() << "没有封面，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_COVER";
        jsonObject["musicid"] = musicid;

        requestedCoverId = musicid;
        qDebug()<<requestedCoverId;
        IsRequestCoverReceived = false;

        sendJsonToServer(jsonObject);
    }

    if(IsRequestMusicReceived == true)
    {
        p->m_player->setMedia(QUrl::fromLocalFile(location + musicid + ".mp3"));
        handlePlaySlot();
        p->m_player->play();
        QString musicName = bubble->currentItem()->text();
        // 歌曲名
        ui->songName->setText(musicName);
    }
    if(IsRequestLyricReceived == true)
    {
        QString lyricPath = location + musicid + ".lrc";
        // 加载歌词
        loadAppointLyric(lyricPath);
    }
    if(IsRequestCoverReceived == true)
    {
        QString albumPath = location + musicid + ".png";
        QPixmap albumPix(albumPath);
        ui->albumPic->setPixmap(albumPix.scaled(ui->albumPic->width(),ui->albumPic->height()));
        ui->PostWidget->SetPixmap(albumPix);
    }
}

void Widget::handleNextSlot()
{
//    int currentRow = ui->musicList->currentRow();
    int currentRow = bubble->currentRow();
    int nextRow = 0;

    if(p->m_playMode == ORDER_PLAY | p->m_playMode == CIRCLE_PLAY)
    {
        nextRow = (currentRow + 1) % bubble->count();
    }
    else if(p->m_playMode == RANDOM_PLAY)
    {
        do
        {
            nextRow = qrand() % bubble->count();
        } while(currentRow == nextRow);
    }
//    ui->musicList->setCurrentRow(nextRow);
    bubble->setCurrentRow(nextRow);
    playAppointMusic(bubble->currentItem());
}

// 播放模式切换
void Widget::handleModeSlot()
{
    // 播放模式
    p->m_playMode = (p->m_playMode + 1)% MAXNUM_PLAY;

    switch(p->m_playMode)
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
    delete p->m_player;
    delete p->m_timer;
    delete p;
    delete bubble;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // 将背景图绘制到整个窗口
    painter.drawImage(0, 0, p->image);
}

void Widget::parseMusicList(const QString &jsonStr, QMap<QString, SongInfo> &songMap, const QString &listName)
{
    qDebug()<<"开始解析json歌单";
//    qDebug()<<jsonStr;
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject jsonObj = doc.object();
    QJsonObject musicList = jsonObj["musiclist"].toObject();
    QJsonArray hotlist = musicList[listName].toArray();

    // 解析 hotlist 数组中的每个歌曲
    for (const QJsonValue &value : hotlist)
    {
        QJsonObject songObj = value.toObject();

        SongInfo song;
        song.id = songObj["id"].toString();
        song.title = songObj["title"].toString();
        song.artist = songObj["artist"].toString();
        song.album = songObj["album"].toString();

        // 将歌曲信息插入到 QMap 中
        songMap.insert(song.id, song);
        qDebug()<<song.id<<"  "<<song.title;
    }
}

void Widget::displayMusicList(QListWidget *listWidget, const QMap<QString, SongInfo> &songMap)
{
    qDebug()<<"开始载入列表";
    listWidget->clear();  // 清空现有内容

    // 遍历 QMap，添加每首歌的名称和歌手到 QListWidget 中
    for (auto it = songMap.begin(); it != songMap.end(); ++it)
    {
        const SongInfo &song = it.value();

        // 创建 QListWidgetItem，并设置 text 和 data
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(song.title + " - " + song.artist);  // 设置显示内容为 歌名 - 歌手
        item->setData(Qt::UserRole, song.id);  // 设置 data 为歌曲的 ID

        // 将 item 添加到 listWidget
        listWidget->addItem(item);
    }
}

void Widget::displayMusicListForPlaylist(bubblePlayList* list, const QMap<QString, SongInfo> &songMap)
{
    qDebug()<<"开始载入列表";
    list->clear();  // 清空现有内容

    // 遍历 QMap，添加每首歌的名称和歌手到 QListWidget 中
    for (auto it = songMap.begin(); it != songMap.end(); ++it)
    {
        const SongInfo &song = it.value();

        // 创建 QListWidgetItem，并设置 text 和 data
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(song.title + " - " + song.artist);  // 设置显示内容为 歌名 - 歌手
        item->setData(Qt::UserRole, song.id);  // 设置 data 为歌曲的 ID

        // 将 item 添加到 listWidget
        list->addItem(item);
    }
}
