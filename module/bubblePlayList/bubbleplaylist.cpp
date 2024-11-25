#include "bubbleplaylist.h"
#include "ui_bubbleplaylist.h"

bubblePlayList::bubblePlayList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bubblePlayList)
{
    ui->setupUi(this);

    QStringList songs = {"Song 1", "Song 2", "Song 3"};
    ui->listWidget->addItems(songs);

//        setFixedSize(200, 150);  // 设置气泡框大小

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);  // 设置为弹出框
    setFocusPolicy(Qt::StrongFocus);  // 确保可以捕获焦点
}

bubblePlayList::~bubblePlayList()
{
    delete ui;
}

void bubblePlayList::showBubble(QPushButton *button)
{
    // 获取按钮的位置，并计算气泡框显示位置
    QPoint globalPos = button->mapToGlobal(button->rect().topLeft());  // 获取按钮的左下角位置

    // 计算气泡框应该出现的位置，这里让气泡框略微偏移
    move(globalPos + QPoint(0, -height()));
    show();
}

void bubblePlayList::hideBubble()
{
    hide();
}

// 捕获点击外部区域的事件
void bubblePlayList::focusOutEvent(QFocusEvent *event)
{
    hideBubble();
    QWidget::focusOutEvent(event);
}

//void bubblePlayList::mousePressEvent(QMouseEvent *event)
//{
//    // 如果点击在气泡框内，不做处理
//    if (rect().contains(event->pos()))
//    {
//        QWidget::mousePressEvent(event);
//    }
//    else
//    {
//        hideBubble();  // 如果点击外部，关闭气泡框
//    }
//}
