#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

float calculate_avg(int col_index, int input_grades[10][6], float output_averages[6]);
void print_input_grades(int input_grades[10][6]);
void print_output_averages(float output_averages[6]);
void GTA_FORK_TAS(int gta_num, int input_grades[10][6], float output_averages[6]);

float calculate_avg(int col_index, int input_grades[10][6], float output_averages[6])
{
    float sum = 0;
    float average = 0;

    for (int i = 0; i < 10; i++)
    {
        int grade = input_grades[i][col_index];
        sum = sum + grade;
    }

    average = sum / 10;
    return average;
}

void print_input_grades(int input_grades[10][6])
{
    printf("\nInput Grades:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("        ");
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", input_grades[i][j]);
            // printf("%d", input_grades[i]);
        }
        printf("\n");
    }
}
void print_output_averages(float output_averages[6])
{
    printf("\nOutput Averages:\n");
    for (int i = 0; i < 6; i++)
    {
        printf("    Assignment %d - Average = %.2f\n", i + 1, output_averages[i]);
    }
}
// write a loop that prints "Hello"

void GTA_FORK_TAS(int gta_num, int input_grades[10][6], float output_averages[6])
{
    // printf("    GTA NUM: %d\n", gta_num);
    printf("    -> In GTA process %d\n", gta_num);
    // int ta_2 = fork();
    // int ta_1 = fork();

    int col_index;
    float avg;

    if (fork() == 0)
    {
        // Info: TA #1 is responsible for assignment 1 (column 0)
        col_index = (gta_num * 2) - 2;
        printf("        ->-> In TA process %d\n", col_index);
        avg = calculate_avg(col_index, input_grades, output_averages);
        output_averages[col_index] = avg;

        exit(0);
    }
    if (fork() == 0)
    {
        // Info: TA #2 is responsible for assignment 2 (column 1)
        col_index = (gta_num * 2) - 1;
        printf("        ->-> In TA process %d\n", col_index);
        avg = calculate_avg(col_index, input_grades, output_averages);
        output_averages[col_index] = avg;

        exit(0);
    }
    wait(NULL);
    printf("        *Tas Complete*\n");
}

int main()
{
    int input_grades[10][6];
    float output_averages[6]; // 6 assignment outputs, 1 average number calculation for each

    FILE *file = fopen("sample_in_grades.txt", "r");

    // READING ALL THE GRADES INTO AN ARRAY FOR US TO USE
    int i = 0;
    while (!feof(file))
    {
        fscanf(file, "%d %d %d %d %d %d",
               &input_grades[i][0],
               &input_grades[i][1],
               &input_grades[i][2],
               &input_grades[i][3],
               &input_grades[i][4],
               &input_grades[i][5]);
        i++;
    }
    print_input_grades(input_grades);

    int gta_num;

    // PARENT PROCESS
    printf("\n- In Teacher process\n");

    if (fork() == 0) {
        // FIRST GTA PROCESS
        // Info: GradTA responsible for chapter 1 (columns 0 & 1)
        gta_num = 1;
        GTA_FORK_TAS(gta_num, input_grades, output_averages);
        exit(0);
    } else{
        wait(NULL);
        printf("        GTA1 Done \n");
    }

    if (fork() == 0) {
        // SECOND GTA PROCESS
        // Info: GradTA responsible for chapter 2 (columns 2 & 3)
        gta_num = 2;
        GTA_FORK_TAS(gta_num, input_grades, output_averages);
        exit(0);
    } else{
        wait(NULL);
        printf("        GTA2 Done \n");
    }
    
    if (fork() == 0) {
        // THIRD GTA PROCESS
        // Info: GradTA responsible for chapter 3 (columns 4 & 5)
        gta_num = 3;
        GTA_FORK_TAS(gta_num, input_grades, output_averages);
        exit(0);
    } else {
        wait(NULL);
        printf("        GTA3 Done \n");
    }

    // wait(NULL);
    printf("\nProgram Finished");
    print_output_averages(output_averages);

    return 0;
}
