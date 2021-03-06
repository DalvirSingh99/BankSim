#ifndef COMMON_H
#define COMMON_H
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Account {
    int balance;
    int id;
    pthread_t thread;
    pthread_mutex_t lock;
    pthread_cond_t cond1;
} Account;

typedef struct Bank {
    int initialBalance;
    int numAccounts;
    long ntransacts;
    int ntransactsInProgress;
    Account **accounts;
    int open;
    pthread_mutex_t lock;
    pthread_cond_t stopthreads;
    pthread_cond_t startthreads;
    int stop;
} Bank;

typedef struct TransferThreadParameters {
    Bank *b;
    int fromAccount;
    int maxAmount;
    
} TransferThreadParameters;


#endif