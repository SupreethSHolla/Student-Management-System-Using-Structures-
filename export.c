#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

int exportDataGUI(struct student s[], int n, int choice)
{
    if(n == 0) return 0;

    if(choice == 1) // TXT
    {
        FILE *fp = fopen("data/export/students.txt","w");
        if(fp == NULL) return -1;

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
        return 1;
    }
    else if(choice == 2) // CSV
    {
        FILE *fp = fopen("data/export/students.csv","w");
        if(fp == NULL) return -1;

        fprintf(fp,"Name,USN,Branch,Sem,Phone\n");
        for(int i=0;i<n;i++)
        {
            fprintf(fp,"%s,%s,%s,%d,%s\n", s[i].name, s[i].USN, s[i].branch, s[i].sem, s[i].phone);
        }
        fclose(fp);
        return 2;
    }
    return 0;
}