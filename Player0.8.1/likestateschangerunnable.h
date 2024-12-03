#ifndef LIKESTATESCHANGERUNNABLE_H
#define LIKESTATESCHANGERUNNABLE_H

#include <QRunnable>
#include <QObject>
#include <QSqlQuery>
#include <QSqlError>

class LikeStatesChangeRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit LikeStatesChangeRunnable(const QString &userId, const QString &musicId, bool like, QObject *parent = nullptr);
    void run() override;
signals:
    void operationCompleted(bool success, bool newLikeState);
    void operationFailed(const QString &error);
public slots:
private:
    QString userId;
    QString musicId;
    bool like;
};

#endif // LIKESTATESCHANGERUNNABLE_H
