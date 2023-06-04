#include "balancestorage.h"

// Статическая переменная-член для хранения баланса
static double balance = 0.0;

double BalanceStorage::getBalance()
{
    return balance;
}

void BalanceStorage::setBalance(double newBalance)
{
    balance = newBalance;
}
