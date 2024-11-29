#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <QByteArray>
#include <QDebug>

class Widget;
class DataHandler
{
public:
    virtual ~DataHandler() = default;
    virtual void handleData(const QByteArray& data,Widget* w) = 0;
};

class JsonDataHandler : public DataHandler
{
public:
    void handleData(const QByteArray& data,Widget* w) override;
};

class AudioDataHandler : public DataHandler
{
public:
    void handleData(const QByteArray& data,Widget* w) override;
};

class LyricDataHandler : public DataHandler
{
public:
    void handleData(const QByteArray& data,Widget* w) override;
};

class CoverDataHandler : public DataHandler
{
public:
    void handleData(const QByteArray& data,Widget* w) override;
};

class DataHandlerFactory
{
public:
    static DataHandler* createHandler(const QByteArray& type)
    {
        if (type == QByteArray("json "))
        {
            return new JsonDataHandler(); // 返回指针
        }
        else if (type == QByteArray("audio"))
        {
            return new AudioDataHandler(); // 返回指针
        }
        else if (type == QByteArray("lyric"))
        {
            return new LyricDataHandler(); // 返回指针
        }
        else if (type == QByteArray("cover"))
        {
            return new CoverDataHandler(); // 返回指针
        }
        else
        {
            qDebug() << "未知数据类型: " << QString(type);
            return nullptr;
        }
    }
};

#endif // DATAHANDLER_H
