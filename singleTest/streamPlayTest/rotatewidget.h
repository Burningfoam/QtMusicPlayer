#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class RotateWidget;
}
QT_END_NAMESPACE

struct RotateWidgetPrivate;
class RotateWidget : public QWidget
{
    Q_OBJECT

public:
    RotateWidget(QWidget *parent = nullptr);
    ~RotateWidget();

    void SetPixmap(const QPixmap& mp);

    void stop();
    void start();

    void paintEvent(QPaintEvent* e)override;
private:
    Ui::RotateWidget *ui;

    RotateWidgetPrivate* p;
};

#endif // ROTATEWIDGET_H
