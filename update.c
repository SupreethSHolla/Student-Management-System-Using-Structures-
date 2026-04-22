#include<stdio.h>   // included for standard types
#include<string.h>  // included for string copying (strncpy) and comparison (strcmp)

// Redefine the core data structure modeling a student
struct student
{
    char name[35];     // length 34 + 1 null terminator
    char USN[15];      // Unique identifier
    char branch[100];
    int sem;
    char phone[15];
};

// Externally mapped save function allowing disk writing per successful update
void saveToFile(struct student s[], int n);

// Function applying new details natively over existing struct indices
// Parameters:
// s[]: Storage mapping array
// n: Max index check boundary
// usn: Search parameter targeting unique student 
// new_name: New Name string to replace matched structural name
// new_phone: New Phone string to replace matched structural phone
int updateStudentGUI(struct student s[], int n, const char *usn, const char *new_name, const char *new_phone)
{
    // Begin scanning full allocated array
    for(int i=0;i<n;i++)
    {
        // On target match comparing input vs structural USN array property
        if(strcmp(s[i].USN,usn)==0)
        {
            // Truncated safe copying overwriting array name string with incoming data
            strncpy(s[i].name, new_name, 34); s[i].name[34] = '\0'; // ensure null termination
            
            // Truncated safe copying overwriting array phone string 
            strncpy(s[i].phone, new_phone, 14); s[i].phone[14] = '\0'; // ensure null termination
            
            // Push internal active memory changes directly out to physical data file
            saveToFile(s,n);
            
            return 1; // Signal completion boolean map 'true'
        }
    }
    
    // No target iterations met the condition, meaning unique object missing
    return 0; // Return false
}