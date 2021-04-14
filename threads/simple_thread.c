#include <stdio.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    printf("Running the new thread\n");
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t;
    printf("Creating thread\n");
    pthread_create(&t, NULL, thread_function, NULL);
    printf("Waiting for the thread to end\n");
    pthread_join(t, NULL);

    return 0;
}