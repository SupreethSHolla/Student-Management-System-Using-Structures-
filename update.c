#include<stdio.h>
#include<string.h>

struct student
{
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

void saveToFile(struct student s[], int n);

int updateStudentGUI(struct student s[], int n, const char *usn, const char *new_name, const char *new_phone)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(s[i].USN,usn)==0)
        {
            strncpy(s[i].name, new_name, 34); s[i].name[34] = '\0';
            strncpy(s[i].phone, new_phone, 14); s[i].phone[14] = '\0';
            saveToFile(s,n);
            return 1;
        }
    }
    return 0;
}