# Student Management System (Windows GUI)

## 📌 Overview
This project is a **Student Management System with a graphical user interface (GUI)** designed to manage student records efficiently. It allows users to add, update, delete, search, and export student data.

The system is built using C (backend logic) with a Windows-based GUI for user interaction.

---

## 🖥️ Features

### ✅ Core Functionalities
- Add new student records
- Update existing student details
- Delete student records
- Display all students in a table format

### 🔍 Search
- Search student by USN (Unique Student Number)

### 📤 Export Options
- Export data to:
  - TXT file
  - CSV file (Excel compatible)

---

## 🧾 Student Fields
Each student record contains:
- USN (Unique Key)
- Name
- Branch
- Semester
- Phone Number

---

## 🧰 GUI Layout

### Main Sections:
1. **Table View**
   - Displays all student records
   - Columns: USN, Name, Branch, Sem, Phone

2. **Operations Panel**
   - Add/Update
   - Delete

3. **Export Panel**
   - Export TXT
   - Export CSV

4. **Search Panel**
   - Input field
   - Find button

5. **Student Details Form**
   - Input fields for:
     - Name
     - USN
     - Branch
     - Semester
     - Phone

---

## ⚙️ How It Works

- Data is stored in a file (or memory depending on implementation)
- GUI interacts with backend C functions:
  - `append.c` → Add records
  - `display.c` → Show records
  - `search.c` → Find student
  - `delete.c` → Remove record
  - `update.c` → Modify record
  - `file.c` → File handling

---

## 🛠️ Compilation & Run

### Requirements:
- GCC Compiler (MinGW recommended for Windows)
- Windows OS

### Compile:
```bash
gcc main.c file.c append.c display.c search.c delete.c update.c -o student.exe
```

### Run:
```bash
./student.exe
```

---

## 📂 Project Structure

```
Student-Management-System-Using-Structures/
├── main.c             # Main application entry point
├── file.c             # File handling operations
├── append.c           # Add student records
├── display.c          # Display student records
├── search.c           # Search student records
├── delete.c           # Delete student records
├── update.c           # Update student records
└── README.md          # Project documentation
```

---

## 📝 Notes

- This project uses **basic GUI concepts** for the user interface
- All backend logic is implemented in C
- Suitable for **mini-project** requirements
- Windows-specific implementation

---

## 🤝 Contributing

Contributions are welcome! This is a learning project, and improvements are always appreciated.

---