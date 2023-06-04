/********************************************************************************
** Form generated from reading UI file 'mainwindowbuy.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWBUY_H
#define UI_MAINWINDOWBUY_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainWindowBuy
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditBuyerName;
    QPushButton *pushButton;
    QTableWidget *tableWidgetConcerts;

    void setupUi(QDialog *MainWindowBuy)
    {
        if (MainWindowBuy->objectName().isEmpty())
            MainWindowBuy->setObjectName(QString::fromUtf8("MainWindowBuy"));
        MainWindowBuy->resize(750, 900);
        MainWindowBuy->setMinimumSize(QSize(750, 900));
        QIcon icon;
        icon.addFile(QString::fromUtf8("//mac/Home/Downloads/fff8406e7b47fcdfea71e0e12b74b0ec.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowBuy->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(MainWindowBuy);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(MainWindowBuy);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditBuyerName = new QLineEdit(MainWindowBuy);
        lineEditBuyerName->setObjectName(QString::fromUtf8("lineEditBuyerName"));

        horizontalLayout->addWidget(lineEditBuyerName);


        verticalLayout->addLayout(horizontalLayout);

        pushButton = new QPushButton(MainWindowBuy);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        tableWidgetConcerts = new QTableWidget(MainWindowBuy);
        if (tableWidgetConcerts->columnCount() < 3)
            tableWidgetConcerts->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetConcerts->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetConcerts->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetConcerts->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidgetConcerts->setObjectName(QString::fromUtf8("tableWidgetConcerts"));

        verticalLayout->addWidget(tableWidgetConcerts);


        retranslateUi(MainWindowBuy);

        QMetaObject::connectSlotsByName(MainWindowBuy);
    } // setupUi

    void retranslateUi(QDialog *MainWindowBuy)
    {
        MainWindowBuy->setWindowTitle(QApplication::translate("MainWindowBuy", "\320\224\320\270\320\260\320\273\320\276\320\263", nullptr));
        label->setText(QApplication::translate("MainWindowBuy", "\320\222\320\260\321\210\320\265 \320\270\320\274\321\217:", nullptr));
        pushButton->setText(QApplication::translate("MainWindowBuy", "\320\232\321\203\320\277\320\270\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetConcerts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindowBuy", "\320\230\321\201\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetConcerts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindowBuy", "\320\224\320\260\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetConcerts->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindowBuy", "\320\246\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowBuy: public Ui_MainWindowBuy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWBUY_H
