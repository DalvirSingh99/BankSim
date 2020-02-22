#include "Account.h"

Account *Account_new(int id, int initialBalance) {
    Account *a = (Account *)malloc(sizeof(Account));
    a->id = id;
    a->balance = initialBalance;
    a->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    a->cond1= (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    return a;
}

void Account_destroy(Account *a) {
    free(a);
}

void Account_deposit(Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
    int newBalance = a->balance + amount;
    a->balance = newBalance;
    pthread_cond_broadcast(&a->cond1);
    pthread_mutex_unlock(&a->lock);
}

int Account_withdraw(Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
    if(amount <= a->balance) {
        int newBalance = a->balance - amount;
        a->balance = newBalance;
//        printf("Account %d waiting for signal", a->id);
        pthread_mutex_unlock(&a->lock);
        return 1;
    } else {
        printf("Account %d waiting for signal\n", a->id);
        pthread_cond_wait(&a->cond1, &a->lock);
        
        return 0;
    }
    
}
