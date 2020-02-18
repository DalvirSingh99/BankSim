#include "Account.h"

Account *Account_new(int id, int initialBalance) {
    Account *a = (Account *)malloc(sizeof(Account));
    a->id = id;
    a->balance = initialBalance;
    
    a->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    return a;
}

void Account_destroy(Account *a) {
    free(a);
}

void Account_deposit(Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
//    fprintf(stderr, "%d has the lock\n", a->id);
    int newBalance = a->balance + amount;
    a->balance = newBalance;
//    fprintf(stderr, "%d has unlocked\n", a->id);
    pthread_mutex_unlock(&a->lock);
    
}

int Account_withdraw(Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
//    fprintf(stderr, "%d has the lock\n", a->id);
    if(amount <= a->balance) {
        int newBalance = a->balance - amount;
        a->balance = newBalance;
//        fprintf(stderr, "%d has unlocked\n", a->id);
    pthread_mutex_unlock(&a->lock);
        return 1;
    } else {
//        fprintf(stderr, "%d has unlocked\n", a->id);
        pthread_mutex_unlock(&a->lock);
        return 0;
    }
    
}
