#ifndef MAINWINDOWBUY_H
#define MAINWINDOWBUY_H

#include <QDialog>
#include <QDate>

namespace Ui {
class MainWindowBuy;
}

class MainWindowBuy : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindowBuy(QWidget *parent = nullptr);
    ~MainWindowBuy();

    void setConcertInfo(const QString& artist, const QDate& concertDate, double price);
    void setConcertData(const QString &artist, const QDate &concertDate, double price);


private slots:
    void on_pushButtonBuy_clicked();
    void onTableWidgetSelectionChanged();


private:
    Ui::MainWindowBuy *ui;
    QString selectedArtist;
    QDate selectedConcertDate;
    double accountBalance;
    double concertPrice;

    bool deductMoneyFromAccount(double amount);
    QString generateTicketNumber(const QString& concert);
    void loadConcertData();
signals:
    void balanceUpdated(double balance);
};

#endif // MAINWINDOWBUY_H
