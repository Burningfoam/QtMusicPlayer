#ifndef COVERLOADERRUNNABLE_H
#define COVERLOADERRUNNABLE_H

#include <QObject>
#include <QRunnable>
#include <QLabel>
#include <QListWidget>

class Widget;
class CoverLoaderRunnable : public QObject,public QRunnable
{
    Q_OBJECT
public:
    explicit CoverLoaderRunnable(const QString& coverFolderPath, QListWidget* currentFreshList,QObject *parent = nullptr);

    void run() override;

public slots:
signals:
    void coversDownloadSuccess();
    void coversLoaded(const QList<QPixmap>& listCovers);
private:
    Widget* widget;
    QString coverFolderPath;
    QListWidget* currentFreshList;
    QLabel* labelListCover;
};

#endif // COVERLOADERRUNNABLE_H
