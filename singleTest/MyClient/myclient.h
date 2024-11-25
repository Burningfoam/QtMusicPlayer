#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class MyClient;
}

class MyClient : public QWidget
{
    Q_OBJECT

public:
    explicit MyClient(QWidget *parent = nullptr);
    ~MyClient();

private:
    Ui::MyClient *ui;

    QTcpSocket socket;
    QByteArray buffer; // 人造缓冲区
    size_t expectedSize; // 存储期望的数据包大小
};

#endif // MYCLIENT_H
