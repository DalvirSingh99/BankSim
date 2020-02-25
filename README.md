# BankSim

**Purpose of Assignment:**
The goal of the assignment is to gain a better understanding of multithreading programming and how race conditions can occur in your program and how you should try to resolve them. We needed to observe and resolve the race condition in a multi-thread program. We were given a prototype bank fund transferring simulation program which did not have any means to protect the critical part of the code to prevent race condition. So race condition always happens when it runs. Therefore, we had to do multiple tasks to resolve the various race conditions in the code. 

**Requirements of the Assignment:**
- Draw a simple  UML sequence diagram to show how the initial race condition occurs in the program. Explain how the race condition is portrayed in the UML and add the explanation and UML to the README.md 

- Implement protection code to resolve the race condition issue. Our solution must allow the bank to transfer multiple fund between unrelated accounts, e.g. from account [2] to account [5] and from account [3] to account [7] at the same time.
- The test method in the bank simulation program implemented Task 2 may still reports an error. This is because while the test method is summing the amounts in each account in one thread, transfers are still taking place in other threads. This is another source to a race condition. Refactoring the method of testing summing the balance in each account in a new and separate thread. Provide code protection so that the newly-created testing thread and any other amount transferring threads are running exclusively, i.e. the testing thread starts with a signal to all transferring threads, waits for all the transferring threads finishing the current transferring, and then takes over the testing task while all the transferring threads are waiting until the test is done.

- The initial code does not allow an account to transfer out fund if the transferring amount is greater than the account balance. Implement a wait/notify solution to defer the transfer until the account balance becomes greater than the transferring amount (assume some the account will receive the fund later).

- Deadlock condition may occur (very rare) if one thread finishes all the fund transfers and exit. Implement a solution in which all thread stop fund transferring (bank is close) whenever one tread completes its fund transfers. This will solve the deadlock condition issue.
