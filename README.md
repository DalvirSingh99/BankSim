# BankSim

**Purpose of Assignment:**
The goal of the assignment is to gain a better understanding of multithreading programming and how race conditions can occur in your program and how you should try to resolve them. We needed to observe and resolve the race condition in a multi-thread program. We were given a prototype bank fund transferring simulation program which did not have any means to protect the critical part of the code to prevent race condition. So race condition always happens when it runs. Therefore, we had to do multiple tasks to resolve the various race conditions in the code. 

**Requirements of the Assignment:**
- Draw a simple  UML sequence diagram to show how the initial race condition occurs in the program. Explain how the race condition is portrayed in the UML and add the explanation and UML to the README.md 

- Implement protection code to resolve the race condition issue. Our solution must allow the bank to transfer multiple fund between unrelated accounts, e.g. from account [2] to account [5] and from account [3] to account [7] at the same time.
