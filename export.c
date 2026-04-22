#include<stdio.h> // stdio included for file read/write APIs

// Setup structure definition globally to align array memory blocks matching system definitions
struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

// Function exporting system mapped data directly into readable physical file text strings correctly mapped into local storage formats
// Parameters:
// s[]: Root structures array block tracking active system state limits natively 
// n: Global loop limit tracker mapping valid initialized structure items
// choice: Int selector routing format paths between regular readable forms (1) and Comma Separated Valued strings (2) mapping to standard spread sheet applications globally
int exportDataGUI(struct student s[], int n, int choice)
{
    // Catch state ensuring active parameters correctly loaded natively
    if(n == 0) return 0; // return block error limits missing initialized parameter references linearly

    if(choice == 1) // TXT branch path formats easily readable human text data linearly exported over target mapped directory spaces
    {
        // initialize local standard pointer writing target logical limits formatting text paths mapping properly 
        FILE *fp = fopen("data/export/students.txt","w");
        if(fp == NULL) return -1; // catch exception limits mapping file creation boundaries safely

        // Sequence through all tracked valid memory limit spaces
        for(int i=0;i<n;i++)
        {
            // Output structural elements sequentially block formatting into regular readable formats into physical files natively
            fprintf(fp,"Student %d\n",i+1);
            fprintf(fp,"Name: %s\n",s[i].name);
            fprintf(fp,"USN: %s\n",s[i].USN);
            fprintf(fp,"Branch: %s\n",s[i].branch);
            fprintf(fp,"Sem: %d\n",s[i].sem);
            fprintf(fp,"Phone: %s\n\n",s[i].phone); // Print new line separator between blocks
        }
        
        // Finalize memory cleanup returning mapped pointers out seamlessly globally
        fclose(fp);
        return 1; // Signal operation complete success limits
    }
    else if(choice == 2) // CSV branch mapping variables uniquely formatted limits mapped dynamically 
    {
        // Target map logical file boundary limits linearly formatting extension target map spaces linearly globally
        FILE *fp = fopen("data/export/students.csv","w");
        if(fp == NULL) return -1;

        // Generate mapping root column string header limit formatting for global CSV references
        fprintf(fp,"Name,USN,Branch,Sem,Phone\n");
        
        // Execute block formatting variables dynamically over memory references safely linearly globally mapped string combinations
        for(int i=0;i<n;i++)
        {
            // Inject property data dynamically mapped safely into specific sequence boundaries limits globally mapping standard CSV blocks natively
            fprintf(fp,"%s,%s,%s,%d,%s\n", s[i].name, s[i].USN, s[i].branch, s[i].sem, s[i].phone);
        }
        
        // Purge parameter references mapped file bounds clearing sequence blocks safely sequentially
        fclose(fp);
        
        return 2; // Signal dynamic csv path completed success
    }
    
    // Exception limits handling unexpected boolean tracking maps safely globally formatting null block references natively linearly
    return 0;
}