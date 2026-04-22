#include<stdio.h>   // included for standard types
#include<string.h>  // included to use strcmp for string comparisons

// Define the global student struct data model locally so this compile unit understands it
struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

// Function performing a linear search to find an index by USN
// Parameters:
// s[]: Array containing all loaded student entries
// n: Provide the current total count (size bound limit)
// usn: Keep track of exactly what character array string we are hunting for
int searchStudentGUI(struct student s[], int n, const char *usn)
{
    // A linear index loop from 0 up to n - 1
    for(int i=0;i<n;i++)
    {
        // Utilizing string comparison on each USN stored vs argument usn string pattern
        if(strcmp(s[i].USN, usn)==0) 
        {
            // In the event of an exact match finding, stop the execution map immediately 
            // Return internal index parameter so callers may natively reference matching element s[i]
            return i; 
        }
    }
    
    // In case execution loop runs to ending bound, no matches ever occurred in the provided array.
    // Return standard error marker -1 to signal a non-existence of searched object 
    return -1; 
}