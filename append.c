#include<stdio.h>   // For standard I/O (often included by default but not strictly needed here)
#include<string.h>  // For string manipulation functions, though none are directly used here

// Redefine the student structure so the compiler knows the data layout and size
struct student
{
    char name[35];     // Array to store name
    char USN[15];      // Array to store USN (University Seat Number)
    char branch[100];  // Array to store Branch String
    int sem;           // Integer for Semester
    char phone[15];    // Array for Phone number
};

// Forward declaration of saveToFile function which takes an array and a size, implemented in file.c
// This is necessary because we call it down below after appending.
void saveToFile(struct student s[], int n);

// Function to append a new student record to the global/passed array (used by GUI)
// Parameters:
// s[]: The array of structures holding current data
// n: Pointer to the variable containing the total current count
// new_s: The data for the new student to be inserted
int appendStudentGUI(struct student s[], int *n, struct student new_s)
{
    // Sanity check: Ensure we don't exceed the array bounds. Array size is 100.
    if(*n >= 100) return 0; // Error max reached, return 0 (false)
    
    // Assign the new student struct to the first empty slot at the end of the current data
    s[*n] = new_s;
    
    // Dereference pointer 'n' and increment the actual count variable by 1
    (*n)++;
    
    // Immediately persist the newly updated array and new count to standard data/students.dat file
    saveToFile(s, *n);
    
    // Return 1 indicating success
    return 1;
}