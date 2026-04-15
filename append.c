#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[30];
    int sem;
    char phone[15];
};

void saveToFile(struct student s[], int n);

void appendStudents(struct student s[], int *n)
{
    int count;
    printf("How many students: ");
    scanf("%d",&count);

    for(int i=0;i<count;i++)
    {
        printf("\nStudent %d\n",*n+1);

        printf("Name: ");
        scanf(" %[^\n]",s[*n].name);

        printf("USN: ");
        scanf("%s",s[*n].USN);

        printf("Branch: ");
        scanf(" %[^\n]",s[*n].branch);

        printf("Sem: ");
        scanf("%d",&s[*n].sem);

        printf("Phone: ");
        scanf("%s",s[*n].phone);

        (*n)++;
    }

    saveToFile(s,*n);
}