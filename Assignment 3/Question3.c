
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

sem_t running;
sem_t even;
sem_t odd;

bool threads_ready = false;
int last_thread_polarity = -1;

void logStart(char *tID);  // function to log that a new thread is started
void logFinish(char *tID); // function to log that a thread has finished its time

void startClock();	   // function to start program clock
long getCurrentTime(); // function to check current time since clock was started
time_t programClock;   // the global timer/clock for the program

typedef struct thread // represents a single thread, you can add more members if required
{
	char tid[4];			// id of the thread as read from file
	unsigned int startTime; // Start time of the thread
	int state;				// 0 if hread is inactive, 1 if thread is active
	pthread_t handle;
	int retVal;
} Thread;

// you can add more functions here if required

int threadsLeft(Thread *threads, int threadCount);
int threadToStart(Thread *threads, int threadCount);
void *threadRun(void *t);						// the thread function, the code executed by each thread
int readFile(char *fileName, Thread **threads); // function to read the file content and build array of threads
void semWaitOrPostBasedOnThreadID(char thread_id, int action);
bool threadsReady(Thread *threads, int threadCount);
int threadPolarity(char thread_id);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}

	// you can add some suitable code anywhere in main() if required

	Thread *threads = NULL;
	int threadCount = readFile(argv[1], &threads);

	sem_init(&running, 0, 1);
	sem_init(&even, 0, 0);
	sem_init(&odd, 0, 0);

	startClock();
	while (threadsLeft(threads, threadCount) > 0) // put a suitable condition here to run your program
	{
		// you can add some suitable code anywhere in this loop if required

		int i = 0;
		while ((i = threadToStart(threads, threadCount)) > -1)
		{
			// you can add some suitable code anywhere in this loop if required
			// Locking the semaphores to the first thread to
			if (i == 0)
			{
				// semWaitOrPostBasedOnThreadID(threads[i].tid[2], 1);
				// last_thread_polarity = threads[i].tid[2];
				sem_post(&even);
				sem_post(&odd);
			}

			threads[i].state = 1;
			threads[i].retVal = pthread_create(&(threads[i].handle), NULL, threadRun, &threads[i]);
		}
		// Checking if all the threads are ready - aka running (have state 1)
		if (threads_ready == false)
		{
			printf("Checking if threads are ready %d\n", threads_ready);
			bool ready = threadsReady(threads, threadCount);

			printf("Threads are ready %d\n\n", !ready);
		}
	}
	return 0;
}

int readFile(char *fileName, Thread **threads) // do not modify this method
{
	FILE *in = fopen(fileName, "r");
	if (!in)
	{
		printf(
			"Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char *fileContent = (char *)malloc(((int)st.st_size + 1) * sizeof(char));
	fileContent[0] = '\0';
	while (!feof(in))
	{
		char line[100];
		if (fgets(line, 100, in) != NULL)
		{
			strncat(fileContent, line, strlen(line));
		}
	}
	fclose(in);

	char *command = NULL;
	int threadCount = 0;
	char *fileCopy = (char *)malloc((strlen(fileContent) + 1) * sizeof(char));
	strcpy(fileCopy, fileContent);
	command = strtok(fileCopy, "\r\n");
	while (command != NULL)
	{
		threadCount++;
		command = strtok(NULL, "\r\n");
	}
	*threads = (Thread *)malloc(sizeof(Thread) * threadCount);

	char *lines[threadCount];
	command = NULL;
	int i = 0;
	command = strtok(fileContent, "\r\n");
	while (command != NULL)
	{
		lines[i] = malloc(sizeof(command) * sizeof(char));
		strcpy(lines[i], command);
		i++;
		command = strtok(NULL, "\r\n");
	}

	for (int k = 0; k < threadCount; k++)
	{
		char *token = NULL;
		int j = 0;
		token = strtok(lines[k], ";");
		while (token != NULL)
		{
			// if you have extended the Thread struct then here
			// you can do initialization of those additional members
			// or any other action on the Thread members
			(*threads)[k].state = 0;
			if (j == 0)
				strcpy((*threads)[k].tid, token);
			if (j == 1)
				(*threads)[k].startTime = atoi(token);
			j++;
			token = strtok(NULL, ";");
		}
	}
	return threadCount;
}

void logStart(char *tID)
{
	printf("[%ld] New Thread with ID %s is started.\n", getCurrentTime(), tID);
}

void logFinish(char *tID)
{
	printf("[%ld] Thread with ID %s is finished.\n", getCurrentTime(), tID);
}

int threadsLeft(Thread *threads, int threadCount)
{
	int remainingThreads = 0;
	for (int k = 0; k < threadCount; k++)
	{
		if (threads[k].state > -1)
			remainingThreads++;
	}
	return remainingThreads;
}

int threadToStart(Thread *threads, int threadCount)
{
	for (int k = 0; k < threadCount; k++)
	{
		if (threads[k].state == 0 && threads[k].startTime == getCurrentTime())
			return k;
	}
	return -1;
}

void *threadRun(void *t) // implement this function in a suitable way
{
	Thread *thread = (Thread *)t;
	char thread_id_y = thread->tid[2];

	logStart(((Thread *)thread)->tid);
	// threadsReady(Thread *threads, int threadCount)
	printf("State %d\n\n", thread->state);

	int current_thread_polarity = threadPolarity(thread_id_y);

	if (last_thread_polarity == -1)
	{
		last_thread_polarity = current_thread_polarity;
		printf("Last Thread Polarity %d\n", thread_id_y);
	}
	else if (last_thread_polarity == current_thread_polarity)
	{
		printf("Last thread MATCHES\n");
	}
	// your synchronization logic will appear here

	semWaitOrPostBasedOnThreadID(thread_id_y, 0);

	// critical section starts here
	printf("[%ld] Thread %s is in its critical section\n", getCurrentTime(),
		   ((Thread *)t)->tid);
	// critical section ends here

	semWaitOrPostBasedOnThreadID(thread_id_y, 1);

	logFinish(((Thread *)thread)->tid);
	((Thread *)thread)->state = -1;
	printf("Threads ready %d\n", threads_ready);
	pthread_exit(0);
}

void startClock()
{
	programClock = time(NULL);
}

long getCurrentTime() // invoke this method whenever you want check how much time units passed
// since you invoked startClock()
{
	time_t now;
	now = time(NULL);
	return now - programClock;
}
void semWaitOrPostBasedOnThreadID(char thread_id, int action)
{
	// Parameters:
	// 	thread_id: the y digit in the id that determines if the thread even or odd
	// 	action: whether to wait the appropriate semaphores (0) or post the semaphores (1)
	// Behaviour:
	// 	Responsible for the syncrhonization management to prevent other threads from runninc simultaneuously

	// printf("Sem function\n");
	if (threads_ready == true)
	{
		if (action == 0)
		{
			printf("Sem waiting\n");
			if (thread_id % 2 == 0)
			{
				printf("EVEN sephamore locked\n");
				sem_wait(&even);
			}
			else
			{
				printf("ODD sephamore locked\n");
				sem_wait(&odd);
			}
			sem_wait(&running);
		}
		else
		{
			sem_post(&running);
			printf("Sem posting\n\n");
			if (thread_id % 2 == 0)
			{
				printf("ODD sephamore freed\n");
				sem_post(&odd);
			}
			else
			{
				printf("EVEN sephamore freed\n");
				sem_post(&even);
			}
		}
		if (thread_id % 2 == 0)
		{
			printf("Polarity :Even\n");
		}
		else
		{
			printf("Polarity :Odd\n");
		}
	}
	else
	{
		printf("THREADS AINT READY!\n");
		int value;
		sem_getvalue(&even, &value);
		if (value == 0)
			sem_post(&even);
		sem_getvalue(&odd, &value);
		if (value == 0)
			sem_post(&odd);
		sem_post(&running);
	}
}

bool threadsReady(Thread *threads, int threadCount)
{
	printf("In threads ready\n");
	printf("Thread count: %d\n", threadCount);
	int i = 0;
	while (i < threadCount)
	{
		printf("Thread state: %d\n", threads[i].state);
		if (threads[i].state < 0)
		{
			threads_ready = false;
			return false;
		}
		i++;
	}
	threads_ready = true;
	printf("Threads status %d\n", threads_ready);
	return true;
}

int threadPolarity(char thread_id)
{
	if (thread_id % 2 == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}