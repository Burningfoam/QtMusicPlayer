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

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1500, 1068);
        currentLyric = new QLabel(Widget);
        currentLyric->setObjectName(QString::fromUtf8("currentLyric"));
        currentLyric->setGeometry(QRect(320, 910, 421, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        currentLyric->setFont(font);
        currentLyric->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 960, 1171, 103));
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
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(processBar->sizePolicy().hasHeightForWidth());
        processBar->setSizePolicy(sizePolicy);
        processBar->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #bbb; /* \346\273\221\346\247\275\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    background: #ccc; /* \346\273\221\346\247\275\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    height: 8px; /* \346\273\221\346\247\275\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \346\273\221\346\247\275\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
" \n"
"QSlider::handle:horizontal {\n"
"    background: #FC3D49; /* \346\273\221\345\235\227\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 1px solid #FC3D49; /* \346\273\221\345\235\227\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    width: 18px; /* \346\273\221\345\235\227\347\232\204\345\256\275\345\272\246 */\n"
"    height: 18px; /* \346\273\221\345\235\227\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 9px; /* \346\273\221\345\235\227\347\232\204\345\234\206\350"
                        "\247\222\345\215\212\345\276\204\357\274\214\347\241\256\344\277\235\346\273\221\345\235\227\346\230\257\345\234\206\345\275\242 */\n"
"    margin: -6px 0; /* \346\273\221\345\235\227\350\266\205\345\207\272\346\273\221\346\247\275\347\232\204\350\276\271\350\267\235 */\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"    /* \344\275\277\347\224\250\347\272\277\346\200\247\346\270\220\345\217\230\345\256\236\347\216\260\345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\346\270\220\345\217\230\346\225\210\346\236\234 */\n"
"    background: qlineargradient(\n"
"        spread: pad, /* \345\241\253\345\205\205\346\250\241\345\274\217 */\n"
"        x1: 0, y1: 0, /* \350\265\267\347\202\271\344\275\215\347\275\256 */\n"
"        x2: 1, y2: 0, /* \347\273\210\347\202\271\344\275\215\347\275\256\357\274\210\346\260\264\345\271\263\346\270\220\345\217\230\357\274\211 */\n"
"        stop: 0 #FC3D49, /* \350\265\267\345\247\213\351\242\234\350\211\262 */\n"
"        stop: 1 #fc9c9e /* \347\273\223"
                        "\346\235\237\351\242\234\350\211\262 */\n"
"    );\n"
"    /*border: 1px solid #FC3D49; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    height: 8px; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"    background: #ccc; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 1px solid #bbb; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    height: 8px; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \346\234\252\351\200"
                        "\232\350\277\207\351\203\250\345\210\206\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
""));
        processBar->setOrientation(Qt::Horizontal);
        songName = new QLabel(widget_2);
        songName->setObjectName(QString::fromUtf8("songName"));
        songName->setGeometry(QRect(80, 20, 180, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI Light"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        songName->setFont(font1);
        currentTime = new QLabel(widget_2);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(310, 50, 61, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
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
        soundBar->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"    border: 1px solid #bbb; /* \346\273\221\346\247\275\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    background: #ccc; /* \346\273\221\346\247\275\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    height: 8px; /* \346\273\221\346\247\275\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \346\273\221\346\247\275\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
" \n"
"QSlider::handle:horizontal {\n"
"    background: #FC3D49; /* \346\273\221\345\235\227\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 1px solid #FC3D49; /* \346\273\221\345\235\227\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    width: 18px; /* \346\273\221\345\235\227\347\232\204\345\256\275\345\272\246 */\n"
"    height: 18px; /* \346\273\221\345\235\227\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 9px; /* \346\273\221\345\235\227\347\232\204\345\234\206\350"
                        "\247\222\345\215\212\345\276\204\357\274\214\347\241\256\344\277\235\346\273\221\345\235\227\346\230\257\345\234\206\345\275\242 */\n"
"    margin: -6px 0; /* \346\273\221\345\235\227\350\266\205\345\207\272\346\273\221\346\247\275\347\232\204\350\276\271\350\267\235 */\n"
"}\n"
" \n"
"QSlider::sub-page:horizontal {\n"
"    /* \344\275\277\347\224\250\347\272\277\346\200\247\346\270\220\345\217\230\345\256\236\347\216\260\345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\346\270\220\345\217\230\346\225\210\346\236\234 */\n"
"    background: qlineargradient(\n"
"        spread: pad, /* \345\241\253\345\205\205\346\250\241\345\274\217 */\n"
"        x1: 0, y1: 0, /* \350\265\267\347\202\271\344\275\215\347\275\256 */\n"
"        x2: 1, y2: 0, /* \347\273\210\347\202\271\344\275\215\347\275\256\357\274\210\346\260\264\345\271\263\346\270\220\345\217\230\357\274\211 */\n"
"        stop: 0 #FC3D49, /* \350\265\267\345\247\213\351\242\234\350\211\262 */\n"
"        stop: 1 #fc9c9e /* \347\273\223"
                        "\346\235\237\351\242\234\350\211\262 */\n"
"    );\n"
"    /*border: 1px solid #FC3D49; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    height: 8px; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \345\267\262\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
" \n"
"QSlider::add-page:horizontal {\n"
"    background: #ccc; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border: 1px solid #bbb; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    height: 8px; /* \346\234\252\351\200\232\350\277\207\351\203\250\345\210\206\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 4px; /* \346\234\252\351\200"
                        "\232\350\277\207\351\203\250\345\210\206\347\232\204\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}"));
        soundBar->setValue(99);
        soundBar->setOrientation(Qt::Horizontal);
        soundBtn = new QPushButton(widget_3);
        soundBtn->setObjectName(QString::fromUtf8("soundBtn"));
        soundBtn->setGeometry(QRect(10, 30, 30, 30));

        horizontalLayout_3->addWidget(widget_3);

        musicList = new QListWidget(Widget);
        musicList->setObjectName(QString::fromUtf8("musicList"));
        musicList->setGeometry(QRect(1190, 260, 241, 521));
        sizePolicy.setHeightForWidth(musicList->sizePolicy().hasHeightForWidth());
        musicList->setSizePolicy(sizePolicy);
        musicList->setMinimumSize(QSize(200, 150));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        musicList->setFont(font3);
        musicList->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256 QListWidget \347\232\204\346\225\264\344\275\223\345\244\226\350\247\202\357\274\214\345\234\206\350\247\222\345\222\214\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"QListWidget {\n"
"    border: 1px solid #ccc;\n"
"    border-radius: 10px; /* \345\234\206\350\247\222 */\n"
"    background-color: #f9f9f9; /* \350\203\214\346\231\257\350\211\262 */\n"
"    padding: 5px;\n"
"	outline:0px;\n"
"}\n"
"\n"
"/* \350\256\276\347\275\256 QListWidget \344\270\255\346\257\217\344\270\252\351\200\211\351\241\271\347\232\204\351\273\230\350\256\244\345\244\226\350\247\202 */\n"
"QListWidget::item {\n"
"    border: 1px solid transparent;\n"
"    border-radius: 5px; /* \345\234\206\350\247\222 */\n"
"    background-color: #ffffff; /* \351\273\230\350\256\244\351\200\211\351\241\271\350\203\214\346\231\257\350\211\262 */\n"
"    padding: 8px;\n"
"    margin: 3px; /* \346\257\217\344\270\252\351\200\211\351\241\271\347\232\204\351\227\264\350\267\235 */\n"
"    color: #333; /* \345\255\227"
                        "\344\275\223\351\242\234\350\211\262 */\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\347\232\204\346\225\210\346\236\234 */\n"
"QListWidget::item:hover {\n"
"    background-color: #ffe6e8; /* \346\202\254\345\201\234\350\203\214\346\231\257\350\211\262 */\n"
"    /*border: 1px solid #91d5ff; /* \346\202\254\345\201\234\346\227\266\347\232\204\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"/* \351\200\211\344\270\255\347\212\266\346\200\201\347\232\204\346\225\210\346\236\234 */\n"
"QListWidget::item:selected {\n"
"    background-color: #FC3D49; /* \351\200\211\344\270\255\350\203\214\346\231\257\350\211\262 */\n"
"    /*border: 1px solid #69c0ff; /* \351\200\211\344\270\255\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    color: #ffffff; /* \351\200\211\344\270\255\346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"\n"
"/* \350\207\252\345\256\232\344\271\211\346\273\221\345\212\250\346\235\241\347\232\204\346"
                        "\240\267\345\274\217 */\n"
"QScrollBar:vertical {\n"
"    border: none; /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"    background: #f0f0f0; /* \346\273\221\345\212\250\346\235\241\350\203\214\346\231\257\350\211\262 */\n"
"    width: 8px; /* \350\256\276\347\275\256\346\273\221\345\212\250\346\235\241\345\256\275\345\272\246 */\n"
"    margin: 0px 0px 0px 0px; /* \346\273\221\345\212\250\346\235\241\344\270\212\344\270\213\347\232\204\350\276\271\350\267\235 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #bfbfbf; /* \346\273\221\345\235\227\351\242\234\350\211\262 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"    min-height: 20px; /* \346\273\221\345\235\227\347\232\204\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #a6a6a6; /* \346\202\254\345\201\234\346\227\266\346\273\221"
                        "\345\235\227\347\232\204\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    background: none; /* \351\232\220\350\227\217\346\273\221\345\212\250\346\235\241\344\270\212\344\270\213\347\232\204\346\214\211\351\222\256 */\n"
"    height: 0px; /* \347\247\273\351\231\244\346\214\211\351\222\256\351\253\230\345\272\246 */\n"
"    width: 0px;\n"
"}\n"
"\n"
"/* \351\230\262\346\255\242\346\273\221\345\235\227\350\266\205\345\207\272\350\214\203\345\233\264 */\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
""));
        PostWidget = new RotateWidget(Widget);
        PostWidget->setObjectName(QString::fromUtf8("PostWidget"));
        PostWidget->setGeometry(QRect(370, 340, 300, 300));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(PostWidget->sizePolicy().hasHeightForWidth());
        PostWidget->setSizePolicy(sizePolicy1);
        PostWidget->setMinimumSize(QSize(300, 300));
        widget_4 = new QWidget(Widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(760, 310, 276, 370));
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
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setUnderline(false);
        font4.setWeight(75);
        lyricLabel_3->setFont(font4);
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
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
