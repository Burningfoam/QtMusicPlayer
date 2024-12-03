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
#include <QFileDialog>
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
#include "searchmusicrunnable.h"
#include "saveplaystatusrunnable.h"
#include "likestatesyncrunnable.h"
#include "likestateschangerunnable.h"

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
    // 本地音乐目录
    QString localPath;
    QString downloadPath;
    // 加载动画
    QMovie* loadingMovie;
    // 定时器
    QTimer* m_timer;
    QTimer* timer_listCover;
    QTimer* timer_likeStatesRefresh;
    // 当前需要加载图片的列表
    QListWidget* currentFreshList;

    // 歌词信息 <key:value> : <时间:歌词>
    QMap<int, QString> m_lyricInfo;
    QMap<int, QString>::iterator lastIter;

    QTcpSocket socket;
    QByteArray buffer; // 人造缓冲区
    QByteArray dataType; // 数据类型
    size_t expectedSize; // 存储期望的数据包大小
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
    p->timer_likeStatesRefresh = new QTimer(this);
    p->m_playMode = ORDER_PLAY;
    p->expectedSize = 0;
    initTempFolder();
    tempPath = QCoreApplication::applicationDirPath() + "/ClientTemp/";
    p->downloadPath = QCoreApplication::applicationDirPath() + "/myDownloadMusic/";
    p->localPath = p->downloadPath;
    IsRequestMusicReceived = true;
    IsRequestLyricReceived = true;
    IsRequestCoverReceived = true;
    p->loadingMovie = new QMovie(":/img/loading.gif");

    // 初始化按钮图标
    initButtonIcon();
    initHomeListLabel();

    // 信号与槽连接函数
    leftBarConnect();
    loginConnect();
    topBarConnect();
    playerBarConnect();
    mediaConnect();
    downloadSuccessConnect();
    serverReceiveConnect();
    musicListWidgetConnect();
    musicListHomeConnect();
    folderConnect();

    /*设置音量条的范围:*/
    ui->soundBar->setRange(0,100);

    // 清理歌词脏数据
    p->m_lyricInfo.clear();
    p->lastIter = p->m_lyricInfo.end();

    // 定时器
    p->m_timer->setInterval(300);
    p->timer_listCover->setInterval(300);
    p->timer_likeStatesRefresh->setInterval(5000);
    timerConnect();

    // 加载本地保存的json播放列表
    initLocalPlayList();

    // 打开时进入音乐播放界面
    ui->stackedWidget->setCurrentWidget(ui->page_music);
    p->pageHistory.push(0);
    // 打开时播放列表第一首歌
    bubble->setCurrentRow(0);
    playAppointMusic();
    p->isFirstPlayed = false;
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
        loadLocalList();
    });
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,[this](int index)
    {
        switch (index)
        {
            case 0:
                selectLeftButtonStyle(ui->pushButton_page_music);
                break;
            case 1:
                selectLeftButtonStyle(ui->pushButton_page_home);
                break;
            case 5:
                selectLeftButtonStyle(ui->pushButton_page_download);
                break;
            case 6:
                selectLeftButtonStyle(ui->pushButton_page_local);
                break;
            default:
                initLeftButtonStyle();
                break;
        }
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
        ui->label_username->setText(userProcess->user_name);
        ui->label_headimg->setPixmap(userProcess->user_headimg.scaled(ui->label_headimg->width(),ui->label_headimg->height()));
        ui->pushButton_login->hide();
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
        QStringList songIds;  // 用于存储歌曲 ID 顺序

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
            songIds.append(musicId);  // 保存歌曲 ID 顺序
        }
        displayMusicListForPlaylist(bubble,songMap);
        qDebug()<<"上次的歌单加载成功";

        // 获取上次播放的歌曲和播放位置
        query.prepare("SELECT last_played_song_id, last_played_song_duration "
                      "FROM UserInfo WHERE user_id = :userId");
        query.bindValue(":userId", userId);
        qDebug()<<"准备查询上次播放的歌曲和播放位置";

        bubble->setCurrentRow(0);
        int lastSongIdInt = 0;
        int lastPlayedDuration = 0;
        if (query.exec() && query.next())
        {
            qDebug()<<"执行查询上次播放的歌曲和播放位置";
            lastSongIdInt = query.value("last_played_song_id").toInt();
            lastPlayedDuration = query.value("last_played_song_duration").toInt();
            qDebug()<<"上次的歌曲id: "<<lastSongIdInt;
            qDebug()<<"上次的位置: "<<lastPlayedDuration;

            // 如果上次播放的歌曲存在
            if (lastSongIdInt > 0)
            {
                QString lastSongId = QString::asprintf("%010d", lastSongIdInt);
                if (songMap.contains(lastSongId))
                {
                    SongInfo lastSongInfo = songMap[lastSongId];

                    // 找到上次播放的歌曲在 songIds 中的位置
                    int lastSongIndex = songIds.indexOf(lastSongId);
                    if (lastSongIndex != -1)
                    {
                        qDebug()<<"找到该歌曲，在播放列表中的位置："<<lastSongIndex;
                        // 设置该歌曲为当前项
                        bubble->setCurrentRow(lastSongIndex);
                        // 你可以在这里设置播放位置，如果有对应的播放器接口
                        p->m_player->setPosition(lastPlayedDuration);  // 假设你有设置播放位置的函数
                    }
                }
            }
        }
        playAppointMusic();
        p->m_player->setPosition(lastPlayedDuration);  // 设置播放位置
        p->isFirstPlayed = false;
        p->timer_likeStatesRefresh->start();
    });
}

void Widget::topBarConnect()
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
    QAction *iconAction = new QAction(ui->lineEdit_search);
    iconAction->setIcon(QIcon(QPixmap(":/img/search.png").scaled(60, 60)));
    ui->lineEdit_search->addAction(iconAction, QLineEdit::TrailingPosition); // 设置图标位置为后面
    connect(iconAction,&QAction::triggered,[this]()
    {
        ui->lineEdit_search->clearFocus(); // 回车时取消焦点
        loadSearchList(ui->lineEdit_search->text());
        ui->stackedWidget->setCurrentWidget(ui->page_search);
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
        QString userId = userProcess->user_id;
        QString musicId = bubble->currentMusicId();

        if (userId.isEmpty() || musicId.isEmpty())
        {
            QMessageBox::warning(this, "喜欢歌曲失败", "请先登录账号");
            return;
        }

        bool isLiked = ui->toolButton_like->property("isliked").toBool();

        auto *runnable = new LikeStatesChangeRunnable(userId, musicId, !isLiked);
        connect(runnable, &LikeStatesChangeRunnable::operationCompleted, this, [this](bool success, bool newLikeState)
        {
            if (success)
            {
                refreshLikeButton(newLikeState);
            }
        });
        connect(runnable, &LikeStatesChangeRunnable::operationFailed, this, [](const QString &error)
        {
            qDebug() << "操作失败:" << error;
        });

        QThreadPool::globalInstance()->start(runnable);
    });
    connect(ui->toolButton_download,&QToolButton::clicked,[this]()
    {
        QString musicid = bubble->currentMusicId();
        QString musicName = bubble->currentItemText().remove(" ");
        QString sourceFilePath = tempPath + "music\\" + musicid + ".mp3";
        QString sourceLyricPath = tempPath + "music\\" + musicid + ".lrc";
        QString sourceCoverPath = tempPath + "music\\" + musicid + ".png";
        QString destinationFilePath = p->downloadPath + musicName + ".mp3";
        QString destinationLyricPath = p->downloadPath + musicName + ".lrc";
        QString destinationCoverPath = p->downloadPath + musicName + ".png";
        qDebug() << sourceFilePath;
        qDebug()<< destinationFilePath;

        // 检查源文件是否存在
        if (!QFile::exists(sourceFilePath))
        {
            qDebug() << "源文件不存在：" << sourceFilePath;
            return;
        }

        // 检查目标路径
        QFileInfo destFileInfo(destinationFilePath);
        QDir destDir = destFileInfo.absoluteDir();
        if (!destDir.exists())
        {
            if (!destDir.mkpath(destDir.absolutePath()))
            {
                qDebug() << "无法创建目标目录：" << destDir.absolutePath();
                return;
            }
        }

        // 如果目标文件已存在，删除它
        if (QFile::exists(destinationFilePath))
        {
            if (!QFile::remove(destinationFilePath))
            {
                qDebug() << "无法删除目标文件：" << destinationFilePath;
                return;
            }
        }

        if (QFile::copy(sourceFilePath, destinationFilePath))
        {
            qDebug() << "文件拷贝成功：" << destinationFilePath;
            QFile::copy(sourceLyricPath, destinationLyricPath);
            QFile::copy(sourceCoverPath, destinationCoverPath);
            QMessageBox::information(this,"歌曲下载","下载成功");
        }
        else
        {
            qDebug() << "文件拷贝失败" ;
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
    connect(ui->listWidget_search, &QListWidget::itemDoubleClicked,[this](QListWidgetItem* item)
    {
        insertMusicToFront(ui->listWidget_search,item);
    });
    connect(ui->pushButton_listPlay,&QPushButton::clicked,[this]()
    {
        QListWidgetItem* item = ui->listWidget_list->item(0);
        QString musicId = item->data(Qt::UserRole).toString();
        playMusicList(ui->listWidget_list,musicId);
    });
    connect(ui->listWidget_local,&QListWidget::itemDoubleClicked,[this]()
    {
        playLocalMusic();
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
        qDebug() << "准备进入子线程扫描文件";
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
    });
    connect(p->timer_likeStatesRefresh, &QTimer::timeout, [this]()
    {
        QString userId = userProcess->user_id;
        QString musicId = bubble->currentMusicId();

        if (userId.isEmpty() || musicId.isEmpty())
        {
            qDebug() << "用户 ID 或音乐 ID 为空，跳过查询";
            return;
        }

        // 创建查询任务
        auto *runnable = new LikeStateSyncRunnable(userId, musicId);
        connect(runnable, &LikeStateSyncRunnable::checkCompleted, this, [this](bool isLiked)
        {
            // 定义当前喜欢状态的变量
            bool currentLikeStatus = ui->toolButton_like->property("isliked").toBool();
            if (isLiked != currentLikeStatus)
            {
                // 如果状态不同，更新本地状态并刷新 UI
                refreshLikeButton(isLiked);
                qDebug() << "喜欢状态已更新: " << isLiked;
            }
            else
            {
                qDebug() << "喜欢状态未变化";
            }
        });
        connect(runnable, &LikeStateSyncRunnable::checkFailed, this, [](const QString &error)
        {
            qDebug() << "查询喜欢状态失败: " << error;
        });

        // 将任务添加到线程池
        QThreadPool::globalInstance()->start(runnable);
    });
}

void Widget::folderConnect()
{
    connect(ui->toolButton_localfolder,&QToolButton::clicked,[this]()
    {
        // 弹出文件夹选择框
        QString folderPath = QFileDialog::getExistingDirectory(this, "选择文件夹", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        // 检查用户是否选择了有效路径
        if (!folderPath.isEmpty())
        {
            // 保存选择的路径
            p->localPath = folderPath;
            qDebug() << "选择的本地音乐文件夹路径：" << p->localPath;
            loadLocalList();
        }
    });
    // 创建菜单
    QMenu *settingMenu = new QMenu(this);
    QAction *deleteAction = settingMenu->addAction("删除缓存文件");
    QAction *setDownloadAction = settingMenu->addAction("设置下载目录");
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
    connect(setDownloadAction, &QAction::triggered,[this]()
    {
        // 弹出文件夹选择框
        QString folderPath = QFileDialog::getExistingDirectory(this, "选择文件夹", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        // 检查用户是否选择了有效路径
        if (!folderPath.isEmpty())
        {
            // 保存选择的路径
            p->downloadPath = folderPath;
            qDebug() << "选择的下载文件夹路径：" << p->downloadPath;
        }
    });
}

void Widget::initTempFolder()
{
    QString parentPath = QCoreApplication::applicationDirPath();
    QString folderName = "ClientTemp";

    QDir dir(parentPath);
    if (dir.mkdir(folderName))
    {
        qDebug() << "临时文件夹创建成功：" << dir.absoluteFilePath(folderName);
    }
    else
    {
        qDebug() << "临时文件夹创建失败：" << dir.absoluteFilePath(folderName);
    }

    folderName = "myDownloadMusic";
    if (dir.mkdir(folderName))
    {
        qDebug() << "下载文件夹创建成功：" << dir.absoluteFilePath(folderName);
    }
    else
    {
        qDebug() << "下载文件夹创建失败：" << dir.absoluteFilePath(folderName);
    }

    parentPath = QCoreApplication::applicationDirPath() + "/ClientTemp/";
    folderName = "music";
    QDir dirMusic(parentPath);
    if (dirMusic.mkdir(folderName))
    {
        qDebug() << "临时文件夹创建成功：" << dir.absoluteFilePath(folderName);
    }
    else
    {
        qDebug() << "临时文件夹创建失败：" << dir.absoluteFilePath(folderName);
    }
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

        qDebug()<<"路径"<<filePath;
    }

    return filePath.isEmpty() ? "N/A" : filePath;  // 如果查询结果为空，返回 "N/A"
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
}

void Widget::loadMusicList(const QString& userid,const QString& listname)
{
    p->isFirstPlayed = true;
    ui->listWidget_list->clear();
    ui->label_listCover->setMovie(p->loadingMovie);
    if(listname == "user_likelist")
        selectLeftButtonStyle(ui->pushButton_page_love);
    else
        initLeftButtonStyle();

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
            SongItemWidget* itemWidget = new SongItemWidget(ui->listWidget_list);
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
}

void Widget::loadSearchList(const QString &keyword)
{
    p->isFirstPlayed = true;
    ui->listWidget_search->clear();
    ui->label_searchTitle->setText("以下是关于 " + keyword + " 的搜索结果：");

    // 创建 MusicListLoaderRunnable 实例
    auto* searchRunnable = new SearchMusicRunnable(keyword,tempPath);

    // 将 loaderRunnable 提交到线程池
    QThreadPool::globalInstance()->start(searchRunnable);

    // 连接加载完成的信号到主线程槽函数
    connect(searchRunnable, &SearchMusicRunnable::searchCompleted, this, [this](const QList<SongInfo> &results)
    {
        int number = 1;
        for (const SongInfo& song : results)
        {
            // 创建 SongItemWidget 并设置歌曲详情
            SongItemWidget* itemWidget = new SongItemWidget();
            itemWidget->setSongDetails(song.title, song.artist, song.album);
            itemWidget->setItemNumber(number);
            itemWidget->setMusicId(song.id);

            // 创建 QListWidgetItem 并将 SongItemWidget 插入到其中
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget_search);
            item->setSizeHint(QSize(1125, 90));  // 设置固定大小
            item->setData(Qt::UserRole, song.id);

            // 将 SongItemWidget 添加到 QListWidgetItem
            ui->listWidget_search->setItemWidget(item, itemWidget);

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

        p->currentFreshList = ui->listWidget_search;
        p->timer_listCover->start();  // 启动封面加载定时器
    });

}

void Widget::loadLocalList()
{
    p->isFirstPlayed = true;
    ui->listWidget_local->clear();

    QDir dir(p->localPath);

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
            ui->listWidget_local->addItem(info.baseName());
    }
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

void Widget::insertMusicToFront(QListWidget *list,QListWidgetItem* item)
{
    QString musicId = item->data(Qt::UserRole).toString();
    if(bubble->isMusicIdInList(musicId) == true)
    {
        bubble->selectMusicById(musicId);
    }
    else
    {
        // 获取对应歌曲的信息
        SongItemWidget* songWidget = qobject_cast<SongItemWidget*>(list->itemWidget(item));
        QString title = songWidget->getSongName();
        QString artist = songWidget->getArtist();
        int currentRow = bubble->currentRow();
        bubble->insertItem(currentRow + 1,title + " - " +artist);
        bubble->item(currentRow + 1)->setData(Qt::UserRole, musicId);

        bubble->setCurrentRow(currentRow +1);
    }
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
}

void Widget::initLeftButtonStyle()
{
    QString style = R"(
        QPushButton
        {
            background-color: transparent;
            border: 2px solid transparent;
            border-radius: 10px;
            /*padding: 10px 15px;*/
            color: #757c8a;
            font-size: 19px;
            text-align: left; padding-left: 10px;
        }

        QPushButton:hover
        {
            background-color: rgba(169, 169, 169, 0.5);  /* 灰色提示 */
        })";
    ui->pushButton_page_home->setStyleSheet(style);
    ui->pushButton_page_home->setIcon(QIcon(":/img/page_home.png"));
    ui->pushButton_page_home->setIconSize(QSize(34,34));
    ui->pushButton_page_music->setStyleSheet(style);
    ui->pushButton_page_music->setIcon(QIcon(":/img/page_play.png"));
    ui->pushButton_page_music->setIconSize(QSize(34,34));
    ui->pushButton_page_love->setStyleSheet(style);
    ui->pushButton_page_love->setIcon(QIcon(":/img/list_love.png"));
    ui->pushButton_page_love->setIconSize(QSize(30,30));
    ui->pushButton_page_download->setStyleSheet(style);
    ui->pushButton_page_download->setIcon(QIcon(":/img/list_download.png"));
    ui->pushButton_page_download->setIconSize(QSize(34,34));
    ui->pushButton_page_local->setStyleSheet(style);
    ui->pushButton_page_local->setIcon(QIcon(":/img/list_local.png"));
    ui->pushButton_page_local->setIconSize(QSize(34,34));
}

void Widget::selectLeftButtonStyle(QPushButton* button)
{
    QString style = R"(
        QPushButton
        {
            background-color: #FC3D49;
            border: 2px solid transparent;
            border-radius: 10px;
            /*padding: 10px 15px;*/
            color: #ffffff;
            font-size: 19px;
            text-align: left; padding-left: 10px;
        })";
    initLeftButtonStyle();
    button->setStyleSheet(style);
    if(button == ui->pushButton_page_home)
    {
        button->setIcon(QIcon(":/img/page_homeClicked.png"));
        button->setIconSize(QSize(34,34));
    }
    else if(button == ui->pushButton_page_music)
    {
        button->setIcon(QIcon(":/img/page_playClicked.png"));
        button->setIconSize(QSize(34,34));
    }
    else if(button == ui->pushButton_page_love)
    {
        button->setIcon(QIcon(":/img/list_loveClicked.png"));
        button->setIconSize(QSize(30,30));
    }
    else if(button == ui->pushButton_page_download)
    {
        button->setIcon(QIcon(":/img/list_downloadClicked.png"));
        button->setIconSize(QSize(34,34));
    }
    else if(button == ui->pushButton_page_local)
    {
        button->setIcon(QIcon(":/img/list_localClicked.png"));
        button->setIconSize(QSize(34,34));
    }
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
        ui->totalTime->setText("/ " + totalTime); // 显示总时长

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

    ui->pushButton_page_download->hide();
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

void Widget::initLocalPlayList()
{
    QMap<QString, SongInfo> map_playList;
    QFile file(tempPath + "playlist.json"); // 打开 文件
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "无法打开播放列表文件！";
        return;
    }

    QByteArray fileContent = file.readAll(); // 读取文件内容
    file.close();
//    qDebug()<<QString(fileContent);
    parseMusicList(fileContent,map_playList,"playlist");
    displayMusicListForPlaylist(bubble,map_playList);
}

// 播放指定的歌曲
void Widget::playAppointMusic(QListWidgetItem *item)
{
    // 处理音频数据
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
        handlePlaySlot();
        p->isFirstPlayed = true;
        QString musicName = bubble->currentItem()->text();
        // 歌曲名
        ui->songName->setText(musicName);
        ui->toolButton_like->show();
        ui->toolButton_download->show();
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

void Widget::playLocalMusic()
{
    p->isFirstPlayed = true;
    QString musicPath = p->localPath + "/";
    QString musicName = ui->listWidget_local->currentItem()->text();
    // 歌曲名
    ui->songName->setText(musicName);
    // 专辑照片
    QString albumPath = musicPath + musicName + ".jpg";
    QPixmap albumPix(albumPath);
    if(albumPix.isNull())
    {
        albumPath = musicPath + musicName + ".png";
        albumPix = QPixmap(albumPath);
    }
    setRoundCornerLabel(albumPix,ui->albumPic,10);

    ui->PostWidget->SetPixmap(albumPix);
    // 歌曲
    QString absoluteName = musicPath + musicName + ".mp3";
    p->m_player->setMedia(QUrl::fromLocalFile(absoluteName));

    // 歌词
    QString lyricPath = musicPath + musicName + ".lrc";
    // 加载歌词
    loadAppointLyric(lyricPath);

    handlePlaySlot();
    p->m_player->play();
    ui->toolButton_like->hide();
    ui->toolButton_download->hide();
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
    delete p->timer_listCover;
    delete p->timer_likeStatesRefresh;
    delete p->loadingMovie;
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

        // 检查是否点击了 QLineEdit，如果点击，则聚焦
        QPoint lineEditPos = ui->lineEdit_search->mapFromGlobal(e->globalPos());
        if (ui->lineEdit_search->geometry().contains(lineEditPos))
        {
//            ui->lineEdit_search->setFocus(); // 点击 QLineEdit 时聚焦
        }
        else
        {
            ui->lineEdit_search->clearFocus(); // 点击其他区域时取消焦点
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    // 检查是否按下回车键
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if (ui->lineEdit_search->hasFocus())
        {
            ui->lineEdit_search->clearFocus(); // 回车时取消焦点
            loadSearchList(ui->lineEdit_search->text());
            ui->stackedWidget->setCurrentWidget(ui->page_search);
        }
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    if(userProcess->user_id == "")
    {
        qDebug()<<"未登录，本地保存";
        bubble->saveToJson(tempPath + "playlist.json");
        return;
    }

    // 获取当前播放的歌曲 ID 和播放时长
    int currentSongId = bubble->currentMusicId().toInt(); // 自行实现，获取当前播放歌曲的ID
    int currentDuration = p->m_player->position(); // 自行实现，获取播放时长

    // 获取播放列表中的歌曲 ID
    QStringList playlist = bubble->getAllSongIds(); // 自行实现，获取播放列表中所有歌曲的 ID

    // 启动保存线程
    SavePlayStatusRunnable* saveThread = new SavePlayStatusRunnable(userProcess->user_id, currentSongId, currentDuration, playlist, this);
    QThreadPool::globalInstance()->start(saveThread);
}
