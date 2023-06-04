#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindowbuy.h"
#include "mainwindowreturn.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QCheckBox>
#include "concertsbydatedialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ticker");

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    MainWindowBuy buyDialog;
    buyDialog.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    MainWindowReturn returnDialog;
    returnDialog.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    // Открытие файла "buyerdata.txt" для чтения
    QFile file("buyerdata.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString ticketNumbers;

        // Чтение номеров билетов из файла
        while (!in.atEnd())
        {
            QString line = in.readLine();
            ticketNumbers += line + "\n";
        }

        file.close();

        // Открытие информационного окна с перечислением номеров билетов
        QMessageBox::information(this, "Ваши билеты:", ticketNumbers);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open buyerdata.txt");
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate& date)
{
    ConcertsByDateDialog dialog(date);
    dialog.exec();
}


// Слот для получения информации о балансе и вывода уведомления
void MainWindow::updateBalance(double balance)
{
    QMessageBox::information(this, "My Balance", "Your account balance is: " + QString::number(balance));
}

void MainWindow::on_actionMyBalance_clicked()
{
    MainWindowBuy buyDialog;
    connect(&buyDialog, &MainWindowBuy::balanceUpdated, this, &MainWindow::updateBalance); // Подключение сигнала и слота
    buyDialog.exec();
}

void MainWindow::addTestConcert(const QString& artist, const QDate& date, double price)
{
    // Запись информации о тестовом концерте в файл "concertdata.txt"
    QFile file("concertdata.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << artist << "," << date.toString("dd.MM.yyyy") << "," << price << endl;
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open concertdata.txt");
    }
}

void MainWindow::clearTestConcerts()
{
    // Очистка тестовых концертов
    QFile file("concertdata.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.resize(0); // Очистка содержимого файла
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open concertdata.txt");
    }
}

void MainWindow::on_actionTest_Mode_1_triggered()
{
    // Включение тестового режима
    QMessageBox::information(this, "Test Mode", "Test mode enabled.");
    generateTestConcerts(); // Генерация тестовых концертов
}

void MainWindow::on_actionTest_Mode_2_triggered()
{
    // Выключение тестового режима
    QMessageBox::information(this, "Test Mode", "Test mode disabled.");
    clearTestConcerts(); // Очистка тестовых концертов
}

void MainWindow::generateTestConcerts()
{
    // Генерация тестовых концертов
    QDate currentDate = QDate::currentDate();
    qsrand(static_cast<uint>(QTime::currentTime().msec()));

    // Генерация случайных данных для тестовых концертов
    QStringList artists = { "Artist1", "Artist2", "Artist3" };
    QStringList firstNames = { "John", "Emma", "Michael", "Sophia" };
    QStringList lastNames = { "Smith", "Johnson", "Williams", "Brown" };

    for (int i = 0; i < 90; ++i) {
        // Генерация случайной даты
        QDate randomDate = currentDate.addDays(qrand() % 30); // Случайная дата в течение 30 дней от текущей даты

        // Генерация случайной цены от 50 до 200
        int randomPrice = qrand() % (200 - 50 + 1) + 50;

        // Генерация случайного имени и фамилии
        QString randomFirstName = firstNames[qrand() % firstNames.size()];
        QString randomLastName = lastNames[qrand() % lastNames.size()];

        // Добавление тестового концерта
        addTestConcert(QString("%1 %2").arg(randomFirstName, randomLastName), randomDate, randomPrice);
    }

    emit testConcertsGenerated();
}






