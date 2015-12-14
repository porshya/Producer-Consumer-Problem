#include <pthread.h>

// Consistency Criterion:
// count >= 0, # of available resources
// count < 0, # of threads waiting on resources
struct sem_t {
  int count;
  pthread_mutex_t mutex;
  int num_threads_blocked;
};

// Initializes a semaphore
int my_sem_init(struct sem_t *sem, int ignore, unsigned int init);

// Increase count of semaphore
int my_sem_post(struct sem_t *sem);

// Blocked a waiting thread
void block(struct sem_t *sem);

// Decrement count of semaphore and waits
int my_sem_wait(struct sem_t *sem);