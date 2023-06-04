#include "mainwindowreturn.h"
#include "ui_mainwindowreturn.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

MainWindowReturn::MainWindowReturn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindowReturn)
{
    ui->setupUi(this);
    this->setWindowTitle("Возврат");

}

MainWindowReturn::~MainWindowReturn()
{
    delete ui;
}

void MainWindowReturn::on_pushButton_clicked()
{
    QString buyerName = ui->lineEdit->text();
    QString ticketNumber = ui->lineEdit_2->text();
    QString returnReason = ui->lineEdit_3->text();

    // Проверка условий для возврата билета
    QFile file("buyerdata.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        bool found = false;
        QString line;
        QStringList currentTicket;
        QList<QStringList> validTickets;
        while (!file.atEnd())
        {
            line = file.readLine().trimmed();
            if (line == "-----------------------------------")
            {
                if (!currentTicket.isEmpty())
                {
                    QString currentTicketNumber;
                    QString currentBuyerName;
                    for (const QString& field : currentTicket)
                    {
                        if (field.startsWith("Number: "))
                        {
                            currentTicketNumber = field.mid(8);
                        }
                        else if (field.startsWith("Name: "))
                        {
                            currentBuyerName = field.mid(6);
                        }
                    }
                    if (currentTicketNumber == ticketNumber && currentBuyerName == buyerName)
                    {
                        found = true;
                    }
                    else
                    {
                        validTickets.append(currentTicket);
                    }
                }
                currentTicket.clear();
            }
            currentTicket.append(line);
        }

        file.close();

        if (found)
        {
            // Возврат средств на баланс
            refundMoneyToAccount(ticketNumber);

            // Запись информации о возврате в файл или базу данных
            QFile returnFile("returndata.txt");
            if (returnFile.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&returnFile);
                for (const QString& field : currentTicket)
                {
                    out << field << endl;
                }
                out << "Return Reason: " << returnReason << endl;
                out << "-----------------------------------" << endl;
                returnFile.close();

                QMessageBox::information(this, "Возврат билета", "Билет успешно возвращен. Возврат средств обработан.");
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл returndata.txt");
            }
        }
        else
        {
            QMessageBox::warning(this, "Некорректные данные", "Некорректный номер билета или имя покупателя.");
        }

        // Перезапись файла buyerdata.txt без возвратившегося билета
        QFile rewriteFile("buyerdata.txt");
        if (rewriteFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&rewriteFile);
            for (const QStringList& ticket : validTickets)
            {
                for (const QString& field : ticket)
                {
                    out << field << endl;
                }
                out << "-----------------------------------" << endl;
            }
            rewriteFile.close();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл buyerdata.txt для перезаписи.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл buyerdata.txt");
    }
}




void MainWindowReturn::refundMoneyToAccount(const QString& )
{
    QFile file("mainwindowbuy.txt");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QStringList fields;
        while (!file.atEnd())
        {
            line = file.readLine().trimmed();
            fields = line.split(",");
            if (fields.size() == 2 && fields.at(0) == "Account Balance")
            {
                double accountBalance = fields.at(1).toDouble();
                // Найден баланс счета, можно начислить сумму возврата
                // Например, если refundAmount - сумма возврата
                accountBalance += 1;

                // Обновляем баланс счета
                file.seek(file.pos() - line.length() - 1);
                QTextStream out(&file);
                out << "Account Balance," << accountBalance << endl;
                break;
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл mainwindowbuy.txt");
    }
}
