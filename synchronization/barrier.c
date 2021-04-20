#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;

void *hello_thread(void *arg)
{
	sleep(1);
	printf("Hello ");
	fflush(stdout);
	pthread_barrier_wait(&barrier);
	return 0;
}

void *world_thread(void *arg)
{
	pthread_barrier_wait(&barrier);
	printf("world \n");
	fflush(stdout);
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t t1, t2;

	pthread_barrier_init(&barrier, NULL, 2);

	int r1 = pthread_create(&t1, NULL, hello_thread, NULL);
	int r2 = pthread_create(&t2, NULL, world_thread, NULL);

	if (r1 || r2)
	{
		printf("Threads were not created\n");
		exit(1);
	}

	r1 = pthread_join(t1, NULL);
	r2 = pthread_join(t2, NULL);

	if (r1 || r2)
	{
		exit(1);
	}

	pthread_barrier_destroy(&barrier);
	return 0;
}
