# BankSim

## UML
![UML](https://github.com/DalvirSingh99/BankSim/blob/Shunsuke_Omura/RaceCondition.png)
## Explanation
The race condition occurs in the original code because accounts are not protected and multiple threads change their balance at the same time. In order to resolve the race condition, we need to add protection to lock each account when one of the threads is executing the transfer and release the lock when the execution is done. 
