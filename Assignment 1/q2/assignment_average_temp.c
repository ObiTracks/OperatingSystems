#include <stdio.h>
#include <unistd.h>

int main()
{
    

    int input_grades[10][6];
    int output_lines[6][1];
    FILE *file = fopen("sample_in_grades.txt", "r");

    // READING ALL THE GRADES INTO AN ARRAY FOR US TO USE
    for (int i = 0; i < 10; i++)
    {
            fscanf(file, "%d %d %d %d %d %d",
                   &input_grades[i][0],
                   &input_grades[i][1],
                   &input_grades[i][2],
                   &input_grades[i][3],
                   &input_grades[i][4],
                   &input_grades[i][5]);
    }


     // 6 assignment outputs, 1 average number calculation for each

    // int id_1, id_2, id_3;
    // id_1 = fork();
    // id_2 = fork();
    // id_3 = fork();

    for (int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf("%d ", input_grades[i][j]);
            // printf("%d", input_grades[i]);
        }
        printf("\nHELLO\n");
    }

    return 0;
}