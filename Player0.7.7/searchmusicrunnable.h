#ifndef SEARCHMUSICRUNNABLE_H
#define SEARCHMUSICRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

struct SongInfo;
class SearchMusicRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit SearchMusicRunnable(const QString &keyword, const QString &tempPath, QObject *parent = nullptr);

    void run() override;

signals:
    void searchCompleted(const QList<SongInfo> &results); // 搜索完成信号
    void searchFailed(const QString &error);             // 搜索失败信号

private:
    QString searchKeyword; // 搜索关键字
    QString tempPath;      // 临时路径
};

#endif // SEARCHMUSICRUNNABLE_H
