#include<stdio.h>
#include<string.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

void saveToFile(struct student s[], int n);

int appendStudentGUI(struct student s[], int *n, struct student new_s)
{
    if(*n >= 100) return 0; // Error max
    s[*n] = new_s;
    (*n)++;
    saveToFile(s, *n);
    return 1;
}