/********************************************************************************
** Form generated from reading UI file 'mainwindowreturn.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWRETURN_H
#define UI_MAINWINDOWRETURN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainWindowReturn
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;

    void setupUi(QDialog *MainWindowReturn)
    {
        if (MainWindowReturn->objectName().isEmpty())
            MainWindowReturn->setObjectName(QString::fromUtf8("MainWindowReturn"));
        MainWindowReturn->resize(645, 414);
        QIcon icon;
        icon.addFile(QString::fromUtf8("//mac/Home/Downloads/27-278343_giving-tickets-icon-ticket-teatro-png-transparent-png.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowReturn->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(MainWindowReturn);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(MainWindowReturn);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(MainWindowReturn);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(MainWindowReturn);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineEdit = new QLineEdit(MainWindowReturn);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        lineEdit_2 = new QLineEdit(MainWindowReturn);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

        lineEdit_3 = new QLineEdit(MainWindowReturn);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);


        verticalLayout->addLayout(formLayout);

        pushButton = new QPushButton(MainWindowReturn);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(MainWindowReturn);

        QMetaObject::connectSlotsByName(MainWindowReturn);
    } // setupUi

    void retranslateUi(QDialog *MainWindowReturn)
    {
        MainWindowReturn->setWindowTitle(QApplication::translate("MainWindowReturn", "Dialog", nullptr));
        label->setText(QApplication::translate("MainWindowReturn", "\320\222\320\260\321\210\320\265 \320\270\320\274\321\217", nullptr));
        label_2->setText(QApplication::translate("MainWindowReturn", "\320\235\320\276\320\274\320\265\321\200 \320\261\320\270\320\273\320\265\321\202\320\260", nullptr));
        label_3->setText(QApplication::translate("MainWindowReturn", "\320\237\321\200\320\270\321\207\320\270\320\275\320\260", nullptr));
        pushButton->setText(QApplication::translate("MainWindowReturn", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214 \320\261\320\270\320\273\320\265\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowReturn: public Ui_MainWindowReturn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWRETURN_H
