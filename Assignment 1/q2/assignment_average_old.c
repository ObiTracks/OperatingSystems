#include <stdio.h>
#include<unistd.h>

int main()
{
    int input_grades[10][6];
    int output_lines[6][1]; // 6 assignment outputs, 1 average number calculation for each

    FILE *file = fopen("sample_in_grades.txt", "r");

    // READING ALL THE GRADES INTO AN ARRAY FOR US TO USE
    int i = 0;
    while(!feof(file)){
            fscanf(file,"%d %d %d %d %d %d",
                &input_grades[i][0],
                &input_grades[i][1],
                &input_grades[i][2],
                &input_grades[i][3],
                &input_grades[i][4],
                &input_grades[i][5]
            );
        i++;
    }
    
    for (int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf("%d ", input_grades[i][j]);
            // printf("%d", input_grades[i]);
        }
        printf("\nHELLO\n");
    }

    int gta_1, gta_2, gta_3;
    gta_1 = fork();
    // gta_2 = fork();
    // gta_3 = fork();

    // ASSIGNING THE GRAD TAs ASSIGNMENTS
    // PARENT PROCESS
    if (gta_1 > 0 && gta_2 > 0 && gta_3 > 0){
        printf("In teacher process\n\n");
    } 
    // FIRST FORK 
    else if (gta_1 == 0 && gta_2 > 0 && gta_3 > 0){
        printf("In grad TA process 1\n\n");
        int ta_1 = fork();
        int ta_2 = fork();
        float total = 0;
        float average = 0;

        int assignment_index;

        // Depending on which TA process is running, specify the assignment they are assigned
        if (ta_1 == 0){
            assignment_index = 0;
        }else if (ta_2 == 0){
            assignment_index = 1;
        }

        for (int i = 0; i < 10; i++){
            int grade = input_grades[i][assignment_index];
            total = total + grade;
        }
        average = total/10;
        output_lines[assignment_index][0] = average;        

    } 
    // SECOND FORK
    
    return 0;
}