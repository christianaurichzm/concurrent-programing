#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
pthread_mutex_t mutex;
int shared_resource;

void *t_function(void *arg)
{
  int t_id = *((int *)arg);
  int value;

  sem_wait(&sem);

  sem_getvalue(&sem, &value);
  printf("Thread %d acquire the semaphore. Value = %d\n", t_id, value);
  pthread_mutex_lock(&mutex);
  shared_resource++;
  printf("Shared resource = %d\n", shared_resource);
  pthread_mutex_unlock(&mutex);

  pthread_mutex_lock(&mutex);
  shared_resource--;
  pthread_mutex_unlock(&mutex);
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
  pthread_mutex_init(&mutex, NULL);

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
  pthread_mutex_destroy(&mutex);

  return 0;
}
