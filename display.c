#include<stdio.h> // included for printf function implementation

// Redefine internal data struct internally to reference internal variables correctly
struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

// Function mapping internal active memory structure states onto the visual Command Line Window
// Parameters:
// s[]: Standard memory array block reference
// n: Numerical variable counting the total mapped structures initialized
void displayStudents(struct student s[], int n)
{
    // Catch-block to prevent mapping blank initialized memory mapping bounds
    if(n==0)
    {
        printf("No data\n"); // Print user text prompt alerting missing data mapping
        return;              // Escape execution map and return context directly
    }

    // Sequence loop across all counted array variable boundaries initialized within active RAM pointer maps
    for(int i=0;i<n;i++)
    {
        // Utilize printf to render the data out to terminal natively formatting the layout and variables properly
        printf("\nStudent %d\n",i+1);                // List numerical progression reference mapping starting with index + 1
        printf("Name: %s\n",s[i].name);              // Format array element string extraction referencing structural .name property
        printf("USN: %s\n",s[i].USN);                // Format string from unique USN variable reference points
        printf("Branch: %s\n",s[i].branch);          // Extract branch mapping character sets natively
        printf("Sem: %d\n",s[i].sem);                // Translate stored numerical digits out to string formatting outputs
        printf("Phone: %s\n",s[i].phone);            // Outbound phone contact character limits output mapping directly
    }
}