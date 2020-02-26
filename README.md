# BankSim

**Purpose of Assignment:**
The goal of the assignment is to gain a better understanding of multithreading programming and how race conditions can occur in your program and how you should try to resolve them. We needed to observe and resolve the race condition in a multi-thread program. We were given a prototype bank fund transferring simulation program which did not have any means to protect the critical part of the code to prevent race condition. So race condition always happens when it runs. Therefore, we had to do multiple tasks to resolve the various race conditions in the code. 

**Requirements of the Assignment:**
- Draw a simple  UML sequence diagram to show how the initial race condition occurs in the program. Explain how the race condition is portrayed in the UML and add the explanation and UML to the README.md 

- Implement protection code to resolve the race condition issue. Our solution must allow the bank to transfer multiple fund between unrelated accounts, e.g. from account [2] to account [5] and from account [3] to account [7] at the same time.
- The test method in the bank simulation program implemented Task 2 may still reports an error. This is because while the test method is summing the amounts in each account in one thread, transfers are still taking place in other threads. This is another source to a race condition. Refactoring the method of testing summing the balance in each account in a new and separate thread. Provide code protection so that the newly-created testing thread and any other amount transferring threads are running exclusively, i.e. the testing thread starts with a signal to all transferring threads, waits for all the transferring threads finishing the current transferring, and then takes over the testing task while all the transferring threads are waiting until the test is done.

- The initial code does not allow an account to transfer out fund if the transferring amount is greater than the account balance. Implement a wait/notify solution to defer the transfer until the account balance becomes greater than the transferring amount (assume some the account will receive the fund later).

- Deadlock condition may occur (very rare) if one thread finishes all the fund transfers and exit. Implement a solution in which all thread stop fund transferring (bank is close) whenever one tread completes its fund transfers. This will solve the deadlock condition issue.

**Implementations to accomplish each task**
- Task 1: We created a UML to show the race condition
- Task 2: In the account struct, we included a mutex lock. Each time a transfer was occuring, the program would lock that specific account until the transfer was completed. We lock the specific account inside the withdraw and deposit functions. 
- Task 3: Race condition occurs because transfer threads and testing threads work at the same time without any protection codes. We used pthread mutex and pthread condtions to make sure that two thread does not access any global variables simultanuously.
- Task 4: Initially, if the amount someone wants to withdraw is greater than the current balance, then the program does nothing. We modified the code such that, if the amount the account wants to withdraw is greater, than that specific account is put into a blocked state through the use of "pthread_cond_wait()". When any amount of money gets deposited to that account, all the threads that were blocked due to low balance of that account gets signaled to wake up through "pthread_cond_broadcast()". Inside the threads, each thread inside the withdraw function checks if the balance is enough to withdraw and does the same thing. 
- Task 5: Initially, a deadlock occurred when a specific transfer thread finished all the desired transactions. The previous solution to task 4 assumes that the account will eventually get enough balance but when a thread finishes, this statement no longer becomes valid. Therefore a dead lock occurs, since threads are waiting for the balance to change but it won't anymore. Our solution to this problem was to stop all the transfer threads when one thread finished all the transactions. We created a open variable in the Bank structure which would indicate if the bank was open for transactions or not. In the constructor, it is initially set to 1, meaning open for transactions. When one transfer thread finishes all the transactions, we set the bank open variable to 0, meaning bank is closed and loop through all the account threads to shut them down. Also, we had to make sure to put a lock on the Bank close method so multiple threads do not try to close the bank at the same time or they will try to access threads that have already been shut down or in the process of being shut down. 

**Desired Tests:**
Since this lab uses multi threads, it is difficult to make a test code. The best way is to test manually and check the result value.

**Test Insights**  
We did manual testings to check the result value is correct. We also wrote printf statements to check the flow of the program.  

**Team Work**  
*Overall contribution*: The work was designed to be evenly split so one person did not have more on his plate than the other. Also we had open discussions to address any problems one may be having.  

- Shunsuke Omura worked on Task 1 - Draw a UML sequence diagram to explain why the race condtion occurs and contributed to Task 2 Adding the mutex locks on the account when one thread is working on withdraw or deposit. Contributed to the solution for Task 3 and drew another UML diagram. 
- Dalvir Singh: Collaborated with Shunsuke Omura on Task 3 since it was difficult because of the Race condition that occurred when the transfer threads and the testing thread are running at the same time. Added mutex lock and wait/signal to make sure they do not access simultanuously. Completed Task 4 by adding pthread condition wait and signal on the account when it has not enough money while leveraging a mutex lock on the bank. When it gets money from other accounts, send signal to stop blocking the thread. Also, completed task 5 to close the bank by creating a close variable in bank struct and then creating a bank close method that signaled the bank has closed and shuts down all the transaction threads. 

- Overall- We had to calloborate on the assignment together since we had to have full understanding of the other person's code in order to not break what the other person had done. Therefore, we sat together worked on all the tasks individually where needed and collaborated on difficult parts when needed. 
---
## UML
## Original (before task 3)
![UML](https://raw.githubusercontent.com/DalvirSingh99/BankSim/Task3/initial.png)
### Explanation
The race condition occurs in the original code because accounts are not protected and multiple threads change the balance value at the simultanuously. In order to resolve the race condition, we need to add protection to lock each account when one of the threads is executing the deposite or withdraw and release the lock when the execution is done.  
## Modified (after task 3)
![UML](https://raw.githubusercontent.com/DalvirSingh99/BankSim/Task3/RaceCondition_InitialVersion.png)
### Explanation
The test method is involked after task 3 when transfer threads are all blocked. This prevents the transfer threads and testing threads to acceesss a global variable simultanuously. The should_test method tests the status and if it is true, create a thread to calls the test method (Bank_test in the uml). Once it is done, send signals to all threads blocked.
