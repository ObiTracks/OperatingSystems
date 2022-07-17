#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

void RQ_command(char *process_name, int size, char *allocation_algorithm); // Request command
void RL_command(char *process_name);                                       // Release command
void C_command();                                                          // Compact command
void Status_command();                                                     // Status command

int main(int argc, char *argv[])
{

    while (1)
    {
        printf("\n");
        printf("Enter command: ");
        char base_command[100];
        char argument_1[100]; // process name
        int argument_2;       // size
        char argument_3[100]; // allocation algorithm

        scanf("%s %s %d %s", base_command, &argument_1, &argument_2, &argument_3);
        if (strcmp(base_command, "RQ") == 0)
        {
            RQ_command(argument_1, argument_2, argument_3);
        }
        else if (strcmp(base_command, "RL") == 0)
        {
            RL_command(argument_1);
        }
        else if (strcmp(base_command, "C") == 0)
        {
            C_command();
        }
        else if (strcmp(base_command, "Status") == 0)
        {
            Status_command();
        }
        else if (strcmp(base_command, "Exit") == 0)
        {
            break;
        }
        else
        {
            printf("Invalid command.\n");
        }
    }

    return 0;
}

void RQ_command(char *process_name, int size, char *allocation_algorithm)
{
}
void RL_command(char *process_name)
{
}
void C_command()
{
}
void Status_command()
{
}