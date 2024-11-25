/********************************************************************************
** Form generated from reading UI file 'loginsignup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSIGNUP_H
#define UI_LOGINSIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginSignUp
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLabel *label_Head;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit_UserName;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit_Passwd;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Login;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Register;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QWidget *loginSignUp)
    {
        if (loginSignUp->objectName().isEmpty())
            loginSignUp->setObjectName(QString::fromUtf8("loginSignUp"));
        loginSignUp->resize(480, 720);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginSignUp->sizePolicy().hasHeightForWidth());
        loginSignUp->setSizePolicy(sizePolicy);
        loginSignUp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        layoutWidget = new QWidget(loginSignUp);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 30, 302, 659));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(layoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(300, 176));
        widget->setMaximumSize(QSize(300, 176));
        label_Head = new QLabel(widget);
        label_Head->setObjectName(QString::fromUtf8("label_Head"));
        label_Head->setGeometry(QRect(75, 13, 150, 150));
        label_Head->setMinimumSize(QSize(150, 150));
        label_Head->setMaximumSize(QSize(150, 150));
        label_Head->setStyleSheet(QString::fromUtf8("background-color: rgb(205, 205, 205);\n"
"border-radius: 75px;"));

        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(20, 35, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        lineEdit_UserName = new QLineEdit(layoutWidget);
        lineEdit_UserName->setObjectName(QString::fromUtf8("lineEdit_UserName"));
        lineEdit_UserName->setMinimumSize(QSize(300, 60));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        lineEdit_UserName->setFont(font);
        lineEdit_UserName->setFocusPolicy(Qt::ClickFocus);
        lineEdit_UserName->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 3px solid #6a6a6a; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\222\214\345\256\275\345\272\246 */\n"
"    border-radius: 15px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    background-color: #f2f2f2; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    font-size: 21px; /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #f71d57; /* \350\201\232\347\204\246\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    background-color: #ffffff; /* \350\201\232\347\204\246\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}"));

        verticalLayout->addWidget(lineEdit_UserName);

        verticalSpacer_2 = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        lineEdit_Passwd = new QLineEdit(layoutWidget);
        lineEdit_Passwd->setObjectName(QString::fromUtf8("lineEdit_Passwd"));
        lineEdit_Passwd->setMinimumSize(QSize(300, 60));
        lineEdit_Passwd->setFont(font);
        lineEdit_Passwd->setFocusPolicy(Qt::ClickFocus);
        lineEdit_Passwd->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: 3px solid #6a6a6a; /* \350\276\271\346\241\206\351\242\234\350\211\262\345\222\214\345\256\275\345\272\246 */\n"
"    border-radius: 15px; /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 5px; /* \345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\346\226\207\346\234\254\347\264\247\350\264\264\350\276\271\346\241\206 */\n"
"    background-color: #f2f2f2; /* \350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"    font-size: 21px; /* \345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #f71d57; /* \350\201\232\347\204\246\346\227\266\350\276\271\346\241\206\351\242\234\350\211\262 */\n"
"    background-color: #ffffff; /* \350\201\232\347\204\246\346\227\266\350\203\214\346\231\257\351\242\234\350\211\262 */\n"
"}\n"
""));
        lineEdit_Passwd->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEdit_Passwd);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_Login = new QPushButton(layoutWidget);
        pushButton_Login->setObjectName(QString::fromUtf8("pushButton_Login"));
        pushButton_Login->setMinimumSize(QSize(180, 60));
        pushButton_Login->setMaximumSize(QSize(250, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setBold(true);
        font1.setWeight(75);
        pushButton_Login->setFont(font1);
        pushButton_Login->setFocusPolicy(Qt::ClickFocus);
        pushButton_Login->setStyleSheet(QString::fromUtf8("QPushButton\n"
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

        horizontalLayout->addWidget(pushButton_Login);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 25, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton_Register = new QPushButton(layoutWidget);
        pushButton_Register->setObjectName(QString::fromUtf8("pushButton_Register"));
        pushButton_Register->setMinimumSize(QSize(180, 60));
        pushButton_Register->setMaximumSize(QSize(250, 16777215));
        pushButton_Register->setFont(font1);
        pushButton_Register->setStyleSheet(QString::fromUtf8("QPushButton\n"
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
"}"));

        horizontalLayout_2->addWidget(pushButton_Register);

        horizontalSpacer_6 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(loginSignUp);

        QMetaObject::connectSlotsByName(loginSignUp);
    } // setupUi

    void retranslateUi(QWidget *loginSignUp)
    {
        loginSignUp->setWindowTitle(QApplication::translate("loginSignUp", "loginSignUp", nullptr));
        label_Head->setText(QString());
        lineEdit_UserName->setText(QString());
        lineEdit_Passwd->setText(QString());
        pushButton_Login->setText(QApplication::translate("loginSignUp", "\347\231\273\345\275\225", nullptr));
        pushButton_Register->setText(QApplication::translate("loginSignUp", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginSignUp: public Ui_loginSignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSIGNUP_H
