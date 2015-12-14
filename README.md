# Producer-Consumer-Problem
Solution to Concurrency Producer-Consumer Problem

Written using POSIX system calls and the C programming language

***
Type command: "make" within the directory to compile and run the source code.

When compiling, explicitly invoke the pthread library and link sem.c .
A typical compiler command is:
  gcc -g -O0 sem.c -o myprog myprog.c -lpthread
***

Solves the classical concurrency problem for shared resources where 
multiple "Producers" and "Consumers" compete for the same resource
through the use of semaphores.

A circular buffer (FIFO queue that has a bounded buffer) of fixed size is used.

After waiting a random amount of time, the producer thread
will then write an integer into the next available slot in the buffer.
  - The producer will then loop back and again call 'sleep' over a random
period of time.  

After waiting a random amount of time, the consumer thread
will then read an integer from the next available slot in the buffer.
  - The consumer thread will then print the integer, and loop back and again
call 'sleep' over a random period of time.

The program expect to see 1, 2, 3, ... being printed to screen.

For multiple producers, each of which will print 1, 2, 3.
For each producer, a copy of each integer should appear (in random order).

Sem.h  defines a semaphore.

Sem.c implements:
  sem_init, which intializes a semaphore
  sem_post, which increment the count of a semaphore
  sem_wait, which decrement the count of a semaphore`
All three functions are already defined in the pthread library.  
Overwritten the definitions in pthread library.

