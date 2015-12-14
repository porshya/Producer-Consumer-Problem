// Kevin Liu
// 2015
// Computer Systems

#include <pthread.h>
#include <unistd.h> // for sleep
#include "sem.h"

// Initializes a semaphore
int my_sem_init(struct sem_t *sem, int pshared, unsigned int init) {
  sem->count = init;
  // ignore pshared, shared betweeen threads of one process
  pthread_mutex_init(&(sem->mutex), NULL);
  sem->num_threads_blocked = 0;
}

// Increase count of semaphore
int my_sem_post(struct sem_t *sem) {
  pthread_mutex_lock( &(sem->mutex) );
    sem->count++;
  pthread_mutex_unlock( &(sem->mutex) );
}

// Decrement count of semaphore and waits
int my_sem_wait(struct sem_t *sem) {
  pthread_mutex_lock( &(sem->mutex) );
  sem->count--;
  if (sem->count < 0) {
    // Must release lock, or else my_sem_post() will never be called.
    pthread_mutex_unlock( &(sem->mutex) );
      block(sem);
    pthread_mutex_lock( &(sem->mutex) );
  }
  pthread_mutex_unlock( &(sem->mutex) );
}

void block(struct sem_t *sem) {
  // sem->count < 0
  pthread_mutex_lock( &(sem->mutex) );
  sem->num_threads_blocked++;
  pthread_mutex_unlock( &(sem->mutex) );
  
  while (pthread_mutex_lock( &(sem->mutex) ), (-(sem->count) >= sem->num_threads_blocked)) {
    pthread_mutex_unlock( &(sem->mutex) );
    sleep(1); // sleep for a second, and check later if count >=0.
  }
  sem->num_threads_blocked--;
  pthread_mutex_unlock( &(sem->mutex) );
}
