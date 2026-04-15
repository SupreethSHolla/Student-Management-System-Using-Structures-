#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[30];
    int sem;
    char phone[15];
};

void exportData(struct student s[], int n)
{
    int choice;

    printf("\nExport Options:\n");
    printf("1. Normal (Text File)\n");
    printf("2. Excel (CSV File)\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    if(choice == 1)
    {
        FILE *fp = fopen("data/export/students.txt","w");

        if(fp == NULL)
        {
            printf("Error creating file\n");
            return;
        }

        for(int i=0;i<n;i++)
        {
            fprintf(fp,"Student %d\n",i+1);
            fprintf(fp,"Name: %s\n",s[i].name);
            fprintf(fp,"USN: %s\n",s[i].USN);
            fprintf(fp,"Branch: %s\n",s[i].branch);
            fprintf(fp,"Sem: %d\n",s[i].sem);
            fprintf(fp,"Phone: %s\n\n",s[i].phone);
        }

        fclose(fp);
        printf("Exported to students.txt\n");
    }

    else if(choice == 2)
    {
        FILE *fp = fopen("data/export/students.csv","w");

        if(fp == NULL)
        {
            printf("Error creating file\n");
            return;
        }

        // Header row (important for Excel)
        fprintf(fp,"Name,USN,Branch,Sem,Phone\n");

        for(int i=0;i<n;i++)
        {
            fprintf(fp,"%s,%s,%s,%d,%s\n",
                s[i].name,
                s[i].USN,
                s[i].branch,
                s[i].sem,
                s[i].phone);
        }

        fclose(fp);
        printf("Exported to students.csv (Open in Excel)\n");
    }

    else
    {
        printf("Invalid choice\n");
    }
}