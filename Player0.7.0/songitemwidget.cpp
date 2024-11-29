#include "songitemwidget.h"
#include "ui_songitemwidget.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
SongItemWidget::SongItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItemWidget)
{
    ui->setupUi(this);

}

SongItemWidget::~SongItemWidget()
{
    delete ui;
}

void SongItemWidget::setSongDetails(const QString &songName, const QString &artist, const QString &album, bool isDelEnable)
{
    ui->label_musicName->setText(songName);
    ui->label_artist->setText(artist);
    ui->label_album->setText(album);
    if(isDelEnable == false)
    {
        ui->toolButton_delete->setEnabled(false);
        ui->toolButton_delete->setVisible(false);
    }
}

void SongItemWidget::setSongCover(const QPixmap &coverImage)
{
    QPixmap image(ui->label_cover->width(),ui->label_cover->height());
    image.fill(Qt::transparent);//设置成透明背景(父窗体的背景)

    QPainter painter(&image);
    // 禁用画笔的边框
    painter.setPen(Qt::NoPen);
    // 开启抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    //设置画笔的来源图片
    painter.setBrush(coverImage.scaled(ui->label_cover->size()));
    // 绘制一个圆角矩形
    int radius = 15; // 可以根据需要调整圆角的半径
    painter.drawRoundedRect(0, 0, ui->label_cover->width(), ui->label_cover->height(), radius, radius);
    ui->label_cover->setPixmap(image);
}

void SongItemWidget::setItemNumber(int n)
{
    ui->label_number->setText(QString::number(n));
}

void SongItemWidget::setMusicId(const QString &id)
{
    musicId = id;
}

QString SongItemWidget::getSongName()
{
    return ui->label_musicName->text();
}

QString SongItemWidget::getArtist()
{
    return ui->label_artist->text();
}

QString SongItemWidget::getAlbum()
{
    return ui->label_album->text();
}
