
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>

#define N_THREADS 5

int main(int argc, char *argv[]);
void *loop_function(void *arg);

int main(int argc, char *argv[])
{

    int i;
    pthread_t tid;
    pthread_attr_t attr;
    int s;
    
    s = pthread_attr_init(&attr);
    if (s != 0)  {
        printf("Thread attr init failed");
        return -1;
    }

    printf("This program would create threads\n");
    s = pthread_create(&tid, &attr, loop_function, NULL);

    if (s == 0){
        sleep(1);
        printf("Custom thread created successfully\n");
        for (i = 0; i < N_THREADS; i++) {
            printf("I am the process created by compiler By default\n");
            sleep(1);
        }
        pthread_join(tid, NULL);
    }
    else {
        printf("Error");
    }
    return 0;
}

void *loop_function(void *args)
{
    for (int i = 0; i < N_THREADS; i++)
    {
        printf("I am a Custom Thread Function Created by user.\n");
        sleep(1);
    }
    exit(0);
}