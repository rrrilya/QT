#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "mainwindowbuy.h"
#include "mainwindowreturn.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateAccountBalance(double balance);
    void on_actionMyBalance_clicked();
public slots:
    void updateBalance(double balance);


private slots:
    void on_actionTest_Mode_1_triggered();
    void on_actionTest_Mode_2_triggered();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void clearTestConcerts();

    void on_calendarWidget_clicked(const QDate &date);
    void generateTestConcerts();
    void addTestConcert(const QString& artist, const QDate& date, double price);



private:
    Ui::MainWindow *ui;
    double accountBalance;
    QDate selectedDate;
signals:
    void testConcertsGenerated();
};

#endif // MAINWINDOW_H
