#ifndef BUBBLEWIDGET_H
#define BUBBLEWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

class BubbleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BubbleWidget(QWidget *parent = nullptr);
    void showBubble(QPushButton *button);
    void hideBubble()
    {
        hide();
    }
signals:

public slots:
protected:
    // 监听鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;

private:
    QListWidget *listWidget;
};

#endif // BUBBLEWIDGET_H
