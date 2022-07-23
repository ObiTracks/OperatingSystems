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

// Command functions
void RQ_command(int process_number, int size, char *allocation_algorithm); // Request command
void RL_command(int process_number);                                       // Release command
void C_command();                                                          // Compact command
void Status_command();                                                     // Status command

// Main funcitons
void initialize_memory(int size);
void first_fit(int process_number, int size);
void best_fit(int process_number, int size);
void worst_fit(int process_number, int size);

int findFirstFit(int size);
int findBestFit(int size);
int findWorstFit(int size);

// Utility functions
void insertProcess(int process_number, int size);
void updateHole(int hole_number, int size);
void mergeHolesifTouching(int hole_number, int next_hole_number);
void mergeHoleToNeighborsIfTouching(int hole_number);
int calculate_total_used_memory();
int calculate_total_Free_memory();

struct HOLE hole_list[100];
struct PROCESS process_list[100];
int num_holes;
int memory;

int main(int argc, char *argv[])
{
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
            printf("RQ was entered\n");
            RQ_command(argument_1[1], argument_2, argument_3);
        }
        else if (strcmp(base_command, "RL") == 0)
        {
            printf("RL was entered\n");
            RL_command(argument_1[1]);
        }
        else if (strcmp(base_command, "C") == 0)
        {
            printf("C was entered\n");
            C_command();
        }
        else if (strcmp(base_command, "Status") == 0)
        {
            printf("Status was entered\n");
            Status_command();
        }
        else if (strcmp(base_command, "Exit") == 0)
        {
            printf("Exit was entered\n");
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

int findFirstFit(int size)
{
    int i;
    for (i = 0; i < num_holes; i++)
    {
        if (hole_list[i].length >= size)
        {
            return i;
        }
    }
    return -1;
}

int findBestFit(int size)
{
    int i;
    int smallest_hole_index = -1;
    int smallest_hole_size = -1;
    for (i = 0; i < num_holes; i++)
    {
        if (hole_list[i].length >= size && hole_list[i].length < smallest_hole_size)
        {
            smallest_hole_index = i;
            smallest_hole_size = hole_list[i].length;
        }
    }
    return smallest_hole_index;
}

int findWorstFit(int size)
{
    int i;
    int biggest_hole_index = -1;
    int biggest_hole_size = -1;
    for (i = 0; i < num_holes; i++)
    {
        if (hole_list[i].length >= size && hole_list[i].length > biggest_hole_size)
        {
            biggest_hole_index = i;
            biggest_hole_size = hole_list[i].length;
        }
    }
    return biggest_hole_index;
}

int findSuitableHole(int size)
{
    // find the first hole that is big enough
    for (int i = 0; i < num_holes; i++)
    {
        if (hole_list[i].length >= size)
        {
            return i;
        }
    }
    return -1;
}

void insertProcess(int process_number, int size)
{
    // insert the process into the process list
    process_list[process_number].start_address = hole_list[process_number].base;
    process_list[process_number].limit = size;
    process_list[process_number].valid = 1;
}

void updateHole(int hole_number, int size)
{
    // update the hole list
    hole_list[hole_number].base = hole_list[hole_number].base + size;
    hole_list[hole_number].length = hole_list[hole_number].length - size;
}

void mergeHolesifTouching(int hole_number, int next_hole_number)
{
    // merge the two holes if they touch
    if (hole_number < next_hole_number)
    {
        if (hole_list[hole_number].base + hole_list[hole_number].length == hole_list[next_hole_number].base)
        {
            hole_list[hole_number].length = hole_list[hole_number].length + hole_list[next_hole_number].length;
            hole_list[next_hole_number].valid = 0;
        }
    }
    else if (next_hole_number < hole_number)
    {
        if (hole_list[next_hole_number].base + hole_list[hole_number].length == hole_list[hole_number].base)
        {
            hole_list[hole_number].base = hole_list[next_hole_number].base;
            hole_list[hole_number].length = hole_list[hole_number].length + hole_list[next_hole_number].length;
            hole_list[next_hole_number].valid = 0;
        }
    }
}

void mergeHoleToNeighborsIfTouching(int hole_number)
{
    // merge the hole with the neighbors if they touch
    if (hole_list[hole_number].base > 0)
    {
        mergeHolesifTouching(hole_number, hole_number - 1);
    }
    if (hole_list[hole_number].base + hole_list[hole_number].length < 100)
    {
        mergeHolesifTouching(hole_number, hole_number + 1);
    }
}

void mergeAllHolesifTouching()
{
    // merge all the holes
    for (int i = 0; i < num_holes; i++)
    {
        mergeHoleToNeighborsIfTouching(i);
    }
}

// // COMMAND FUNCTIONS
void RQ_command(int process_number, int size, char *allocation_algorithm)
{
    if (strcmp(allocation_algorithm, "F") == 0)
    {
        printf("\n%d %d %s\n", process_number, size, allocation_algorithm);
        first_fit(process_number, size);
    }
    else if (strcmp(allocation_algorithm, "B") == 0)
    {
        printf("\n%d %d %s\n", process_number, size, allocation_algorithm);
        best_fit(process_number, size);
    }
    else if (strcmp(allocation_algorithm, "W") == 0)
    {
        printf("%d %d %s\n", process_number, size, allocation_algorithm);
        worst_fit(process_number, size);
    }
    else
    {
        printf("Invalid allocation algorithm.\n");
    }
}

void RL_command(int process_number)
{
    struct PROCESS process = process_list[process_number];
    int freed_memory_start = process.start_address;
    int freed_memory_end = process.start_address + process.limit;
    process_list[process_number].start_address = NULL;
    process_list[process_number].limit = NULL;
    process_list[process_number].valid = NULL;

    struct HOLE hole;
    hole_index = findSpaceForNewHole();
    if (hole_index != -1)
    {
        hole = hole_list[i];
        printf("Successfully released memory for process P%d\n", process_number);
        mergeHoleToNeighborsIfTouching(i);
    }
    else
    {
        printf("Unable to release memory\n");
    }
}

int findSpaceForNewHole()
{
    for (int i = 0; i < num_holes; i++)
    {
        if (hole_list[i] == NULL)
        {
            return i
        }
    }
    return -1;
}

void C_command()
{
}

void Status_command()
{
    // print allocated memory
    printf("\nPartitions [Allocated memory = %d]\n", calculate_total_used_memory());

    // print out processes
    for (int i = 0; i < num_processes; i++)
    {
        if (process_list[i].valid == 1)
        {
            printf("Address [%d:%d] Process P%s\n", process_list[i].start_address, process_list[i].start_address + process_list[i].limit, i);
        }
    }

    // print out holes
    printf("\Holes [Free memory = %d]\n", calculate_total_free_memory());

    // print out processes
    for (int i = 0; i < num_processes; i++)
    {
        if (process_list[i].valid == 1)
        {
            printf("Address [%d:%d] Len = %d\n", hole_list[i].start_address, hole_list[i].start_address + hole_list[i].length, hole_list[i].length);
        }
    }
}

int calculate_total_used_memory()
{
    int total_used_memory = 0;

    for (int i = 0; i < num_processes; i++)
    {
        total_used_memory = total_used_memory + process_list[i].limit;
    }

    return total_used_memory;
}

int calculate_total_free_memory()
{
    int total_free_memory = 0;

    for (int i = 0; i < num_processes; i++)
    {
        total_free_memory = total_free_memory + hole_list[i].length;
    }

    return total_free_memory;
}

// ALLOCATION ALGORITHMS

void first_fit(int process_number, int size)
{
    // find the first hole that is big enough
    int hole_number = findFirstFit(size);
    if (hole_number == -1)
    {
        printf("No hole of sufficient size\n");
    }
    else
    {
        // insert the process into the process list
        insertProcess(process_number, size);
        // update the hole list
        updateHole(hole_number, size);
        // merge the holes if they touch
        mergeAllHolesifTouching();
        printf("Successfully allocated %d to process P%d\n", size, process_number);
    }
}

void best_fit(int process_number, int size)
{
    // find the best hole that is big enough
    int hole_number = findBestFit(size);
    if (hole_number == -1)
    {
        printf("No hole of sufficient size\n");
    }
    else
    {
        // insert the process into the process list
        insertProcess(process_number, size);
        // update the hole list
        updateHole(hole_number, size);
        // merge the holes if they touch
        mergeAllHolesifTouching();
        printf("Successfully allocated %d to process P%d\n", size, process_number);
    }
}

void worst_fit(int process_number, int size)
{
    // find the worst hole that is big enough
    int hole_number = findWorstFit(size);
    if (hole_number == -1)
    {
        printf("No hole of sufficient size\n");
    }
    else
    {
        // insert the process into the process list
        insertProcess(process_number, size);
        // update the hole list
        updateHole(hole_number, size);
        // merge the holes if they touch
        mergeAllHolesifTouching();
        printf("Successfully allocated %d to process P%d\n", size, process_number);
    }
}

void update_holes_list()
{
}
