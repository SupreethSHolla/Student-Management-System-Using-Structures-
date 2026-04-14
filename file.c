#include<stdio.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

void saveToFile(struct student s[], int n)
{
    FILE *fp = fopen("data/backup/students.dat","wb");
    fwrite(&n,sizeof(int),1,fp);
    fwrite(s,sizeof(struct student),n,fp);
    fclose(fp);
}

int loadFromFile(struct student s[])
{
    FILE *fp = fopen("data/backup/students.dat","rb");
    int n=0;

    if(fp==NULL)
    {
        printf("No file found\n");
        return 0;
    }

    fread(&n,sizeof(int),1,fp);
    fread(s,sizeof(struct student),n,fp);
    fclose(fp);

    printf("Data imported\n");
    return n;
}