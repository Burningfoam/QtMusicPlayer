#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->playlistButton, &QPushButton::clicked, this, &Widget::toggleBubble);

    // 创建气泡框
    bubbleWidget = new bubblePlayList(this);

    // 设置气泡框初始隐藏
    bubbleWidget->hide();
}

Widget::~Widget()
{
    delete ui;
}

//void Widget::mousePressEvent(QMouseEvent *event)
//{
//    if (bubbleWidget->isVisible() && !bubbleWidget->rect().contains(bubbleWidget->mapFromGlobal(event->globalPos())))
//        {
//            bubbleWidget->hideBubble();
//        }

//        QWidget::mousePressEvent(event);
//}

void Widget::toggleBubble()
{
    if (bubbleWidget->isVisible())
    {
        bubbleWidget->hideBubble();
    }
    else
    {
        bubbleWidget->showBubble(ui->playlistButton);
    }
}
