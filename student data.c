#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[20];
    int sem;
    char phone[15];
};

int main()
{
    int n,i;

    printf("Enter the number of students: ");
    scanf("%d",&n);

    struct student s[n];

    for(i=0;i<n;i++)
    {
        printf("\nEnter details of student %d\n",i+1);

        printf("Name: ");
        scanf(" %[^\n]", s[i].name);

        printf("USN: ");
        scanf("%s",s[i].USN);

        printf("Branch: ");
        scanf("%s",s[i].branch);

        printf("Semester: ");
        scanf("%d",&s[i].sem);

        printf("Phone: ");
        scanf("%s",s[i].phone);
    }

    printf("\n----- Student Details -----\n");

    for(i=0;i<n;i++)
    {
        printf("\nStudent %d\n",i+1);
        printf("Name : %s\n",s[i].name);
        printf("USN : %s\n",s[i].USN);
        printf("Branch : %s\n",s[i].branch);
        printf("Semester : %d\n",s[i].sem);
        printf("Phone : %s\n",s[i].phone);
    }

    return 0;
}