#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main() {

    // Call z_creator to create a zombie process
    system("./z_creator &");
    printf("Parent process finished running\n");
    system("ps -l");

    sleep(2);
    printf("Killing the parent process to kill zombie processes \n");
    system("kill -9 $(ps -l|grep -w Z|tr -s ' '|cut -d ' ' -f 5)");
    
    sleep(4);
    printf("\n\nNew Process States\n");

    system("ps -l");


    return 0;
}
