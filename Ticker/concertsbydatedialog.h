#ifndef CONCERTSBYDATEDIALOG_H
#define CONCERTSBYDATEDIALOG_H

#include <QDialog>
#include <QDate>

namespace Ui {
class ConcertsByDateDialog;
}

class ConcertsByDateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConcertsByDateDialog(const QDate& date, QWidget *parent = nullptr);
    ~ConcertsByDateDialog();

private:
    Ui::ConcertsByDateDialog *ui;
};

#endif // CONCERTSBYDATEDIALOG_H
