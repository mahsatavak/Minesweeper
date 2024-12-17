/********************************************************************************
** Form generated from reading UI file 'statistik.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIK_H
#define UI_STATISTIK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Statistik
{
public:
    QTableWidget *tableWidget;

    void setupUi(QDialog *Statistik)
    {
        if (Statistik->objectName().isEmpty())
            Statistik->setObjectName(QString::fromUtf8("Statistik"));
        Statistik->resize(405, 315);
        tableWidget = new QTableWidget(Statistik);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 30, 351, 251));
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        retranslateUi(Statistik);

        QMetaObject::connectSlotsByName(Statistik);
    } // setupUi

    void retranslateUi(QDialog *Statistik)
    {
        Statistik->setWindowTitle(QCoreApplication::translate("Statistik", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Statistik: public Ui_Statistik {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIK_H
