#include<stdio.h>

// Structure (must repeat)
struct student
{
    char name[35];
    char USN[15];
    char branch[30];
    int sem;
    char phone[15];
};

// Function prototypes
void saveToFile(struct student s[], int n);
int loadFromFile(struct student s[]);
void appendStudents(struct student s[], int *n);
void displayStudents(struct student s[], int n);
void searchStudent(struct student s[], int n);
void deleteStudent(struct student s[], int *n);
void updateStudent(struct student s[], int n);

int main()
{
    struct student s[100];
    int n = 0, choice;

    while(1)
    {
        printf("\n--- Student Management System ---\n");
        printf("1. Import\n2. Append\n3. Display\n4. Search\n5. Delete\n6. Update\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: n = loadFromFile(s); break;
            case 2: appendStudents(s,&n); break;
            case 3: displayStudents(s,n); break;
            case 4: searchStudent(s,n); break;
            case 5: deleteStudent(s,&n); break;
            case 6: updateStudent(s,n); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
    }
}