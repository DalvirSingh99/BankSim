#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "common.h"

Account *Account_new(int id, int initialBalance);
void Account_destroy(Account *a);
void Account_deposit(Bank *b, Account *a, int amount);
int Account_withdraw(Bank *b, Account *a, int amount);
#endif