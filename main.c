#include "Bank.h"

#define NACCOUNTS 10
#define INITIAL_BALANCE 10000

int main() {
    srand(time(NULL));
    Bank *b = Bank_new(NACCOUNTS, INITIAL_BALANCE);
    
//    for(int j=0; j<10; j++){
//        printf("Account ## %d is %d \n", j, b->accounts[j]->balance);
//    }
    Bank_open(b);
//    for(int j=0; j<10; j++){
//        printf("Account %d is %d \n", j, b->accounts[j]->balance);
//    }
    Bank_destroy(b);
}