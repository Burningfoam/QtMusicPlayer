#ifndef BUBBLEPLAYLIST_H
#define BUBBLEPLAYLIST_H

#include <QWidget>
#include <QToolButton>
#include <QFocusEvent>
#include <QListWidgetItem>

namespace Ui {
class bubblePlayList;
}
class Widget;
class bubblePlayList : public QWidget
{
    Q_OBJECT

public:
    explicit bubblePlayList(Widget* wid,QWidget *parent = nullptr);
    ~bubblePlayList();
    // 展示气泡窗口
    void showBubble(QToolButton *button);
    // 监听聚焦事件
    void focusOutEvent(QFocusEvent *event);
    void addItem(QListWidgetItem *item);
    QListWidgetItem *currentItem();
    void setCurrentRow(int row);
    int currentRow();
    int count();
    void clear();
public slots:
    void handleDoubleClick(QListWidgetItem *item);
private:
    Ui::bubblePlayList *ui;

    Widget* wid;

};

#endif // BUBBLEPLAYLIST_H
