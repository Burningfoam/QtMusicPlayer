#ifndef LOGINSIGNUP_H
#define LOGINSIGNUP_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class loginSignUp;
}

struct WidgetPrivate;
class loginSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit loginSignUp(QWidget *parent = nullptr);
    ~loginSignUp();
    // 鼠标点击更换头像
    void mousePressEvent(QMouseEvent* e);
public slots:
    void handleRegisterSlot();
    void handleLoginSlot();
private:
    Ui::loginSignUp *ui;
    WidgetPrivate* p;
};

#endif // LOGINSIGNUP_H
