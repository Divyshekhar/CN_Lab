#include <stdio.h>
#include <stdlib.h>

struct dob
{
    int day;
    int month;
    int year;
};

struct student
{
    int roll;
    char name[50];
    float CGPA;
    struct dob age;
};

void call_byr(struct student *a)
{
    printf("The roll number is\t%d\n", a->roll);
    printf("The name is \t%s\n", a->name);
    printf("The CGPA is \t%f\n", a->CGPA);
    printf("The day of the dob is \t%d\n", a->age.day);
    printf("The month of the dob is \t%d\n", a->age.month);
    printf("The year of the dob is \t%d\n", a->age.year);
}

void call_byv(struct student a)
{
    printf("The roll number is\t%d\n", a.roll);
    printf("The name is \t%s\n", a.name);
    printf("The CGPA is \t%f\n", a.CGPA);
    printf("The day of the dob is \t%d\n", a.age.day);
    printf("The month of the dob is \t%d\n", a.age.month);
    printf("The year of the dob is \t%d\n", a.age.year);
}

int main()
{
    struct student stud;
    printf("enter the roll number of the student");
    scanf("%d", &stud.roll);
    printf("\nenter the name of the student");
    scanf("%s", stud.name);
    printf("\nenter the cgpa of the student");
    scanf("%f", &stud.CGPA);
    printf("\nenter the day of your dob");
    scanf("%d", &stud.age.day);
    printf("\nenter the day of your dob");
    scanf("%d", &stud.age.month);
    printf("\nenter the year of your dob");
    scanf("%d", &stud.age.year);

    printf("the values using call by reference is \n");
    call_byr(&stud);
    printf("the values using call by value is \n");
    call_byv(stud);

    return 0;
}