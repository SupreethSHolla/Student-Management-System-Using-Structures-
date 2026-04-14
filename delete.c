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

int deleteStudentGUI(struct student s[], int *n, const char *usn)
{
    for(int i=0;i<*n;i++)
    {
        if(strcmp(s[i].USN, usn)==0)
        {
            for(int j=i;j<*n-1;j++)
                s[j]=s[j+1];

            (*n)--;
            saveToFile(s,*n);
            return 1; // found and deleted
        }
    }
    return 0; // not found
}