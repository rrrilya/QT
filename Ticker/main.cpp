#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Создание объекта QIcon с указанием пути к иконке
      QIcon avatarIcon(":/images/ticker-logo.png");

      // Установка иконки для главного окна приложения
      a.setWindowIcon(avatarIcon);

    MainWindow w;
    w.show();
    return a.exec();
}
