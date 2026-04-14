#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

void displayStudents(struct student s[], int n)
{
    if(n==0)
    {
        printf("No data\n");
        return;
    }

    for(int i=0;i<n;i++)
    {
        printf("\nStudent %d\n",i+1);
        printf("Name: %s\n",s[i].name);
        printf("USN: %s\n",s[i].USN);
        printf("Branch: %s\n",s[i].branch);
        printf("Sem: %d\n",s[i].sem);
        printf("Phone: %s\n",s[i].phone);
    }
}