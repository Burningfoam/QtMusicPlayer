#include "coverloaderrunnable.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include "songitemwidget.h"
#include "widget.h"

CoverLoaderRunnable::CoverLoaderRunnable(const QString& coverFolderPath, QListWidget* currentFreshList, QObject *parent)
    : QObject(parent),
      coverFolderPath(coverFolderPath),
      currentFreshList(currentFreshList)
{  
    setAutoDelete(true);
}

void CoverLoaderRunnable::run()
{
    qDebug() << "子线程开始扫描文件";

    QDir coverDir(coverFolderPath);

    if (!coverDir.exists())
    {
        qDebug() << "封面文件夹不存在: " << coverFolderPath;
        return;
    }

    bool allCoversExist = true;

    // 遍历当前歌单中的所有项，检查对应封面是否存在
    for (int i = 0; i < currentFreshList->count(); ++i)
    {
        QString musicId = currentFreshList->item(i)->data(Qt::UserRole).toString();
        QString coverFilePath = coverFolderPath + musicId + ".png";  // 封面路径

        if (!QFile::exists(coverFilePath))
        {
            allCoversExist = false;
            break;
        }
    }

    // 如果所有封面都存在，开始加载封面
    if (allCoversExist)
    {
        qDebug() << "所有封面图片都已下载完毕，开始加载封面";
        emit coversDownloadSuccess();
        QList<QPixmap> listCovers;

        // 加载所有封面图
        for (int i = 0; i < currentFreshList->count(); ++i)
        {
            // 仅获取数据，不访问 QListWidget 本身
            QString musicId = currentFreshList->item(i)->data(Qt::UserRole).toString();
            QString coverFilePath = coverFolderPath + musicId + ".png";  // 封面路径

            if (QFile::exists(coverFilePath))
            {
                QPixmap coverPixmap(coverFilePath);
                listCovers.append(coverPixmap);
                qDebug() << "加载封面: " << coverFilePath;
            }
        }
        emit coversLoaded(listCovers);
    }
    else
    {
        qDebug() << "等待封面下载完成...";
    }
}
