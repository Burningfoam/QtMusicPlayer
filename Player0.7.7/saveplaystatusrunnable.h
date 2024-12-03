#ifndef SAVEPLAYSTATUSRUNNABLE_H
#define SAVEPLAYSTATUSRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class SavePlayStatusRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit SavePlayStatusRunnable(const QString& userId, int currentSongId, int currentDuration, const QStringList& playlist, QObject *parent = nullptr);
    void run() override;
signals:

public slots:
private:
    QString userId;
    int currentSongId;
    int currentDuration;
    QStringList playlist;
};

#endif // SAVEPLAYSTATUSRUNNABLE_H
