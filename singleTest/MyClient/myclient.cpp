#include "myclient.h"
#include "ui_myclient.h"
#include <QFile>

MyClient::MyClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyClient)
{
    ui->setupUi(this);
    expectedSize = 0;

    socket.connectToHost("192.168.0.159",8080);

    connect(&socket,&QTcpSocket::connected,[]()
    {
        qDebug()<<"连接服务器成功!"<<endl;
    });

    connect(ui->pushButton,&QPushButton::clicked,[this]()
    {
        auto Content = ui->textEdit->toPlainText().toUtf8();
        size_t size = Content.size();
        socket.write((const char*)&size,sizeof (size_t));// 先发包头
        socket.write(Content);// 写数据给服务器
    });

    // 监听 readyRead 信号，接收服务器返回的数据
    connect(&socket, &QTcpSocket::readyRead, [this]() {
        auto Content = socket.readAll(); // 读取套接字缓冲区的数据
        buffer.append(Content);          // 追加到自定义缓冲区

        // 解析缓冲区的数据包
        while (buffer.size() > sizeof(size_t)) {
            if (expectedSize == 0) {
                // 提取包头，获取数据包大小
                memcpy(&expectedSize, buffer.data(), sizeof(size_t));
            }

            // 如果缓冲区中的数据不足以构成完整包，退出循环
            if (buffer.size() < expectedSize + sizeof(size_t)) {
                break;
            }

            // 提取完整数据包内容
            auto data = buffer.mid(sizeof(size_t), expectedSize);

//            // 处理接收到的数据（例如显示在界面上）
//            QString message = QString::fromUtf8(data);
//            ui->textBrowser->append("服务器：" + message); // 在 UI 界面显示
            // 保存文件
            QFile file("D:\\File\\Desktop\\111.mp3");
            if (file.open(QIODevice::WriteOnly)) {
                file.write(data);
                file.close();
                qDebug() << "文件保存成功！";
            } else {
                qDebug() << "无法保存文件！";
            }


            // 移除已处理的数据包
            buffer.remove(0, expectedSize + sizeof(size_t));

            // 重置期望大小
            expectedSize = 0;
        }
    });
}

MyClient::~MyClient()
{
    delete ui;
}
