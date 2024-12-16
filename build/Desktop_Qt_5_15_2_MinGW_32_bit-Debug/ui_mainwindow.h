/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEinstellungsfenster;
    QAction *actionStatistikfenster;
    QAction *actionHilfefenster;
    QAction *actionEinstellung;
    QAction *actionStatistik;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *Neu;
    QPushButton *Pause;
    QPushButton *Beenden;
    QSpacerItem *horizontalSpacer_5;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuMen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(333, 413);
        MainWindow->setAcceptDrops(false);
        actionEinstellungsfenster = new QAction(MainWindow);
        actionEinstellungsfenster->setObjectName(QString::fromUtf8("actionEinstellungsfenster"));
        actionStatistikfenster = new QAction(MainWindow);
        actionStatistikfenster->setObjectName(QString::fromUtf8("actionStatistikfenster"));
        actionHilfefenster = new QAction(MainWindow);
        actionHilfefenster->setObjectName(QString::fromUtf8("actionHilfefenster"));
        actionEinstellung = new QAction(MainWindow);
        actionEinstellung->setObjectName(QString::fromUtf8("actionEinstellung"));
        actionStatistik = new QAction(MainWindow);
        actionStatistik->setObjectName(QString::fromUtf8("actionStatistik"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(6, 6, 323, 26));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Neu = new QPushButton(horizontalLayoutWidget);
        Neu->setObjectName(QString::fromUtf8("Neu"));

        horizontalLayout->addWidget(Neu);

        Pause = new QPushButton(horizontalLayoutWidget);
        Pause->setObjectName(QString::fromUtf8("Pause"));

        horizontalLayout->addWidget(Pause);

        Beenden = new QPushButton(horizontalLayoutWidget);
        Beenden->setObjectName(QString::fromUtf8("Beenden"));

        horizontalLayout->addWidget(Beenden);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(6, 36, 321, 311));
        scrollArea->setMaximumSize(QSize(16777202, 16777215));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 319, 309));
        gridLayoutWidget = new QWidget(scrollAreaWidgetContents);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(-1, -1, 321, 311));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 333, 22));
        menubar->setTabletTracking(true);
        menubar->setNativeMenuBar(true);
        menuMen = new QMenu(menubar);
        menuMen->setObjectName(QString::fromUtf8("menuMen"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setAcceptDrops(true);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMen->menuAction());
        menuMen->addAction(actionEinstellung);
        menuMen->addAction(actionStatistik);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionEinstellungsfenster->setText(QCoreApplication::translate("MainWindow", "Einstellung", nullptr));
        actionStatistikfenster->setText(QCoreApplication::translate("MainWindow", "Statistik", nullptr));
        actionHilfefenster->setText(QCoreApplication::translate("MainWindow", "Hilfe", nullptr));
        actionEinstellung->setText(QCoreApplication::translate("MainWindow", "Einstellung", nullptr));
        actionStatistik->setText(QCoreApplication::translate("MainWindow", "Statistik", nullptr));
        Neu->setText(QCoreApplication::translate("MainWindow", "Neu", nullptr));
        Pause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        Beenden->setText(QCoreApplication::translate("MainWindow", "Beenden", nullptr));
        menuMen->setTitle(QCoreApplication::translate("MainWindow", "Men\303\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
