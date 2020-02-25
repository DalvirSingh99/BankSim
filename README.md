# BankSim
## 1. Requirements:
Task 1: Draw a UML sequence diagram to explain why the race condition occurs in the initial code and explain it in words.
Task 2: One of issues in the initial code is threads access to the global variable of balance at the same time. This happens because there is no protection code on the deposite/withdraw functions, so we added the mutex locks to make sure no other threads can access to the critical section while one is accessing.  
Task 3: Another race condition happens when we uncomment the bank transfer function. Since threads may run on different methods at the same time without protections, it is possible that the transfer and summation occur simultaneously. We make threads to wait until other jobs are done and resume their jobs by a signal.  
Task 4: 
Task 5: 
## 2. Team Work
Shunsuke Omura: Task 1, Task 3, README  
Dalvir Singh : Task 2, Task 4, Task 5, README
## 3. Testing
We manually check the result of the code  
## 4. UML
1. Initial Version  
![UML](https://github.com/DalvirSingh99/BankSim/blob/Shunsuke_Omura/RaceCondition.png)
### Explanation
The race condition occurs in the original code because accounts are not protected and multiple threads change their balance at the same time. In order to resolve the race condition, we need to add protection to lock each account when one of the threads is executing the transfer and release the lock when the execution is done.  
  
2. Task 3

### Explanation
