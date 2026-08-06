# CHAPTER 21 — PROJECT 1: STUDENT MANAGEMENT SYSTEM

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"You don't really know a topic until
 you've built something real with it."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 20](chapter-20-data-structures.md) | [🏠 Home](README.md) | [Chapter 22 ➡️](chapter-22-project-bank-system.md)**

```
                  PART 5: PROJECTS
```

---

## 1. 🎯 PROBLEM STATEMENT — What & Why

Schools drown in paper registers. Our task: a console **Student Management System** that stores students (roll, name, marks), saves them to disk automatically, and answers real questions: *who's the topper? did roll 102 pass? show everyone sorted by marks.*

**Chapters it combines:** 3 (variables) → 4/5/6 (input, decisions, loops) → 7 (functions) → 9 (strings) → 11–13 (classes, constructors) → 17 (files) → 18 (exceptions, lightly) → 19 (`vector`, `sort`, algorithms). *Everything, converging.*

## 2. 📋 FEATURES LIST

```
1 ➕  Add student (validates: non-empty name, marks 0-100, unique roll)
2 📜  List all students (numbered)
3 🔍  Search by roll number
4 ✏️   Update marks of an existing student
5 🥇  Show topper + class average
6 🔃  List sorted by marks (descending)
7 🗑️   Delete a student by roll
8 💾  Auto-save after every change; auto-load at start (students.csv)
9 🚪  Exit (everything already safely saved)
```

## 3. 🗺️ PLANNING PHASE

```
DATA MODEL
  class Student: roll, name, marks, grade()  + toCSV()/fromCSV helpers

STORAGE
  vector<Student> students        (in memory — fast)
  students.csv                    (on disk — permanent)
  Format per line:  roll,name,marks   →  101,Ali Raza,78

FLOW
  START → loadCSV() → MENU LOOP ─┬─ add      → validate → push → saveCSV()
                                 ├─ list     → range-for print
                                 ├─ search   → find by roll → print info
                                 ├─ update   → find → set marks → saveCSV()
                                 ├─ stats    → max_element + average
                                 ├─ sort     → copy + sort(desc) → print
                                 ├─ delete   → find → erase → saveCSV()
                                 └─ exit     → break → bye

VALIDATION LAWS (all live in one place: addStudent)
  ✗ empty name      ✗ marks outside 0-100      ✗ duplicate roll
  ✗ non-numeric text input (safeReadInt handles)

PSEUDOCODE — menu loop:
  while true:
      print menu; choice = safeReadInt()
      switch(choice): 1..8 call the matching function; 0 → exit
```

## 4. 💻 COMPLETE CODE

> Save as `student_management.cpp` → `g++ student_management.cpp -o sms` → run.

```cpp
// @SMS-START
// ============================================
// PROJECT 1: STUDENT MANAGEMENT SYSTEM
// Chapters used: 3-7, 9, 11-13, 17, 18, 19
// ============================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

const string FILE_NAME = "students.csv";

// ---------------- MODEL ----------------
class Student {
public:
    int    roll;
    string name;
    int    marks;

    char grade() const {                 // derived data, always consistent
        if (marks >= 90) return 'A';
        if (marks >= 80) return 'B';
        if (marks >= 70) return 'C';
        if (marks >= 60) return 'D';
        return 'F';
    }

    string toCSV() const {               // serialize (Ch. 17)
        return to_string(roll) + "," + name + "," + to_string(marks);
    }
};

// ---------------- SAFE INPUT (Ch. 18) ----------------
int safeReadInt(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        try { return stoi(line); }
        catch (const invalid_argument&) {
            cout << "  ✗ Numbers only. Try again.\n";
        }
    }
}

// ---------------- FILE LAYER ----------------
vector<Student> loadCSV() {
    vector<Student> v;
    ifstream in(FILE_NAME);
    if (!in.is_open()) return v;                       // first run = empty school

    string line;
    while (getline(in, line)) {
        try {
            int c1 = line.find(',');
            int c2 = line.find(',', c1 + 1);
            if (c1 == (int)string::npos || c2 == (int)string::npos) continue;

            Student s;
            s.roll  = stoi(line.substr(0, c1));
            s.name  = line.substr(c1 + 1, c2 - c1 - 1);
            s.marks = stoi(line.substr(c2 + 1));
            v.push_back(s);
        }
        catch (...) { /* skip corrupt row quietly */ }
    }
    return v;
}

void saveCSV(const vector<Student>& v) {
    ofstream out(FILE_NAME);                           // full rewrite = current truth
    for (const Student& s : v) out << s.toCSV() << "\n";
}

// ---------------- OPERATIONS ----------------
void addStudent(vector<Student>& v) {
    Student s;
    s.roll = safeReadInt("Roll no: ");

    for (const Student& old : v)
        if (old.roll == s.roll) { cout << "✗ Roll already exists!\n"; return; }

    cout << "Name: ";
    getline(cin, s.name);
    if (s.name.empty()) { cout << "✗ Name can't be empty!\n"; return; }

    s.marks = safeReadInt("Marks (0-100): ");
    if (s.marks < 0 || s.marks > 100) { cout << "✗ Marks out of range!\n"; return; }

    v.push_back(s);
    saveCSV(v);
    cout << "✓ Added and saved.\n";
}

void listAll(const vector<Student>& v) {
    if (v.empty()) { cout << "(no students yet)\n"; return; }
    cout << "\n #  Roll  Name                 Marks  Grade\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << " "  << i + 1 << "   "
             << v[i].roll << "   "
             << v[i].name;
        for (int p = (int)v[i].name.length(); p < 20; p++) cout << " ";   // padding
        cout << " " << v[i].marks << "     "  << v[i].grade() << "\n";
    }
}

int findIndexByRoll(const vector<Student>& v, int roll) {
    for (int i = 0; i < (int)v.size(); i++)
        if (v[i].roll == roll) return i;
    return -1;
}

void searchStudent(const vector<Student>& v) {
    int roll = safeReadInt("Roll to search: ");
    int i = findIndexByRoll(v, roll);
    if (i == -1) { cout << "✗ Not found.\n"; return; }
    cout << "→ " << v[i].name << " scored " << v[i].marks
         << " (" << v[i].grade() << ")\n";
}

void updateMarks(vector<Student>& v) {
    int roll = safeReadInt("Roll to update: ");
    int i = findIndexByRoll(v, roll);
    if (i == -1) { cout << "✗ Not found.\n"; return; }
    int m = safeReadInt("New marks (0-100): ");
    if (m < 0 || m > 100) { cout << "✗ Out of range!\n"; return; }
    v[i].marks = m;
    saveCSV(v);
    cout << "✓ Updated.\n";
}

void showStats(const vector<Student>& v) {
    if (v.empty()) { cout << "(no students yet)\n"; return; }

    auto topIt = max_element(v.begin(), v.end(),
        [](const Student& a, const Student& b) { return a.marks < b.marks; });

    double total = 0;
    for (const Student& s : v) total += s.marks;

    cout << "🥇 Topper: " << topIt->name << " (" << topIt->marks << ")\n";
    cout << "Class average: " << total / v.size() << "\n";
}

void listSortedDesc(vector<Student> v) {              // copy! order stays intact
    sort(v.begin(), v.end(),
        [](const Student& a, const Student& b) { return a.marks > b.marks; });
    listAll(v);
}

void deleteStudent(vector<Student>& v) {
    int roll = safeReadInt("Roll to delete: ");
    int i = findIndexByRoll(v, roll);
    if (i == -1) { cout << "✗ Not found.\n"; return; }
    cout << "Deleting " << v[i].name << "...\n";
    v.erase(v.begin() + i);
    saveCSV(v);
    cout << "✓ Deleted.\n";
}

// ---------------- MAIN / DIRECTOR ----------------
int main() {

    vector<Student> students = loadCSV();
    cout << "Loaded " << students.size() << " students from disk.\n";

    while (true) {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n"
             << "1 Add      2 List      3 Search    4 Update marks\n"
             << "5 Stats    6 Sort desc  7 Delete    0 Exit\n> ";
        int choice = safeReadInt("");

        switch (choice) {
            case 1: addStudent(students);   break;
            case 2: listAll(students);      break;
            case 3: searchStudent(students);break;
            case 4: updateMarks(students);  break;
            case 5: showStats(students);    break;
            case 6: listSortedDesc(students);break;
            case 7: deleteStudent(students);break;
            case 0:
                cout << "Data is saved. Goodbye! 👋\n";
                return 0;
            default: cout << "✗ Choose 0-7.\n";
        }
    }
}
// @SMS-END
```

## 5. 📺 OUTPUT SCREENSHOT (text)

```
Loaded 3 students from disk.

===== STUDENT MANAGEMENT SYSTEM =====
1 Add      2 List      3 Search    4 Update marks
5 Stats    6 Sort desc  7 Delete    0 Exit
> 2

 #  Roll  Name                 Marks  Grade
------------------------------------------------
 1   101   Ali Raza              78     C
 2   102   Sara Ahmed            91     A
 3   103   Omar Farooq           64     D

> 5
🥇 Topper: Sara Ahmed (91)
Class average: 77.6667

> 6
 #  Roll  Name                 Marks  Grade
------------------------------------------------
 1   102   Sara Ahmed            91     A
 2   101   Ali Raza              78     C
 3   103   Omar Farooq           64     D

> 0
Data is saved. Goodbye! 👋
```

## 6. 🚀 HOW TO EXTEND IT

1. **Multiple subjects** — make marks a `vector<int>` and grade() average them
2. **Attendance %** — new field, added to CSV row
3. **Login screen** — reuse Chapter 18's safe CLI patterns before menu unlocks
4. **Search by name (substring)** — `name.find(q) != npos` over the vector
5. **Export honors report** — write a second file `honors.txt` for marks ≥ 85
6. **Undo delete** — push the deleted Student onto a `stack<Student>` (Ch. 19!)

## 7. 🔍 CODE REVIEW — Key Decisions

| Decision | Why |
|---|---|
| `vector<Student>` in memory | RAM-speed operations; file = backup, not workspace |
| Save after EVERY change | crash mid-session loses zero data |
| `.csv` plain text | human-readable, Excel opens it, diffable |
| `safeReadInt` + stoi | letter input can NEVER crash the app (Ch. 18) |
| Validation inside `addStudent` | one law office — nowhere else can create bad data |
| sort on a COPY | keeps add-order while showing ranked order |
| `grade()` computed, not stored | can't drift out of sync with marks |

## 8. 🐛 COMMON BUGS & FIXES

| Bug you'll hit | Why | Fix |
|---|---|---|
| Empty file → "no students" forever | loadCSV skips everything | normal! add one |
| Comma in a name breaks parsing | CSV naïve split | forbid commas in names or use `;` as separator |
| Menu loops forever on letters | raw `cin >> choice` fails mid-loop | `safeReadInt` (already in) |
| Sorted list reorders original | sorted the real vector | sort a copy (done) |
| Roll duplicates sneak in | forgot the check | loop-scan in addStudent (done) |

**Motivation:** This is no toy — it loads, saves, validates, searches, and sorts like a departmental tool. You wrote it. 🏆

---

**⬅️ [Chapter 20](chapter-20-data-structures.md) | [🏠 Home](README.md) | [Chapter 22 ➡️](chapter-22-project-bank-system.md)**
