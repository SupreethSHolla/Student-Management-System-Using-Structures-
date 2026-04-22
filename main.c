#include<stdio.h> // Include standard input/output library for printf and scanf

// Structure definition to store individual student records
struct student
{
    char name[35];     // Array to store the student's full name (up to 34 characters)
    char USN[15];      // Array to store the University Seat Number, used as a unique identifier
    char branch[100];  // Array to store the student's branch of study (e.g., Computer Science)
    int sem;           // Integer variable to store the current semester of the student
    char phone[15];    // Array to store the student's contact phone number
};

// Function Prototypes: Declare functions before they are used so the compiler knows about them
// These functions are implemented in their respective individual .c files
int importData(struct student s[]);                  // Loads array from file. Returns number of students loaded.
void saveToFile(struct student s[], int n);          // Saves current array of size 'n' to a file.
void appendStudents(struct student s[], int *n);     // Adds new students to array. Passes pointer to update 'n'.
void displayStudents(struct student s[], int n);     // Prints all students currently in the array to console.
void searchStudent(struct student s[], int n);       // Searches array for a specific student by USN.
void deleteStudent(struct student s[], int *n);      // Removes a student by USN and decrements count '*n'.
void updateStudent(struct student s[], int n);       // Finds a student and updates their details.
void exportData(struct student s[], int n);          // Exports the current array to external files (TXT/CSV).

int main()
{
    struct student s[100]; // Create an array of 100 'student' structs to hold our data in memory
    int n = 0;             // Variable to keep track of the current number of valid student records in the array
    int choice;            // Variable to store the user's menu selection

    // Infinite loop to keep the menu running until the user explicitly chooses to exit
    while(1)
    {
        // Display the main menu options to the user
        printf("\n========== Student Management System ==========\n");
        printf("1. Import Data\n");         // Option to load from data/students.dat
        printf("2. Append Students\n");     // Option to add new records
        printf("3. Display Students\n");    // Option to view all current records
        printf("4. Search Student\n");      // Option to find a specific record
        printf("5. Delete Student\n");      // Option to remove a record
        printf("6. Update Student\n");      // Option to modify a record
        printf("7. Export Data\n");         // Option to save to text or csv
        printf("8. Exit\n");                // Option to terminate program
        
        printf("Enter your choice: ");      // Prompt the user for input
        scanf("%d", &choice);               // Read the integer input and store it in 'choice'

        // Switch statement to execute code based on the user's choice
        switch(choice)
        {
            case 1:
                n = importData(s);          // Call importData and update 'n' with the returned count
                break;                      // Break to exit switch block

            case 2:
                appendStudents(s, &n);      // Pass array and address of 'n' so append function can increment it
                break;

            case 3:
                displayStudents(s, n);      // Pass array and current count to print all valid records
                break;

            case 4:
                searchStudent(s, n);        // Pass array and count to search for a USN
                break;

            case 5:
                deleteStudent(s, &n);       // Pass address of 'n' so delete function can decrement it on success
                break;

            case 6:
                updateStudent(s, n);        // Pass array and count. Number of students doesn't change on update.
                break;

            case 7:
                exportData(s, n);           // Pass array and count to save visible text versions
                break;

            case 8:
                printf("Exiting program...\n"); // Inform user we are shutting down
                return 0;                       // Return 0 to OS, which typically means successful execution

            default:
                // Handling invalid input that doesn't match cases 1-8
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0; // Final return, though the while loop's return handles normal exit
}