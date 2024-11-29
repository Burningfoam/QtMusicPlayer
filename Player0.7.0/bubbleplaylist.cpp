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

void bubblePlayList::handleDoubleClick(QListWidgetItem *item)
{
//    qDebug()<<"双击："<<item->data(Qt::UserRole).toString();
    emit wid->playListDoubleClicked(item);
}
