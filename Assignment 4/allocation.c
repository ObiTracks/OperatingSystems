#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct HOLE
{
    int base;
    int length;
    int valid; // true 1 or false 0
};
struct PROCESS
{
    int start_address;
    int limit;
    int valid; // true 1 or false 0
};

void RQ_command(int process_number, int size, char *allocation_algorithm); // Request command
void RL_command(int process_number);                                       // Release command
void C_command();                                                          // Compact command
void Status_command();                                                     // Status command

void initialize_memory(int size);
// void first_fit(int process_number, int size);
// void best_fit(int process_number, int size);
// void worst_fit(int process_number, int size);
// void update_holes_list();

// int findSuitableHole(int size);
// void insertProcess(int process_number, int size);
// void updateHole(int hole_number, int size);
// void mergeHolesifTouching(int hole_number, int next_hole_number);
// void mergeHoleToNeighborsIfTouching(int hole_number);

// int blockSize[] = {30, 5, 10};
// int processSize[] = {10, 6, 9};
// int m = sizeof(blockSize)/sizeof(blockSize[0]);
// int n = sizeof(processSize)/sizeof(processSize[0]);
struct HOLE hole_list[100];
struct PROCESS process_list[100];
int num_holes;
int memory;

int main(int argc, char *argv[])
{

    // char *a = argv[1];
    // int size = atoi(a);
    // initialize_memory(size);
    initialize_memory(atoi(argv[1]));

    while (1)
    {
        printf("\n");
        printf("Enter command: ");
        char base_command[100];
        char argument_1[100]; // process name
        int argument_2;       // size
        char argument_3[100]; // allocation algorithm

        scanf("%s %s %d %s", base_command, argument_1, &argument_2, argument_3);
        if (strcmp(base_command, "RQ") == 0)
        {
            printf("RQ was entered");
            // RQ_command(argument_1[1], argument_2, argument_3);
        }
        else if (strcmp(base_command, "RL") == 0)
        {
            printf("RL was entered");
            // RL_command(argument_1[1]);
        }
        else if (strcmp(base_command, "C") == 0)
        {
            printf("C was entered");
            // C_command();
        }
        else if (strcmp(base_command, "Status") == 0)
        {
            printf("Status was entered");
            // Status_command();
        }
        else if (strcmp(base_command, "Exit") == 0)
        {
            printf("Exit was entered");
            break;
        }
        else
        {
            printf("Invalid command. Enter a valid command or type 'Exit' to end the program.\n");
        }
    }

    return 0;
}

// PROGRAM FUNCTIONS
void initialize_memory(int size)
{
    // allocate the initial memoryd
    memory = size;
    printf("Allocated %d bytes of memory\n", size);

    // initially there is just one big hole
    hole_list[0].base = 0;
    hole_list[0].length = size;
    hole_list[0].base = 0;
    num_holes = 1;
}

// int findSuitableHole(int size) {
//     // find the first hole that is big enough
//     for (int i = 0; i < num_holes; i++) {
//         if (hole_list[i].length >= size) {
//             return i;
//         }
//     }
//     return -1;
// }

// void insertProcess(int process_number, int size) {
//     // insert the process into the process list
//     process_list[process_number].start_address = hole_list[process_number].base;
//     process_list[process_number].limit = size;
//     process_list[process_number].valid = 1;
// }

// void updateHole(int hole_number, int size) {
//     // update the hole list
//     hole_list[hole_number].base = hole_list[hole_number].base + size;
//     hole_list[hole_number].length = hole_list[hole_number].length - size;
// }

// void mergeHolesifTouching(int hole_number, int next_hole_number) {
//     // merge the two holes if they touch
//     if (hole_number < next_hole_number){
//         if (hole_list[hole_number].base + hole_list[hole_number].length == hole_list[next_hole_number].base) {
//             hole_list[hole_number].length = hole_list[hole_number].length + hole_list[next_hole_number].length;
//             hole_list[next_hole_number].valid = 0;
//         }
//     }
//     else if (next_hole_number < hole_number){
//         if (hole_list[next_hole_number].base + hole_list[hole_number].length == hole_list[hole_number].base) {
//             hole_list[hole_number].base = hole_list[next_hole_number].base;
//             hole_list[hole_number].length = hole_list[hole_number].length + hole_list[next_hole_number].length;
//             hole_list[next_hole_number].valid = 0;
//         }
//     }
// }

// void mergeHoleToNeighborsIfTouching(int hole_number) {
//     // merge the hole with the neighbors if they touch
//     if (hole_list[hole_number].base > 0) {
//         mergeHolesifTouching(hole_number, hole_number - 1);
//     }
//     if (hole_list[hole_number].base + hole_list[hole_number].length < 100) {
//         mergeHolesifTouching(hole_number, hole_number + 1);
//     }
// }

// void mergeAllHolesifTouching() {
//     // merge all the holes
//     for (int i = 0; i < num_holes; i++) {
//         mergeHoleToNeighborsIfTouching(i);
//     }
// }

// // COMMAND FUNCTIONS
// void RQ_command(int process_number, int size, char *allocation_algorithm)
// {
//     if(strcmp(allocation_algorithm, "F") == 0){
//         printf("%d %d %s\n", process_number, size, allocation_algorithm);
//         first_fit(process_number, size);
//     }
//     else if(strcmp(allocation_algorithm, "B") == 0){
//         printf("%d %d %s\n", process_number, size, allocation_algorithm);
//         best_fit(process_number, size);
//     }
//     else if(strcmp(allocation_algorithm, "W") == 0){
//         printf("%d %d %s\n", process_number, size, allocation_algorithm);
//         worst_fit(process_number, size);
//     }
//     else{
//         printf("Invalid allocation algorithm.\n");
//     }
// }

// void RL_command(int process_number)
// {
// }

// void C_command()
// {
// }

// void Status_command()
// {
// }

// // ALLOCATION ALGORITHMS

// void first_fit(int process_number, int size) {
//     // find the first hole that is big enough
//     int hole_number = findSuitableHole(size);
//     if (hole_number == -1) {
//         printf("No suitable hole found.\n");
//     } else {
//         // insert the process into the process list
//         insertProcess(process_number, size);
//         // update the hole list
//         updateHole(hole_number, size);
//         // merge the holes if they touch
//         mergeAllHolesifTouching();
//     }
// }

// void best_fit(int process_number, int size){

// }
// void worst_fit(int process_number, int size){

// }
// void update_holes_list(){

// }