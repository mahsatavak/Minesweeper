/********************************************************************************
** Form generated from reading UI file 'einstellung.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EINSTELLUNG_H
#define UI_EINSTELLUNG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Einstellung
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSpinBox *row;
    QSpacerItem *verticalSpacer;
    QSpinBox *col;
    QSpacerItem *verticalSpacer_2;
    QSpinBox *mine;
    QSpacerItem *verticalSpacer_3;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QDialog *Einstellung)
    {
        if (Einstellung->objectName().isEmpty())
            Einstellung->setObjectName(QString::fromUtf8("Einstellung"));
        Einstellung->resize(399, 249);
        buttonBox = new QDialogButtonBox(Einstellung);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 200, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(Einstellung);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(240, 20, 51, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        row = new QSpinBox(verticalLayoutWidget);
        row->setObjectName(QString::fromUtf8("row"));
        row->setMaximum(100);

        verticalLayout->addWidget(row);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        col = new QSpinBox(verticalLayoutWidget);
        col->setObjectName(QString::fromUtf8("col"));
        col->setMaximum(100);

        verticalLayout->addWidget(col);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        mine = new QSpinBox(verticalLayoutWidget);
        mine->setObjectName(QString::fromUtf8("mine"));
        mine->setMaximum(80);

        verticalLayout->addWidget(mine);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayoutWidget_2 = new QWidget(Einstellung);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(50, 20, 171, 160));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_6);


        retranslateUi(Einstellung);
        QObject::connect(buttonBox, SIGNAL(accepted()), Einstellung, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Einstellung, SLOT(reject()));

        QMetaObject::connectSlotsByName(Einstellung);
    } // setupUi

    void retranslateUi(QDialog *Einstellung)
    {
        Einstellung->setWindowTitle(QCoreApplication::translate("Einstellung", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Einstellung", "Zeilenanzahl (maximal 100)", nullptr));
        label_2->setText(QCoreApplication::translate("Einstellung", "Spaltenanzahl (maximal 100)", nullptr));
        label_3->setText(QCoreApplication::translate("Einstellung", "Minenanzahl (maximal 80)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Einstellung: public Ui_Einstellung {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EINSTELLUNG_H
