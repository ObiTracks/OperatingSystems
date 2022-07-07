#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
// Global Data variables.
int a = 5, b = 7;
pthread_mutex_t mutex;
sem_t semaphore;

// Function that access the global data.
void *inc_dec(void *arg)
{
	sem_wait(&semaphore); // locked
	printf("Read value of 'a' global variable is: %d\n", a);
	printf("Read value of 'b' global variable is: %d\n", b);
	sleep(1);
	a = a + 1;
	b = b - 1;
	printf("Updated value of 'a' variable is: %d\n", a);
	printf("Updated value of 'b' variable is: %d\n", b);
	sem_post(&semaphore); // unlocked

	return 0;
}
int main()
{
	// Creating the thread instances.
	sem_init(&semaphore, 0, 1); // Initializing the semaphore
	pthread_t t1, t2, t3;
	pthread_create(&t1, NULL, inc_dec, NULL);
	pthread_create(&t2, NULL, inc_dec, NULL);
	pthread_create(&t3, NULL, inc_dec, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	// Destroying the threads.
	pthread_exit((pthread_t *) t1);
	pthread_exit((pthread_t *) t2);
	pthread_exit((pthread_t *) t3);

	sem_destroy(&semaphore); // Destroying the semaphore from memory
	return 0;
}
