#include "databaseconnectionpool.h"

QSqlDatabase DatabaseConnectionPool::getConnection()
{
    QMutexLocker locker(&mutex);

    if (!availableConnections.isEmpty())
    {
        // 复用已存在的连接
        QString connectionName = availableConnections.dequeue();
        qDebug() << "复用数据库连接: " << connectionName;
        return QSqlDatabase::database(connectionName);
    }
    else if (currentConnectionCount < maxConnections)
    {
        // 创建新连接
        QString connectionName = QString("Connection_%1").arg(++lastConnectionId);
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
        db.setHostName("192.168.109.128");
//        db.setHostName("121.40.108.31");
        db.setUserName("root");
        db.setPassword("1");
        db.setPort(3306);
        db.setDatabaseName("musicDB");

        if (!db.open())
        {
            qDebug() << "数据库连接失败: " << db.lastError().text();
        }
        else
        {
            ++currentConnectionCount;
            qDebug() << "创建新数据库连接: " << connectionName;
        }
        return db;
    }
    else
    {
        // 等待空闲连接释放
        qDebug() << "等待空闲数据库连接...";
        waitCondition.wait(&mutex);

        // 递归调用以获取连接
        return getConnection();
    }
}

void DatabaseConnectionPool::releaseConnection(const QSqlDatabase &db)
{
    QMutexLocker locker(&mutex);

    QString connectionName = db.connectionName();
    if (QSqlDatabase::contains(connectionName))
    {
        availableConnections.enqueue(connectionName);
        qDebug() << "释放数据库连接: " << connectionName;

        // 唤醒等待的线程
        waitCondition.wakeOne();
    }
}

DatabaseConnectionPool::~DatabaseConnectionPool()
{
    QMutexLocker locker(&mutex);
    while (!availableConnections.isEmpty())
    {
        QString connectionName = availableConnections.dequeue();
        QSqlDatabase::removeDatabase(connectionName);
    }
}
