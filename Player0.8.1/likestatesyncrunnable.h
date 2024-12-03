#ifndef LIKESTATESYNCRUNNABLE_H
#define LIKESTATESYNCRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QList>
#include <QTimer>

class LikeStateSyncRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit LikeStateSyncRunnable(const QString& userId,  const QString &musicId, QObject *parent = nullptr);
    void run() override;
public slots:
signals:
    void checkCompleted(bool isLiked);
    void checkFailed(const QString &error);
private:
    QString userId;
    QString musicId;
};

#endif // LIKESTATESYNCRUNNABLE_H
