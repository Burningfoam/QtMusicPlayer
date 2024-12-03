#ifndef LOADMUSICLISTRUNNABLE_H
#define LOADMUSICLISTRUNNABLE_H

#include <QObject>
#include <QRunnable>

struct SongInfo;
class loadMusicListRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit loadMusicListRunnable(const QString& userid,const QString& listname,const QString& tempPath,QObject *parent = nullptr);

    void run()override;

signals:
    void loadCompleted(const QList<SongInfo>& songList);  // 加载完成信号
    void loadFailed(const QString& errorMessage);         // 加载失败信号

private:
    QString userId;
    QString listName;
    QString tempPath;
};

#endif // LOADMUSICLISTRUNNABLE_H
