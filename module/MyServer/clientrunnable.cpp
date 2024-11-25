#include "clientrunnable.h"
#include "requesthandler.h"
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QEventLoop>
#include <QFile>

ClientRunnable::ClientRunnable(qintptr sock,MyServer* server,QObject *parent) : QObject(parent),server(server)
{
    this->sock = sock;
    setAutoDelete(true);
    expectedSize = 0;
}

void ClientRunnable::run()
{
    QTcpSocket socket;
    socket.setSocketDescriptor(sock);// 把通信套接字给到通信类

    if(!socket.waitForConnected(3000))// 等待连接，时长 3s
    {
        return;// 当前套接字已经失效，不能实现TCP连接
    }
//    QHostAddress address = socket.peerAddress();
//    qDebug()<<"连接ip："<<address<<"连接的端口号："<<socket.peerPort();

    QEventLoop loop;
    // 当放出信号的对象被释放，connect 自动断开连接
    // readyRead: tcp缓冲区中有数据可以读取
    // readyRead*** tcp缓冲区满或发送结束才触发信号
    connect(&socket, &QTcpSocket::readyRead, [this, &socket]()
    {
        auto Content = socket.readAll();  // 读取缓冲区所有数据
        buffer.append(Content);            // 将读取到的数据追加到缓冲区

        // 解析缓冲区的数据包
        while (buffer.size() > sizeof(size_t) + 5)
        {
            if (expectedSize == 0)
            {
                // 提取包头，获取数据包大小
                memcpy(&expectedSize, buffer.data(), sizeof(size_t));
            }

            // 如果缓冲区中的数据不足以构成完整包，退出循环
            if (buffer.size() < expectedSize + sizeof(size_t) + 5)
            {
                break;
            }

            // 提取包头（数据类型）
            auto type = buffer.mid(sizeof(size_t), 5); // 类型长度为5字节（例如："audio" 或 "json "）
            // 提取完整数据包内容
            auto data = buffer.mid(sizeof(size_t) + 5, expectedSize);

            // 此处处理数据（比如 JSON 解析等）
            if (type == "json ")
            {
                // 解析JSON内容
                QJsonDocument doc = QJsonDocument::fromJson(data);
                if (!doc.isObject())
                {
                    qWarning() << "Invalid JSON data";
                    break;
                }

                // 获取请求类型
                QJsonObject request = doc.object();
                QString type = request["type"].toString();

                // 根据请求类型调用相应的策略
                RequestHandler* handler = RequestHandlerRegistry::instance().getHandler(type);
                if (handler)
                {
                    handler->handleRequest(request, socket,server->songMap);
                }
                else
                {
                    qDebug() << "No handler for request type:" << type;
                }
            }




//            if(QString(data) == "aaa")
//            {
//                auto Content2 = QString("666").toUtf8();
//                size_t size2 = Content2.size();
//                socket.write((const char*)&size2,sizeof (size_t));// 先发包头
//                socket.write(Content2);// 写数据给服务器

//                QFile file(server->songMap["2639534833"].filePath); // 打开要发送的 MP3 文件
//                if (!file.open(QIODevice::ReadOnly))
//                {
//                    qDebug()<<server->songMap["2639534833"].filePath;
//                    qDebug() << "无法打开文件！";
//                    return;
//                }

//                QByteArray fileContent = file.readAll(); // 读取文件内容
//                file.close();

//                size_t fileSize = fileContent.size(); // 获取文件大小

//                auto Type = QString("json ").toUtf8();
//                auto Content = QString("this is json").toUtf8();
//                size_t size = Content.size();

//                socket.write((const char*)&size,sizeof (size_t));// 先发包头
//                socket.write(Type);
//                socket.write(Content);// 写数据给服务器
//                // 发送包头（文件大小）
//                QByteArray testjson = "";
//                socket.write(sizeof(testjson));

//                // 发送文件内容
//                socket.write("");
//            }
//            else if(QString(data) == "bbb")
//            {
//                QFile file(server->songMap["2775921610"].filePath); // 打开要发送的 MP3 文件
//                if (!file.open(QIODevice::ReadOnly))
//                {
//                    qDebug()<<server->songMap["2775921610"].filePath;
//                    qDebug() << "无法打开文件！";
//                    return;
//                }

//                QByteArray fileContent = file.readAll(); // 读取文件内容
//                file.close();

//                size_t fileSize = fileContent.size(); // 获取文件大小
//                auto Type = QString("audio").toUtf8();

//                // 发送包头（文件大小）
//                socket.write((const char*)&fileSize, sizeof(size_t));
//                socket.write(Type);
//                // 发送文件内容
//                socket.write(fileContent);
//            }

            // 移除已处理的数据包
            buffer.remove(0, expectedSize + sizeof(size_t) + 5);

            // 重置期望的包大小
            expectedSize = 0;
        }
    });

    connect(&socket,&QTcpSocket::disconnected,[&loop]()
    {
        loop.quit();// 断开了连接，退出事件循环
    });
    loop.exec();// 执行事件循环：死循环监听信号和槽

    //收尾
    socket.close(); // 关闭套接字

}
