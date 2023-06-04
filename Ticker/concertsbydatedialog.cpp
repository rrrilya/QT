#include "concertsbydatedialog.h"
#include "ui_concertsbydatedialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ConcertsByDateDialog::ConcertsByDateDialog(const QDate& date, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConcertsByDateDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Концерты в выбранный день");
    ui->tableWidgetConcerts->setColumnCount(3);
    ui->tableWidgetConcerts->setHorizontalHeaderLabels({"Исполнитель", "Дата", "Цена"});

    // Открытие файла "concertdata.txt" для чтения
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
                QString dateString = data[1];
                QString priceString = data[2];

                // Преобразование строки с датой в QDate
                QDate concertDate = QDate::fromString(dateString, "dd.MM.yyyy");

                // Проверка соответствия даты концерта выбранной дате
                if (concertDate == date)
                {
                    // Добавление концерта в таблицу
                    int row = ui->tableWidgetConcerts->rowCount();
                    ui->tableWidgetConcerts->insertRow(row);
                    ui->tableWidgetConcerts->setItem(row, 0, new QTableWidgetItem(concert));
                    ui->tableWidgetConcerts->setItem(row, 1, new QTableWidgetItem(dateString));
                    ui->tableWidgetConcerts->setItem(row, 2, new QTableWidgetItem(priceString));
                }
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open concertdata.txt");
    }
}

ConcertsByDateDialog::~ConcertsByDateDialog()
{
    delete ui;
}
