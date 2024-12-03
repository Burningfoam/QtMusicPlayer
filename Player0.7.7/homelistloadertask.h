#ifndef HOMELISTLOADERTASK_H
#define HOMELISTLOADERTASK_H
#include <QRunnable>
#include <QSqlQuery>
#include <QPixmap>
#include <QByteArray>

class HomelistLoaderTask : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit HomelistLoaderTask(QObject *parent = nullptr);

    void run() override;  // 重写run函数，执行查询操作

signals:
    void coversLoaded(const QList<QPixmap> &covers); // 数据加载完成时发射此信号

private:
};

#endif // HOMELISTLOADERTASK_H
