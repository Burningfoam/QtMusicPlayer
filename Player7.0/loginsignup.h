#ifndef LOGINSIGNUP_H
#define LOGINSIGNUP_H

#include <QWidget>
#include <QMouseEvent>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class loginSignUp;
}

class Widget;
struct loginWidgetPrivate;
class loginSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit loginSignUp(Widget* wid,QWidget *parent = nullptr);
    ~loginSignUp();
    // 鼠标点击更换头像
    void mousePressEvent(QMouseEvent* e);

public:
    QSqlDatabase db;
    QString user_name;
    QString user_id;
    bool isLogin;
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
