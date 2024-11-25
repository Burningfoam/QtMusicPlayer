#include "loginsignup.h"
#include "ui_loginsignup.h"
#include <QIcon>
#include <QDebug>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPainter>
#include <QBuffer>
#include <QMessageBox>
#include <openssl/sha.h>

struct WidgetPrivate
{
    QSqlDatabase db;
};

loginSignUp::loginSignUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginSignUp),
    p(new WidgetPrivate)
{
    ui->setupUi(this);
    // 数据库
        p->db = QSqlDatabase::addDatabase("QMYSQL"); // 根据字符串获取数据库驱动
        p->db.setHostName("192.168.109.128");
        p->db.setUserName("root");
        p->db.setPassword("1");
        p->db.setPort(3306);
        p->db.setDatabaseName("musicDB");
        if(p->db.open())
            qDebug()<<"打开数据库成功!\n";
        else
            qDebug()<<"打开数据库失败!\n"<<p->db.lastError();
        connect(ui->pushButton_Register,&QPushButton::clicked,[this]()
        {
            auto name = ui->lineEdit_UserName->text();
            auto passwd = ui->lineEdit_Passwd->text();

            // 把图片对象变成二进制数据
            // QImage -> QByteArray
            auto image = ui->label_Head->pixmap()->toImage();// 将label里存储的图片取出
            QByteArray imageData;
            QBuffer buffer(&imageData);// QT缓冲区对象
            buffer.open(QIODevice::WriteOnly);// 以写的形式打开缓冲区，输入数据
            image.save(&buffer,"PNG");

            // 二进制数据不能直接放入字符串
            QSqlQuery query(p->db);// 数据库语句执行对象
            query.prepare("insert into test267 values(:name,:passwd,:image);"); // :变量 拼接sql语句时，不直接把值放进去，而是稍后以变量赋值形式替换变量
            // 变量绑定的形式
            query.bindValue(":name",name);
            query.bindValue(":passwd",passwd);
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

        QSqlQuery query(p->db);// 数据库语句执行对象
        if(query.exec("select image from test267 where name = 'test';"))
        {
            if(query.next())// 如果下一行数据存在，就进行读取
            {
                // value参数是列名
                auto ImageData = query.value("image").toByteArray();//取出数据 转成字节数组
                QPixmap mp;
                mp.loadFromData(ImageData);
                ui->label_Head->setPixmap(mp);
            }
        }

        setFixedSize(480, 720);

        // 修改程序的标题
        setWindowTitle("Login");

        // 设置程序的图标
        QIcon icon(":/picture/headimg.jpeg");
        setWindowIcon(icon);

        // 设置头像
        QPixmap headPix(":/picture/8.png");
    //    ui->headLabel->setPixmap(headPix.scaled(ui->headLabel->width(),ui->headLabel->height()));

        ui->lineEdit_UserName->setPlaceholderText("请输入账号");
        ui->lineEdit_Passwd->setPlaceholderText("请输入密码");

        // 信号和槽
        connect(ui->pushButton_Register,&QPushButton::clicked,this,&loginSignUp::handleRegisterSlot);
        connect(ui->pushButton_Login,&QPushButton::clicked,this,&loginSignUp::handleLoginSlot);
}

loginSignUp::~loginSignUp()
{
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
            QPixmap mp(path);

            QPixmap image(ui->label_Head->width(),ui->label_Head->height());
            image.fill(Qt::transparent);//设置成透明背景(父窗体的背景)

            QPainter painter(&image);
            //设置画笔的来源图片
            painter.setBrush(mp.scaled(ui->label_Head->size()));
            //画出一个圆形图片
            painter.drawEllipse(0,0,ui->label_Head->width(),ui->label_Head->height());
            ui->label_Head->setPixmap(image);
        }
    }
}

void loginSignUp::handleRegisterSlot()
{
    qDebug()<< "注册按钮被按下";
    QString accountInfo = ui->lineEdit_UserName->text();
    QString passwdInfo = ui->lineEdit_Passwd->text();

    qDebug()<<"account:"<< accountInfo;
    qDebug()<<"passwd:"<< passwdInfo;
}

void loginSignUp::handleLoginSlot()
{
    qDebug()<< "登录按钮被按下";
}
