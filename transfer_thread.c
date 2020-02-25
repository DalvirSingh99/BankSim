#include "Bank.h"
#include <pthread.h>

TransferThreadParameters *TransferThreadParameters_new(Bank *b, int fromAccount, int maxAmount) {
    TransferThreadParameters *param = (TransferThreadParameters *)malloc(sizeof(TransferThreadParameters));
    param->b = b;
    param->fromAccount = fromAccount;
    param->maxAmount = maxAmount;

    return param;
}

void *transfer_thread(void *vargp) {
//    fprintf(stderr, "%s\n", "lock is in here");
    TransferThreadParameters *param = (TransferThreadParameters *)vargp;
    Bank *b = param->b;
    
    int fromAccount = param->fromAccount;
    int maxAmount = param->maxAmount;
    
    free(param);
    //For 1000 iterations
    int i = 0;
    
    for(i = 0; i < 1000; ++i) {
        
        //Put money to random account in the bank
        int toAccount = (int)(rand() % b->numAccounts);
        //Put random amount into the random account
        int amount = (int)(rand() % maxAmount);  
        //If Bank is close, exit the thread since one of the threads finished their transactions
        Bank_transfer(b, fromAccount, toAccount, amount);
        
    }
    printf("Account[%d] is done.\n", fromAccount);
//  Close the bank 
    Bank_close(b);
    
}
