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

int importDataGUI(struct student s[], int choice)
{
    int n = 0;
    if(choice == 1)
    {
        FILE *fp = fopen("data/backup/students.dat","rb");
        if(fp == NULL) return -1;

        fread(&n,sizeof(int),1,fp);
        if (n > 100) n = 100;
        fread(s,sizeof(struct student),n,fp);
        fclose(fp);
        return n;
    }
    else if(choice == 2)
    {
        FILE *fp = fopen("data/import/students.txt","r");
        if(fp == NULL) return -1;

        while(n < 100 && fscanf(fp,"%34[^,],%14[^,],%99[^,],%d,%14s\n", s[n].name, s[n].USN, s[n].branch, &s[n].sem, s[n].phone) == 5) n++;
        fclose(fp);
        return n;
    }
    else if(choice == 3)
    {
        FILE *fp = fopen("data/import/students.csv","r");
        if(fp == NULL) return -1;

        char line[200];
        fgets(line, sizeof(line), fp);
        while(n < 100 && fscanf(fp,"%34[^,],%14[^,],%99[^,],%d,%14s\n", s[n].name, s[n].USN, s[n].branch, &s[n].sem, s[n].phone) == 5) n++;
        fclose(fp);
        return n;
    }
    return 0;
}