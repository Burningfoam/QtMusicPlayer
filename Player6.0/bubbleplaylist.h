#ifndef BUBBLEPLAYLIST_H
#define BUBBLEPLAYLIST_H

#include <QWidget>
#include <QToolButton>
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
    // 展示气泡窗口
    void showBubble(QToolButton *button);
    // 监听聚焦事件
    void focusOutEvent(QFocusEvent *event);
private:
    Ui::bubblePlayList *ui;
};

#endif // BUBBLEPLAYLIST_H
