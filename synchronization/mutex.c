#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int shared_resource;

void *t_function(void *arg)
{
  int t_id = *((int *)arg);

  pthread_mutex_lock(&mutex);
  printf("Thread %d acquire the mutex\n", t_id);
  shared_resource = t_id;
  usleep(1);

  printf("Shared resource = %d\n", shared_resource);
  printf("Thread %d release the mutex\n", t_id);
  pthread_mutex_unlock(&mutex);

  return 0;
}

int main(int argc, char **argv)
{
  int n_threads = atoi(argv[1]);
  int ids[n_threads];
  int i;
  pthread_t threads[n_threads];

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

  pthread_mutex_destroy(&mutex);

  return 0;
}
