#include "homelistloadertask.h"
#include <QSqlError>
#include <QDebug>
HomelistLoaderTask::HomelistLoaderTask(QObject *parent)
{
    // 设置为高优先级，确保后台任务不会排队太久
    setAutoDelete(true);  // 任务完成后自动删除
}

void HomelistLoaderTask::run()
{
    qDebug()<<"进入主页子线程！";
    // 每个子线程都使用独立的数据库连接
    QSqlDatabase db;

    // 检查是否已经存在连接
    if (!QSqlDatabase::contains("HomelistLoaderConnection"))
    {
        db = QSqlDatabase::addDatabase("QMYSQL", "HomelistLoaderConnection"); // 使用独立连接名称
//        db.setHostName("192.168.109.128");
        db.setHostName("121.40.108.31");
        db.setUserName("root");
        db.setPassword("1");
        db.setPort(3306);
        db.setDatabaseName("musicDB");
    }
    else
    {
        // 如果连接已经存在，获取该连接对象
        db = QSqlDatabase::database("HomelistLoaderConnection");
    }

    // 打开数据库连接
    if (!db.isOpen() && !db.open())
    {
        qDebug() << "子线程数据库打开失败:" << db.lastError().text();
        return;  // 如果数据库无法打开，直接返回
    }
    else
    {
        qDebug() << "子线程数据库连接成功";
    }

    // 执行数据库查询
    QSqlQuery query(db);
    query.prepare("SELECT playlist_name, playlist_cover FROM Playlist WHERE playlist_name IN (:name1, :name2, :name3, :name4, :name5)");
    query.bindValue(":name1", "hotlist");
    query.bindValue(":name2", "newlist");
    query.bindValue(":name3", "uplist");
    query.bindValue(":name4", "goldlist");
    query.bindValue(":name5", "jaylist");

    if (!query.exec())
    {
        qDebug() << "子线程数据库查询失败:" << query.lastError().text();
        return;
    }

    QList<QPixmap> covers;

    // 处理查询结果
    while (query.next())
    {
        QByteArray imageData = query.value(1).toByteArray();
        QPixmap pixmap;
        if (pixmap.loadFromData(imageData))
        {
            covers.append(pixmap);
        }
        else
        {
            qDebug() << "添加了空图";
            covers.append(QPixmap());  // 如果图片加载失败，添加一个空的QPixmap
        }
    }

    // 数据加载完成后发射信号回到主线程
    emit coversLoaded(covers);

    // 子线程完成数据库操作后关闭连接
    db.close();
}
