#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    long *thread_id = (long *)arg;
    printf("Running thread %ld\n", *thread_id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int n_threads = atol(argv[1]);
    pthread_t t[n_threads];
    long *ids[n_threads];
    long i;

    for (i = 0; i < n_threads; i++)
    {
        ids[i] = malloc(sizeof(long));
        *ids[i] = i;
        printf("Creating thread %ld\n", i);
        pthread_create(&t[i], NULL, thread_function, (void *)ids[i]);
    }

    printf("Waiting for the threads to end\n");

    for (i = 0; i < n_threads; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("The threads are over\n");

    return 0;
}