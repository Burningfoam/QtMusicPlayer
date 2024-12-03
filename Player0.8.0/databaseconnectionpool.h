#ifndef DATABASECONNECTIONPOOL_H
#define DATABASECONNECTIONPOOL_H

#include <QSqlDatabase>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QSqlError>
#include <QDebug>

class DatabaseConnectionPool
{
public:
    // 获取单例实例
    static DatabaseConnectionPool& instance()
    {
        static DatabaseConnectionPool pool;
        return pool;
    }

    // 获取连接
    QSqlDatabase getConnection();

    // 释放连接
    void releaseConnection(const QSqlDatabase& db);

private:
    DatabaseConnectionPool()
        : maxConnections(10), currentConnectionCount(0), lastConnectionId(0) {}

    ~DatabaseConnectionPool();

private:
    QQueue<QString> availableConnections; // 可用连接队列
    QMutex mutex;                         // 互斥锁
    QWaitCondition waitCondition;         // 条件变量
    int maxConnections;                   // 最大连接数
    int currentConnectionCount;           // 当前已创建的连接数
    int lastConnectionId;                 // 最后一次连接 ID
};

#endif // DATABASECONNECTIONPOOL_H
