#include "bubblewidget.h"

BubbleWidget::BubbleWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);  // 无边框并且为弹出窗口
    setAttribute(Qt::WA_TranslucentBackground);  // 背景透明

    // 创建QListWidget
    listWidget = new QListWidget(this);
    QStringList songs = {"Song 1", "Song 2", "Song 3"};
    listWidget->addItems(songs);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(listWidget);
    setLayout(layout);

    setFixedSize(200, 150);  // 设置气泡框大小
}

void BubbleWidget::showBubble(QPushButton *button)
{
    // 获取按钮的位置，并计算气泡框显示位置
    QPoint globalPos = button->mapToGlobal(button->rect().topLeft());  // 获取按钮的左下角位置

    // 计算气泡框应该出现的位置，这里让气泡框略微偏移
    QPoint bubblePos = globalPos + QPoint(0, -160);  // 10像素偏移到右侧
      // 5像素的偏移，让气泡框显示在按钮下面
    move(bubblePos);
    show();
}

void BubbleWidget::mousePressEvent(QMouseEvent *event)
{
    // 如果点击在气泡框内，不做处理
    if (rect().contains(event->pos()))
    {
        QWidget::mousePressEvent(event);
    }
    else
    {
        hideBubble();  // 如果点击外部，关闭气泡框
    }
}
