#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

typedef struct
{
	int ready;
	pthread_mutex_t mutex;
	pthread_cond_t cond_var;
} shared_state_t;

shared_state_t *shared;

void cond_var_init()
{
	shared->ready = FALSE;
	pthread_mutex_init(&shared->mutex, NULL);
	pthread_cond_init(&shared->cond_var, NULL);
}

void cond_var_destroy()
{
	pthread_mutex_destroy(&shared->mutex);
	pthread_cond_destroy(&shared->cond_var);
}

void *hello_thread(void *arg)
{
	sleep(1);
	pthread_mutex_lock(&shared->mutex);
	printf("Hello ");

	shared->ready = TRUE;
	pthread_cond_signal(&shared->cond_var);
	pthread_mutex_unlock(&shared->mutex);
	return 0;
}

void *world_thread(void *arg)
{
	pthread_mutex_lock(&shared->mutex);
	while (!shared->ready)
	{
		pthread_cond_wait(&shared->cond_var, &shared->mutex);
	}
	printf("world \n");
	pthread_mutex_unlock(&shared->mutex);
	return 0;
}

int main(int argc, char **argv)
{
	shared = malloc(sizeof(shared_state_t));
	cond_var_init();
	pthread_t t1, t2;

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

	cond_var_destroy();
	return 0;
}
