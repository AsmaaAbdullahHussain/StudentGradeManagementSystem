#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include<windows.h>
typedef struct Subject Subject;
typedef struct Student Student;


struct Subject {
    char name[20];
    float score;
};
struct Student {
    int Id;
    char name[20];
    Subject *subjects;
    char grade;
    float averageScore;
    int numberOfSubjects;
};

int ExtendArray(Student** students, int numberOfStudents);
float CalculateAverageScore(Subject* subjects, int numberOfSubjects);
char CalculateGrade(float averageScore);
void AddStudent(Student** students, int* arraySize, int* numberOfStudents);
void UpdateScores(Student* std);
Student* SearchById(Student** students, int id, int numberOfStudents);
void DisplayStudent(Student* student);
void DisplayAllStudents(Student** students, int numberOfStudents);
void DisplayStudentWithHighestScore(Student** students, int numberOfStudents);
void DisplayPassedStudents(Student** students, int numberOfStudents);
void DisplayFailedStudents(Student** students, int numberOfStudents);


void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
int ExtendArray(Student*** students, int numberOfStudents)
{
    Student** newArray = (Student**)malloc(2 * numberOfStudents * sizeof(Student*));
    for (int i = 0;i < numberOfStudents;i++)
    {
        newArray[i] = (*students)[i];
    }
    *students = newArray;
    return 2 * numberOfStudents;

}
float CalculateAverageScore(Subject* subjects,int numberOfSubjects) {
    int sum = 0;
    for (int i = 0;i < numberOfSubjects;i++) {
        sum += subjects[i].score;
    }
    return (float)sum / numberOfSubjects;
}
char CalculateGrade(float averageScore)
{
    if (averageScore >= 90) {
        return 'A';
    }
    else if(averageScore >= 80) {
        return 'B';
    }
    else if (averageScore >= 70) {
        return 'C';
    }
    else if (averageScore >= 60) {
        return 'D';
    }
    else {
        return 'F';
    }
}
void AddStudent(Student** students ,int* arraySize,int* numberOfStudents)
{
    Student* std = (Student*)malloc(1 * sizeof(Student));
    printf("\nEnter Student ID : ");
    scanf_s("%d", &std->Id );
    while (SearchById(students, std->Id, *numberOfStudents) != 0) {
        SetColor(4);
        printf("this id alredy exist enter another id : ");
        SetColor(15);
        scanf_s("%d", &std->Id);
    }
    printf("\nEnter Student Name : ");
    scanf_s("%s", std->name,20);
    printf("\nEnter number of subjects : ");
    scanf_s("%d", &std->numberOfSubjects);
    std->subjects = (Subject*)malloc(std->numberOfSubjects * sizeof(Subject));
    
    for (int i = 0;i < std->numberOfSubjects;i++)
    {
        printf("\nEnter subject%d name : ",i+1);
        scanf_s("%s", std->subjects[i].name,20);
        
        printf("\nEnter subject%d score :", i+1);
        scanf_s("%f", &std->subjects[i].score); 
        
    }
    std->averageScore = CalculateAverageScore(std->subjects, std->numberOfSubjects);
    std->grade = CalculateGrade(std->averageScore);
    
    
    if (*numberOfStudents == *arraySize)
    {
        *arraySize= ExtendArray(&students,*numberOfStudents);
    }
    students[(*numberOfStudents)++] = std;
    
}
void UpdateScores(Student* std) {
    for (int i = 0;i < std->numberOfSubjects;i++) {
        printf("enter new score of subject %s \n", std->subjects[i].name);
        scanf_s("%f", &std->subjects[i].score);
    }
    std->averageScore = CalculateAverageScore(std->subjects, std->numberOfSubjects);
    std->grade = CalculateGrade(std->averageScore);
}
Student* SearchById(Student** students,int id,int numberOfStudents) {
    int i = 0;
    while (i < numberOfStudents && students[i]->Id != id ) {
        i++;
    }
    if (i == numberOfStudents) {
        return 0;
    }
    return students[i];

}
void DisplayStudent(Student* student) {
    printf("Student information\n\n");
    printf("Id : %d\tName : %s\tAverage score : %f\tGrade : %c\n", student->Id, student->name, student->averageScore, student->grade);
    printf("Student Subjects\n");
    for (int i = 0;i < student->numberOfSubjects;i++) {
        printf("\tName : %s \t Score : %f\n", student->subjects[i].name, student->subjects[i].score);
    }

}
void DisplayAllStudents(Student** students,int numberOfStudents) {
    for (int i = 0;i < numberOfStudents;i++) {
        printf("Student%d information\n\n", i);
        printf("Id : %d\tName : %s\tAverage score : %f\tGrade : %c\n", students[i]->Id, students[i]->name, students[i]->averageScore, students[i]->grade);

    }
}
void DisplayStudentWithHighestScore(Student** students,int numberOfStudents) 
{
    float max = students[0]->averageScore;
    int index=0;
    for (int i = 0;i < numberOfStudents;i++)
    {
        if (students[i]->averageScore > max) {
            max = students[i]->averageScore;
            index = i;
        }
    }
    printf("Student With Highest Score :\nId : %d\tName : %s\tScore : %f\n", students[index]->Id, students[index]->name, students[index]->averageScore);
}
void DisplayScoreForAllStudents(Student** students, int numberOfStudents)
{
    if (numberOfStudents == 0) {
        SetColor(4);
        printf("there is no students.\n");
    }
    else {
        SetColor(6);
        printf("the average score of all students.\n\n");
        SetColor(15);
        for (int i = 0;i < numberOfStudents;i++) {
            printf("Id : %d\tName : %s\tAverage Score : %f\n", students[i]->Id, students[i]->name, students[i]->averageScore);
        }
    }
  
}
void DisplayPassedStudents(Student** students, int numberOfStudents)
{
    printf("list of students who passed \n");
    int check=0;
    for (int i = 0;i < numberOfStudents;i++) {
        if (students[i]->grade != 'F')
        {
            printf("Id : %d\tName : %s\tAverage Score : %f\tGrade : %c\n", students[i]->Id, students[i]->name, students[i]->averageScore, students[i]->grade);
            check = 1;
        }
    }

}
void DisplayFailedStudents(Student** students, int numberOfStudents)
{
    printf("list of students who failed \n");
    for (int i = 0;i < numberOfStudents;i++) {
        if (students[i]->grade == 'F')
        {
            printf("Id : %d\tName : %s\tAverage Score : %f\tGrade : %c\n", students[i]->Id, students[i]->name, students[i]->averageScore, students[i]->grade);

        }
    }
}



int main()
{
    Student** students;
    int numberOfStudents = 0, arraySize = 2;
    students= (Student**)malloc(2 * sizeof(Student*));
    char fileName[20] = "StudentData.txt";
    //ReadFromFile(fileName, &students, &arraySize, &numberOfStudents);
    char menu[10][50] = 
    { 
        {"Add Student"},
        {"Display all Students"},
        {"Find Student By ID"},
        {"Update Scores"},
        {"display the student with highest score"},
        {"display the average score of all students"},
        {"display passed Students"},
        {"display failed students"},
        {"close"}
    };
    char ch1, ch2, next;
    int index = 0, colorIndex = 0, i = 0, condition = 1 ,id;
    Student* std;
    SetColor(9);
    do {
        system("cls");
        SetColor(9);
        printf("\n\t\t\t\t--------------------------------------\n\t\t\t\t|  Student Grade Management System  |\n\t\t\t\t--------------------------------------\n\n");
        SetColor(15);

        for (index = 0;index < 9; index++)
        {
            if (index == colorIndex)
            {
                SetColor(2);
                printf("\t\t\t\t\t%s\n", menu[index]);

                SetColor(15);
            }
            else
            {

                printf("\t\t\t\t\t%s\n", menu[index]);
            }

        }
        ch1 = _getch();


        if (ch1 == -32)
        {
            ch2 = _getch();
            switch (ch2)
            {
            case 80: //down
                colorIndex = ((++colorIndex % 9) + 9) % 9;

                break;
            case 72:  //up
                colorIndex = ((--colorIndex % 9) + 9) % 9;
                break;
            default:
                break;
            }

        }
        else if (ch1 == 13)
        {
            switch (colorIndex)
            {
            case 0://Add Student
            
                AddStudent(students, &arraySize, &numberOfStudents);

                break;
            
            case 1://Display all Students
            
                DisplayAllStudents(students, numberOfStudents);
                next=_getch();
                break;
            
            case 2://Find Student By ID
            
                
                printf("enter student id : ");
                scanf_s("%d", &id);
                std = SearchById(students, id, numberOfStudents);
                if (std != NULL) {
                    DisplayStudent(std);
                    
                }
                else {
                    printf("Student not found.\n");

                }
                next = _getch();
                break;
            
            case 3://Update Scores
            
                
                printf("enter student id : ");
                scanf_s("%d", &id);
                std = SearchById(students, id, numberOfStudents);
                if (std != NULL) {
                    DisplayStudent(std);
                    UpdateScores(std);
                }
                else {
                    printf("Student not found.\n");
                }
                next = _getch();
                break;
            
            case 4://display the student with highest score
            
                DisplayStudentWithHighestScore(students, numberOfStudents);
                next = _getch();
                break;
            
            case 5://display the average score of all students
            
                DisplayScoreForAllStudents(students, numberOfStudents);
                next = _getch();
                break;
            
            case 6://display passed Students
            
                DisplayPassedStudents(students, numberOfStudents);
                next = _getch();
                break;
            
            case 7://display failed students
            
                DisplayFailedStudents(students, numberOfStudents);
                next = _getch();
                break;
            
            case 8://close
                return 0;
            default:

                break;
            }
        }
    } while (1);

    return 0;
}
