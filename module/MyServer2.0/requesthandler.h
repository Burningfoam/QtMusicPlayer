#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>

struct SongInfo;
class RequestHandler
{
public:
    virtual ~RequestHandler() = default;
    virtual void handleRequest(const QJsonObject& request, QTcpSocket& socket, QMap<QString, SongInfo>& songMap) = 0;
};

class DownloadMusicHandler : public RequestHandler
{
public:
    void handleRequest(const QJsonObject& request, QTcpSocket& socket, QMap<QString, SongInfo>& songMap) override;
};

class DownloadCoverHandler : public RequestHandler
{
public:
    void handleRequest(const QJsonObject& request, QTcpSocket& socket, QMap<QString, SongInfo>& songMap) override;
};

class DownloadLyricHandler : public RequestHandler
{
public:
    void handleRequest(const QJsonObject& request, QTcpSocket& socket, QMap<QString, SongInfo>& songMap) override;
};

class GetMusicListHandler : public RequestHandler
{
public:
    void handleRequest(const QJsonObject& request, QTcpSocket& socket, QMap<QString, SongInfo>& songMap) override;
};

class RequestHandlerRegistry
{
public:
    static RequestHandlerRegistry& instance()
    {
        static RequestHandlerRegistry registry;
        return registry;
    }

    void registerHandler(const QString& type, RequestHandler* handler)
    {
        handlers[type] = handler;
    }

    RequestHandler* getHandler(const QString& type)
    {
        return handlers.value(type, nullptr);
    }

private:
    QHash<QString, RequestHandler*> handlers;
    RequestHandlerRegistry() = default;
    ~RequestHandlerRegistry()
    {
        qDeleteAll(handlers);
    }

//    QHash<QString, RequestHandler*> handlers;
};

#endif // REQUESTHANDLER_H
