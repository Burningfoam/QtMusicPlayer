/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <rotatewidget.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *currentLyric;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
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
    QListWidget *musicList;
    RotateWidget *PostWidget;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout;
    QLabel *lyricLabel_1;
    QLabel *lyricLabel_2;
    QLabel *lyricLabel_3;
    QLabel *lyricLabel_4;
    QLabel *lyricLabel_5;
    QLabel *lyricLabel_6;
    QLabel *lyricLabel_7;
    QPushButton *pushButton_StreamTest;
    QPushButton *pushButton_StreamTest2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1051, 705);
        currentLyric = new QLabel(Widget);
        currentLyric->setObjectName(QString::fromUtf8("currentLyric"));
        currentLyric->setGeometry(QRect(20, 530, 421, 41));
        QFont font;
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        currentLyric->setFont(font);
        currentLyric->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 580, 1015, 103));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(layoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(293, 86));
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


        horizontalLayout_3->addWidget(widget);

        horizontalSpacer_2 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        widget_2 = new QWidget(layoutWidget);
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
        font1.setWeight(75);
        songName->setFont(font1);
        currentTime = new QLabel(widget_2);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(310, 50, 61, 30));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        currentTime->setFont(font2);
        totalTime = new QLabel(widget_2);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(370, 50, 60, 30));
        totalTime->setFont(font2);

        horizontalLayout_3->addWidget(widget_2);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        widget_3 = new QWidget(layoutWidget);
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

        musicList = new QListWidget(Widget);
        musicList->setObjectName(QString::fromUtf8("musicList"));
        musicList->setGeometry(QRect(780, 30, 241, 521));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(musicList->sizePolicy().hasHeightForWidth());
        musicList->setSizePolicy(sizePolicy);
        musicList->setMinimumSize(QSize(200, 150));
        PostWidget = new RotateWidget(Widget);
        PostWidget->setObjectName(QString::fromUtf8("PostWidget"));
        PostWidget->setGeometry(QRect(80, 140, 300, 300));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(PostWidget->sizePolicy().hasHeightForWidth());
        PostWidget->setSizePolicy(sizePolicy1);
        PostWidget->setMinimumSize(QSize(300, 300));
        widget_4 = new QWidget(Widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(450, 100, 276, 370));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lyricLabel_1 = new QLabel(widget_4);
        lyricLabel_1->setObjectName(QString::fromUtf8("lyricLabel_1"));
        lyricLabel_1->setMinimumSize(QSize(200, 40));
        lyricLabel_1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_1->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_1);

        lyricLabel_2 = new QLabel(widget_4);
        lyricLabel_2->setObjectName(QString::fromUtf8("lyricLabel_2"));
        lyricLabel_2->setMinimumSize(QSize(200, 40));
        lyricLabel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_2->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_2);

        lyricLabel_3 = new QLabel(widget_4);
        lyricLabel_3->setObjectName(QString::fromUtf8("lyricLabel_3"));
        lyricLabel_3->setMinimumSize(QSize(250, 50));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setUnderline(false);
        font3.setWeight(75);
        lyricLabel_3->setFont(font3);
        lyricLabel_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_3->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_3);

        lyricLabel_4 = new QLabel(widget_4);
        lyricLabel_4->setObjectName(QString::fromUtf8("lyricLabel_4"));
        lyricLabel_4->setMinimumSize(QSize(200, 40));
        lyricLabel_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_4->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_4);

        lyricLabel_5 = new QLabel(widget_4);
        lyricLabel_5->setObjectName(QString::fromUtf8("lyricLabel_5"));
        lyricLabel_5->setMinimumSize(QSize(200, 40));
        lyricLabel_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_5->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_5);

        lyricLabel_6 = new QLabel(widget_4);
        lyricLabel_6->setObjectName(QString::fromUtf8("lyricLabel_6"));
        lyricLabel_6->setMinimumSize(QSize(200, 40));
        lyricLabel_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_6->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_6);

        lyricLabel_7 = new QLabel(widget_4);
        lyricLabel_7->setObjectName(QString::fromUtf8("lyricLabel_7"));
        lyricLabel_7->setMinimumSize(QSize(200, 40));
        lyricLabel_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_7->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_7);

        pushButton_StreamTest = new QPushButton(Widget);
        pushButton_StreamTest->setObjectName(QString::fromUtf8("pushButton_StreamTest"));
        pushButton_StreamTest->setGeometry(QRect(380, 510, 161, 51));
        pushButton_StreamTest2 = new QPushButton(Widget);
        pushButton_StreamTest2->setObjectName(QString::fromUtf8("pushButton_StreamTest2"));
        pushButton_StreamTest2->setGeometry(QRect(570, 510, 161, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        currentLyric->setText(QApplication::translate("Widget", "Welcome!", nullptr));
        prevBtn->setText(QString());
        playerBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        albumPic->setText(QString());
        songName->setText(QApplication::translate("Widget", "\346\210\221\346\200\200\345\277\265\347\232\204 - \345\255\231\347\207\225\345\247\277", nullptr));
        currentTime->setText(QApplication::translate("Widget", "03:51/", nullptr));
        totalTime->setText(QApplication::translate("Widget", "04:50", nullptr));
        soundBtn->setText(QString());
        lyricLabel_1->setText(QString());
        lyricLabel_2->setText(QString());
        lyricLabel_3->setText(QApplication::translate("Widget", "Welcome!", nullptr));
        lyricLabel_4->setText(QString());
        lyricLabel_5->setText(QString());
        lyricLabel_6->setText(QString());
        lyricLabel_7->setText(QString());
        pushButton_StreamTest->setText(QApplication::translate("Widget", "\344\270\200\345\277\265\344\271\213\351\227\264", nullptr));
        pushButton_StreamTest2->setText(QApplication::translate("Widget", "\345\244\234\346\233\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
