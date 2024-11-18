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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <rotatewidget.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *currentLyric;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevBtn;
    QPushButton *playerBtn;
    QPushButton *nextBtn;
    QPushButton *modeBtn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_2;
    QLabel *albumPic;
    QSlider *processBar;
    QLabel *songName;
    QLabel *currentTime;
    QLabel *totalTime;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_3;
    QSlider *soundBar;
    QPushButton *soundBtn;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_2;
    RotateWidget *PostWidget;
    QSpacerItem *horizontalSpacer;
    QListWidget *musicList;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1025, 600);
        currentLyric = new QLabel(Widget);
        currentLyric->setObjectName(QString::fromUtf8("currentLyric"));
        currentLyric->setGeometry(QRect(300, 420, 421, 41));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        currentLyric->setFont(font);
        currentLyric->setAlignment(Qt::AlignCenter);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 480, 1015, 103));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setMinimumSize(QSize(293, 86));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        prevBtn = new QPushButton(widget1);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(prevBtn);

        playerBtn = new QPushButton(widget1);
        playerBtn->setObjectName(QString::fromUtf8("playerBtn"));
        playerBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(playerBtn);

        nextBtn = new QPushButton(widget1);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(nextBtn);

        modeBtn = new QPushButton(widget1);
        modeBtn->setObjectName(QString::fromUtf8("modeBtn"));
        modeBtn->setMinimumSize(QSize(60, 60));

        horizontalLayout->addWidget(modeBtn);


        horizontalLayout_3->addWidget(widget1);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(461, 101));
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
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI Light"));
        font1.setPointSize(8);
        font1.setBold(true);
        songName->setFont(font1);
        currentTime = new QLabel(widget_2);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(310, 50, 61, 30));
        QFont font2;
        font2.setBold(true);
        currentTime->setFont(font2);
        totalTime = new QLabel(widget_2);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(370, 50, 60, 30));
        totalTime->setFont(font2);

        horizontalLayout_3->addWidget(widget_2);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setMinimumSize(QSize(181, 80));
        soundBar = new QSlider(widget_3);
        soundBar->setObjectName(QString::fromUtf8("soundBar"));
        soundBar->setGeometry(QRect(50, 35, 111, 22));
        soundBar->setOrientation(Qt::Horizontal);
        soundBtn = new QPushButton(widget_3);
        soundBtn->setObjectName(QString::fromUtf8("soundBtn"));
        soundBtn->setGeometry(QRect(10, 30, 30, 30));

        horizontalLayout_3->addWidget(widget_3);

        widget2 = new QWidget(Widget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(111, 80, 829, 303));
        horizontalLayout_2 = new QHBoxLayout(widget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        PostWidget = new RotateWidget(widget2);
        PostWidget->setObjectName(QString::fromUtf8("PostWidget"));
        PostWidget->setMinimumSize(QSize(300, 300));

        horizontalLayout_2->addWidget(PostWidget);

        horizontalSpacer = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        musicList = new QListWidget(widget2);
        musicList->setObjectName(QString::fromUtf8("musicList"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(musicList->sizePolicy().hasHeightForWidth());
        musicList->setSizePolicy(sizePolicy);
        musicList->setMinimumSize(QSize(451, 301));

        horizontalLayout_2->addWidget(musicList);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        currentLyric->setText(QCoreApplication::translate("Widget", "\347\224\237\346\227\245\345\277\253\344\271\220", nullptr));
        prevBtn->setText(QString());
        playerBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        albumPic->setText(QString());
        songName->setText(QCoreApplication::translate("Widget", "\346\210\221\346\200\200\345\277\265\347\232\204 - \345\255\231\347\207\225\345\247\277", nullptr));
        currentTime->setText(QCoreApplication::translate("Widget", "03:51/", nullptr));
        totalTime->setText(QCoreApplication::translate("Widget", "04:50", nullptr));
        soundBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
