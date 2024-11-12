/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QListWidget *musicList;
    QWidget *widget_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevBtn;
    QPushButton *playerBtn;
    QPushButton *nextBtn;
    QPushButton *modeBtn;
    QWidget *widget_2;
    QLabel *albumPic;
    QSlider *processBar;
    QLabel *songName;
    QLabel *currentTime;
    QLabel *totalTime;
    QLabel *currentLyric;
    QWidget *widget_3;
    QSlider *soundBar;
    QPushButton *soundBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1025, 600);
        musicList = new QListWidget(Widget);
        musicList->setObjectName(QString::fromUtf8("musicList"));
        musicList->setGeometry(QRect(200, 30, 451, 301));
        widget_4 = new QWidget(Widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(20, 460, 971, 121));
        widget = new QWidget(widget_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 293, 86));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        prevBtn = new QPushButton(widget);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(prevBtn);

        playerBtn = new QPushButton(widget);
        playerBtn->setObjectName(QString::fromUtf8("playerBtn"));
        playerBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(playerBtn);

        nextBtn = new QPushButton(widget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(nextBtn);

        modeBtn = new QPushButton(widget);
        modeBtn->setObjectName(QString::fromUtf8("modeBtn"));
        modeBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(modeBtn);

        widget_2 = new QWidget(widget_4);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(310, 9, 461, 101));
        albumPic = new QLabel(widget_2);
        albumPic->setObjectName(QString::fromUtf8("albumPic"));
        albumPic->setGeometry(QRect(10, 20, 60, 60));
        albumPic->setMinimumSize(QSize(60, 60));
        processBar = new QSlider(widget_2);
        processBar->setObjectName(QString::fromUtf8("processBar"));
        processBar->setGeometry(QRect(80, 60, 221, 22));
        processBar->setOrientation(Qt::Horizontal);
        songName = new QLabel(widget_2);
        songName->setObjectName(QString::fromUtf8("songName"));
        songName->setGeometry(QRect(80, 20, 151, 23));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI Light"));
        font.setPointSize(8);
        font.setBold(true);
        songName->setFont(font);
        currentTime = new QLabel(widget_2);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(310, 50, 61, 30));
        QFont font1;
        font1.setBold(true);
        currentTime->setFont(font1);
        totalTime = new QLabel(widget_2);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(370, 50, 60, 30));
        totalTime->setFont(font1);
        currentLyric = new QLabel(widget_2);
        currentLyric->setObjectName(QString::fromUtf8("currentLyric"));
        currentLyric->setGeometry(QRect(220, 12, 231, 41));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        currentLyric->setFont(font2);
        currentLyric->setAlignment(Qt::AlignCenter);
        widget_3 = new QWidget(widget_4);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(780, 20, 181, 80));
        soundBar = new QSlider(widget_3);
        soundBar->setObjectName(QString::fromUtf8("soundBar"));
        soundBar->setGeometry(QRect(50, 35, 111, 22));
        soundBar->setOrientation(Qt::Horizontal);
        soundBtn = new QPushButton(widget_3);
        soundBtn->setObjectName(QString::fromUtf8("soundBtn"));
        soundBtn->setGeometry(QRect(10, 30, 30, 30));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        prevBtn->setText(QString());
        playerBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        albumPic->setText(QString());
        songName->setText(QCoreApplication::translate("Widget", "\346\210\221\346\200\200\345\277\265\347\232\204 - \345\255\231\347\207\225\345\247\277", nullptr));
        currentTime->setText(QCoreApplication::translate("Widget", "03:51/", nullptr));
        totalTime->setText(QCoreApplication::translate("Widget", "04:50", nullptr));
        currentLyric->setText(QCoreApplication::translate("Widget", "\347\224\237\346\227\245\345\277\253\344\271\220", nullptr));
        soundBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
