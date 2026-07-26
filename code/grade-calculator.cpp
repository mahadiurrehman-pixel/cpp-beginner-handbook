// ============================================
// Chapter 5 Companion: grade-calculator.cpp
// ============================================
// else-if ladder + validation + ternary verdict.
// Compile:  g++ grade-calculator.cpp -o grades
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    double marks;
    cout << "Enter marks (0-100): ";
    cin  >> marks;

    // ---- The bouncer: validate BEFORE processing ----
    if (marks < 0 || marks > 100) {
        cout << "Invalid marks! Range is 0-100." << endl;
        return 0;                        // stop here for bad input
    }

    // ---- The ladder: check highest first! ----
    char grade;
    if (marks >= 90)      grade = 'A';
    else if (marks >= 80) grade = 'B';
    else if (marks >= 70) grade = 'C';
    else if (marks >= 60) grade = 'D';
    else                  grade = 'F';

    cout << "Grade: " << grade << endl;

    // ---- Ternary one-liner for the verdict ----
    cout << (grade == 'F' ? "Result: Fail — comeback loading..." 
                          : "Result: Pass — well done!") << endl;

    return 0;
}
