#include "bubbleplaylist.h"
#include "ui_bubbleplaylist.h"
#include "widget.h"

bubblePlayList::bubblePlayList(Widget* wid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bubblePlayList),
    wid(wid)
{
    ui->setupUi(this);

    QStringList songs = {"Song 1", "Song 2", "Song 3"}; // 默认值
    ui->listWidget->addItems(songs);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);  // 设置为弹出框
    setFocusPolicy(Qt::StrongFocus);  // 确保可以捕获焦点

//    ui->listWidget->setCurrentRow(0);

    connect(ui->listWidget,&QListWidget::itemDoubleClicked,this,&bubblePlayList::handleDoubleClick);
}

bubblePlayList::~bubblePlayList()
{
    delete ui;
}

void bubblePlayList::showBubble(QToolButton *button)
{
    // 获取按钮的位置，并计算气泡框显示位置
    QPoint globalPos = button->mapToGlobal(button->rect().topLeft());  // 获取按钮的左下角位置

    // 计算气泡框应该出现的位置，这里让气泡框略微偏移
    move(globalPos + QPoint(-50, -height()));
    show();
}

// 捕获点击外部区域的事件
void bubblePlayList::focusOutEvent(QFocusEvent *event)
{
    hide();
    QWidget::focusOutEvent(event);
}

void bubblePlayList::addItem(QListWidgetItem *item)
{
    ui->listWidget->addItem(item);
}

QListWidgetItem *bubblePlayList::currentItem()
{
    return ui->listWidget->currentItem();
}

void bubblePlayList::setCurrentRow(int row)
{
    ui->listWidget->setCurrentRow(row);
}

int bubblePlayList::currentRow()
{
    return ui->listWidget->currentRow();
}

int bubblePlayList::count()
{
    return ui->listWidget->count();
}

void bubblePlayList::clear()
{
    ui->listWidget->clear();
}

QString bubblePlayList::currentMusicId()
{
    return ui->listWidget->currentItem()->data(Qt::UserRole).toString();
}

QString bubblePlayList::currentItemText()
{
    return ui->listWidget->currentItem()->text();
}

void bubblePlayList::insertItem(int row,const QString& songNameAndArtist)
{
    // 检查 row 是否有效
    if (row < 0 || row > ui->listWidget->count())
    {
        qWarning() << "Invalid row index!";
        return;
    }

    // 使用 QListWidget::insertItem 在指定行插入新的 item
    ui->listWidget->insertItem(row, songNameAndArtist);
}

QListWidgetItem *bubblePlayList::item(int row)
{
    ui->listWidget->item(row);
}

void bubblePlayList::handleDoubleClick(QListWidgetItem *item)
{
//    qDebug()<<"双击："<<item->data(Qt::UserRole).toString();
    emit wid->playListDoubleClicked(item);
}

QStringList bubblePlayList::getAllSongIds()
{
    QStringList songIds;

    // 遍历 QListWidget 中的所有项
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);

        // 获取每个项的 Qt::UserRole 数据，并将其存入 songIds 列表
        QString songId = item->data(Qt::UserRole).toString();
        songIds.append(songId);
    }

    return songIds;
}

bool bubblePlayList::isMusicIdInList(const QString &musicId)
{
    // 遍历 QListWidget 的所有项
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == musicId)
        {
            // 如果找到匹配的音乐 ID，返回 true
            return true;
        }
    }
    // 如果没有找到，返回 false
    return false;
}

bool bubblePlayList::selectMusicById(const QString &musicId)
{
    // 遍历 QListWidget 的所有项
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if (item->data(Qt::UserRole).toString() == musicId)
        {
            // 找到匹配的音乐 ID，将其设为当前选中项
            ui->listWidget->setCurrentItem(item);
            return true; // 表示成功找到并选择了音乐 ID
        }
    }
    // 如果没有找到匹配的音乐 ID，返回 false
    return false;
}

void bubblePlayList::saveToJson(const QString &filePath)
{
    QJsonArray playlistArray;

    // 遍历 QListWidget 的所有项
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        QString text = item->text();

        // 分割歌曲名和歌手名
        QStringList parts = text.split(" - ");
        if (parts.size() != 2)
        {
            qWarning() << "Invalid format for song:" << text;
            continue;
        }

        QString title = parts[0].trimmed();
        QString artist = parts[1].trimmed();
        QString id = item->data(Qt::UserRole).toString();

        QJsonObject songObject;
        songObject["title"] = title;  // 歌曲名
        songObject["artist"] = artist;  // 歌手
        songObject["id"] = id;  // ID 存储在 Qt::UserRole

        playlistArray.append(songObject);
    }

    // 构建 JSON 对象
    QJsonObject musicListObject;
    musicListObject["playlist"] = playlistArray;

    QJsonObject rootObject;
    rootObject["musiclist"] = musicListObject;

    // 创建 JSON 文档
    QJsonDocument doc(rootObject);

    // 写入文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning() << "Failed to open file for writing:" << filePath;
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));  // 格式化输出
    file.close();

    qDebug() << "Playlist saved to" << filePath;
}
