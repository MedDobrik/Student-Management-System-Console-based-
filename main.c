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

    printf("\n======- Students List -======\n\n");
    for(int i = 0; i < TOTAL_STUDENTS; i++){
        if(Students[i].name[0] != '\0'){
            printf("\nName\t: %s\nID\t:%s\nAge\t:%d\nGrade\t:%.2f\n", 
                Students[i].name,
                Students[i].ID,
                Students[i].age,
                Students[i].grade);
            printf("-----------------------");
        }
    }
    printf("\n=============================\n\n");

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

void UpdateStudent(Student Students[], int *TOTAL_STUDENTS) {
    // Find Student :
    int i, found, OP;
    char Find_name[50];
    printf("\n\nEnter Students Name : ");
    getchar();
    gets(Find_name);

    for(i = 0; i < *TOTAL_STUDENTS; i++){
        if(strcmp(Find_name, Students[i].name) == 0){
            found = i;
            printf("\n\n======- Students Found -======\n");
            printf("\nName\t: %s\nID\t:%s\nAge\t:%d\nGrade\t:%.2f\n", 
                Students[i].name,
                Students[i].ID,
                Students[i].age,
                Students[i].grade);
            printf("-----------------------");
            int run = 1;
            do{
                printf("\n\n1 - Change Name\n2 - Change ID\n3 - Change Age\n4 - Change grade\n5 - quit");
                printf("\n Chose From 1 to 5 : ");
                scanf("%d", &OP);
                if(OP == 1){
                    printf("\nEnter The New Name : ");
                    getchar();
                    gets(Students[found].name);
                    printf("\nThe Name is changed Successfully");
                }
                else if (OP == 2)
                {
                    printf("\nEnter The New ID : ");
                    getchar();
                    gets(Students[found].ID);
                    printf("\nThe ID is changed Successfully");

                }
                else if (OP == 3)
                {
                    printf("\nEnter The New Age : ");
                    scanf("%d", &Students[found].age);
                    printf("\nThe Age is changed Successfully");

                }
                else if (OP == 4)
                {
                    printf("\nEnter The New Grade : ");
                    scanf("%f", &Students[found].grade);
                    printf("\nThe Grade is changed Successfully");

                }
                else run = 0;
            }while(run == 1);
            
            break;
        }

        if(i == *TOTAL_STUDENTS - 1 && found != i){
            printf("\n=====- Students Not Found -=====\n");
        }
    }
}

void DeleteStudent(Student Students[], int TOTAL_STUDENTS) {

    char name[50];

    printf("\n\nEnter Students Name To Delete : ");
    getchar();
    gets(name);

    for(int i = 0; i < TOTAL_STUDENTS; i++){
        if (strcmp(Students[i].name,name) == 0){
            Students[i].name[0] = '\0';
            printf("Students Deleted Successfully");
        }
    }
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
                    UpdateStudent(Students, &TOTAL_STUDENTS);
                }
                else if (OP2 == 4)
                {
                    DeleteStudent(Students, TOTAL_STUDENTS);
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

        if(Students[i].name[0] != '\0'){
            fprintf(file2, "%s,%s,%d,%f\n",
                Students[i].name,
                Students[i].ID,
                Students[i].age,
                Students[i].grade);
        }
        
        if (ferror(file2)){
            printf("Error Writing To The File");
            return 1;
        }
    }

    fclose(file2);
    // Save Students System into The Students File
    return 0;
}