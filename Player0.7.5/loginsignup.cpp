#include "loginsignup.h"
#include "ui_loginsignup.h"
#include <QIcon>
#include <QDebug>
#include <QPixmap>
#include <QFileDialog>
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QTimer>
#include "widget.h"

struct loginWidgetPrivate
{
    Widget* w;
};

loginSignUp::loginSignUp(Widget* wid,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginSignUp),
    p(new loginWidgetPrivate)
{
    ui->setupUi(this);
    // 数据库
    db = QSqlDatabase::addDatabase("QMYSQL","mainConnection"); // 根据字符串获取数据库驱动
//    db.setHostName("192.168.109.128");
    db.setHostName("121.40.108.31");
    db.setUserName("root");
    db.setPassword("1");
    db.setPort(3306);
    db.setDatabaseName("musicDB");
    if(db.open())
        qDebug()<<"打开数据库成功!\n";
    else
        qDebug()<<"打开数据库失败!\n"<<db.lastError();
    p->w = wid;
    isLogin = false;
    RegisterButtonConnect();
    LoginButtonConnect();

    setFixedSize(480, 720);

    // 修改程序的标题
    setWindowTitle("Login");

    // 设置程序的图标
    QIcon icon(":/picture/headimg.jpeg");
    setWindowIcon(icon);

    // 设置默认头像
    setHeadIcon(":/img/netease.png");

    ui->lineEdit_UserName->setPlaceholderText("请输入账号");
    ui->lineEdit_Passwd->setPlaceholderText("请输入密码");
}

void loginSignUp::RegisterButtonConnect()
{
    connect(ui->pushButton_Register,&QPushButton::clicked,[this]()
    {
        auto name = ui->lineEdit_UserName->text();
        auto passwd = ui->lineEdit_Passwd->text();

        if (name.isEmpty() || passwd.isEmpty())
        {
            QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
            return;
        }

        QPair<QString,QString> saltedPasswd = hashPasswordWithSalt(passwd);

        // 把图片对象变成二进制数据
        // QImage -> QByteArray
        auto image = ui->label_Head->pixmap()->toImage();// 将label里存储的图片取出
        QByteArray imageData;
        QBuffer buffer(&imageData);// QT缓冲区对象
        buffer.open(QIODevice::WriteOnly);// 以写的形式打开缓冲区，输入数据
        image.save(&buffer,"PNG");

        if(db.open())
            qDebug()<<"打开数据库成功!\n";
        else
            qDebug()<<"打开数据库失败!\n"<<db.lastError();
        // 二进制数据不能直接放入字符串
        QSqlQuery query(db);// 数据库语句执行对象
        query.prepare("insert into UserInfo values(:name,:passwd,:salt,:image);"); // :变量 拼接sql语句时，不直接把值放进去，而是稍后以变量赋值形式替换变量
        // 变量绑定的形式
        query.bindValue(":name",name);
        query.bindValue(":passwd",saltedPasswd.first);
        query.bindValue(":salt",saltedPasswd.second);
        query.bindValue(":image",imageData); // 可以绑定二进制数据
        if(!query.exec())// 执行sql语句
        {
            QMessageBox::warning(this,"提示",query.lastError().text());
        }
        else
        {
            QMessageBox::information(this,"提示","注册成功！");
        }
    });
}

void loginSignUp::LoginButtonConnect()
{
    connect(ui->pushButton_Login,&QPushButton::clicked,[this]()
    {
        auto name = ui->lineEdit_UserName->text();
        auto passwd = ui->lineEdit_Passwd->text();

        if (name.isEmpty() || passwd.isEmpty())
        {
            QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
            return;
        }

        if(IsPasswdSame(name,passwd) == true)
        {
//            QMessageBox::information(this, "提示", "登录成功！");
            user_name = name; // 保存用户名至成员变量
            isLogin = true;

            ui->pushButton_Login->setText("正在登录中...");

            QSqlQuery query(db);// 数据库语句执行对象
            query.prepare("SELECT user_id, image FROM UserInfo WHERE user_name = :name;");
            query.bindValue(":name", name);

            if (!query.exec()) // 执行查询
            {
                QMessageBox::warning(this, "提示", query.lastError().text());
                return;
            }

            if (query.next()) // 如果有结果，表示用户名和密码匹配
            {
                // 获取并保存 user_id
                user_id = query.value("user_id").toString(); // 将user_id存入成员变量
                emit p->w->userLoginSuccess();
                // value参数是列名
                auto ImageData = query.value("image").toByteArray();//取出数据 转成字节数组
                QPixmap mp;
                mp.loadFromData(ImageData);
                ui->label_Head->setPixmap(mp);
            }
            // 设置延迟 2 秒后关闭窗口
            QTimer::singleShot(2000, this, [this]()
            {
                this->close(); // 关闭窗口
            });
        }
        else
        {
            QMessageBox::warning(this, "提示", "用户名或密码错误！");
        }
    });
}

loginSignUp::~loginSignUp()
{
    db.close();
    delete ui;
    delete p;
}

void loginSignUp::mousePressEvent(QMouseEvent *e)
{
    if(e->button()== Qt::LeftButton)
    {
        // 鼠标的坐标落在label区域内
        // 要把鼠标的坐标变换成label的相对坐标
        QPoint pos = ui->label_Head->mapFromParent(e->pos());

        // 判断鼠标点在了label内
        if(ui->label_Head->rect().contains(pos))
        {
            qDebug()<<"鼠标点击在Label内!\n";

            QString path = QFileDialog::getOpenFileName(this,"获取头像",R"(D:\File\Documents\QtProjects\MusicPlayer\module\loginSignUp\picture)");
            setHeadIcon(path);
        }
    }
}

void loginSignUp::setHeadIcon(const QString &filePath)
{
    QPixmap mp(filePath);
    QPixmap image(ui->label_Head->width(),ui->label_Head->height());
    image.fill(Qt::transparent);//设置成透明背景(父窗体的背景)

    QPainter painter(&image);
    // 禁用画笔的边框
    painter.setPen(Qt::NoPen);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画笔的来源图片
    painter.setBrush(mp.scaled(ui->label_Head->size()));
    //画出一个圆形图片
    painter.drawEllipse(0,0,ui->label_Head->width(),ui->label_Head->height());
    ui->label_Head->setPixmap(image);
}

QString loginSignUp::generateSalt()
{
    QString s;
    s.resize(16); //16字节的盐
    for(int i=0;i<16;i++)
    {
        //字符区间：32~126 ASCII可见字符 把空格32排除
        s[i] = qrand()% 94 + 33; //126-33+1=94  33:从33开始
    }
    return s;
}

QPair<QString,QString> loginSignUp::hashPasswordWithSalt(const QString &password)
{
    auto salt = generateSalt();

    auto TruePasswd = password + salt;
    QByteArray bytePasswd = TruePasswd.toUtf8(); // 转换为 UTF-8 字节数组
    QByteArray hash = QCryptographicHash::hash(bytePasswd, QCryptographicHash::Sha256);
    auto s = hash.toHex();

    return {s, salt};
}

bool loginSignUp::IsPasswdSame(const QString &name, const QString &passwd)
{
    if(db.open())
        qDebug()<<"打开数据库成功!\n";
    else
        qDebug()<<"打开数据库失败!\n"<<db.lastError();
    // 数据库查询用户名和密码
    QSqlQuery query(db);
    query.prepare("SELECT * FROM UserInfo WHERE user_name = :name;");
    query.bindValue(":name", name);

    if (!query.exec()) // 执行查询
    {
        QMessageBox::warning(this, "提示", query.lastError().text());
        return false;
    }

    if (query.next()) // 如果有结果，表示用户名和密码匹配
    {
        // value参数是列名
        auto salt = query.value("salt").toByteArray();//取出数据
        auto truePasswd = query.value("user_passwd").toByteArray();//取出数据
        // 拼接盐与密码
        QByteArray saltedPassword = passwd.toUtf8() + salt;

        QByteArray hash = QCryptographicHash::hash(saltedPassword, QCryptographicHash::Sha256);
        auto hashedPassword = hash.toHex();

        return hashedPassword == truePasswd;
    }
    else
    {
        return false;
    }
}
