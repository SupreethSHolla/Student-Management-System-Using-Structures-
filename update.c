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
    char usn[15];
    printf("Enter USN to update: ");
    scanf("%s",usn);

    for(int i=0;i<n;i++)
    {
        if(strcmp(s[i].USN,usn)==0)
        {
            printf("New Name: ");
            scanf(" %[^\n]",s[i].name);

            printf("New Phone: ");
            scanf("%s",s[i].phone);

            saveToFile(s,n);
            printf("Updated\n");
            return;
        }
    }

    printf("Not found\n");
}