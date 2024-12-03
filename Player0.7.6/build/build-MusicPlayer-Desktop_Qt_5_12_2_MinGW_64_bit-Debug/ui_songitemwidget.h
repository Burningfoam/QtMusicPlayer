/********************************************************************************
** Form generated from reading UI file 'songitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGITEMWIDGET_H
#define UI_SONGITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SongItemWidget
{
public:
    QLabel *label_number;
    QLabel *label_cover;
    QLabel *label_musicName;
    QLabel *label_artist;
    QLabel *label_album;
    QToolButton *toolButton_delete;

    void setupUi(QWidget *SongItemWidget)
    {
        if (SongItemWidget->objectName().isEmpty())
            SongItemWidget->setObjectName(QString::fromUtf8("SongItemWidget"));
        SongItemWidget->resize(1125, 90);
        SongItemWidget->setStyleSheet(QString::fromUtf8(""));
        label_number = new QLabel(SongItemWidget);
        label_number->setObjectName(QString::fromUtf8("label_number"));
        label_number->setGeometry(QRect(30, 10, 70, 70));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(11);
        label_number->setFont(font);
        label_number->setStyleSheet(QString::fromUtf8(""));
        label_number->setAlignment(Qt::AlignCenter);
        label_cover = new QLabel(SongItemWidget);
        label_cover->setObjectName(QString::fromUtf8("label_cover"));
        label_cover->setGeometry(QRect(150, 10, 70, 70));
        label_cover->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border-radius: 15px;  /* \350\256\276\347\275\256\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"}\n"
""));
        label_musicName = new QLabel(SongItemWidget);
        label_musicName->setObjectName(QString::fromUtf8("label_musicName"));
        label_musicName->setGeometry(QRect(240, 20, 300, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(10);
        label_musicName->setFont(font1);
        label_musicName->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    border-radius: 10px;  /* \350\256\276\347\275\256\345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"\n"
"    padding: 5px;  /* \345\217\257\351\200\211\357\274\214\347\273\231\346\226\207\346\234\254\345\221\250\345\233\264\347\225\231\344\272\233\347\251\272\347\231\275 */\n"
"	\n"
"}"));
        label_artist = new QLabel(SongItemWidget);
        label_artist->setObjectName(QString::fromUtf8("label_artist"));
        label_artist->setGeometry(QRect(570, 20, 100, 50));
        label_artist->setFont(font1);
        label_artist->setStyleSheet(QString::fromUtf8(""));
        label_album = new QLabel(SongItemWidget);
        label_album->setObjectName(QString::fromUtf8("label_album"));
        label_album->setGeometry(QRect(735, 20, 250, 50));
        label_album->setFont(font1);
        label_album->setStyleSheet(QString::fromUtf8(""));
        toolButton_delete = new QToolButton(SongItemWidget);
        toolButton_delete->setObjectName(QString::fromUtf8("toolButton_delete"));
        toolButton_delete->setGeometry(QRect(1050, 25, 40, 40));
        toolButton_delete->setStyleSheet(QString::fromUtf8("background-color: transparent; /* \350\256\276\347\275\256QListWidget\347\232\204\350\203\214\346\231\257\344\270\272\351\200\217\346\230\216 */"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_delete->setIcon(icon);
        toolButton_delete->setIconSize(QSize(30, 30));

        retranslateUi(SongItemWidget);

        QMetaObject::connectSlotsByName(SongItemWidget);
    } // setupUi

    void retranslateUi(QWidget *SongItemWidget)
    {
        SongItemWidget->setWindowTitle(QApplication::translate("SongItemWidget", "Form", nullptr));
        label_number->setText(QApplication::translate("SongItemWidget", "TextLabel", nullptr));
        label_cover->setText(QString());
        label_musicName->setText(QApplication::translate("SongItemWidget", "TextLabel", nullptr));
        label_artist->setText(QApplication::translate("SongItemWidget", "TextLabel", nullptr));
        label_album->setText(QApplication::translate("SongItemWidget", "TextLabel", nullptr));
        toolButton_delete->setText(QApplication::translate("SongItemWidget", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SongItemWidget: public Ui_SongItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGITEMWIDGET_H
