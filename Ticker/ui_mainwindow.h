/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_Concert;
    QAction *actionTest_Mode_1;
    QAction *actionTest_Mode_3;
    QAction *actionMyBalance_2;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QCalendarWidget *calendarWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QMenu *menuTicker;
    QMenu *menuTest_mode;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 900);
        MainWindow->setMinimumSize(QSize(900, 900));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/ticker-logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAdd_Concert = new QAction(MainWindow);
        actionAdd_Concert->setObjectName(QString::fromUtf8("actionAdd_Concert"));
        actionTest_Mode_1 = new QAction(MainWindow);
        actionTest_Mode_1->setObjectName(QString::fromUtf8("actionTest_Mode_1"));
        actionTest_Mode_3 = new QAction(MainWindow);
        actionTest_Mode_3->setObjectName(QString::fromUtf8("actionTest_Mode_3"));
        actionMyBalance_2 = new QAction(MainWindow);
        actionMyBalance_2->setObjectName(QString::fromUtf8("actionMyBalance_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        calendarWidget = new QCalendarWidget(centralwidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        verticalLayout->addWidget(calendarWidget);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
        menuTicker = new QMenu(menubar);
        menuTicker->setObjectName(QString::fromUtf8("menuTicker"));
        menuTest_mode = new QMenu(menuTicker);
        menuTest_mode->setObjectName(QString::fromUtf8("menuTest_mode"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTicker->menuAction());
        menuTicker->addAction(menuTest_mode->menuAction());
        menuTest_mode->addSeparator();
        menuTest_mode->addAction(actionTest_Mode_1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAdd_Concert->setText(QApplication::translate("MainWindow", "Add Concert", nullptr));
        actionTest_Mode_1->setText(QApplication::translate("MainWindow", "\321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\276\320\275\321\206\320\265\321\200\321\202\321\213", nullptr));
        actionTest_Mode_3->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        actionMyBalance_2->setText(QApplication::translate("MainWindow", ",\320\260\320\273\320\260\320\275\321\201", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\232\321\203\320\277\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "\320\234\320\276\320\270 \320\261\320\270\320\273\320\265\321\202\321\213", nullptr));
        menuTicker->setTitle(QApplication::translate("MainWindow", "Ticker", nullptr));
        menuTest_mode->setTitle(QApplication::translate("MainWindow", "Test mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
