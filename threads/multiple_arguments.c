#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

typedef struct rectangle_t
{
    double length;
    double width;
} rectangle;

void *thread_function(void *arg)
{
    rectangle *r = (rectangle *)arg;
    float r_length = r->length;
    float r_width = r->width;
    float r_area = r_length * r_width;
    printf("l=%.2f, w=%.2f, area=%.2f\n", r_length, r_width, r_area);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t[NUM_THREADS];
    rectangle *r1, *r2;
    long i;

    r1 = malloc(sizeof(rectangle));
    r1->length = 4;
    r1->width = 2;

    r2 = malloc(sizeof(rectangle));
    r2->length = 6.8;
    r2->width = 4;

    printf("Creating thread 1\n");
    pthread_create(&t[0], NULL, thread_function, (void *)r1);

    printf("Creating thread 2\n");
    pthread_create(&t[1], NULL, thread_function, (void *)r2);

    printf("Waiting for the threads to end\n");

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("The threads are over\n");

    return 0;
}