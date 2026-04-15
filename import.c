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

int importData(struct student s[])
{
    int choice, n = 0;

    printf("\nImport Options:\n");
    printf("1. Binary (.dat)\n");
    printf("2. Text (.txt)\n");
    printf("3. Excel (.csv)\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    // ---------- 1. Binary ----------
    if(choice == 1)
    {
        FILE *fp = fopen("students.dat","rb");

        if(fp == NULL)
        {
            printf("No binary file found\n");
            return 0;
        }

        fread(&n,sizeof(int),1,fp);
        fread(s,sizeof(struct student),n,fp);
        fclose(fp);

        printf("Imported from students.dat\n");
        return n;
    }

    // ---------- 2. TXT ----------
    else if(choice == 2)
    {
        FILE *fp = fopen("data/import/students.dat","rb");

        if(fp == NULL)
        {
            printf("No txt file found\n");
            return 0;
        }

        while(fscanf(fp,"%[^,],%[^,],%[^,],%d,%s\n",
              s[n].name,
              s[n].USN,
              s[n].branch,
              &s[n].sem,
              s[n].phone) == 5)
        {
            n++;
        }

        fclose(fp);
        printf("Imported from students.txt\n");
        return n;
    }

    // ---------- 3. CSV ----------
    else if(choice == 3)
    {
        FILE *fp = fopen("data/import/students.csv","r");

        if(fp == NULL)
        {
            printf("No csv file found\n");
            return 0;
        }

        // skip header
        char line[200];
        fgets(line, sizeof(line), fp);

        while(fscanf(fp,"%[^,],%[^,],%[^,],%d,%s\n",
              s[n].name,
              s[n].USN,
              s[n].branch,
              &s[n].sem,
              s[n].phone) == 5)
        {
            n++;
        }

        fclose(fp);
        printf("Imported from students.csv\n");
        return n;
    }

    else
    {
        printf("Invalid choice\n");
        return 0;
    }
}