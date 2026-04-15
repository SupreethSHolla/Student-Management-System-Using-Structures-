#include<stdio.h>

// Structure
struct student
{
    char name[35];
    char USN[15];
    char branch[30];
    int sem;
    char phone[15];
};

// Function Prototypes
int importData(struct student s[]);
void saveToFile(struct student s[], int n);
void appendStudents(struct student s[], int *n);
void displayStudents(struct student s[], int n);
void searchStudent(struct student s[], int n);
void deleteStudent(struct student s[], int *n);
void updateStudent(struct student s[], int n);
void exportData(struct student s[], int n);

int main()
{
    struct student s[100];
    int n = 0;
    int choice;

    while(1)
    {
        printf("\n========== Student Management System ==========\n");
        printf("1. Import Data\n");
        printf("2. Append Students\n");
        printf("3. Display Students\n");
        printf("4. Search Student\n");
        printf("5. Delete Student\n");
        printf("6. Update Student\n");
        printf("7. Export Data\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                n = importData(s);
                break;

            case 2:
                appendStudents(s, &n);
                break;

            case 3:
                displayStudents(s, n);
                break;

            case 4:
                searchStudent(s, n);
                break;

            case 5:
                deleteStudent(s, &n);
                break;

            case 6:
                updateStudent(s, n);
                break;

            case 7:
                exportData(s, n);
                break;

            case 8:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}