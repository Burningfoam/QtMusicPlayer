/********************************************************************************
** Form generated from reading UI file 'rotatewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTATEWIDGET_H
#define UI_ROTATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RotateWidget
{
public:

    void setupUi(QWidget *RotateWidget)
    {
        if (RotateWidget->objectName().isEmpty())
            RotateWidget->setObjectName(QString::fromUtf8("RotateWidget"));
        RotateWidget->resize(600, 600);

        retranslateUi(RotateWidget);

        QMetaObject::connectSlotsByName(RotateWidget);
    } // setupUi

    void retranslateUi(QWidget *RotateWidget)
    {
        RotateWidget->setWindowTitle(QCoreApplication::translate("RotateWidget", "RotateWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RotateWidget: public Ui_RotateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTATEWIDGET_H
