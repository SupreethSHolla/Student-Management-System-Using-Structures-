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

int searchStudentGUI(struct student s[], int n, const char *usn)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(s[i].USN, usn)==0)
        {
            return i; // return index
        }
    }
    return -1; // not found
}