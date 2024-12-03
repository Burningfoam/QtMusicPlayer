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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <rotatewidget.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *currentLyric;
    QStackedWidget *stackedWidget;
    QWidget *page_music;
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
    QLabel *lyricLabel_8;
    QLabel *lyricLabel_9;
    QWidget *page_home;
    QLabel *label_enter_hotlist;
    QLabel *label_enter_newlist;
    QLabel *label_enter_uplist;
    QLabel *label_enter_goldlist;
    QLabel *label_enter_jaylist;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *page_search;
    QListWidget *listWidget_search;
    QLabel *label_searchTitle;
    QWidget *page_love;
    QLabel *label_likeCover;
    QLabel *label_likeTitle;
    QPushButton *pushButton_likePlay;
    QListWidget *listWidget_like;
    QWidget *page_list;
    QLabel *label_listCover;
    QLabel *label_listTitle;
    QPushButton *pushButton_listPlay;
    QListWidget *listWidget_list;
    QWidget *page_download;
    QWidget *page_local;
    QPushButton *pushButton_page_music;
    QPushButton *pushButton_page_home;
    QPushButton *pushButton_page_love;
    QPushButton *pushButton_page_download;
    QPushButton *pushButton_page_local;
    QPushButton *pushButton_login;
    QToolButton *toolButton_playlist;
    QToolButton *toolButton_settings;
    QToolButton *toolButton_like;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prevBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *playerBtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *nextBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *modeBtn;
    QWidget *widget_2;
    QLabel *albumPic;
    QSlider *processBar;
    QLabel *songName;
    QLabel *currentTime;
    QLabel *totalTime;
    QWidget *widget_3;
    QSlider *soundBar;
    QPushButton *soundBtn;
    QToolButton *toolButton_back;
    QLabel *label_headimg;
    QLabel *label_username;
    QLineEdit *lineEdit_search;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1500, 1068);
        currentLyric = new QLabel(Widget);
        currentLyric->setObjectName(QString::fromUtf8("currentLyric"));
        currentLyric->setGeometry(QRect(320, 920, 421, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(8);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        currentLyric->setFont(font);
        currentLyric->setAlignment(Qt::AlignCenter);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(292, 80, 1200, 850));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page_music = new QWidget();
        page_music->setObjectName(QString::fromUtf8("page_music"));
        PostWidget = new RotateWidget(page_music);
        PostWidget->setObjectName(QString::fromUtf8("PostWidget"));
        PostWidget->setGeometry(QRect(150, 220, 400, 400));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PostWidget->sizePolicy().hasHeightForWidth());
        PostWidget->setSizePolicy(sizePolicy);
        PostWidget->setMinimumSize(QSize(400, 400));
        widget_4 = new QWidget(page_music);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(673, 130, 461, 671));
        verticalLayout = new QVBoxLayout(widget_4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lyricLabel_1 = new QLabel(widget_4);
        lyricLabel_1->setObjectName(QString::fromUtf8("lyricLabel_1"));
        lyricLabel_1->setMinimumSize(QSize(200, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font1.setPointSize(13);
        font1.setStyleStrategy(QFont::PreferAntialias);
        lyricLabel_1->setFont(font1);
        lyricLabel_1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_1->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_1);

        lyricLabel_2 = new QLabel(widget_4);
        lyricLabel_2->setObjectName(QString::fromUtf8("lyricLabel_2"));
        lyricLabel_2->setMinimumSize(QSize(200, 40));
        lyricLabel_2->setFont(font1);
        lyricLabel_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_2->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_2);

        lyricLabel_3 = new QLabel(widget_4);
        lyricLabel_3->setObjectName(QString::fromUtf8("lyricLabel_3"));
        lyricLabel_3->setMinimumSize(QSize(250, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        lyricLabel_3->setFont(font2);
        lyricLabel_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_3->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_3);

        lyricLabel_4 = new QLabel(widget_4);
        lyricLabel_4->setObjectName(QString::fromUtf8("lyricLabel_4"));
        lyricLabel_4->setMinimumSize(QSize(200, 40));
        lyricLabel_4->setFont(font1);
        lyricLabel_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_4->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_4);

        lyricLabel_5 = new QLabel(widget_4);
        lyricLabel_5->setObjectName(QString::fromUtf8("lyricLabel_5"));
        lyricLabel_5->setMinimumSize(QSize(200, 40));
        lyricLabel_5->setFont(font1);
        lyricLabel_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_5->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_5);

        lyricLabel_6 = new QLabel(widget_4);
        lyricLabel_6->setObjectName(QString::fromUtf8("lyricLabel_6"));
        lyricLabel_6->setMinimumSize(QSize(200, 40));
        lyricLabel_6->setFont(font1);
        lyricLabel_6->setStyleSheet(QString::fromUtf8(""));
        lyricLabel_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_6->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_6);

        lyricLabel_7 = new QLabel(widget_4);
        lyricLabel_7->setObjectName(QString::fromUtf8("lyricLabel_7"));
        lyricLabel_7->setMinimumSize(QSize(200, 40));
        lyricLabel_7->setFont(font1);
        lyricLabel_7->setStyleSheet(QString::fromUtf8(""));
        lyricLabel_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_7->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_7);

        lyricLabel_8 = new QLabel(widget_4);
        lyricLabel_8->setObjectName(QString::fromUtf8("lyricLabel_8"));
        lyricLabel_8->setMinimumSize(QSize(200, 40));
        lyricLabel_8->setFont(font1);
        lyricLabel_8->setStyleSheet(QString::fromUtf8(""));
        lyricLabel_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_8->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_8);

        lyricLabel_9 = new QLabel(widget_4);
        lyricLabel_9->setObjectName(QString::fromUtf8("lyricLabel_9"));
        lyricLabel_9->setMinimumSize(QSize(200, 40));
        lyricLabel_9->setFont(font1);
        lyricLabel_9->setStyleSheet(QString::fromUtf8(""));
        lyricLabel_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lyricLabel_9->setWordWrap(true);

        verticalLayout->addWidget(lyricLabel_9);

        stackedWidget->addWidget(page_music);
        page_home = new QWidget();
        page_home->setObjectName(QString::fromUtf8("page_home"));
        label_enter_hotlist = new QLabel(page_home);
        label_enter_hotlist->setObjectName(QString::fromUtf8("label_enter_hotlist"));
        label_enter_hotlist->setGeometry(QRect(60, 80, 280, 280));
        label_enter_hotlist->setMouseTracking(true);
        label_enter_hotlist->setStyleSheet(QString::fromUtf8(""));
        label_enter_newlist = new QLabel(page_home);
        label_enter_newlist->setObjectName(QString::fromUtf8("label_enter_newlist"));
        label_enter_newlist->setGeometry(QRect(440, 80, 280, 280));
        label_enter_newlist->setStyleSheet(QString::fromUtf8(""));
        label_enter_uplist = new QLabel(page_home);
        label_enter_uplist->setObjectName(QString::fromUtf8("label_enter_uplist"));
        label_enter_uplist->setGeometry(QRect(830, 80, 280, 280));
        label_enter_uplist->setStyleSheet(QString::fromUtf8(""));
        label_enter_goldlist = new QLabel(page_home);
        label_enter_goldlist->setObjectName(QString::fromUtf8("label_enter_goldlist"));
        label_enter_goldlist->setGeometry(QRect(60, 460, 280, 280));
        label_enter_goldlist->setStyleSheet(QString::fromUtf8(""));
        label_enter_jaylist = new QLabel(page_home);
        label_enter_jaylist->setObjectName(QString::fromUtf8("label_enter_jaylist"));
        label_enter_jaylist->setGeometry(QRect(440, 460, 280, 280));
        label_enter_jaylist->setStyleSheet(QString::fromUtf8(""));
        label_6 = new QLabel(page_home);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 20, 261, 50));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font3.setPointSize(15);
        font3.setBold(true);
        font3.setWeight(75);
        label_6->setFont(font3);
        label_7 = new QLabel(page_home);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(130, 370, 130, 50));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font4.setPointSize(11);
        label_7->setFont(font4);
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(page_home);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(520, 370, 130, 50));
        label_8->setFont(font4);
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(page_home);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(910, 370, 130, 50));
        label_9->setFont(font4);
        label_9->setAlignment(Qt::AlignCenter);
        label_10 = new QLabel(page_home);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(130, 750, 130, 50));
        label_10->setFont(font4);
        label_10->setAlignment(Qt::AlignCenter);
        label_11 = new QLabel(page_home);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(520, 750, 130, 50));
        label_11->setFont(font4);
        label_11->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page_home);
        page_search = new QWidget();
        page_search->setObjectName(QString::fromUtf8("page_search"));
        listWidget_search = new QListWidget(page_search);
        listWidget_search->setObjectName(QString::fromUtf8("listWidget_search"));
        listWidget_search->setGeometry(QRect(30, 85, 1138, 735));
        listWidget_search->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: transparent; /* \350\256\276\347\275\256QListWidget\347\232\204\350\203\214\346\231\257\344\270\272\351\200\217\346\230\216 */\n"
"    border: none; /* \344\270\215\346\230\276\347\244\272\350\276\271\346\241\206 */\n"
"    border-radius: 10px; /* \346\225\264\344\275\223\345\234\206\350\247\222 */\n"
"	outline:0px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    /*height: 150px; /* \350\256\276\347\275\256\346\257\217\344\270\200\351\241\271\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 10px; /* \346\257\217\344\270\200\351\241\271\344\271\237\350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    /*padding: 10px; /* \350\256\276\347\275\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    /*background-color: #4CAF50; /* \351\200\211\344\270\255\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    /*color: white; /* \351\200\211\344\270\255\351\241\271\347\232\204\346\226\207\345\255\227"
                        "\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #f0f0f0; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 10px; /* \344\277\235\346\214\201\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"/* \350\207\252\345\256\232\344\271\211\346\273\221\345\212\250\346\235\241\347\232\204\346\240\267\345\274\217 */\n"
"QScrollBar:vertical {\n"
"    border: none; /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"    background: #f0f0f0; /* \346\273\221\345\212\250\346\235\241\350\203\214\346\231\257\350\211\262 */\n"
"    width: 8px; /* \350\256\276\347\275\256\346\273\221\345\212\250\346\235\241\345\256\275\345\272\246 */\n"
"    margin: 0px 0px 0px 0px; /* \346\273\221\345\212\250\346\235\241\344\270\212\344\270\213\347\232\204\350\276\271\350\267\235 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QScrollBar::"
                        "handle:vertical {\n"
"    background: #bfbfbf; /* \346\273\221\345\235\227\351\242\234\350\211\262 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"    min-height: 20px; /* \346\273\221\345\235\227\347\232\204\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #a6a6a6; /* \346\202\254\345\201\234\346\227\266\346\273\221\345\235\227\347\232\204\351\242\234\350\211\262 */\n"
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
""
                        "    background: none;\n"
"}\n"
""));
        label_searchTitle = new QLabel(page_search);
        label_searchTitle->setObjectName(QString::fromUtf8("label_searchTitle"));
        label_searchTitle->setGeometry(QRect(40, 20, 1071, 61));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setWeight(75);
        label_searchTitle->setFont(font5);
        stackedWidget->addWidget(page_search);
        page_love = new QWidget();
        page_love->setObjectName(QString::fromUtf8("page_love"));
        label_likeCover = new QLabel(page_love);
        label_likeCover->setObjectName(QString::fromUtf8("label_likeCover"));
        label_likeCover->setGeometry(QRect(60, 40, 300, 300));
        label_likeCover->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_likeTitle = new QLabel(page_love);
        label_likeTitle->setObjectName(QString::fromUtf8("label_likeTitle"));
        label_likeTitle->setGeometry(QRect(400, 40, 300, 60));
        label_likeTitle->setFont(font3);
        label_likeTitle->setStyleSheet(QString::fromUtf8(""));
        pushButton_likePlay = new QPushButton(page_love);
        pushButton_likePlay->setObjectName(QString::fromUtf8("pushButton_likePlay"));
        pushButton_likePlay->setGeometry(QRect(400, 270, 160, 70));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        pushButton_likePlay->setFont(font6);
        pushButton_likePlay->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius: 15px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    background-color: #FC3D49; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    font-size: 23px; /* \345\255\227\344\275\223\345\244\247\345\260\217*/\n"
"	color: #ffffff;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"    background-color: #e63742; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
"\n"
""));
        listWidget_like = new QListWidget(page_love);
        listWidget_like->setObjectName(QString::fromUtf8("listWidget_like"));
        listWidget_like->setGeometry(QRect(40, 369, 1135, 441));
        listWidget_like->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: transparent; /* \350\256\276\347\275\256QListWidget\347\232\204\350\203\214\346\231\257\344\270\272\351\200\217\346\230\216 */\n"
"    border: none; /* \344\270\215\346\230\276\347\244\272\350\276\271\346\241\206 */\n"
"    border-radius: 10px; /* \346\225\264\344\275\223\345\234\206\350\247\222 */\n"
"	outline:0px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    /*height: 150px; /* \350\256\276\347\275\256\346\257\217\344\270\200\351\241\271\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 10px; /* \346\257\217\344\270\200\351\241\271\344\271\237\350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    /*padding: 10px; /* \350\256\276\347\275\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    /*background-color: #4CAF50; /* \351\200\211\344\270\255\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    /*color: white; /* \351\200\211\344\270\255\351\241\271\347\232\204\346\226\207\345\255\227"
                        "\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #f0f0f0; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 10px; /* \344\277\235\346\214\201\345\234\206\350\247\222 */\n"
"}\n"
""));
        stackedWidget->addWidget(page_love);
        page_list = new QWidget();
        page_list->setObjectName(QString::fromUtf8("page_list"));
        label_listCover = new QLabel(page_list);
        label_listCover->setObjectName(QString::fromUtf8("label_listCover"));
        label_listCover->setGeometry(QRect(60, 40, 300, 300));
        label_listCover->setStyleSheet(QString::fromUtf8(""));
        label_listTitle = new QLabel(page_list);
        label_listTitle->setObjectName(QString::fromUtf8("label_listTitle"));
        label_listTitle->setGeometry(QRect(400, 40, 300, 60));
        label_listTitle->setFont(font3);
        label_listTitle->setStyleSheet(QString::fromUtf8(""));
        label_listTitle->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        pushButton_listPlay = new QPushButton(page_list);
        pushButton_listPlay->setObjectName(QString::fromUtf8("pushButton_listPlay"));
        pushButton_listPlay->setGeometry(QRect(400, 270, 160, 70));
        pushButton_listPlay->setFont(font6);
        pushButton_listPlay->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius: 15px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    background-color: #FC3D49; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    font-size: 23px; /* \345\255\227\344\275\223\345\244\247\345\260\217*/\n"
"	color: #ffffff;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"    background-color: #e63742; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
"\n"
""));
        listWidget_list = new QListWidget(page_list);
        listWidget_list->setObjectName(QString::fromUtf8("listWidget_list"));
        listWidget_list->setGeometry(QRect(40, 369, 1138, 465));
        listWidget_list->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: transparent; /* \350\256\276\347\275\256QListWidget\347\232\204\350\203\214\346\231\257\344\270\272\351\200\217\346\230\216 */\n"
"    border: none; /* \344\270\215\346\230\276\347\244\272\350\276\271\346\241\206 */\n"
"    border-radius: 10px; /* \346\225\264\344\275\223\345\234\206\350\247\222 */\n"
"	outline:0px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    /*height: 150px; /* \350\256\276\347\275\256\346\257\217\344\270\200\351\241\271\347\232\204\351\253\230\345\272\246 */\n"
"    border-radius: 10px; /* \346\257\217\344\270\200\351\241\271\344\271\237\350\256\276\347\275\256\345\234\206\350\247\222 */\n"
"    /*padding: 10px; /* \350\256\276\347\275\256\345\206\205\350\276\271\350\267\235 */\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    /*background-color: #4CAF50; /* \351\200\211\344\270\255\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    /*color: white; /* \351\200\211\344\270\255\351\241\271\347\232\204\346\226\207\345\255\227"
                        "\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #f0f0f0; /* \351\274\240\346\240\207\346\202\254\345\201\234\346\227\266\351\241\271\347\232\204\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    border-radius: 10px; /* \344\277\235\346\214\201\345\234\206\350\247\222 */\n"
"}\n"
"\n"
"/* \350\207\252\345\256\232\344\271\211\346\273\221\345\212\250\346\235\241\347\232\204\346\240\267\345\274\217 */\n"
"QScrollBar:vertical {\n"
"    border: none; /* \347\247\273\351\231\244\350\276\271\346\241\206 */\n"
"    background: #f0f0f0; /* \346\273\221\345\212\250\346\235\241\350\203\214\346\231\257\350\211\262 */\n"
"    width: 8px; /* \350\256\276\347\275\256\346\273\221\345\212\250\346\235\241\345\256\275\345\272\246 */\n"
"    margin: 0px 0px 0px 0px; /* \346\273\221\345\212\250\346\235\241\344\270\212\344\270\213\347\232\204\350\276\271\350\267\235 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"}\n"
"\n"
"QScrollBar::"
                        "handle:vertical {\n"
"    background: #bfbfbf; /* \346\273\221\345\235\227\351\242\234\350\211\262 */\n"
"    border-radius: 4px; /* \345\234\206\350\247\222\346\225\210\346\236\234 */\n"
"    min-height: 20px; /* \346\273\221\345\235\227\347\232\204\346\234\200\345\260\217\351\253\230\345\272\246 */\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #a6a6a6; /* \346\202\254\345\201\234\346\227\266\346\273\221\345\235\227\347\232\204\351\242\234\350\211\262 */\n"
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
""
                        "    background: none;\n"
"}\n"
""));
        stackedWidget->addWidget(page_list);
        page_download = new QWidget();
        page_download->setObjectName(QString::fromUtf8("page_download"));
        stackedWidget->addWidget(page_download);
        page_local = new QWidget();
        page_local->setObjectName(QString::fromUtf8("page_local"));
        stackedWidget->addWidget(page_local);
        pushButton_page_music = new QPushButton(Widget);
        pushButton_page_music->setObjectName(QString::fromUtf8("pushButton_page_music"));
        pushButton_page_music->setGeometry(QRect(38, 190, 222, 48));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font7.setBold(true);
        font7.setWeight(75);
        pushButton_page_music->setFont(font7);
        pushButton_page_music->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 10px;\n"
"	text-align: left; padding-left: 10px;\n"
"    color: #757c8a;\n"
"	font-size: 19px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(169, 169, 169, 0.5);  /* \347\201\260\350\211\262\346\217\220\347\244\272 */\n"
"}\n"
""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/page_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_page_music->setIcon(icon);
        pushButton_page_music->setIconSize(QSize(34, 34));
        pushButton_page_home = new QPushButton(Widget);
        pushButton_page_home->setObjectName(QString::fromUtf8("pushButton_page_home"));
        pushButton_page_home->setGeometry(QRect(38, 141, 222, 48));
        pushButton_page_home->setFont(font7);
        pushButton_page_home->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 10px;\n"
"    /*padding: 10px 15px;*/\n"
"	color: #757c8a;\n"
"	font-size: 19px;\n"
"	text-align: left; padding-left: 10px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(169, 169, 169, 0.5);  /* \347\201\260\350\211\262\346\217\220\347\244\272 */\n"
"}\n"
"\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/page_home.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_page_home->setIcon(icon1);
        pushButton_page_home->setIconSize(QSize(34, 34));
        pushButton_page_love = new QPushButton(Widget);
        pushButton_page_love->setObjectName(QString::fromUtf8("pushButton_page_love"));
        pushButton_page_love->setGeometry(QRect(36, 507, 222, 48));
        pushButton_page_love->setFont(font7);
        pushButton_page_love->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 10px;\n"
"   	text-align: left; padding-left: 10px;\n"
"    color: #757c8a;\n"
"	font-size: 19px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(169, 169, 169, 0.5);  /* \347\201\260\350\211\262\346\217\220\347\244\272 */\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img/list_love.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_page_love->setIcon(icon2);
        pushButton_page_love->setIconSize(QSize(30, 30));
        pushButton_page_download = new QPushButton(Widget);
        pushButton_page_download->setObjectName(QString::fromUtf8("pushButton_page_download"));
        pushButton_page_download->setGeometry(QRect(36, 727, 222, 48));
        pushButton_page_download->setFont(font7);
        pushButton_page_download->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 10px;\n"
"    text-align: left; padding-left: 10px;\n"
"    color: #757c8a;\n"
"	font-size: 19px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(169, 169, 169, 0.5);  /* \347\201\260\350\211\262\346\217\220\347\244\272 */\n"
"}\n"
""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/img/list_download.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_page_download->setIcon(icon3);
        pushButton_page_download->setIconSize(QSize(34, 34));
        pushButton_page_local = new QPushButton(Widget);
        pushButton_page_local->setObjectName(QString::fromUtf8("pushButton_page_local"));
        pushButton_page_local->setGeometry(QRect(36, 779, 222, 48));
        pushButton_page_local->setFont(font7);
        pushButton_page_local->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: transparent;\n"
"    border: 2px solid transparent;\n"
"    border-radius: 10px;\n"
"    text-align: left; padding-left: 10px;\n"
"    color: #757c8a;\n"
"	font-size: 19px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgba(169, 169, 169, 0.5);  /* \347\201\260\350\211\262\346\217\220\347\244\272 */\n"
"}\n"
""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/img/list_local.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_page_local->setIcon(icon4);
        pushButton_page_local->setIconSize(QSize(34, 34));
        pushButton_login = new QPushButton(Widget);
        pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));
        pushButton_login->setGeometry(QRect(1220, 30, 110, 50));
        pushButton_login->setFont(font6);
        pushButton_login->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"    border-radius: 15px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    background-color: #FC3D49; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    font-size: 23px; /* \345\255\227\344\275\223\345\244\247\345\260\217*/\n"
"	color: #ffffff;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"    background-color: #e63742; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
"\n"
""));
        toolButton_playlist = new QToolButton(Widget);
        toolButton_playlist->setObjectName(QString::fromUtf8("toolButton_playlist"));
        toolButton_playlist->setGeometry(QRect(1410, 985, 50, 50));
        toolButton_playlist->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,0);"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/img/icon_playlist.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_playlist->setIcon(icon5);
        toolButton_playlist->setIconSize(QSize(50, 50));
        toolButton_settings = new QToolButton(Widget);
        toolButton_settings->setObjectName(QString::fromUtf8("toolButton_settings"));
        toolButton_settings->setGeometry(QRect(1432, 35, 40, 40));
        toolButton_settings->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	background-color:rgba(255,255,255,0);\n"
"}\n"
"\n"
"QToolButton::menu-indicator\n"
"{\n"
"     /* \350\257\245\344\273\243\347\240\201\347\224\250\344\272\216\350\256\276\350\256\241\351\232\220\350\227\217\344\270\211\350\247\222\345\275\242\347\256\255\345\244\264 */\n"
"     width:0px;\n"
"\n"
"}\n"
""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/img/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_settings->setIcon(icon6);
        toolButton_settings->setIconSize(QSize(40, 40));
        toolButton_settings->setArrowType(Qt::NoArrow);
        toolButton_like = new QToolButton(Widget);
        toolButton_like->setObjectName(QString::fromUtf8("toolButton_like"));
        toolButton_like->setGeometry(QRect(1015, 995, 40, 40));
        toolButton_like->setMinimumSize(QSize(40, 40));
        toolButton_like->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,0);"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/img/dislike.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_like->setIcon(icon7);
        toolButton_like->setIconSize(QSize(40, 40));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(80, 970, 415, 91));
        widget->setMinimumSize(QSize(293, 86));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        prevBtn = new QPushButton(widget);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setMinimumSize(QSize(65, 65));
        prevBtn->setMaximumSize(QSize(65, 65));

        horizontalLayout->addWidget(prevBtn);

        horizontalSpacer_3 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        playerBtn = new QPushButton(widget);
        playerBtn->setObjectName(QString::fromUtf8("playerBtn"));
        playerBtn->setMinimumSize(QSize(65, 65));
        playerBtn->setMaximumSize(QSize(65, 65));

        horizontalLayout->addWidget(playerBtn);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        nextBtn = new QPushButton(widget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setMinimumSize(QSize(65, 65));
        nextBtn->setMaximumSize(QSize(65, 65));

        horizontalLayout->addWidget(nextBtn);

        horizontalSpacer = new QSpacerItem(35, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        modeBtn = new QPushButton(widget);
        modeBtn->setObjectName(QString::fromUtf8("modeBtn"));
        modeBtn->setMinimumSize(QSize(65, 65));
        modeBtn->setMaximumSize(QSize(65, 65));

        horizontalLayout->addWidget(modeBtn);

        widget_2 = new QWidget(Widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(520, 959, 485, 101));
        widget_2->setMinimumSize(QSize(461, 101));
        widget_2->setLayoutDirection(Qt::LeftToRight);
        albumPic = new QLabel(widget_2);
        albumPic->setObjectName(QString::fromUtf8("albumPic"));
        albumPic->setGeometry(QRect(10, 10, 85, 85));
        albumPic->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    /*border-radius: 10px;  /* \350\256\276\347\275\256\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    /*padding: 5px;  /* \345\217\257\351\200\211\357\274\214\347\273\231\346\226\207\346\234\254\345\221\250\345\233\264\347\225\231\344\272\233\347\251\272\347\231\275 */\n"
"\n"
"}"));
        processBar = new QSlider(widget_2);
        processBar->setObjectName(QString::fromUtf8("processBar"));
        processBar->setGeometry(QRect(120, 65, 221, 22));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(processBar->sizePolicy().hasHeightForWidth());
        processBar->setSizePolicy(sizePolicy1);
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
        songName->setGeometry(QRect(120, 25, 350, 23));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Microsoft YaHei UI Light"));
        font8.setPointSize(10);
        font8.setBold(true);
        font8.setWeight(75);
        songName->setFont(font8);
        currentTime = new QLabel(widget_2);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(350, 58, 55, 30));
        currentTime->setFont(font7);
        totalTime = new QLabel(widget_2);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(405, 58, 71, 30));
        totalTime->setFont(font7);
        widget_3 = new QWidget(Widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(1180, 962, 221, 80));
        widget_3->setMinimumSize(QSize(181, 80));
        soundBar = new QSlider(widget_3);
        soundBar->setObjectName(QString::fromUtf8("soundBar"));
        soundBar->setGeometry(QRect(70, 40, 111, 22));
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
        soundBtn->setGeometry(QRect(10, 30, 40, 40));
        toolButton_back = new QToolButton(Widget);
        toolButton_back->setObjectName(QString::fromUtf8("toolButton_back"));
        toolButton_back->setGeometry(QRect(330, 25, 50, 50));
        toolButton_back->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,0);"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/img/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_back->setIcon(icon8);
        label_headimg = new QLabel(Widget);
        label_headimg->setObjectName(QString::fromUtf8("label_headimg"));
        label_headimg->setGeometry(QRect(1240, 33, 45, 45));
        label_headimg->setStyleSheet(QString::fromUtf8(""));
        label_username = new QLabel(Widget);
        label_username->setObjectName(QString::fromUtf8("label_username"));
        label_username->setGeometry(QRect(1295, 40, 131, 31));
        label_username->setFont(font6);
        label_username->setStyleSheet(QString::fromUtf8("color: #757c8a;"));
        lineEdit_search = new QLineEdit(Widget);
        lineEdit_search->setObjectName(QString::fromUtf8("lineEdit_search"));
        lineEdit_search->setGeometry(QRect(398, 25, 366, 55));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        lineEdit_search->setFont(font9);
        lineEdit_search->setFocusPolicy(Qt::ClickFocus);
        lineEdit_search->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    /*border: 1px solid #757c8a; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\222\214\345\256\275\345\272\246 */\n"
"	border: 2px solid #D9E6FA; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\222\214\345\256\275\345\272\246 */\n"
"    border-radius: 12px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    /*background-color: #f2f2f2; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"	\n"
"	background-color: rgb(234, 240, 251);\n"
"    font-size: 21px; /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"	/*border: 1px solid; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\222\214\345\256\275\345\272\246 */\n"
"    border-color: #f71d57; /* \350\201\232\347\204\246\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    back"
                        "ground-color: #ffffff; /* \350\201\232\347\204\246\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
"\n"
"QLineEdit::add-action {\n"
"	 height: 55px; width: 55px; \n"
"}"));
        currentLyric->raise();
        stackedWidget->raise();
        pushButton_page_music->raise();
        pushButton_page_home->raise();
        pushButton_page_love->raise();
        pushButton_page_download->raise();
        pushButton_page_local->raise();
        toolButton_playlist->raise();
        toolButton_settings->raise();
        toolButton_like->raise();
        widget->raise();
        widget_2->raise();
        widget_3->raise();
        toolButton_back->raise();
        label_headimg->raise();
        label_username->raise();
        pushButton_login->raise();
        lineEdit_search->raise();

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        currentLyric->setText(QApplication::translate("Widget", "Welcome!", nullptr));
        lyricLabel_1->setText(QString());
        lyricLabel_2->setText(QString());
        lyricLabel_3->setText(QApplication::translate("Widget", "Welcome!", nullptr));
        lyricLabel_4->setText(QString());
        lyricLabel_5->setText(QString());
        lyricLabel_6->setText(QString());
        lyricLabel_7->setText(QString());
        lyricLabel_8->setText(QString());
        lyricLabel_9->setText(QString());
        label_enter_hotlist->setText(QString());
        label_enter_newlist->setText(QString());
        label_enter_uplist->setText(QString());
        label_enter_goldlist->setText(QString());
        label_enter_jaylist->setText(QString());
        label_6->setText(QApplication::translate("Widget", "\346\255\214\345\215\225\345\271\277\345\234\272", nullptr));
        label_7->setText(QApplication::translate("Widget", "\347\203\255\351\227\250\346\255\214\346\233\262\346\246\234", nullptr));
        label_8->setText(QApplication::translate("Widget", "\346\226\260\346\255\214\346\246\234", nullptr));
        label_9->setText(QApplication::translate("Widget", "\351\243\231\345\215\207\346\246\234", nullptr));
        label_10->setText(QApplication::translate("Widget", "\345\215\216\350\257\255\351\207\221\346\233\262", nullptr));
        label_11->setText(QApplication::translate("Widget", "\345\221\250\346\235\260\344\274\246\347\262\276\351\200\211", nullptr));
        label_searchTitle->setText(QString());
        label_likeCover->setText(QApplication::translate("Widget", "\345\226\234\346\254\242\345\210\227\350\241\250\345\260\201\351\235\242", nullptr));
        label_likeTitle->setText(QApplication::translate("Widget", "\346\210\221\345\226\234\346\254\242\347\232\204\351\237\263\344\271\220", nullptr));
        pushButton_likePlay->setText(QApplication::translate("Widget", "\346\222\255\346\224\276", nullptr));
        label_listCover->setText(QString());
        label_listTitle->setText(QApplication::translate("Widget", "\346\210\221\345\226\234\346\254\242\347\232\204\351\237\263\344\271\220-1", nullptr));
        pushButton_listPlay->setText(QApplication::translate("Widget", "\346\222\255\346\224\276", nullptr));
        pushButton_page_music->setText(QApplication::translate("Widget", " \351\237\263\344\271\220", nullptr));
        pushButton_page_home->setText(QApplication::translate("Widget", " \346\216\250\350\215\220", nullptr));
        pushButton_page_love->setText(QApplication::translate("Widget", " \346\210\221\345\226\234\346\254\242\347\232\204\351\237\263\344\271\220", nullptr));
        pushButton_page_download->setText(QApplication::translate("Widget", " \344\270\213\350\275\275\347\256\241\347\220\206", nullptr));
        pushButton_page_local->setText(QApplication::translate("Widget", " \346\234\254\345\234\260\351\237\263\344\271\220", nullptr));
        pushButton_login->setText(QApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        toolButton_playlist->setText(QApplication::translate("Widget", "...", nullptr));
        toolButton_settings->setText(QApplication::translate("Widget", "...", nullptr));
        toolButton_like->setText(QApplication::translate("Widget", "...", nullptr));
        prevBtn->setText(QString());
        playerBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        albumPic->setText(QString());
        songName->setText(QApplication::translate("Widget", "\346\210\221\346\200\200\345\277\265\347\232\204 - \345\255\231\347\207\225\345\247\277", nullptr));
        currentTime->setText(QApplication::translate("Widget", "03:51", nullptr));
        totalTime->setText(QApplication::translate("Widget", "/ 04:50", nullptr));
        soundBtn->setText(QString());
        toolButton_back->setText(QApplication::translate("Widget", "...", nullptr));
        label_headimg->setText(QString());
        label_username->setText(QString());
        lineEdit_search->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
