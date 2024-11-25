#ifndef LOGINSIGNUP_H
#define LOGINSIGNUP_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class loginSignUp;
}

struct loginWidgetPrivate;
class loginSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit loginSignUp(QWidget *parent = nullptr);
    ~loginSignUp();
    // 鼠标点击更换头像
    void mousePressEvent(QMouseEvent* e);
public slots:
//    void handleRegisterSlot();
//    void handleLoginSlot();
private:
    void RegisterButtonConnect();
    void LoginButtonConnect();
    void setHeadIcon(const QString &filePath);
    QString generateSalt();
    QPair<QString,QString> hashPasswordWithSalt(const QString &password);
    bool IsPasswdSame(const QString &name,const QString &passwd);
private:
    Ui::loginSignUp *ui;
    loginWidgetPrivate* p;
};

#endif // LOGINSIGNUP_H
