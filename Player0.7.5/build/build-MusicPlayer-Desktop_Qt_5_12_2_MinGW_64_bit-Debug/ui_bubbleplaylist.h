/********************************************************************************
** Form generated from reading UI file 'bubbleplaylist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUBBLEPLAYLIST_H
#define UI_BUBBLEPLAYLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bubblePlayList
{
public:
    QListWidget *listWidget;

    void setupUi(QWidget *bubblePlayList)
    {
        if (bubblePlayList->objectName().isEmpty())
            bubblePlayList->setObjectName(QString::fromUtf8("bubblePlayList"));
        bubblePlayList->resize(380, 500);
        listWidget = new QListWidget(bubblePlayList);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 380, 500));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        listWidget->setFont(font);
        listWidget->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256 QListWidget \347\232\204\346\225\264\344\275\223\345\244\226\350\247\202\357\274\214\345\234\206\350\247\222\345\222\214\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
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
"}"));

        retranslateUi(bubblePlayList);

        QMetaObject::connectSlotsByName(bubblePlayList);
    } // setupUi

    void retranslateUi(QWidget *bubblePlayList)
    {
        bubblePlayList->setWindowTitle(QApplication::translate("bubblePlayList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bubblePlayList: public Ui_bubblePlayList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUBBLEPLAYLIST_H
