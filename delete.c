#include<stdio.h>   // Included for standard types/functions
#include<string.h>  // Included for string comparison function (strcmp)

// Redefine the student structure so the compiler knows the data layout
struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

// Forward declaration of saveToFile, implemented in file.c
// Needed to persist the deletion instantly
void saveToFile(struct student s[], int n);

// Function to delete a student by their unique USN
// Parameters:
// s[]: Array of structures
// n: Pointer to count of students
// usn: The target USN string to search for and delete
int deleteStudentGUI(struct student s[], int *n, const char *usn)
{
    // Iterate through all currently loaded students
    for(int i=0;i<*n;i++)
    {
        // Use strcmp to compare the target usn with the current student's USN. 
        // strcmp returns 0 if the two strings match perfectly.
        if(strcmp(s[i].USN, usn)==0)
        {
            // Student found at index 'i'. 
            // We now overwrite the deleted entry by shifting every subsequent entry one slot to the left
            for(int j=i;j<*n-1;j++)
                s[j]=s[j+1]; // Copy data from the next element into the current element

            // Decrease the total student count by 1 since we've logically "deleted" one item
            (*n)--;
            
            // Re-save the now smaller structural array to the disk to make the deletion permanent
            saveToFile(s,*n);
            
            return 1; // Deletion was successful, return 1 (true)
        }
    }
    
    // If the loop finishes executing without returning, it means no struct had a matching USN
    return 0; // Return 0 (false) indicating not found
}