#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Student Management System (Console-based)

typedef struct Student{
    char name[50];
    char ID[20];
    int age;
    float grade;
}Student;

void PrintAllStudents(Student Students[],int TOTAL_STUDENTS) {
    int i;
    for(int i = 0; i < TOTAL_STUDENTS; i++){
        printf("\n%s | %s | %d | %.2f\n", 
                Students[i].name,
                Students[i].ID,
                Students[i].age,
                Students[i].grade);
    }
}

void AddStudent(Student Students[],int *TOTAL_STUDENTS) {
    printf("\nCurrent Total Students is : %d\n", *TOTAL_STUDENTS);

    printf("\nEntre The Name Of The New Student : ");
    getchar();
    gets(Students[*TOTAL_STUDENTS].name);
    printf("\nEnter The ID Of The New Student : ");
    getchar();
    gets(Students[*TOTAL_STUDENTS].ID);
    printf("\nEnter The Age Of The New Student : ");
    scanf("%d", &Students[*TOTAL_STUDENTS].age);
    printf("\nEnter The Grade OF The New Student : ");
    scanf("%f", &Students[*TOTAL_STUDENTS].grade);

    *TOTAL_STUDENTS += 1;
    printf("\nCurrent Total Students is : %d\n", *TOTAL_STUDENTS);
}

void UpdateStudent() {
    
}

void DeleteStudent() {

}


int main(){
    int i;
    int TOTAL_STUDENTS = 0;
    // Load Students From The Students File

    Student Students[100];
    

    FILE *file1;
    FILE *file2;
    file1 = fopen("file.csv", "r");

    if (file1 == NULL){
        printf("File Error");
        return 1;
    } 
    int read = 0;
    do{
        read = fscanf(file1, "%49[^,],%49[^,],%d,%f\n",
              Students[TOTAL_STUDENTS].name,
              Students[TOTAL_STUDENTS].ID,
              &Students[TOTAL_STUDENTS].age, 
              &Students[TOTAL_STUDENTS].grade);
        printf("\n\n%d\n\n", read);
        if (read = 4) TOTAL_STUDENTS++;
    }while(!feof(file1));

    fclose(file1);
    //Students System
    bool run1 = true;
    while (run1 == true){
        printf("\nWelcome To Our School Students System :\n");
        printf("\n1 - Check The Students List\n2 - Quit");
        int OP1;
        printf("\nChose 1 or 2 :");
        scanf("%d", &OP1);

        if (OP1 == 1)
        {
            bool run2 = true;
            while (run2 == true){
                printf("\n\n1 - Show All Students\n2 - Add New Student\n3 - update Student Information\n4 - Delete Student\n5 - quit");
                int OP2;
                printf("\nChose from 1 to 5 : ");
                scanf("%d", &OP2);
                if (OP2 == 1)
                {
                    PrintAllStudents(Students, TOTAL_STUDENTS);
                }
                else if (OP2 == 2)
                {
                    AddStudent(Students, &TOTAL_STUDENTS);
                }
                else if (OP2 == 3)
                {
                    /* update Student Information */
                }
                else if (OP2 == 4)
                {
                    /* Delete Student */
                }
                else run2 = false;
                
            }
        }
        else run1 = false; 
    }

    file2 = fopen("file.csv", "w");
    if (file2 == NULL){
        printf("File Loading Error");
        return 1;
    }
    
    for(i = 0; i < TOTAL_STUDENTS; i++){
        fprintf(file2, "%s,%s,%d,%f\n",
                Students[i].name,
                Students[i].ID,
                Students[i].age,
                Students[i].grade);
        if (ferror(file2)){
            printf("Error Writing To The File");
            return 1;
        }
    }

    fclose(file2);
    // Save Students System into The Students File
    return 0;
}
