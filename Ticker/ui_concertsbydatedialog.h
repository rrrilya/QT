/********************************************************************************
** Form generated from reading UI file 'concertsbydatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONCERTSBYDATEDIALOG_H
#define UI_CONCERTSBYDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ConcertsByDateDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidgetConcerts;

    void setupUi(QDialog *ConcertsByDate)
    {
        if (ConcertsByDate->objectName().isEmpty())
            ConcertsByDate->setObjectName(QString::fromUtf8("ConcertsByDate"));
        ConcertsByDate->resize(750, 300);
        ConcertsByDate->setMinimumSize(QSize(750, 0));
        verticalLayout = new QVBoxLayout(ConcertsByDate);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidgetConcerts = new QTableWidget(ConcertsByDate);
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


        retranslateUi(ConcertsByDate);

        QMetaObject::connectSlotsByName(ConcertsByDate);
    } // setupUi

    void retranslateUi(QDialog *ConcertsByDate)
    {
        ConcertsByDate->setWindowTitle(QApplication::translate("ConcertsByDateDialog", "Concerts by Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetConcerts->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ConcertsByDateDialog", "\320\230\321\201\320\277\320\276\320\273\320\275\320\270\321\202\320\265\320\273\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetConcerts->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("ConcertsByDateDialog", "\320\224\320\260\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetConcerts->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("ConcertsByDateDialog", "\320\246\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConcertsByDateDialog: public Ui_ConcertsByDateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONCERTSBYDATEDIALOG_H
