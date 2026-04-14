#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>

#define ID_LISTVIEW 1001
#define ID_BTN_ADD 1002
#define ID_BTN_DELETE 1003
#define ID_BTN_SEARCH 1004
#define ID_BTN_EXPORT 1005
#define ID_BTN_EXPORT_CSV 1006

#define ID_EDIT_NAME 2001
#define ID_EDIT_USN 2002
#define ID_EDIT_BRANCH 2003
#define ID_EDIT_SEM 2004
#define ID_EDIT_PHONE 2005
#define ID_EDIT_SEARCH 2006

struct student {
    char name[35];
    char USN[15];
    char branch[100];
    int sem;
    char phone[15];
};

struct student s[100];
int student_count = 0;

// Logic externs
extern int appendStudentGUI(struct student s[], int *n, struct student new_s);
extern int deleteStudentGUI(struct student s[], int *n, const char *usn);
extern int searchStudentGUI(struct student s[], int n, const char *usn);
extern int updateStudentGUI(struct student s[], int n, const char *usn, const char *new_name, const char *new_phone);
extern int exportDataGUI(struct student s[], int n, int choice);
extern int loadFromFile(struct student s[]);
extern void saveToFile(struct student s[], int n);

HWND hListView, hName, hUSN, hBranch, hSem, hPhone, hSearchBox;

void RefreshListView() {
    ListView_DeleteAllItems(hListView);
    for (int i = 0; i < student_count; i++) {
        LVITEM lvI;
        lvI.pszText   = s[i].USN;
        lvI.mask      = LVIF_TEXT;
        lvI.iSubItem  = 0;
        lvI.iItem     = i;
        ListView_InsertItem(hListView, &lvI);
        
        ListView_SetItemText(hListView, i, 1, s[i].name);
        ListView_SetItemText(hListView, i, 2, s[i].branch);
        
        char semStr[10];
        snprintf(semStr, sizeof(semStr), "%d", s[i].sem);
        ListView_SetItemText(hListView, i, 3, semStr);
        ListView_SetItemText(hListView, i, 4, s[i].phone);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CREATE: {
            // Ensure directories exist
            _mkdir("data");
            _mkdir("data/backup");
            _mkdir("data/export");
            _mkdir("data/import");

            // Load initial data
            student_count = loadFromFile(s);
            if (student_count < 0) student_count = 0;

            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER,
                20, 20, 500, 300, hwnd, (HMENU)ID_LISTVIEW, NULL, NULL);
            
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            
            LVCOLUMN lvc;
            lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
            lvc.fmt = LVCFMT_LEFT;
            
            char *cols[] = {"USN", "Name", "Branch", "Sem", "Phone"};
            int widths[] = {80, 150, 100, 50, 100};
            
            for (int i=0; i<5; i++) {
                lvc.iSubItem = i;
                lvc.cx = widths[i];
                lvc.pszText = cols[i];
                ListView_InsertColumn(hListView, i, &lvc);
            }
            
            CreateWindow("BUTTON", "Add/Update", WS_VISIBLE | WS_CHILD, 540, 20, 100, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "Delete", WS_VISIBLE | WS_CHILD, 540, 60, 100, 30, hwnd, (HMENU)ID_BTN_DELETE, NULL, NULL);
            CreateWindow("BUTTON", "Export TXT", WS_VISIBLE | WS_CHILD, 540, 140, 100, 30, hwnd, (HMENU)ID_BTN_EXPORT, NULL, NULL);
            CreateWindow("BUTTON", "Export CSV", WS_VISIBLE | WS_CHILD, 540, 180, 100, 30, hwnd, (HMENU)ID_BTN_EXPORT_CSV, NULL, NULL);

            // Dedicated Search Input
            CreateWindow("STATIC", "Search USN:", WS_VISIBLE | WS_CHILD, 540, 230, 100, 20, hwnd, NULL, NULL, NULL);
            hSearchBox = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 540, 250, 100, 20, hwnd, (HMENU)ID_EDIT_SEARCH, NULL, NULL);
            
            // Inputs  
            CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 20, 340, 50, 20, hwnd, NULL, NULL, NULL);
            hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 340, 120, 20, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);
            
            CreateWindow("STATIC", "USN (Key):", WS_VISIBLE | WS_CHILD, 20, 370, 70, 20, hwnd, NULL, NULL, NULL);
            hUSN = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 370, 100, 20, hwnd, (HMENU)ID_EDIT_USN, NULL, NULL);
            
            CreateWindow("STATIC", "Branch:", WS_VISIBLE | WS_CHILD, 20, 400, 50, 20, hwnd, NULL, NULL, NULL);
            hBranch = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 70, 400, 120, 20, hwnd, (HMENU)ID_EDIT_BRANCH, NULL, NULL);
            
            CreateWindow("STATIC", "Sem:", WS_VISIBLE | WS_CHILD, 220, 340, 40, 20, hwnd, NULL, NULL, NULL);
            hSem = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 260, 340, 50, 20, hwnd, (HMENU)ID_EDIT_SEM, NULL, NULL);
            
            CreateWindow("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, 220, 370, 50, 20, hwnd, NULL, NULL, NULL);
            hPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 270, 370, 100, 20, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);

            RefreshListView();
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) == ID_BTN_ADD) {
                struct student new_s = {0};
                GetWindowText(hName, new_s.name, 34);
                GetWindowText(hUSN, new_s.USN, 14);
                GetWindowText(hBranch, new_s.branch, 99);
                char sem_str[10];
                GetWindowText(hSem, sem_str, 9);
                new_s.sem = atoi(sem_str);
                GetWindowText(hPhone, new_s.phone, 14);
                
                if (strlen(new_s.USN) == 0) {
                    MessageBox(hwnd, "USN cannot be empty!", "Error", MB_ICONERROR);
                    break;
                }

                int found = searchStudentGUI(s, student_count, new_s.USN);
                if (found != -1) {
                    updateStudentGUI(s, student_count, new_s.USN, new_s.name, new_s.phone);
                    s[found].sem = new_s.sem;
                    strncpy(s[found].branch, new_s.branch, 99);
                    saveToFile(s, student_count);
                    MessageBox(hwnd, "Student updated successfully!", "Info", MB_OK);
                } else {
                    if (appendStudentGUI(s, &student_count, new_s))
                        MessageBox(hwnd, "Student added successfully!", "Success", MB_OK);
                    else
                        MessageBox(hwnd, "Failed to add. Max 100 students.", "Error", MB_ICONERROR);
                }
                RefreshListView();
            }
            else if (LOWORD(wParam) == ID_BTN_DELETE) {
                char usn[15];
                GetWindowText(hUSN, usn, 14);
                if (deleteStudentGUI(s, &student_count, usn)) {
                    MessageBox(hwnd, "Deleted successfully!", "Success", MB_OK);
                    RefreshListView();
                } else {
                    MessageBox(hwnd, "USN not found.", "Error", MB_ICONERROR);
                }
            }
            else if (LOWORD(wParam) == ID_BTN_SEARCH) {
                char usn[15];
                GetWindowText(hSearchBox, usn, 14);
                if (strlen(usn) == 0) {
                    MessageBox(hwnd, "Please enter a USN in the Search Box.", "Error", MB_ICONERROR);
                    break;
                }
                int found = searchStudentGUI(s, student_count, usn);
                if(found != -1) {
                    char msg[200];
                    snprintf(msg, sizeof(msg), "Found:\nName: %s\nBranch: %s\nSem: %d\nPhone: %s", 
                        s[found].name, s[found].branch, s[found].sem, s[found].phone);
                    MessageBox(hwnd, msg, "Search Result", MB_OK);
                    
                    // Auto-fill edit boxes
                    SetWindowText(hName, s[found].name);
                    SetWindowText(hBranch, s[found].branch);
                    char sStr[10]; snprintf(sStr,10,"%d",s[found].sem);
                    SetWindowText(hSem, sStr);
                    SetWindowText(hPhone, s[found].phone);
                } else {
                    MessageBox(hwnd, "Not found.", "Error", MB_ICONERROR);
                }
            }
            else if (LOWORD(wParam) == ID_BTN_EXPORT) {
                if (exportDataGUI(s, student_count, 1)) {
                    MessageBox(hwnd, "Exported to data/export/students.txt", "Success", MB_OK);
                } else {
                    MessageBox(hwnd, "Failed to export", "Error", MB_ICONERROR);
                }
            }
            else if (LOWORD(wParam) == ID_BTN_EXPORT_CSV) {
                if (exportDataGUI(s, student_count, 2)) {
                    MessageBox(hwnd, "Exported to data/export/students.csv", "Success", MB_OK);
                } else {
                    MessageBox(hwnd, "Failed to export CSV", "Error", MB_ICONERROR);
                }
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "StudentGUI";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("StudentGUI", "Student Management System Windows UI",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 680, 500, NULL, NULL, hInstance, NULL);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
