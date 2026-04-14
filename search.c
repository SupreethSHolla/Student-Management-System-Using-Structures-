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

void searchStudent(struct student s[], int n)
{
    if (n == 0)
    {
        printf("No data to search\n");
        return;
    }

    char usn[15];
    printf("Enter USN: ");
    scanf("%14s",usn);

    for(int i=0;i<n;i++)
    {
        if(strcmp(s[i].USN,usn)==0)
        {
            printf("\nFound:\n");
            printf("Name: %s\n",s[i].name);
            printf("Branch: %s\n",s[i].branch);
            printf("Sem: %d\n",s[i].sem);
            printf("Phone: %s\n",s[i].phone);
            return;
        }
    }

    printf("Not found\n");
}