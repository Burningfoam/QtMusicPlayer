#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "bubbleplaylist.h"
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
//    void mousePressEvent(QMouseEvent *event);
private slots:
    void toggleBubble();
private:
    Ui::Widget *ui;

    bubblePlayList *bubbleWidget;
};

#endif // WIDGET_H
