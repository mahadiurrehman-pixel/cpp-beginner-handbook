// ============================================
// Chapter 6 Companion: star-patterns.cpp
// ============================================
// Four classic nested-loop patterns in one program.
// Compile:  g++ star-patterns.cpp -o patterns
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Enter pattern size: ";
    cin  >> n;                       // try 5

    // ---------- 1. Square ----------
    cout << "\n--- Square ---\n";
    for (int r = 1; r <= n; r++) {
        for (int c = 1; c <= n; c++) cout << "* ";
        cout << endl;
    }

    // ---------- 2. Rising triangle ----------
    cout << "\n--- Triangle (up) ---\n";
    for (int r = 1; r <= n; r++) {           // stars = row number
        for (int c = 1; c <= r; c++) cout << "* ";
        cout << endl;
    }

    // ---------- 3. Falling triangle ----------
    cout << "\n--- Triangle (down) ---\n";
    for (int r = n; r >= 1; r--) {           // count DOWN!
        for (int c = 1; c <= r; c++) cout << "* ";
        cout << endl;
    }

    // ---------- 4. Pyramid ----------
    cout << "\n--- Pyramid ---\n";
    for (int r = 1; r <= n; r++) {
        for (int s = 1; s <= n - r; s++)     cout << "  ";   // spaces first
        for (int st = 1; st <= 2 * r - 1; st++) cout << "* "; // then stars
        cout << endl;
    }

    return 0;
}
