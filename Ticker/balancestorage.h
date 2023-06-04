#ifndef BALANCESTORAGE_H
#define BALANCESTORAGE_H

#include <QString>

class BalanceStorage
{
public:
    static double getBalance();
    static void setBalance(double balance);
};

#endif // BALANCESTORAGE_H
