#include "mainwindowbuy.h"
#include "ui_mainwindowbuy.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

MainWindowBuy::MainWindowBuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindowBuy),
    accountBalance(10000.0) // Изначальный баланс счета
{
    ui->setupUi(this);
    this->setWindowTitle("Купить");


    // Загрузка данных о концертах
    loadConcertData();

    // Подключение сигнала изменения выбора элемента в таблице
    connect(ui->tableWidgetConcerts, &QTableWidget::itemSelectionChanged, this, &MainWindowBuy::onTableWidgetSelectionChanged);

    // Подключение сигнала нажатия кнопки покупки
        connect(ui->pushButton, &QPushButton::clicked, this, &MainWindowBuy::on_pushButtonBuy_clicked);

        // Отключение кнопки покупки при запуске
    // Отключение кнопки покупки при запуске
    ui->pushButton->setEnabled(false);
}

MainWindowBuy::~MainWindowBuy()
{
    delete ui;
}

void MainWindowBuy::setConcertInfo(const QString& artist, const QDate& concertDate, double price)
{
    selectedArtist = artist;
    selectedConcertDate = concertDate;
    concertPrice = price;
}

void MainWindowBuy::setConcertData(const QString &artist, const QDate &concertDate, double price)
{
    ui->tableWidgetConcerts->clearContents();
    ui->tableWidgetConcerts->setRowCount(0);

    int row = ui->tableWidgetConcerts->rowCount();
    ui->tableWidgetConcerts->insertRow(row);
    ui->tableWidgetConcerts->setItem(row, 0, new QTableWidgetItem(artist));
    ui->tableWidgetConcerts->setItem(row, 1, new QTableWidgetItem(concertDate.toString("dd.MM.yyyy")));
    ui->tableWidgetConcerts->setItem(row, 2, new QTableWidgetItem(QString::number(price)));
}

void MainWindowBuy::on_pushButtonBuy_clicked()
{
    // Получение имени покупателя из поля ввода
    QString buyerName = ui->lineEditBuyerName->text();

    // Проверка, выбран ли концерт и введено ли имя покупателя
    if (!selectedArtist.isEmpty() && !buyerName.isEmpty())
    {
        // Проверка, достаточно ли средств на счете
        if (deductMoneyFromAccount(concertPrice))
        {
            // Генерация номера билета
            QString ticketNumber = generateTicketNumber(selectedArtist);

            // Формирование сообщения о покупке
            QString message = "Поздравляем, " + buyerName + "!\n";
            message += "Вы успешно приобрели билет на концерт " + selectedArtist + ".\n";
            message += "Дата концерта: " + selectedConcertDate.toString("dd.MM.yyyy") + "\n";
            message += "Цена билета: " + QString::number(concertPrice) + "\n";
            message += "Номер билета: " + ticketNumber;

            // Вывод сообщения о покупке
            QMessageBox::information(this, "Покупка билета", message);

            // Сброс выбора и отключение кнопки покупки
            ui->tableWidgetConcerts->clearSelection();
            ui->pushButton->setEnabled(false);

            // Отправка сигнала обновления баланса
            emit balanceUpdated(accountBalance);

            // Запись информации о покупке в файл
            QFile file("buyerdata.txt");
            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream out(&file);
                out << "Name: " << buyerName << endl;
                out << "Concert: " << selectedArtist << endl;
                out << "Date: " << selectedConcertDate.toString("dd.MM.yyyy") << endl;
                out << "Number: " << ticketNumber << endl;
                out << "Price: " << QString::number(concertPrice) << endl;
                out << "-----------------------------------" << endl;
                file.close();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "Не удалось открыть файл buyerdata.txt для записи.");
            }
        }
        else
        {
            // Вывод сообщения об отсутствии средств на счете
            QMessageBox::critical(this, "Ошибка", "На вашем счете недостаточно средств.");
        }
    }
    else
    {
        // Вывод сообщения о незаполненных полях
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите концерт и введите ваше имя.");
    }
}


void MainWindowBuy::onTableWidgetSelectionChanged()
{
    // Получение выбранной строки
    QList<QTableWidgetItem*> selectedItems = ui->tableWidgetConcerts->selectedItems();

    // Проверка, выбрана ли строка
    if (!selectedItems.isEmpty())
    {
        // Получение информации о выбранном концерте
        int row = ui->tableWidgetConcerts->row(selectedItems.at(0));
        QString artist = ui->tableWidgetConcerts->item(row, 0)->text();
        QDate concertDate = QDate::fromString(ui->tableWidgetConcerts->item(row, 1)->text(), "dd.MM.yyyy");
        double price = ui->tableWidgetConcerts->item(row, 2)->text().toDouble();

        // Установка информации о концерте
        setConcertInfo(artist, concertDate, price);

        // Включение кнопки покупки
        ui->pushButton->setEnabled(true);
    }
    else
    {
        // Отключение кнопки покупки
        ui->pushButton->setEnabled(false);
    }
}

bool MainWindowBuy::deductMoneyFromAccount(double amount)
{
    // Проверка, достаточно ли средств на счете
    if (accountBalance >= amount)
    {
        // Вычет суммы покупки со счета
        accountBalance -= amount;
        return true;
    }
    else
    {
        return false;
    }
}

QString MainWindowBuy::generateTicketNumber(const QString& concert)
{
    // Получение текущей даты
    QDate currentDate = QDate::currentDate();

    // Преобразование даты в строку без точек (ддммгггг)
    QString dateString = currentDate.toString("ddMMyyyy");

    // Преобразование имени исполнителя в верхний регистр и взятие первых трех символов
    QString artistCode = concert.left(3).toUpper();

    // Получение текущего времени в миллисекундах
    qint64 currentMillis = QDateTime::currentDateTime().currentMSecsSinceEpoch();

    // Получение последних трех цифр из текущего времени в миллисекундах
    QString millisString = QString::number(currentMillis % 1000);

    // Генерация номера билета на основе даты, кода исполнителя и миллисекунд
    QString ticketNumber = artistCode  + dateString + millisString;

    return ticketNumber;
}




void MainWindowBuy::loadConcertData()
{
    ui->tableWidgetConcerts->setColumnCount(3);
    ui->tableWidgetConcerts->setHorizontalHeaderLabels({"Concert", "Date", "Price"});

    QFile file("concertdata.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList data = line.split(",");
            if (data.size() >= 3)
            {
                QString concert = data[0];
                QString date = data[1];
                QString price = data[2];

                // Добавить запись в таблицу
                int row = ui->tableWidgetConcerts->rowCount();
                ui->tableWidgetConcerts->insertRow(row);
                ui->tableWidgetConcerts->setItem(row, 0, new QTableWidgetItem(concert));
                ui->tableWidgetConcerts->setItem(row, 1, new QTableWidgetItem(date));
                ui->tableWidgetConcerts->setItem(row, 2, new QTableWidgetItem(price));
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open concertdata.txt");
    }
}

