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
#include <QMenu>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QThreadPool>
#include <QMovie>
#include <QStack>
#include "datahandler.h"
#include "songitemwidget.h"
#include "homelistloadertask.h"
#include "coverloaderrunnable.h"
#include "loadmusiclistrunnable.h"
#define BUFFER_SIZE 128

struct WidgetPrivate
{
    QImage image; // 背景图

    QMediaPlayer* m_player; // 媒体播放器

    // 播放模式
    int m_playMode;
    // 是否为首次启动
    bool isFirstPlayed;
    // 用栈保存历史页面
    QStack<int> pageHistory;
    // 加载动画
    QMovie* loadingMovie;
    // 定时器
    QTimer* m_timer;
    QTimer* timer_listCover;
    // 当前需要加载图片的列表
    QListWidget* currentFreshList;

    // 歌词信息 <key:value> : <时间:歌词>
    QMap<int, QString> m_lyricInfo;
    QMap<int, QString>::iterator lastIter;

    QTcpSocket socket;
    QByteArray buffer; // 人造缓冲区
    QByteArray dataType; // 数据类型
    size_t expectedSize; // 存储期望的数据包大小

    QMap<QString, SongInfo> map_playList;

};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    p(new WidgetPrivate),
    userProcess(new loginSignUp(this)),
    bubble(new bubblePlayList(this))
{
    ui->setupUi(this);

    p->socket.connectToHost("192.168.0.157",8080);
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
    p->timer_listCover = new QTimer(this);
    p->m_playMode = ORDER_PLAY;
    p->expectedSize = 0;
    tempPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\ClientTemp\\";
    map_hotList.clear();
    p->map_playList.clear();
    IsRequestMusicReceived = true;
    IsRequestLyricReceived = true;
    IsRequestCoverReceived = true;
    p->loadingMovie = new QMovie(":/img/loading.gif");


    // 初始化按钮图标
    initButtonIcon();
    initHomeListLabel();

    leftBarConnect();
    loginConnect();
    searchBarConnect();
    playerBarConnect();
    mediaConnect();
    downloadSuccessConnect();
    serverReceiveConnect();
    musicListWidgetConnect();
    musicListHomeConnect();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    p->m_lyricInfo.clear();
    p->lastIter = p->m_lyricInfo.end();

    // 定时器
    p->m_timer->setInterval(300);
    p->timer_listCover->setInterval(300);
    timerConnect();


    // 设置多媒体路径
//    m_musicPath = "D:\\File\\Documents\\QtProjects\\MusicPlayer\\music\\artists\\artist_test\\album_test\\";
//    loadAppointMusicDir(m_musicPath);
    loadLocalPlayList();

    // 打开时进入音乐播放界面
    ui->stackedWidget->setCurrentWidget(ui->page_music);
    p->pageHistory.push(0);
    // 打开时播放列表第一首歌
    bubble->setCurrentRow(0);
    playAppointMusic();
    p->isFirstPlayed = false;
//    handlePlaySlot();
}

void Widget::leftBarConnect()
{
    connect(ui->pushButton_page_home,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_home);
        loadHomelistCover();
    });
    connect(ui->pushButton_page_music,&QPushButton::clicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_music);
    });
    connect(ui->pushButton_page_love,&QPushButton::clicked,[this]()
    {
        if(userProcess->isLogin == false)
        {
            QMessageBox::warning(this,"打开失败","请先登录账号");
            return ;
        }
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        loadLikeList();
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

void Widget::loginConnect()
{
    connect(ui->pushButton_login,&QPushButton::clicked,[this]()
    {
        userProcess->show();
    });
    connect(this,&Widget::userLoginSuccess,[this]()
    {
        bubble->clear();

        QString userId = userProcess->user_id;  // 当前用户的 ID
        qDebug()<<"用户id："<<userId;
        QSqlQuery query(userProcess->db);

        // 获取用户名为 'user_likelist' 的歌单 ID
        query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = :playlist_name");
        query.bindValue(":userId", userId);
        query.bindValue(":playlist_name", "user_playlist");

        if (!query.exec() || !query.next())
        {
            qDebug() << "没有找到该歌单："<<"user_playlist";
            return;
        }

        int playlistId = query.value("playlist_id").toInt();  // 获取歌单 ID

        // 查询 'user_likelist' 歌单中的歌曲
        query.prepare("SELECT S.music_id, S.title, S.artist "
                      "FROM SongInfo S "
                      "JOIN PlaylistSong PS ON S.music_id = PS.music_id "
                      "WHERE PS.playlist_id = :playlistId");
        query.bindValue(":playlistId", playlistId);

        if (!query.exec())
        {
            qDebug() << "加载云端播放列表数据库查询失败" << query.lastError().text();
            return;
        }
        // 定义 QMap 用于存储歌曲信息
        QMap<QString, SongInfo> songMap;

        while (query.next())
        {
            int musicIdInt = query.value("music_id").toInt();
            QString musicId = QString::asprintf("%010d", musicIdInt);

            QString title = query.value("title").toString();
            QString artist = query.value("artist").toString();

            // 创建 SongInfo 结构体并填充数据
            SongInfo songInfo;
            songInfo.title = title;
            songInfo.artist = artist;
            songInfo.id = musicId;

            // 将歌曲信息存入 QMap，以 musicId 为键
            songMap.insert(musicId, songInfo);
        }
        displayMusicListForPlaylist(bubble,songMap);
        bubble->setCurrentRow(0);
        playAppointMusic();
        p->isFirstPlayed = false;
        refreshLikeButton(isSongLiked());
    });
    // 创建菜单
    QMenu *settingMenu = new QMenu(this);
    QAction *deleteAction = settingMenu->addAction("删除缓存文件");
    // 将菜单连接到ToolButton
    ui->toolButton_settings->setMenu(settingMenu);
    ui->toolButton_settings->setPopupMode(QToolButton::InstantPopup);
    connect(deleteAction, &QAction::triggered,[this]()
    {
        QString dirPath = tempPath + "music\\"; // 需要删除文件的目录路径
        QDir dir(dirPath);
        // 检查目录是否存在
        if (!dir.exists())
        {
            qDebug() << "删除目录不存在";
            return;
        }
        // 获取目录中的所有文件
        QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
        for (const QFileInfo &fileInfo : fileList)
        {
            if (QFile::remove(fileInfo.absoluteFilePath()))
            {
                qDebug() << "文件删除成功:" << fileInfo.absoluteFilePath();
            }
            else
            {
                qDebug() << "文件删除失败:" << fileInfo.absoluteFilePath();
            }
        }
        fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
        if (fileList.isEmpty())
        {
            QMessageBox::information(this,"缓存删除","缓存文件已清空");
        }
        else
        {
            QMessageBox::warning(this,"缓存删除","缓存文件清除失败");
        }
    });
}

void Widget::searchBarConnect()
{
    connect(ui->toolButton_back,&QToolButton::clicked,[this]()
    {
        // 如果栈中有历史页面，返回上一页
        if (p->pageHistory.size() > 1)
        {
            // 保证栈中至少有一个页面索引
            p->pageHistory.pop();  // 弹出当前页面
            int prevPageIndex = p->pageHistory.top();  // 获取上一页面的索引
            ui->stackedWidget->setCurrentIndex(prevPageIndex);
        }
    });
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,[this](int index)
    {
        // 如果栈非空，记录上一个页面
        if (!p->pageHistory.isEmpty())
        {
            int prevPageIndex = p->pageHistory.top();  // 获取上一个页面的索引
            if (prevPageIndex != index)
            {
                p->pageHistory.push(index);  // 将当前页面的索引压入栈中
            }
        }
        else
        {
            p->pageHistory.push(index);  // 第一次进入页面，直接压入
        }
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
    connect(ui->toolButton_like, &QToolButton::clicked, [this]()
    {
        if (ui->toolButton_like->property("isliked") == false)
        {
            QString userId = userProcess->user_id;  // 当前用户的 ID
            QString musicId = bubble->currentMusicId();  // 获取当前正在播放的音乐 ID

            if (userId.isEmpty())
            {
                QMessageBox::warning(this,"喜欢歌曲失败","请先登录账号");
                return;
            }

            if (userId.isEmpty() || musicId.isEmpty())
            {
                qDebug() << "喜欢失败, user:" << userId << " 音乐:" << musicId;
                return;
            }

            // 查找当前用户是否已经有名为 'user_likelist' 的歌单
            QSqlQuery query(userProcess->db);
            query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_likelist'");
            query.bindValue(":userId", userId);

            if (!query.exec() || !query.next())
            {
                qDebug() << "没有找到名为 'user_likelist' 的歌单，正在创建...";
                // 如果没有找到，创建一个新的 'user_likelist' 歌单
                query.prepare("INSERT INTO Playlist (user_id, playlist_name) VALUES (:userId, 'user_likelist')");
                query.bindValue(":userId", userId);

                if (!query.exec())
                {
                    qDebug() << "创建 'user_likelist' 歌单失败！" << query.lastError().text();
                    return;
                }

                // 获取新创建的歌单 ID
                int playlistId = query.lastInsertId().toInt();

                // 插入音乐到 PlaylistSong 表
                query.prepare("INSERT INTO PlaylistSong (playlist_id, music_id) VALUES (:playlistId, :musicId)");
                query.bindValue(":playlistId", playlistId);
                query.bindValue(":musicId", musicId);

                if (!query.exec())  // 执行插入操作
                    qDebug() << "喜欢这首歌失败！" << query.lastError().text();
                else
                {
                    qDebug() << "成功喜欢：" << musicId;
                    refreshLikeButton(true);
                }
            }
            else
            {
                // 如果已经有 'user_likelist' 歌单，直接插入歌曲
                int playlistId = query.value("playlist_id").toInt();

                query.prepare("INSERT INTO PlaylistSong (playlist_id, music_id) VALUES (:playlistId, :musicId)");
                query.bindValue(":playlistId", playlistId);
                query.bindValue(":musicId", musicId);

                if (!query.exec())  // 执行插入操作
                    qDebug() << "喜欢这首歌失败！" << query.lastError().text();
                else
                {
                    qDebug() << "成功喜欢：" << musicId;
                    refreshLikeButton(true);
                }
            }
        }
        else
        {
            // 如果已经喜欢过这首歌，进行取消喜欢操作
            QString userId = userProcess->user_id;  // 当前用户的 ID
            QString musicId = bubble->currentMusicId();  // 获取当前正在播放的音乐 ID

            QSqlQuery query(userProcess->db);
            // 查找 'user_likelist' 歌单的 playlist_id
            query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_likelist'");
            query.bindValue(":userId", userId);

            if (!query.exec() || !query.next())
            {
                qDebug() << "没有找到名为 'user_likelist' 的歌单";
                return;
            }

            int playlistId = query.value("playlist_id").toInt();

            // 删除 PlaylistSong 中的歌曲
            query.prepare("DELETE FROM PlaylistSong WHERE playlist_id = :playlistId AND music_id = :musicId");
            query.bindValue(":playlistId", playlistId);
            query.bindValue(":musicId", musicId);

            if (!query.exec())  // 执行删除操作
                qDebug() << "取消喜欢失败！" << query.lastError().text();
            else
            {
                qDebug() << "成功取消喜欢：" << musicId;
                refreshLikeButton(false);
            }
        }
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

void Widget::musicListWidgetConnect()
{
    // 双击切换歌曲
    connect(this,&Widget::playListDoubleClicked,[this](QListWidgetItem *item)
    {
//        qDebug()<<"音乐列表连接："<<item->data(Qt::UserRole).toString();
//        p->CurrentItem = item;
        playAppointMusic(bubble->currentItem());
    });
    connect(ui->listWidget_list, &QListWidget::itemDoubleClicked,[this](QListWidgetItem* item)
    {
        // 获取当前点击歌曲的 musicId
        QString clickedMusicId = item->data(Qt::UserRole).toString();
        playMusicList(ui->listWidget_list,clickedMusicId);
    });
    connect(ui->pushButton_listPlay,&QPushButton::clicked,[this]()
    {
        QListWidgetItem* item = ui->listWidget_list->item(0);
        QString musicId = item->data(Qt::UserRole).toString();
        playMusicList(ui->listWidget_list,musicId);
    });
}

void Widget::musicListHomeConnect()
{
    connect(this,&Widget::hotlistClicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        ui->label_listTitle->setText("热门歌曲榜");
        loadMusicList("0000000004","hotlist");
    });
    connect(this,&Widget::newlistClicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        ui->label_listTitle->setText("新歌榜");
        loadMusicList("0000000004","newlist");
    });
    connect(this,&Widget::uplistClicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        ui->label_listTitle->setText("飙升榜");
        loadMusicList("0000000004","uplist");
    });
    connect(this,&Widget::goldlistClicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        ui->label_listTitle->setText("华语金曲");
        loadMusicList("0000000004","goldlist");
    });
    connect(this,&Widget::jaylistClicked,[this]()
    {
        ui->stackedWidget->setCurrentWidget(ui->page_list);
        ui->label_listTitle->setText("周杰伦精选");
        loadMusicList("0000000004","jaylist");
    });
}

void Widget::downloadSuccessConnect()
{
    connect(this, &Widget::downloadSuccess_music, [this]()
    {
        // 下载成功后的操作
        qDebug()<<"下载成功,开始播放！";
        if(p->isFirstPlayed == true)
            playAppointMusic(bubble->currentItem());
        else
        {
            playAppointMusic(bubble->currentItem());
            p->isFirstPlayed = false;
        }
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
        if(bubble->currentMusicId() == requestedCoverId)
        {
            QString albumPath = tempPath + "music\\" + requestedCoverId + ".png";
            QPixmap albumPix(albumPath);
            setRoundCornerLabel(albumPix,ui->albumPic,10);
            ui->PostWidget->SetPixmap(albumPix);
            if(p->isFirstPlayed == true)
                ui->PostWidget->start();
        }
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

void Widget::timerConnect()
{
    connect(p->m_timer, &QTimer::timeout, this, &Widget::handleTimeoutSlot);
    connect(p->timer_listCover,&QTimer::timeout,[this]()
    {
        qDebug() << "开始扫描！！！！！！！！！！！！！！！！！！！";
        QString coverFolderPath = tempPath + "music\\";

        // 创建一个新的 CoverLoaderRunnable，并将其提交到线程池
        CoverLoaderRunnable* loaderRunnable = new CoverLoaderRunnable(coverFolderPath,p->currentFreshList);

        // 连接信号和槽
        connect(loaderRunnable, &CoverLoaderRunnable::coversDownloadSuccess,this,[this]()
        {
            // 停止定时器，因为所有封面已经加载完毕
            p->timer_listCover->stop();
            showBigCover(p->currentFreshList,ui->label_listCover);
        }, Qt::QueuedConnection);
        connect(loaderRunnable, &CoverLoaderRunnable::coversLoaded, this, [this](const QList<QPixmap>& listCovers)
        {
            // 确保 listCovers 中的封面数量与 currentFreshList 中的项数量一致
            if (listCovers.size() != p->currentFreshList->count())
            {
                qDebug() << "封面数量与歌单项数量不匹配！";
                return;
            }

            // 遍历当前歌单中的所有项，更新对应的封面
            for (int i = 0; i < p->currentFreshList->count(); ++i)
            {
                QListWidgetItem* item = p->currentFreshList->item(i);

                // 获取当前项对应的封面
                QPixmap coverPixmap = listCovers.at(i);  // 获取当前项的封面图

                // 获取该项的 widget
                SongItemWidget* itemWidget = qobject_cast<SongItemWidget*>(p->currentFreshList->itemWidget(item));

                if (itemWidget)
                {
                    // 设置当前项的封面
                    itemWidget->setSongCover(coverPixmap);
                    qDebug() << "更新封面: " << i;
                }
            }
        }, Qt::QueuedConnection);

        // 获取 Qt 默认线程池并提交任务
        QThreadPool::globalInstance()->start(loaderRunnable);


//        qDebug()<<"开始扫描！！！！！！！！！！！！！！！！！！！";
//        QString coverFolderPath = tempPath + "music\\";
//        QDir coverDir(coverFolderPath);

//        if (!coverDir.exists())
//        {
//            qDebug() << "封面文件夹不存在: " << coverFolderPath;
//            return;
//        }

//        bool allCoversExist = true;

//        // 遍历当前歌单中的所有项，检查对应封面是否存在
//        for (int i = 0; i < p->currentFreshList->count(); ++i)
//        {
//            QListWidgetItem *item = p->currentFreshList->item(i);
//            QString musicId = item->data(Qt::UserRole).toString();  // 获取歌曲 ID
//            QString coverFilePath = coverFolderPath + musicId + ".png";  // 封面路径

//            // 如果任意一个封面文件不存在，标记为 false
//            if (!QFile::exists(coverFilePath))
//            {
//                allCoversExist = false;
//                break;
//            }
//        }

//        if (allCoversExist)
//        {
//            qDebug() << "所有封面图片都已下载完毕，开始加载封面";
//            showBigCover(p->currentFreshList,ui->label_listCover);

//            // 加载所有封面图
//            for (int i = 0; i < p->currentFreshList->count(); ++i)
//            {
//                QListWidgetItem *item = p->currentFreshList->item(i);
//                QString musicId = item->data(Qt::UserRole).toString();  // 获取歌曲 ID
//                QString coverFilePath = coverFolderPath + musicId + ".png";  // 封面路径

//                // 如果封面文件存在，更新显示
//                if (QFile::exists(coverFilePath))
//                {
//                    SongItemWidget* itemWidget = qobject_cast<SongItemWidget*>(p->currentFreshList->itemWidget(item));
//                    if (itemWidget)
//                    {
//                        itemWidget->setSongCover(QPixmap(coverFilePath));  // 设置封面图
//                        qDebug() << "加载封面: " << coverFilePath;
//                    }
//                }
//            }
//            // 停止定时器，因为所有封面已经加载完毕
//            p->timer_listCover->stop();
//            p->currentFreshList = nullptr;
//        }
//        else
//        {
//            qDebug() << "等待封面下载完成...";
//        }
    });
}

QString Widget::getFilePathFromDatabase(const QString &musicId, const QString &fileType)
{
    // 使用 SQL 查询对象查询数据
    QSqlQuery query(userProcess->db);

    // 根据文件类型构造查询字段
    QString field;
    if (fileType == "cover")
    {
        field = "coverPath";
    }
    else if (fileType == "lyric")
    {
        field = "lyricsPath";
    }
    else if (fileType == "audio")
    {
        field = "filePath";
    }
    else
    {
        qDebug() << "文件类型错误，无法查询文件地址！";
        return "";
    }

    // 准备查询 SQL
    query.prepare("SELECT " + field + " FROM SongInfo WHERE music_id = :music_id");
    query.bindValue(":music_id", musicId.toInt());

    // 执行查询
    if (!query.exec())
    {
        qDebug() << "Query failed:" << query.lastError();
        return "";
    }

    // 获取查询结果
    QString filePath = "";
    if (query.next())
    {
        filePath = query.value(0).toString();
    }

    return filePath.isEmpty() ? "N/A" : filePath;  // 如果查询结果为空，返回 "N/A"
}

bool Widget::isSongLiked()
{
    QString userId = userProcess->user_id;
    QString musicId = bubble->currentMusicId();

    if (userId.isEmpty() || musicId.isEmpty())
    {
        qDebug() << "用户ID或音乐ID为空，无法判断是否喜欢";
        return false;  // 返回 false，表示无法判断
    }

    QSqlQuery query(userProcess->db);

    // 查询名为 'user_likelist' 的歌单的 playlist_id
    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_likelist'");
    query.bindValue(":userId", userId);

    if (!query.exec() || !query.next())
    {
        qDebug() << "没有找到名为 'user_likelist' 的歌单";
        return false;  // 如果没有找到歌单，则返回 false
    }

    int playlistId = query.value("playlist_id").toInt();

    // 查询 PlaylistSong 表，看是否包含当前音乐ID
    query.prepare("SELECT COUNT(*) FROM PlaylistSong WHERE playlist_id = :playlistId AND music_id = :musicId");
    query.bindValue(":playlistId", playlistId);
    query.bindValue(":musicId", musicId);

    if (!query.exec())  // 执行查询
    {
        qDebug() << "查询失败！" << query.lastError().text();
        return false;  // 查询失败返回 false
    }

    if (query.next())  // 如果查询有结果
    {
        int count = query.value(0).toInt();
        return count > 0;  // 如果返回的计数大于 0，表示用户已经喜欢过该歌曲
    }

    return false;  // 默认返回 false，表示未喜欢过
}

void Widget::refreshLikeButton(bool status)
{
    if(status)
    {
        ui->toolButton_like->setIcon(QIcon(":/img/like.png"));
        ui->toolButton_like->setIconSize(QSize(ui->toolButton_like->width(),ui->toolButton_like->height()));
        ui->toolButton_like->setProperty("isliked",true);
    }
    else
    {
        ui->toolButton_like->setIcon(QIcon(":/img/dislike.png"));
        ui->toolButton_like->setIconSize(QSize(ui->toolButton_like->width(),ui->toolButton_like->height()));
        ui->toolButton_like->setProperty("isliked",false);
    }
}

void Widget::loadLikeList()
{
    QString userId = userProcess->user_id;  // 假设你知道当前用户的 ID
    ui->label_listTitle->setText("我喜欢的音乐");
    loadMusicList(userId,"user_likelist");


//    QSqlQuery query(p->loginWidget.db);

//    // 获取用户名为 'user_likelist' 的歌单 ID
//    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = 'user_likelist'");
//    query.bindValue(":userId", userId);

//    if (!query.exec() || !query.next())
//    {
//        qDebug() << "没有找到名为'user_likelist'的歌单";
//        return;
//    }

//    int playlistId = query.value("playlist_id").toInt();  // 获取歌单 ID

//    // 查询 'user_likelist' 歌单中的歌曲
//    query.prepare("SELECT S.music_id, S.title, S.artist, S.album, S.coverPath "
//                  "FROM SongInfo S "
//                  "JOIN PlaylistSong PS ON S.music_id = PS.music_id "
//                  "WHERE PS.playlist_id = :playlistId");
//    query.bindValue(":playlistId", playlistId);

//    if (!query.exec())
//    {
//        qDebug() << "加载喜欢列表数据库查询失败" << query.lastError().text();
//        return;
//    }

//    int number = 1;
//    while (query.next())
//    {
//        int musicIdInt = query.value("music_id").toInt();
//        QString musicId = QString::asprintf("%010d", musicIdInt);

//        QString title = query.value("title").toString();
//        QString artist = query.value("artist").toString();
//        QString album = query.value("album").toString();
//        QString coverPath = query.value("coverPath").toString();

//        if(!QFile::exists(tempPath + "music\\" + musicId + ".png"))
//        {
//            qDebug() << "歌单列表没有封面，开始请求";
//            QJsonObject jsonObject;
//            jsonObject["type"] = "DOWNLOAD_COVER";
//            jsonObject["downloadPath"] = coverPath;
//            downloadCoverQueue.enqueue(musicId);
//            sendJsonToServer(jsonObject);
//        }

//        qDebug() << "喜欢的歌：" << title;

//        // 创建 SongItemWidget 并设置歌曲详情
//        SongItemWidget* itemWidget = new SongItemWidget();
//        itemWidget->setSongDetails(title, artist, album);
//        itemWidget->setItemNumber(number);
//        itemWidget->setMusicId(musicId);

//        // 创建 QListWidgetItem 并将 SongItemWidget 插入到其中
//        QListWidgetItem* item = new QListWidgetItem(ui->listWidget_like);
//        item->setSizeHint(QSize(1125, 90));  // 设置固定大小
//        item->setData(Qt::UserRole, musicId);

//        // 将 SongItemWidget 添加到 QListWidgetItem
//        ui->listWidget_like->setItemWidget(item, itemWidget);
//        number++;
//    }

//    p->currentFreshList = ui->listWidget_like;
//    p->timer_listCover->start();
}

//void Widget::loadLikeList()
//{
//    // 查询用户喜欢的歌曲
//    QString userId = p->loginWidget.user_id;  // 假设你知道当前用户的 ID
//    QSqlQuery query(p->loginWidget.db);
//    query.prepare("SELECT S.music_id, S.title, S.artist, S.album ,S.coverPath "
//                  "FROM SongInfo S "
//                  "JOIN UserLike U ON S.music_id = U.music_id "
//                  "WHERE U.user_id = :userId");
//    query.bindValue(":userId", userId);

//    if (!query.exec())
//    {
////        QMessageBox::critical(nullptr, "Query Error", query.lastError().text());
//        qDebug()<<"加载喜欢列表数据库查询失败"<<query.lastError().text();
//        return;
//    }
//    int number = 1;
//    while (query.next())
//    {
//        // 获取歌曲信息
////        QString musicId = query.value("music_id").toString();
//        int musicIdInt = query.value("music_id").toInt();  // 获取 music_id 字段，转换为整数
//        QString musicId = QString::asprintf("%010d", musicIdInt);  // 格式化为10位字符串，前导零

//        QString title = query.value("title").toString();
//        QString artist = query.value("artist").toString();
//        QString album = query.value("album").toString();
//        QString coverPath = query.value("coverPath").toString();

////        if(!QFile::exists(tempPath + "music\\" + musicId + ".png") && IsRequestCoverReceived == true)
//        if(!QFile::exists(tempPath + "music\\" + musicId + ".png"))
//        {
//            qDebug() << "歌单列表没有封面，开始请求";
//            // 创建一个 JSON 对象
//            QJsonObject jsonObject;
//            jsonObject["type"] = "DOWNLOAD_COVER";
//            jsonObject["downloadPath"] = coverPath;
//            downloadCoverQueue.enqueue(musicId);
////            requestedCoverId = musicId;
////            qDebug()<<requestedCoverId;
////            IsRequestCoverReceived = false;
//            sendJsonToServer(jsonObject);
//        }

//        qDebug()<<"喜欢的歌："<<title;
//        // 创建 SongItemWidget 并设置歌曲详情
//        SongItemWidget* itemWidget = new SongItemWidget();
//        itemWidget->setSongDetails(title, artist, album);
//        itemWidget->setItemNumber(number);
//        itemWidget->setMusicId(musicId);

//        // 创建 QListWidgetItem 并将 SongItemWidget 插入到其中
//        QListWidgetItem* item = new QListWidgetItem(ui->listWidget_like);
//        item->setSizeHint(QSize(1125, 90));  // 设置固定大小
//        item->setData(Qt::UserRole, musicId);  // 设置 data 为歌曲的 ID
////        item->setSizeHint(itemWidget->sizeHint());  // 设置项的大小

//        // 将 SongItemWidget 添加到 QListWidgetItem
//        ui->listWidget_like->setItemWidget(item, itemWidget);
//        number++;
//    }
//    p->currentFreshList = ui->listWidget_like;
//    p->timer_listCover->start();
//}

void Widget::loadMusicList(const QString& userid,const QString& listname)
{
    p->isFirstPlayed = true;
    ui->listWidget_list->clear();
    ui->label_listCover->setMovie(p->loadingMovie);

    // 创建 MusicListLoaderRunnable 实例
    auto* loaderRunnable = new loadMusicListRunnable(userid, listname,tempPath);

    // 将 loaderRunnable 提交到线程池
    QThreadPool::globalInstance()->start(loaderRunnable);

    // 连接加载完成的信号到主线程槽函数
    connect(loaderRunnable, &loadMusicListRunnable::loadCompleted, this, [this](const QList<SongInfo>& songList)
    {
        int number = 1;
        for (const SongInfo& song : songList)
        {
            // 创建 SongItemWidget 并设置歌曲详情
            SongItemWidget* itemWidget = new SongItemWidget();
            itemWidget->setSongDetails(song.title, song.artist, song.album);
            itemWidget->setItemNumber(number);
            itemWidget->setMusicId(song.id);

            // 创建 QListWidgetItem 并将 SongItemWidget 插入到其中
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_list);
            item->setSizeHint(QSize(1125, 90));  // 设置固定大小
            item->setData(Qt::UserRole, song.id);

            // 将 SongItemWidget 添加到 QListWidgetItem
            ui->listWidget_list->setItemWidget(item, itemWidget);

            // 如果封面不存在，加入下载队列
            if (!song.coverExists)
            {
                QJsonObject jsonObject;
                jsonObject["type"] = "DOWNLOAD_COVER";
                jsonObject["downloadPath"] = song.coverPath;
                downloadCoverQueue.enqueue(song.id);
                sendJsonToServer(jsonObject);
            }
            number++;
        }

        p->currentFreshList = ui->listWidget_list;
        p->timer_listCover->start();  // 启动封面加载定时器
    });

//    QString userId = userid;  // 假设你知道当前用户的 ID
//    if (!userProcess->db.isValid()) {
//        qDebug() << "Database is not valid.";
//    } else {
//        qDebug() << "Database is valid.";
//    }
//    if(userProcess->db.open())
//        qDebug()<<"打开数据库成功!\n";
//    else
//        qDebug()<<"打开数据库失败!\n"<<userProcess->db.lastError();
//    QSqlQuery query(userProcess->db);

//    // 获取用户名为 'user_likelist' 的歌单 ID
//    query.prepare("SELECT playlist_id FROM Playlist WHERE user_id = :userId AND playlist_name = :playlist_name");
//    query.bindValue(":userId", userId);
//    query.bindValue(":playlist_name", listname);

//    if (!query.exec() || !query.next())
//    {
//        qDebug() << "没有找到该歌单："<<listname;
//        return;
//    }

//    int playlistId = query.value("playlist_id").toInt();  // 获取歌单 ID

//    // 查询 'user_likelist' 歌单中的歌曲
//    query.prepare("SELECT S.music_id, S.title, S.artist, S.album, S.coverPath "
//                  "FROM SongInfo S "
//                  "JOIN PlaylistSong PS ON S.music_id = PS.music_id "
//                  "WHERE PS.playlist_id = :playlistId");
//    query.bindValue(":playlistId", playlistId);

//    if (!query.exec())
//    {
//        qDebug() << "加载喜欢列表数据库查询失败" << query.lastError().text();
//        return;
//    }

//    int number = 1;
//    while (query.next())
//    {
//        int musicIdInt = query.value("music_id").toInt();
//        QString musicId = QString::asprintf("%010d", musicIdInt);

//        QString title = query.value("title").toString();
//        QString artist = query.value("artist").toString();
//        QString album = query.value("album").toString();
//        QString coverPath = query.value("coverPath").toString();

//        if(!QFile::exists(tempPath + "music\\" + musicId + ".png"))
//        {
//            qDebug() << "歌单列表没有封面，开始请求";
//            QJsonObject jsonObject;
//            jsonObject["type"] = "DOWNLOAD_COVER";
//            jsonObject["downloadPath"] = coverPath;
//            downloadCoverQueue.enqueue(musicId);
//            sendJsonToServer(jsonObject);
//        }

//        qDebug() << "喜欢的歌：" << title;

//        // 创建 SongItemWidget 并设置歌曲详情
//        SongItemWidget* itemWidget = new SongItemWidget();
//        itemWidget->setSongDetails(title, artist, album);
//        itemWidget->setItemNumber(number);
//        itemWidget->setMusicId(musicId);

//        // 创建 QListWidgetItem 并将 SongItemWidget 插入到其中
//        QListWidgetItem* item = new QListWidgetItem(ui->listWidget_list);
//        item->setSizeHint(QSize(1125, 90));  // 设置固定大小
//        item->setData(Qt::UserRole, musicId);

//        // 将 SongItemWidget 添加到 QListWidgetItem
//        ui->listWidget_list->setItemWidget(item, itemWidget);
//        number++;
//    }

//    p->currentFreshList = ui->listWidget_list;
//    p->timer_listCover->start();
}

void Widget::showBigCover(QListWidget* list,QLabel* label)
{
    // 确保列表非空
    if (list->count() == 0)
    {
        qDebug() << "列表为空，无法显示封面";
        return;
    }

    // 获取第一项
    QListWidgetItem* firstItem = list->item(0);
    QString musicId = firstItem->data(Qt::UserRole).toString();  // 获取歌曲 ID
    QString coverFolderPath = tempPath + "music\\";
    QString coverFilePath = coverFolderPath + musicId + ".png";  // 封面路径

    // 检查封面文件是否存在
    if (QFile::exists(coverFilePath))
    {
        // 如果封面存在，加载到 QLabel 中
        QPixmap coverPixmap(coverFilePath);
        QPixmap image(label->width(),label->height());
        image.fill(Qt::transparent);//设置成透明背景(父窗体的背景)

        QPainter painter(&image);
        // 禁用画笔的边框
        painter.setPen(Qt::NoPen);
        // 开启抗锯齿
        painter.setRenderHint(QPainter::Antialiasing);
        //设置画笔的来源图片
        painter.setBrush(coverPixmap.scaled(label->size()));
        // 绘制一个圆角矩形
        int radius = 15; // 可以根据需要调整圆角的半径
        painter.drawRoundedRect(0, 0, label->width(), label->height(), radius, radius);
        label->setPixmap(image);
        setFadeInEffect(label); // 启用淡入效果
        qDebug() << "显示封面: " << coverFilePath;
    }
    else
    {
        qDebug() << "封面文件不存在: " << coverFilePath;
    }
}

void Widget::playMusicList(QListWidget *list, const QString &id)
{
    // 创建一个 QMap 来存储所有歌曲的信息
    QMap<QString, SongInfo> songMap;
    int clickedRow = 0;
    // 遍历喜欢列表，获取每一首歌曲的信息
    for (int row = 0; row < list->count(); ++row)
    {
        QListWidgetItem* item = list->item(row);
        QString musicId = item->data(Qt::UserRole).toString();

        // 获取对应歌曲的信息
        SongItemWidget* songWidget = qobject_cast<SongItemWidget*>(list->itemWidget(item));
        QString title = songWidget->getSongName();
        QString artist = songWidget->getArtist();

        // 存储歌曲信息到 QMap
        SongInfo songInfo;
        songInfo.id = musicId;
        songInfo.title = title;
        songInfo.artist = artist;

        songMap.insert(musicId, songInfo);
        if(musicId == id)
            clickedRow = row;
    }
    displayMusicListForPlaylist(bubble,songMap);
    bubble->setCurrentRow(clickedRow);
    playAppointMusic();
}

void Widget::setFadeInEffect(QLabel *label)
{
    // 创建一个透明度效果
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(this);
    label->setGraphicsEffect(opacityEffect);

    // 创建动画效果，给透明度设置动画
    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    fadeInAnimation->setDuration(150);  // 动画持续时间：1秒
    fadeInAnimation->setStartValue(0);   // 初始透明度为0
    fadeInAnimation->setEndValue(1);     // 最终透明度为1
    fadeInAnimation->start();            // 启动动画
}

void Widget::setRoundCornerLabel(const QPixmap &Image, QLabel *label,int radius)
{
    QPixmap image(label->width(),label->height());
    image.fill(Qt::transparent);//设置成透明背景(父窗体的背景)

    QPainter painter(&image);
    // 禁用画笔的边框
    painter.setPen(Qt::NoPen);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画笔的来源图片
    painter.setBrush(Image.scaled(label->size()));
    // 绘制一个圆角矩形
//    int radius = 15; // 可以根据需要调整圆角的半径
    painter.drawRoundedRect(0, 0, label->width(), label->height(), radius, radius);
    label->setPixmap(image);
}

void Widget::loadHomelistCover()
{
    // 创建并提交任务到线程池
    HomelistLoaderTask *task = new HomelistLoaderTask;
    connect(task, &HomelistLoaderTask::coversLoaded,this,[this](const QList<QPixmap> &covers)
    {
        // 确保接收到封面列表后，更新UI
        if (covers.size() > 0)
        {
            setRoundCornerLabel(covers[0], ui->label_enter_hotlist);
            setFadeInEffect(ui->label_enter_hotlist);
        }
        if (covers.size() > 1)
        {
            setRoundCornerLabel(covers[1], ui->label_enter_newlist);
            setFadeInEffect(ui->label_enter_newlist);
        }
        if (covers.size() > 2)
        {
            setRoundCornerLabel(covers[2], ui->label_enter_uplist);
            setFadeInEffect(ui->label_enter_uplist);
        }
        if (covers.size() > 3)
        {

            setRoundCornerLabel(covers[3], ui->label_enter_goldlist);
            setFadeInEffect(ui->label_enter_goldlist);
        }
        if (covers.size() > 4)
        {
            setRoundCornerLabel(covers[4], ui->label_enter_jaylist);
            setFadeInEffect(ui->label_enter_jaylist);
        }
    }, Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(task);
//    // 查询多个歌单封面，使用IN语句一次查询
//    QSqlQuery query(userProcess->db);
//    query.prepare("SELECT playlist_name, playlist_cover FROM Playlist WHERE playlist_name IN (:name1, :name2, :name3, :name4, :name5)");
//    query.bindValue(":name1", "goldlist");
//    query.bindValue(":name2", "hotlist");
//    query.bindValue(":name3", "jaylist");
//    query.bindValue(":name4", "newlist");
//    query.bindValue(":name5", "uplist");
//    query.exec();

//    // 循环处理查询结果
//    while (query.next())
//    {
//        QString playlistName = query.value(0).toString();
//        QByteArray imageData = query.value(1).toByteArray();  // 获取longblob数据
//        QPixmap pixmap;

//        // 加载图片数据
//        if (pixmap.loadFromData(imageData))
//        {
//            // 4. 根据playlistName设置相应的QLabel
//            if (playlistName == "goldlist")
//            {
//                setRoundCornerLabel(pixmap,ui->label_enter_goldlist);
//                setFadeInEffect(ui->label_enter_goldlist);
//            }
//            else if (playlistName == "hotlist")
//            {
//                setRoundCornerLabel(pixmap,ui->label_enter_hotlist);
//                setFadeInEffect(ui->label_enter_hotlist);
//            }
//            else if (playlistName == "jaylist")
//            {
//                setRoundCornerLabel(pixmap,ui->label_enter_jaylist);
//                setFadeInEffect(ui->label_enter_jaylist);
//            }
//            else if (playlistName == "newlist")
//            {
//                setRoundCornerLabel(pixmap,ui->label_enter_newlist);
//                setFadeInEffect(ui->label_enter_newlist);
//            }
//            else if (playlistName == "uplist")
//            {
//                setRoundCornerLabel(pixmap,ui->label_enter_uplist);
//                setFadeInEffect(ui->label_enter_uplist);
//            }
//        } else {
//            // 如果图片加载失败，可以进行相应处理，比如设置默认封面等
//            QMessageBox::warning(nullptr, "Image Load Error", "Failed to load image for playlist " + playlistName);
//        }
//    }

}

void Widget::handleTimeoutSlot()
{
    RefreshLyric();
    if(p->isFirstPlayed == false)
    {
        QIcon playerIcon(":/img/play.png");
        ui->playerBtn->setIcon(playerIcon);

        p->m_player->pause();

        // 定时器停止
        p->m_timer->stop();
        ui->PostWidget->stop();
    }
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

    // 向后添加 6 条歌词
    QMap<int, QString>::iterator nextIter = currentIter;
    for (int i = 0; i < 6; ++i)
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

    // 确保歌词列表大小为 9
    while (lyrics.size() < 9)
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
    ui->lyricLabel_8->setText(lyrics[7]);
    ui->lyricLabel_9->setText(lyrics[8]);

    p->lastIter = currentIter;
}

void Widget::ClearLyric()
{
    // 更新 UI
    ui->lyricLabel_1->setText("");
    ui->lyricLabel_2->setText("");
    ui->lyricLabel_3->setText("歌词加载中..."); // 当前歌词
    ui->currentLyric->setText("歌词加载中...");
    ui->lyricLabel_4->setText("");
    ui->lyricLabel_5->setText("");
    ui->lyricLabel_6->setText("");
    ui->lyricLabel_7->setText("");
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

void Widget::initHomeListLabel()
{
    ui->label_enter_hotlist->setMovie(p->loadingMovie);
    ui->label_enter_newlist->setMovie(p->loadingMovie);
    ui->label_enter_uplist->setMovie(p->loadingMovie);
    ui->label_enter_goldlist->setMovie(p->loadingMovie);
    ui->label_enter_jaylist->setMovie(p->loadingMovie);
    p->loadingMovie->start();
}

void Widget::handlePrevSlot()
{
    p->isFirstPlayed = true;
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
    p->isFirstPlayed = true;
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

//void Widget::loadAppointMusicDir(const QString& filepath)
//{
//    QDir dir(filepath);

//    if(dir.exists() == false)
//    {
//        QMessageBox::warning(this,"打开文件夹", "文件夹不存在");
//        return;
//    }

//    const QFileInfoList& fileInfos = dir.entryInfoList(QDir::Files);
//    for (const QFileInfo& info : fileInfos)
//    {
//        // if(info.suffix() == "mp3" || info.suffix() == "flac")
//        if(info.suffix() == "mp3")
//        // 文件名
//            ui->musicList->addItem(info.baseName());
//    }
//}

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
    QString musicid;
    if(item == nullptr)
        musicid = bubble->currentMusicId();
    else
        musicid = item->data(Qt::UserRole).toString();

    if(!QFile::exists(location + musicid + ".mp3") && IsRequestMusicReceived == true)
    {
        qDebug() << "没有这首歌，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_MUSIC";
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"audio");

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
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"lyric");

        requestedLyricId = musicid;
        qDebug()<<requestedLyricId;
        IsRequestLyricReceived = false;

        sendJsonToServer(jsonObject);
    }
//    if(!QFile::exists(location + musicid + ".png") && IsRequestCoverReceived == true)
    if(!QFile::exists(location + musicid + ".png"))
    {
        qDebug() << "没有封面，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_COVER";
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"cover");
        downloadCoverQueue.enqueue(musicid);
        requestedCoverId = musicid;
//        qDebug()<<requestedCoverId;
//        IsRequestCoverReceived = false;

        sendJsonToServer(jsonObject);
    }

    if(IsRequestMusicReceived == true)
    {
        ClearLyric();
        p->m_player->setMedia(QUrl::fromLocalFile(location + musicid + ".mp3"));
        handlePlaySlot();
        p->isFirstPlayed = true;
        QString musicName = bubble->currentItem()->text();
        // 歌曲名
        ui->songName->setText(musicName);
        refreshLikeButton(isSongLiked());
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
        ui->PostWidget->SetPixmap(albumPix);
        setRoundCornerLabel(albumPix,ui->albumPic,10);
    }
}

void Widget::setAppointMusic(QListWidgetItem *item)
{
    p->isFirstPlayed = false;
    QString location = tempPath + "music\\";
    QString musicid;
    if(item == nullptr)
        musicid = bubble->currentMusicId();
    else
        musicid = item->data(Qt::UserRole).toString();

    if(!QFile::exists(location + musicid + ".mp3") && IsRequestMusicReceived == true)
    {
        qDebug() << "没有这首歌，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_MUSIC";
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"audio");

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
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"lyric");

        requestedLyricId = musicid;
        qDebug()<<requestedLyricId;
        IsRequestLyricReceived = false;

        sendJsonToServer(jsonObject);
    }
    if(!QFile::exists(location + musicid + ".png"))
    {
        qDebug() << "没有封面，开始请求";
        // 创建一个 JSON 对象
        QJsonObject jsonObject;
        jsonObject["type"] = "DOWNLOAD_COVER";
        jsonObject["downloadPath"] = getFilePathFromDatabase(musicid,"cover");
        downloadCoverQueue.enqueue(musicid);
        requestedCoverId = musicid;

        sendJsonToServer(jsonObject);
    }

    if(IsRequestMusicReceived == true)
    {
        ClearLyric();
        p->m_player->setMedia(QUrl::fromLocalFile(location + musicid + ".mp3"));

        QString musicName = bubble->currentItem()->text();
        // 歌曲名
        ui->songName->setText(musicName);
        refreshLikeButton(isSongLiked());
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
        ui->PostWidget->SetPixmap(albumPix);
        ui->PostWidget->stop();
        setRoundCornerLabel(albumPix,ui->albumPic,10);
    }
}

void Widget::handleNextSlot()
{
    p->isFirstPlayed = true;
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
    delete userProcess;
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

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()== Qt::LeftButton)
    {
        if (ui->stackedWidget->currentWidget() == ui->page_home)
        {
            // 要把鼠标的坐标变换成label的相对坐标
            QPoint pos = ui->stackedWidget->mapFromGlobal(e->globalPos());
            // 判断鼠标点在了label内
            if(ui->label_enter_hotlist->geometry().contains(pos))
            {
                qDebug()<<"鼠标点击主页热门歌单";
                emit hotlistClicked();
            }
            else if(ui->label_enter_newlist->geometry().contains(pos))
            {
                qDebug()<<"鼠标点击主页新歌歌单";
                emit newlistClicked();
            }
            else if(ui->label_enter_uplist->geometry().contains(pos))
            {
                qDebug()<<"鼠标点击主页飙升歌单";
                emit uplistClicked();
            }
            else if(ui->label_enter_goldlist->geometry().contains(pos))
            {
                qDebug()<<"鼠标点击主页金曲歌单";
                emit goldlistClicked();
            }
            else if(ui->label_enter_jaylist->geometry().contains(pos))
            {
                qDebug()<<"鼠标点击主页杰伦歌单";
                emit jaylistClicked();
            }
        }

        QPoint pos = ui->widget_2->mapFromGlobal(e->globalPos());
        // 判断鼠标点在了label内
        if(ui->albumPic->geometry().contains(pos))
        {
            qDebug()<<"鼠标点击播放栏封面";
            ui->stackedWidget->setCurrentWidget(ui->page_music);
        }
    }
}
