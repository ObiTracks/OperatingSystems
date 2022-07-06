#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
  int id = fork();

  if (id > 0){
    // wait(NULL);
    printf("\nExecuting parent process\n");

    // Make the zombie process continue to run for x seconds
    int x = 5;
    sleep(x);

    
  } else if (id == 0){
    printf("Executing child process\n");
    exit(0);

  } else {
    printf("Fork Failed To Execute\n", NULL);
    exit(-1);
  }


  return 0;
}
