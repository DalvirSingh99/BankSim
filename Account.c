#include "Account.h"

Account *Account_new(int id, int initialBalance) {
    Account *a = (Account *) malloc(sizeof (Account));
    a->id = id;
    a->balance = initialBalance;

    a->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    a->cond1 = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    return a;
}

void Account_destroy(Account *a) {
    free(a);
}

void Account_deposit(Bank *b, Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
    int newBalance = a->balance + amount;
    a->balance = newBalance;
    //Signal sleep threads that the balance has changed
    pthread_cond_broadcast(&a->cond1);
    pthread_mutex_unlock(&a->lock);

}

int Account_withdraw(Bank *b, Account *a, int amount) {
    pthread_mutex_lock(&a->lock);
    //While amount we want to withdraw is less, wait for the balance to be right
    while (b->open && amount >= a->balance) {
        pthread_cond_wait(&a->cond1, &a->lock);
    }
    //At this point, the balance is good 
    if (b->open) {
        int newBalance = a->balance - amount;
        a->balance = newBalance;
        pthread_mutex_unlock(&a->lock);
        return 1;
    }
    pthread_mutex_unlock(&a->lock);
    return 0;
}
