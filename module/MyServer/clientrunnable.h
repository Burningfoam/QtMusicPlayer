#ifndef CLIENTRUNNABLE_H
#define CLIENTRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include "myserver.h"

class ClientRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit ClientRunnable(qintptr sock,MyServer* server,QObject *parent = nullptr);
    void run()override;

signals:
public slots:
private:
    qintptr sock;
    QByteArray buffer; // 人造缓冲区
    size_t expectedSize; // 存储期望的数据包大小
    MyServer* server; // 保存 MyServer 实例
};

#endif // CLIENTRUNNABLE_H
