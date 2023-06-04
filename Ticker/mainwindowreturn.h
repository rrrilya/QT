#ifndef MAINWINDOWRETURN_H
#define MAINWINDOWRETURN_H

#include <QDialog>

namespace Ui {
class MainWindowReturn;
}

class MainWindowReturn : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindowReturn(QWidget *parent = nullptr);
    ~MainWindowReturn();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindowReturn *ui;
    void refundMoneyToAccount(const QString &ticketNumber);
        double accountBalance;
};

#endif // MAINWINDOWRETURN_H
