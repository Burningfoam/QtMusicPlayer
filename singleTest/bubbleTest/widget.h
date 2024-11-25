#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "bubblewidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void toggleBubble();

private:
    Ui::Widget *ui;

    BubbleWidget *bubbleWidget;
};

#endif // WIDGET_H
