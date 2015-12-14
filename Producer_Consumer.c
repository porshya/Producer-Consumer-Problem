// Kevin Liu
// 2015
// Computer Systems

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for rand
#include <unistd.h> // for sleep
#include <assert.h> // for testing
#include "sem.h"

#define LEN 4

// global semaphores
struct sem_t sem_producer;  // Count number of empty slots available
struct sem_t sem_consumer;  // Count number of items in the buffer

// global lock for buffer
pthread_mutex_t mut_buf = PTHREAD_MUTEX_INITIALIZER;

// global buffers
int buf[LEN];
int first_occupied = 0;
int first_empty = 0;

// Add item to buffer
void push_buf(int val) {
  buf[first_empty] = val;
  first_empty++;
  if (first_empty >= LEN) {
    first_empty = 0;
  }
}

// Remove item from buffer
int take_from_buf() {
  int val = buf[first_occupied];
  first_occupied++;
  if (first_occupied >= LEN) {
    first_occupied = 0;
  }
  return val;
}

// Producer Thead
void *producer(void *arg) {
  int work_item = 1;

  while (1) {
    sleep( rand() % 5 );
    my_sem_wait(&sem_producer);  // Wait for empty slots

    pthread_mutex_lock(&mut_buf);
      push_buf(work_item++);  
    pthread_mutex_unlock(&mut_buf);

    my_sem_post(&sem_consumer);  // Tell the consumer there's a new work item
  }
}

// Consumer Thread
void *consumer(void *arg) {
  while (1) {
    int work_item;

    sleep( rand() % 5 );
    my_sem_wait(&sem_consumer); // Wait for item to consume

    pthread_mutex_lock(&mut_buf);
      work_item = take_from_buf();
    pthread_mutex_unlock(&mut_buf);

    my_sem_post(&sem_producer); // Tell producer there's a new work item

    printf("%d ", work_item);
    fflush(stdout);  // Force printing now; don't wait for the newline
  }
  return NULL;
}

// Run producer thread num_P times and consumer thread num_C times
int run(int num_P, int num_C) {
	// Initialize the threads
	my_sem_init(&sem_producer, 0, LEN);
	my_sem_init(&sem_consumer, 0, 0);
  
  int rc;

	// Create Producer threads
	for (int i = 0; i < num_P; i++) {

	  pthread_t pro;
	  rc = pthread_create(&pro, NULL, &producer, NULL);
    assert(rc == 0);
	}
   
  // Create Consumer threads
  for (int i = 0; i < num_P; i++) {

	  pthread_t con;
	  rc = pthread_create(&con, NULL, &consumer, NULL);
    assert(rc == 0);
  }
  
  // WARNING: The primary thread runs on main()
  // When main exits, primary thread exits.
  while (1) {
    sleep(1); // Don't let primary thread exit.
  }
}

int main() {
	// Run(x, y)
	// Runs with x many producers and y many consumers
  int numProducer;
  int numConsumer;

  printf("How many producers?\n");
  scanf("%d", &numProducer);

  printf("How many consumers?\n");
  scanf("%d", &numConsumer);

	run(numProducer, numConsumer);

	return 0;
}
