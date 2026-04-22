#include <windows.h>      // Includes standard Windows API functions and types for GUI creation
#include <commctrl.h>     // Includes Common Controls library (used for ListView control)
#include <stdio.h>        // Includes standard input/output functions (like snprintf)
#include <string.h>       // Includes string manipulation functions (like strcpy, strlen)
#include <stdlib.h>       // Includes standard library functions (like atoi)
#include <direct.h>       // Includes directory manipulation functions (like _mkdir)

// Define unique integer IDs for our UI controls (Buttons, ListViews, etc.)
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

// Define the 'student' structure to hold details of each student
struct student {
    char name[35];        // Array to store student's name
    char USN[15];         // Array to store student's USN (University Seat Number), acts as primary key
    char branch[100];     // Array to store the student's branch/course
    int sem;              // Integer to store student's current semester
    char phone[15];       // Array to store student's phone number
};

// Global variables for managing our data in memory
struct student s[100];    // Array of 100 students to store data in RAM while program runs
int student_count = 0;    // Counter to keep track of how many students are currently stored

// External declarations for logic functions defined in other source files (.c files)
// These functions perform the actual data manipulation
extern int appendStudentGUI(struct student s[], int *n, struct student new_s);
extern int deleteStudentGUI(struct student s[], int *n, const char *usn);
extern int searchStudentGUI(struct student s[], int n, const char *usn);
extern int updateStudentGUI(struct student s[], int n, const char *usn, const char *new_name, const char *new_phone);
extern int exportDataGUI(struct student s[], int n, int choice);
extern int loadFromFile(struct student s[]);
extern void saveToFile(struct student s[], int n);

// Global Handles to Windows (HWND) for individual UI elements so we can interact with them later
HWND hListView, hName, hUSN, hBranch, hSem, hPhone, hSearchBox;
HFONT hFont;              // Handle for the custom font we will apply to controls

// Callback function used by EnumChildWindows to apply the custom font to all child controls
BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam) {
    // Send a message to the child window telling it to set its font to the one passed in lParam
    SendMessage(hwndChild, WM_SETFONT, (WPARAM)lParam, TRUE);
    return TRUE;          // Return TRUE to continue enumerating through windows
}

// Function to refresh the contents of the ListView table based on the student array 's'
void RefreshListView() {
    // First, delete all existing items in the ListView to avoid duplicates
    ListView_DeleteAllItems(hListView);
    
    // Loop through each student currently in our array
    for (int i = 0; i < student_count; i++) {
        LVITEM lvI;                     // Structure to hold information about a ListView item
        lvI.pszText   = s[i].USN;       // Set the primary text (Column 0) to be the USN
        lvI.mask      = LVIF_TEXT;      // Indicate we are only providing text info
        lvI.iSubItem  = 0;              // Sub-item 0 means the first column
        lvI.iItem     = i;              // The row index
        
        // Insert the new row into the ListView
        ListView_InsertItem(hListView, &lvI);
        
        // Now set the text for subsequent columns in this row
        ListView_SetItemText(hListView, i, 1, s[i].name);      // Column 1: Name
        ListView_SetItemText(hListView, i, 2, s[i].branch);    // Column 2: Branch
        
        char semStr[10];                                       // Buffer to hold string version of semester integer
        snprintf(semStr, sizeof(semStr), "%d", s[i].sem);      // Convert sem integer to string
        ListView_SetItemText(hListView, i, 3, semStr);         // Column 3: Semester string
        
        ListView_SetItemText(hListView, i, 4, s[i].phone);     // Column 4: Phone number
    }
}

// The Window Procedure: This function receives and handles all messages (events) sent to our main window
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        // Message when a static control (like a text label) is colored
        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;                             // Get drawing context
            SetBkMode(hdcStatic, TRANSPARENT);                       // Make text background transparent
            return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);         // Return standard background color brush
        }
        
        // Message sent once when the window is first created
        case WM_CREATE: {
            NONCLIENTMETRICS ncm;                                    // Structure to hold system metrics including fonts
            ncm.cbSize = sizeof(NONCLIENTMETRICS);                   // Must set size before calling SystemParametersInfo
            
            // Try to get the standard system message font
            if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0)) {
                hFont = CreateFontIndirect(&ncm.lfMessageFont);      // Create font from system parameters
            } else {
                hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);     // Fallback text font if above fails
            }

            // Ensure necessary data directories exist. _mkdir creates it if missing.
            _mkdir("data");
            _mkdir("data/backup");
            _mkdir("data/export");
            _mkdir("data/import");

            // Load initial student data from the file into our 's' array
            student_count = loadFromFile(s);
            if (student_count < 0) student_count = 0;                // Handle potential read errors

            // Create the central ListView control (the table showing all data)
            hListView = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_REPORT | WS_BORDER,
                20, 20, 490, 300, hwnd, (HMENU)ID_LISTVIEW, NULL, NULL);
            
            // Add gridlines and enable full-row selection for better UX
            ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            
            LVCOLUMN lvc;                                            // Structure for list view column configuration
            lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM; // The properties we want to set
            lvc.fmt = LVCFMT_LEFT;                                   // Align text to the left
            
            char *cols[] = {"USN", "Name", "Branch", "Sem", "Phone"};// Array of column header strings
            int widths[] = {80, 150, 100, 50, 100};                  // Width in pixels for each column
            
            // Loop 5 times to create the 5 columns
            for (int i=0; i<5; i++) {
                lvc.iSubItem = i;                                    // Column index
                lvc.cx = widths[i];                                  // Set width
                lvc.pszText = cols[i];                               // Set column title string
                ListView_InsertColumn(hListView, i, &lvc);           // Let Windows create it
            }
            
            // UI Operations Group Box (A border grouping controls visually)
            CreateWindow("BUTTON", "Operations", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 530, 10, 120, 100, hwnd, NULL, NULL, NULL);
            // Button to Add or Update a student
            CreateWindow("BUTTON", "Add/Update", WS_VISIBLE | WS_CHILD, 540, 30, 100, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            // Button to Delete a student
            CreateWindow("BUTTON", "Delete", WS_VISIBLE | WS_CHILD, 540, 70, 100, 30, hwnd, (HMENU)ID_BTN_DELETE, NULL, NULL);

            // Export Options Group Box
            CreateWindow("BUTTON", "Export", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 530, 120, 120, 90, hwnd, NULL, NULL, NULL);
            // Button to export as plain text
            CreateWindow("BUTTON", "Export TXT", WS_VISIBLE | WS_CHILD, 540, 140, 100, 25, hwnd, (HMENU)ID_BTN_EXPORT, NULL, NULL);
            // Button to export as CSV (Comma Separated Values)
            CreateWindow("BUTTON", "Export CSV", WS_VISIBLE | WS_CHILD, 540, 175, 100, 25, hwnd, (HMENU)ID_BTN_EXPORT_CSV, NULL, NULL);

            // Dedicated Search Input Group Box
            CreateWindow("BUTTON", "Search", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 530, 220, 120, 100, hwnd, NULL, NULL, NULL);
            // Text box (EDIT control) where user types USN to search
            hSearchBox = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 540, 245, 100, 25, hwnd, (HMENU)ID_EDIT_SEARCH, NULL, NULL);
            // Find button to execute the search
            CreateWindow("BUTTON", "Find", WS_VISIBLE | WS_CHILD, 540, 280, 100, 30, hwnd, (HMENU)ID_BTN_SEARCH, NULL, NULL);

            // Inputs Group Box for capturing individual student details
            CreateWindow("BUTTON", "Student Details", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 330, 490, 130, hwnd, NULL, NULL, NULL);
            
            // Name Label & Edit box
            CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 35, 360, 50, 20, hwnd, NULL, NULL, NULL);
            hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 355, 130, 25, hwnd, (HMENU)ID_EDIT_NAME, NULL, NULL);
            
            // USN Label & Edit box
            CreateWindow("STATIC", "USN (Key):", WS_VISIBLE | WS_CHILD, 35, 395, 70, 20, hwnd, NULL, NULL, NULL);
            hUSN = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 110, 390, 110, 25, hwnd, (HMENU)ID_EDIT_USN, NULL, NULL);
            
            // Branch Label & Edit box
            CreateWindow("STATIC", "Branch:", WS_VISIBLE | WS_CHILD, 35, 430, 50, 20, hwnd, NULL, NULL, NULL);
            hBranch = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 90, 425, 130, 25, hwnd, (HMENU)ID_EDIT_BRANCH, NULL, NULL);
            
            // Semester Label & Edit box
            CreateWindow("STATIC", "Sem:", WS_VISIBLE | WS_CHILD, 240, 360, 40, 20, hwnd, NULL, NULL, NULL);
            hSem = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 290, 355, 60, 25, hwnd, (HMENU)ID_EDIT_SEM, NULL, NULL);
            
            // Phone Label & Edit box
            CreateWindow("STATIC", "Phone:", WS_VISIBLE | WS_CHILD, 240, 395, 50, 20, hwnd, NULL, NULL, NULL);
            hPhone = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 290, 390, 130, 25, hwnd, (HMENU)ID_EDIT_PHONE, NULL, NULL);

            // Call EnumChildWindows to apply the nice modern font created above to all labels and text boxes
            EnumChildWindows(hwnd, EnumChildProc, (LPARAM)hFont);

            // Once the UI is built, populate the ListView with the data we loaded
            RefreshListView();
            break;  // End of WM_CREATE handling
        }
        
        // Message sent when the user interacts with controls (e.g., clicks a button)
        case WM_COMMAND: {
            // Check if the user clicked the Add/Update button
            if (LOWORD(wParam) == ID_BTN_ADD) {
                struct student new_s = {0};                      // Initialize a new temporary struct with zeros
                
                // Read text from text boxes and put it into the struct
                GetWindowText(hName, new_s.name, 34);            // Get Name max length 34
                GetWindowText(hUSN, new_s.USN, 14);              // Get USN max length 14
                GetWindowText(hBranch, new_s.branch, 99);        // Get Branch max length 99
                
                char sem_str[10];
                GetWindowText(hSem, sem_str, 9);                 // Get Sem as string
                new_s.sem = atoi(sem_str);                       // Convert Sem string to int
                
                GetWindowText(hPhone, new_s.phone, 14);          // Get Phone max length 14
                
                // USN is the primary key and cannot be empty
                if (strlen(new_s.USN) == 0) {
                    MessageBox(hwnd, "USN cannot be empty!", "Error", MB_ICONERROR); // Show warning dialog
                    break;
                }

                // Check if this student already exists in our array using the USN
                int found = searchStudentGUI(s, student_count, new_s.USN);
                
                if (found != -1) {
                    // If student exists, update their record instead of appending new
                    updateStudentGUI(s, student_count, new_s.USN, new_s.name, new_s.phone);
                    s[found].sem = new_s.sem;                                // Also manually update sem
                    strncpy(s[found].branch, new_s.branch, 99);              // Also manually update branch
                    saveToFile(s, student_count);                            // Persist changes to disc
                    MessageBox(hwnd, "Student updated successfully!", "Info", MB_OK);
                } else {
                    // If student doesn't exist, we add them
                    if (appendStudentGUI(s, &student_count, new_s))
                        MessageBox(hwnd, "Student added successfully!", "Success", MB_OK); // Added OK
                    else
                        MessageBox(hwnd, "Failed to add. Max 100 students.", "Error", MB_ICONERROR); // Array is full
                }
                RefreshListView(); // Refresh the GUI table with the new/updated changes
            }
            // Check if the user clicked the Delete button
            else if (LOWORD(wParam) == ID_BTN_DELETE) {
                char usn[15];
                GetWindowText(hUSN, usn, 14); // Read the USN typed in the form block
                
                // Try deleting. The function handles shifting memory and saving to disc.
                if (deleteStudentGUI(s, &student_count, usn)) {
                    MessageBox(hwnd, "Deleted successfully!", "Success", MB_OK);
                    RefreshListView(); // Update table after deletion
                } else {
                    MessageBox(hwnd, "USN not found.", "Error", MB_ICONERROR); // Student doesn't exist
                }
            }
            // Check if user clicked the specific Find/Search button
            else if (LOWORD(wParam) == ID_BTN_SEARCH) {
                char usn[15];
                GetWindowText(hSearchBox, usn, 14); // Read the specific search box text
                
                // Check if they typed anything before searching
                if (strlen(usn) == 0) {
                    MessageBox(hwnd, "Please enter a USN in the Search Box.", "Error", MB_ICONERROR);
                    break;
                }
                
                // Find index via external function
                int found = searchStudentGUI(s, student_count, usn);
                if(found != -1) {
                    char msg[200];
                    // Format a nice multi-line string containing the user's data
                    snprintf(msg, sizeof(msg), "Found:\nName: %s\nBranch: %s\nSem: %d\nPhone: %s", 
                        s[found].name, s[found].branch, s[found].sem, s[found].phone);
                    MessageBox(hwnd, msg, "Search Result", MB_OK); // Display the data in a popup
                    
                    // Auto-fill the bottom edit boxes so the user can easily update or view completely
                    SetWindowText(hName, s[found].name);
                    SetWindowText(hBranch, s[found].branch);
                    char sStr[10]; snprintf(sStr,10,"%d",s[found].sem); // Convert sem to string for box
                    SetWindowText(hSem, sStr);
                    SetWindowText(hPhone, s[found].phone);
                    // Crucially, fill the USN field so "Update" works if clicked next
                    SetWindowText(hUSN, s[found].USN); 
                } else {
                    // Not found means it does not exist in array
                    MessageBox(hwnd, "Not found.", "Error", MB_ICONERROR);
                }
            }
            // Check if user clicked Export TXT
            else if (LOWORD(wParam) == ID_BTN_EXPORT) {
                // calls external function passing flag '1' meaning txt output
                if (exportDataGUI(s, student_count, 1)) {
                    MessageBox(hwnd, "Exported to data/export/students.txt", "Success", MB_OK);
                } else {
                    MessageBox(hwnd, "Failed to export", "Error", MB_ICONERROR);
                }
            }
            // Check if user clicked Export CSV
            else if (LOWORD(wParam) == ID_BTN_EXPORT_CSV) {
                // calls external function passing flag '2' meaning csv output
                if (exportDataGUI(s, student_count, 2)) {
                    MessageBox(hwnd, "Exported to data/export/students.csv", "Success", MB_OK);
                } else {
                    MessageBox(hwnd, "Failed to export CSV", "Error", MB_ICONERROR);
                }
            }
            break; // End of WM_COMMAND handling
        }
        
        // Message sent when the window is closed/destroyed
        case WM_DESTROY: {
            if (hFont) DeleteObject(hFont); // Free up the memory used by our custom font
            PostQuitMessage(0);             // Tells the message loop in WinMain to stop and exit the app
            break;                          // End of WM_DESTROY handling
        }
    }
    
    // For any messages we don't manually handle above, we pass them back to standard Windows handler
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// WinMain: This is the actual entry point for typical Windows GUI applications (like main() in console apps)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize common controls so our ListView control works on modern Windows versions
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);     // Must set the size of struct
    icex.dwICC = ICC_LISTVIEW_CLASSES;              // Tell Windows we want ListView classes
    InitCommonControlsEx(&icex);                    // Activate the controls
    
    // Setup and register a Window Class for our main window
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;                       // Tie our message handler function to this window class
    wc.hInstance = hInstance;                       // Handle to the current running application instance
    wc.lpszClassName = "StudentGUI";                // A unique string identifier for this class
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1); // Set default background color to standard button face color
    
    RegisterClass(&wc);                             // Register it with the Windows OS
    
    // Actually invoke creation of the main window using the class we just formulated
    HWND hwnd = CreateWindow("StudentGUI", "Student Management System Windows UI",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,           // Window style (has title bar, resizable, visible by default)
        100, 100, 690, 520,                         // X pos, Y pos, Width, Height
        NULL, NULL, hInstance, NULL);               // Parent, Menu, Instance, extra params
    
    // MSG struct stores messages the OS sends us (clicks, keypresses, system signals)
    MSG msg;
    // Enter the infinite loop that keeps the application running and processing user interactions
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);                     // Convert virtual-key messages to character messages
        DispatchMessage(&msg);                      // Forward the message to our WndProc function
    }
    
    return 0; // Return gracefully to OS
}
