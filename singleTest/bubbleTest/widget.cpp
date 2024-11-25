#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPushButton *playlistButton = new QPushButton("播放列表", this);
    connect(playlistButton, &QPushButton::clicked, this, &Widget::toggleBubble);

    // 设置按钮位置
    playlistButton->move(50, 50);

    // 创建气泡框
    bubbleWidget = new BubbleWidget(this);

//    setFixedSize(400, 300);  // 主窗口大小
}

Widget::~Widget()
{
    delete ui;
}

void Widget::toggleBubble()
{
    if (bubbleWidget->isVisible())
    {
        bubbleWidget->hideBubble();
    }
    else
    {
        bubbleWidget->showBubble(qobject_cast<QPushButton*>(sender()));
    }
}
