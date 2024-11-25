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
#include <QBuffer>
#include <QMediaMetaData>

#include "datahandler.h"

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

    expectedSize = 0;
    socket.connectToHost("192.168.0.157",8080);
    connect(&socket,&QTcpSocket::connected,[]()
    {
        qDebug()<<"连接服务器成功!"<<endl;
    });
    // 连接信号和槽
    connect(this, &Widget::downloadSuccess_music, [this]()
    {
        // 下载成功后的操作
        qDebug()<<"进入槽函数";
        playAppointMusic();
    });
    connect(this, &Widget::downloadSuccess_lyric, [this]()
    {
        // 下载成功后的操作
        QString lyricPath = m_musicPath + requestedLyricId + ".lrc";
        qDebug()<<lyricPath;
        // 加载歌词
        loadAppointLyric(lyricPath);
    });
//    connect(ui->pushButton_StreamTest,&QPushButton::clicked,[this]()
//    {
//        auto Content = QString("aaa").toUtf8();
//        size_t size = Content.size();
//        QString type = "json";
//        socket.write((const char*)&size,sizeof (size_t));// 先发包头
//        socket.write(Content);// 写数据给服务器
//    });
//    connect(ui->pushButton_StreamTest2,&QPushButton::clicked,[this]()
//    {
//        auto Content = QString("bbb").toUtf8();
//        size_t size = Content.size();
//        socket.write((const char*)&size,sizeof (size_t));// 先发包头
//        socket.write(Content);// 写数据给服务器
//    });
    connect(&socket, &QTcpSocket::readyRead, [this]()
    {
        auto Content = socket.readAll();  // 读取套接字缓冲区的数据
        buffer.append(Content);           // 追加到自定义缓冲区

        // 解析缓冲区的数据包
        while (buffer.size() > sizeof(size_t) + 5)
        {
            if (expectedSize == 0)
            {
                // 提取包头，获取数据包大小
                memcpy(&expectedSize, buffer.data(), sizeof(size_t));
            }

            // 如果缓冲区中的数据不足以构成完整包，退出循环
            if (buffer.size() < expectedSize + sizeof(size_t) + 5) {
                break;
            }

            // 提取包头（数据类型）
            auto type = buffer.mid(sizeof(size_t), 5); // 类型长度为5字节（例如："audio" 或 "json "）
            // 提取完整数据包内容
            auto data = buffer.mid(sizeof(size_t) + 5, expectedSize);

            // 使用工厂方法创建对应的处理策略
            auto handler = DataHandlerFactory::createHandler(type);
            if (handler)
            {
                handler->handleData(data,this);  // 执行数据处理
                delete handler;
            }

//            // 根据数据类型处理数据
//            if (type == QByteArray("json ") )
//            {
//                // 处理JSON数据
//                qDebug() << "Received JSON data: " << QString::fromUtf8(data);
//                QString jsonStr = R"({
//                    "musiclist": {
//                        "hotlist": [
//                            {
//                                "album": "自定义",
//                                "artist": "许嵩",
//                                "id": "431352237",
//                                "title": "有何不可"
//                            },
//                            {
//                                "album": "逆光",
//                                "artist": "孙燕姿",
//                                "id": "2561447689",
//                                "title": "我怀念的"
//                            },
//                          {
//                              "album": "自定义",
//                              "artist": "许嵩",

//                              "id": "2775921610",

//                              "title": "清明雨上"
//                          }
//                        ]
//                    }
//                })";
//                parseMusicList(jsonStr);
//                // 显示到 QListWidget（假设已有一个 QListWidget 指针 listWidget）
//                displayMusicList(ui->musicList);
//            }
//            else if (type == "audio")
//            {
//                // 处理音频数据

//                QFile file("D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\2775921610.mp3");
//                if (file.open(QIODevice::WriteOnly))
//                {
//                    file.write(data);
//                    file.close();
//                    qDebug() << "文件保存成功！";
//                } else
//                {
//                    qDebug() << "无法保存文件！";
//                }

//                m_player->setMedia(QUrl::fromLocalFile("D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\2775921610.mp3"));
//                m_player->play();
//            }
//            else {
//                qDebug() << "未知数据类型: " << QString(type);
//            }

//            QFile file("D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\1.mp3");
//            if (file.open(QIODevice::WriteOnly)) {
//                file.write(data);
//                file.close();
//                qDebug() << "文件保存成功！";
//            } else {
//                qDebug() << "无法保存文件！";
//            }

//            m_player->setMedia(QUrl::fromLocalFile("D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\1.mp3"));
//            m_player->play();

            // 移除已处理的数据包
            buffer.remove(0, expectedSize + sizeof(size_t) + 5);

            // 重置期望大小
            expectedSize = 0;
            dataType.clear();
        }
    });

    connect(m_player, &QMediaPlayer::bufferStatusChanged, this, &Widget::handleBufferStatusChanged);

    map_hotList.clear();
    map_playList.clear();
    IsRequestMusicReceived = true;
    IsRequestLyricReceived = true;



    // 初始化按钮图标
    initButtonIcon();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    m_lyricInfo.clear();
    lastIter = m_lyricInfo.end();

    // 信号和槽：
    // 按钮
    connect(ui->prevBtn, &QPushButton::clicked, this, &Widget::handlePrevSlot);
    connect(ui->playerBtn, &QPushButton::clicked, this, &Widget::handlePlaySlot);
    connect(ui->nextBtn, &QPushButton::clicked, this, &Widget::handleNextSlot);
    connect(ui->modeBtn, &QPushButton::clicked, this, &Widget::handleModeSlot);
    // 多媒体相关
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Widget::handleMediaStatusChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::handlePositionSlot);// 信号传入position形参，并触发槽函数
    // 进度条
    connect(ui->processBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setPosition);
    connect(ui->soundBar, &QSlider::sliderMoved, m_player, &QMediaPlayer::setVolume);
    // 播放完毕
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Widget::handlePlayFinish);
    // 双击切换歌曲
    connect(ui->musicList,&QListWidget::itemDoubleClicked,this,&Widget::handleDoubleClickList);

    connect(m_player, &QMediaPlayer::stateChanged, this, &Widget::handleStateChanged);

    // 定时器
    m_timer->setInterval(300);
    connect(m_timer, &QTimer::timeout, this, &Widget::handleTimeoutSlot);

    // 设置多媒体路径
    m_musicPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
    loadAppointMusicDir(m_musicPath);

//    // 打开时播放列表第一首歌
//    ui->musicList->setCurrentRow(0);

//    playAppointMusic();
//    handlePlaySlot();
//    StreamTest();

//    connect(ui->pushButton_StreamTest, &QPushButton::clicked, this, &Widget::StreamTest);
}

void Widget::handleBufferStatusChanged(int percent) {
    if (percent == 100) {
        qDebug()<<"buffer done";
        // 缓冲完成，准备播放
        m_player->play();
    }
}


void Widget::handleStateChanged(QMediaPlayer::State state)
{
//    qDebug()<<state;
//    if (state == QMediaPlayer::PlayingState)
//    {
//        qint64 duration = m_player->duration();
//        qDebug() << "PlayingState - Duration:" << duration;

//        if (duration > 0)
//        {
//            QString totalTime = formatMilliseconds(duration);
//            ui->totalTime->setText(totalTime);
//            ui->processBar->setRange(0, duration);
//        }
//    }
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
    if(m_lyricInfo.isEmpty())
        return;
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

void Widget::parseMusicList(const QString &jsonStr,QMap<QString, SongInfo>& songMap,const QString& listName)
{
    qDebug()<<"开始解析json歌单";
    qDebug()<<jsonStr;
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

void Widget::displayMusicList(QListWidget *listWidget,const QMap<QString, SongInfo>& songMap)
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

void Widget::sendJsonToServer(const QJsonObject &jsonObj)
{
    // 将 JSON 对象转换为 JSON 文档
    QJsonDocument jsonDocument(jsonObj);
    QByteArray json = jsonDocument.toJson();

    size_t fileSize = json.size(); // 获取文件大小
    auto Type = QString("json ").toUtf8();

    // 发送包头（文件大小）
    socket.write((const char*)&fileSize, sizeof(size_t));
    socket.write(Type);
    // 发送文件内容
    socket.write(json);
}

// 加载歌词
void Widget::loadAppointLyric(const QString& filepath)
{
    // 清除上一首歌词
    m_lyricInfo.clear();

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
//        qDebug()<<lyric;
        // 插入哈希表
        m_lyricInfo[time] = lyric;

        memset(buffer,0,sizeof(buffer));
    }
}

void Widget::handleMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "Media Status: " << m_player->mediaStatus();
    if (status == QMediaPlayer::BufferedMedia)
    {
//        qDebug()<<"load success!";
//        qint64 duration = m_player->duration();
        qint64 duration = m_player->metaData(QMediaMetaData::Duration).toInt();
        qDebug()<<"duration："<<duration;
        QString totalTime = formatMilliseconds(duration);
        ui->totalTime->setText(totalTime);
        ui->processBar->setRange(0, duration);
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

    QIcon modeIcon(":/img/sequenceCycle.png");
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

    QFile file("D:\\File\\Documents\\QtProjects\\MusicPlayer\\ClientTemp\\playlist.json"); // 打开 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "无法打开文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();
    qDebug()<<QString(fileContent);
    parseMusicList(fileContent,map_playList,"playlist");
    displayMusicList(ui->musicList,map_playList);

//    if(dir.exists() == false)
//    {
//        QMessageBox::warning(this,"打开文件夹", "文件夹不存在");
//        return;
//    }

//    const QFileInfoList& fileInfos = dir.entryInfoList(QDir::Files);
//    for (const QFileInfo& info : fileInfos)
//    {
//        if(info.suffix() == "mp3")
//        // 文件名
//            ui->musicList->addItem(info.baseName());
//    }
}

// 播放指定的歌曲
void Widget::playAppointMusic()
{
    // 处理音频数据
    QString location = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\singleTest\\streamPlayTest\\temp\\";
    QString musicid = ui->musicList->currentItem()->data(Qt::UserRole).toString();

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
        qDebug() << "没有这首歌，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_LYRIC";
        jsonObject["musicid"] = musicid;

        requestedLyricId = musicid;
        qDebug()<<requestedLyricId;
        IsRequestLyricReceived = false;

        sendJsonToServer(jsonObject);
    }
//    QFile file(locat + downName);
//    if (file.open(QIODevice::WriteOnly))
//    {
//        file.write(data);
//        file.close();
//        qDebug() << "文件保存成功！";
//    } else
//    {
//        qDebug() << "无法保存文件！";
//    }
    if(IsRequestMusicReceived == true)
    {
        m_player->setMedia(QUrl::fromLocalFile(location + musicid + ".mp3"));
        handlePlaySlot();
        m_player->play();
    }
    if(IsRequestLyricReceived == true)
    {
        QString lyricPath = location + musicid + ".lrc";
//        qDebug()<<lyricPath;
        // 加载歌词
        loadAppointLyric(lyricPath);
    }

//    // 暂不使用此参数
//    Q_UNUSED(filepath);

//    QString musicName = ui->musicList->currentItem()->text();
//    // 歌曲名
//    ui->songName->setText(musicName);
//    // 专辑照片
//    QString albumPath = m_musicPath + musicName + ".jpg";
//    QPixmap albumPix(albumPath);
//    if(albumPix.isNull())
//    {
//        albumPath = m_musicPath + musicName + ".png";
//        albumPix = QPixmap(albumPath);
//    }
//    ui->albumPic->setPixmap(albumPix.scaled(ui->albumPic->width(),ui->albumPic->height()));
//    ui->PostWidget->SetPixmap(albumPix);
//    // 歌曲
//    QString absoluteName = m_musicPath + musicName + ".mp3";
//    m_player->setMedia(QUrl::fromLocalFile(absoluteName));

//    // 歌词
//    QString lyricPath = m_musicPath + musicName + ".lrc";
//    // 加载歌词
//    loadAppointLyric(lyricPath);

//    handlePlaySlot();
//    m_player->play();
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

    delete ui;
}
