#ifndef SONGITEMWIDGET_H
#define SONGITEMWIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class SongItemWidget;
}

class SongItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SongItemWidget(QWidget *parent = nullptr);
    ~SongItemWidget();

    void setSongDetails(const QString &songName, const QString &artist, const QString &album, bool isDelEnable = false);
    void setSongCover(const QPixmap &coverImage);
    void setItemNumber(int n);
    void setMusicId(const QString& id);

    QString getSongName();
    QString getArtist();
    QString getAlbum();

public:
    QString musicId;

private:
    Ui::SongItemWidget *ui;
};

#endif // SONGITEMWIDGET_H
