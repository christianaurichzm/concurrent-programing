#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *t_function(void *arg)
{
  int t_id = *((int *)arg);
  int value;

  sem_wait(&sem);

  sem_getvalue(&sem, &value);
  printf("Thread %d acquire the semaphore. Value = %d\n", t_id, value);
  usleep(1);
  printf("Thread %d release the semaphore\n", t_id);
  sem_post(&sem);

  return 0;
}

int main(int argc, char **argv)
{
  int n_threads = atoi(argv[1]);
  int ids[n_threads];
  int i;
  pthread_t threads[n_threads];

  sem_init(&sem, 0, 2);

  for (i = 0; i < n_threads; i++)
  {
    ids[i] = i;
    pthread_create(&threads[i], NULL, t_function, &ids[i]);
  }

  for (i = 0; i < n_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }

  sem_destroy(&sem);

  return 0;
}
