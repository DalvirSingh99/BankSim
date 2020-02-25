#include "Bank.h"

Bank *Bank_new(int numAccounts, int initialBalance) {
    //Construtor which creates the bank
    Bank *b = (Bank *) malloc(sizeof (Bank));
    b->initialBalance = initialBalance;
    b->numAccounts = numAccounts;
    b->ntransacts = 0;
    b->accounts = (Account **) malloc(numAccounts * sizeof (Account *));
    for (int i = 0; i < numAccounts; ++i) {
        b->accounts[i] = Account_new(i, initialBalance);
    }
    b->open = 1; //Bank is open
    b->lock = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    b->startthreads = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    b->stopthreads =(pthread_cond_t) PTHREAD_COND_INITIALIZER;
    b->ntransactsInProgress=0;
    b->stop=0; 
    return b;
}

void Bank_destroy(Bank *b) {
    for (int i = 0; i < b->numAccounts; ++i) {
        Account_destroy(b->accounts[i]);
    }
    free(b);
}

void Bank_open(Bank *b) {
    //Goes through all the accounts

    for (int i = 0; i < b->numAccounts; ++i) {

        TransferThreadParameters *params = TransferThreadParameters_new(b, i, b->initialBalance);
        pthread_create(&b->accounts[i]->thread, NULL, transfer_thread, params);
    }
    for (int i = 0; i < b->numAccounts; ++i) {
        pthread_join(b->accounts[i]->thread, NULL);
    }

    Bank_test(b);

    puts("Bank is finished running.");
}

void Bank_transfer(Bank *b, int from, int to, int amount) {
    // Uncomment line when race condition in Bank_test() has been resolved.
    if(!b->open){
        return;
    }
    if(Bank_shouldTest(b)) BankTester(b);
    
    
    //Locked due to race condition
    pthread_mutex_lock(&b->lock);
    printf("Transfer get Lock\n");
    //Waiting for signal from test thread that it has finished
    while(b->stop == 1){
        pthread_cond_wait(&b->startthreads, &b->lock);
    }
    
    b->ntransactsInProgress++; 
    printf("Number of Transaction is %d\n", b->ntransactsInProgress);
    pthread_mutex_unlock(&b->lock);
    
    if (b->open && Account_withdraw(b, b->accounts[from], amount)) {
        Account_deposit(b, b->accounts[to], amount);
    }
    
    //Locked due to race conditions
    pthread_mutex_lock(&b->lock);
    b->ntransactsInProgress--; 
    printf("Number of Transaction is %d\n", b->ntransactsInProgress);
    if(b->ntransactsInProgress==0){
        //Block the threads 
        printf("Signaled threads that transaction is zero\n");
        pthread_cond_broadcast(&b->stopthreads);
    }
   
    pthread_mutex_unlock(&b->lock);
}

void Bank_close(Bank *b) {
    pthread_mutex_lock(&b->lock);
    //Close bank
    if (b->open) {
        b->open = 0;
        int i = 0;
        for (int i = 0; i < b->numAccounts; ++i) {
            printf("Closed Account %d\n", b->accounts[i]->id);
            
            pthread_cancel(b->accounts[i]->thread);
        }
        printf("Bank is Closed\n");
        pthread_mutex_unlock(&b->lock);
    } else {
        pthread_mutex_unlock(&b->lock);
    }

}

void *Bank_test(Bank *b) {

    //Lock the bank 
    pthread_mutex_lock(&b->lock);
    fprintf(stderr, "%s\n", "got the lock in test");
    //Tell the other threads to stop 
    b->stop=1; 
    while(b->ntransactsInProgress !=0 ){
        fprintf(stderr, "%s\n", "transactions in progress, releasing lock");
        pthread_cond_wait(&b->stopthreads, &b->lock);
        printf("\n\nReceived signal\n\n\n");
    }
    fprintf(stderr, "%s\n", "transactions complete, regained lock");
    //At this point all the threads have been stopped
    int sum = 0;
    for (int i = 0; i < b->numAccounts; ++i) {
        pthread_t currentThreadId = pthread_self();
        Account *currAccount = b->accounts[i];
        printf("%lu Account[%d] balance %d\n", pthread_self(), currAccount->id, currAccount->balance);
        sum += b->accounts[i]->balance;
    }
    printf("%lu Sum: %d\n", pthread_self(), sum);
    if (sum != b->numAccounts * b->initialBalance) {
        printf("%lu Money was gained or lost!\n", pthread_self());
        b->stop=0;
        //Tell other transfer threads to start up
        fprintf(stderr, "%s\n", "done testing, releasing lock");
        pthread_mutex_unlock(&b->lock);
        pthread_cond_broadcast(&b->startthreads);
        exit(0);
    } else {
        printf("%lu The bank is in balance!\n", pthread_self());
        b->stop=0; //Other threads can proceed
        //Signal transfer threads to start
        fprintf(stderr, "%s\n", "done testing, releasing lock");

        pthread_mutex_unlock(&b->lock);
        pthread_cond_broadcast(&b->startthreads);
    }
}
void BankTester(Bank *b){
    pthread_t *bankTester = (pthread_t*)malloc(sizeof(pthread_t));
    pthread_create(bankTester, NULL, Bank_test, b);
    //Wait for test thread to complete
    pthread_join(*bankTester, NULL);
}

int Bank_shouldTest(Bank *b) {
    //pthread_mutex_lock(&b->lock);
    b->ntransacts++;
    //pthread_mutex_unlock(&b->lock);
    return b->ntransacts % NTEST == 0;
}