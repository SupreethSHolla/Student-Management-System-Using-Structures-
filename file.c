#include<stdio.h> // included for FILE, fopen, fread, fwrite, fclose native operational types

// Global configuration block representing array structures dynamically
struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

// File function converting operational active mapped struct arrays to stored binary binary dat file formats
// Parameters:
// s[]: Standard initialized array index map structure reference pointer block mapping
// n: Global numerical count size variable pointing exact data loop maps dynamically initialized 
void saveToFile(struct student s[], int n)
{
    // Launch standard file pointer mapped operation targeting binary write out command formatting natively inside system directory
    FILE *fp = fopen("data/backup/students.dat","wb"); 
    
    // Dump logical block variables representing structure counter limit direct binary formatted string
    fwrite(&n,sizeof(int),1,fp);
    
    // Launch native array size block parameter limit writing fully active memory mapping variable structures formatting system maps globally
    fwrite(s,sizeof(struct student),n,fp);
    
    // Properly clean mapped file pointer data bounds returning memory blocks cleanly 
    fclose(fp);
}

// Memory sequence function returning numerical total representing items mapping onto current structurally indexed mapping variables linearly
// Loading active disk binary data blocks directly over initialized application runtime map
int loadFromFile(struct student s[])
{
    // Setup file load logical pointer mapping targeting correct static local directories explicitly formatting "rb" (read binary) map limits
    FILE *fp = fopen("data/backup/students.dat","rb"); 
    int n=0; // Create limit block parameter tracking loop boundaries linearly

    // Safety guard checking if standard target mapped file map points properly initialized mapping
    // Triggers normally on brand new data initialized system directory spaces mapping naturally
    if(fp==NULL)
    {
        printf("No file found\n");
        return 0; // Break load mapping context safely back
    }

    // Read direct pointer mapped variables storing loaded integer sizes
    fread(&n,sizeof(int),1,fp);
    
    // Execute sequence mapping pulling file array block elements out into initialized parameters mappings seamlessly linearly mapped parameters safely
    fread(s,sizeof(struct student),n,fp);
    
    // File handler cleanup routines
    fclose(fp);

    // Provide visual load state parameters dynamically referencing proper loaded parameters state correctly linearly globally formatted strings correctly 
    printf("Data imported\n");
    
    // Return count limits to parameter caller logically mapped properly linearly referencing true loaded maps globally
    return n;
}