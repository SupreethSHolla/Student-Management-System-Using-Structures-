#include<stdio.h>
#include<string.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[30];
    int sem;
    char phone[15];
};

void saveToFile(struct student s[], int n);

void updateStudent(struct student s[], int n)
{
    if (n == 0)
    {
        printf("No data to update\n");
        return;
    }

    char usn[15];
    printf("Enter USN to update: ");
    scanf("%14s",usn);

    for(int i=0;i<n;i++)
    {
        if(strcmp(s[i].USN,usn)==0)
        {
            printf("New Name: ");
            scanf(" %34[^\n]",s[i].name);

            printf("New Phone: ");
            scanf("%14s",s[i].phone);

            saveToFile(s,n);
            printf("Updated\n");
            return;
        }
    }

    printf("Not found\n");
}