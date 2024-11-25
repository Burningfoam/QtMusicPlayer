#ifndef BUBBLEPLAYLIST_H
#define BUBBLEPLAYLIST_H

#include <QWidget>
#include <QPushButton>
#include <QFocusEvent>

namespace Ui {
class bubblePlayList;
}

class bubblePlayList : public QWidget
{
    Q_OBJECT

public:
    explicit bubblePlayList(QWidget *parent = nullptr);
    ~bubblePlayList();
    void showBubble(QPushButton *button);
    void hideBubble();

    // 监听鼠标点击事件
//    void mousePressEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event);
private:
    Ui::bubblePlayList *ui;
};

#endif // BUBBLEPLAYLIST_H
