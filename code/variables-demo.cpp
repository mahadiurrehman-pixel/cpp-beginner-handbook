// ============================================
// Chapter 3 Companion: variables-demo.cpp
// ============================================
// A tour of every basic data type, const, auto, sizeof, casting.
// Compile:  g++ variables-demo.cpp -o variables
// ============================================

#include <iostream>
#include <string>       // required for the string type
using namespace std;

int main() {

    // ---------- 1. The core types ----------
    int     age      = 20;          // whole numbers
    double  height   = 5.9;         // precise decimals
    float   weight   = 68.5f;       // compact decimals (note the f)
    char    initial  = 'M';         // ONE character, single quotes
    bool    isCoder  = true;        // true / false
    string  name     = "Mahadi";    // text, double quotes

    cout << "Name: "    << name    << endl;
    cout << "Age: "     << age     << endl;
    cout << "Height: "  << height  << endl;
    cout << "Weight: "  << weight  << endl;
    cout << "Initial: " << initial << endl;
    cout << "Coder? "   << isCoder << endl;   // prints 1

    cout << endl;

    // ---------- 2. const: the locked box ----------
    const double PI = 3.14159;      // ALL_CAPS by convention
    double radius = 7.0;
    cout << "Circle area (r=7): " << PI * radius * radius << endl;

    // ---------- 3. auto: let the compiler deduce ----------
    auto year  = 2026;              // deduced: int
    auto ratio = 0.75;              // deduced: double
    cout << "year=" << year << "  ratio=" << ratio << endl;

    // ---------- 4. sizeof: measuring the boxes ----------
    cout << "\nsizeof(int)="    << sizeof(int)
         << "  sizeof(double)=" << sizeof(double)
         << "  sizeof(char)="   << sizeof(char) << endl;

    // ---------- 5. integer division vs casting ----------
    int a = 5, b = 2;
    cout << "\n5/2 as ints:       " << a / b            << endl;  // 2
    cout << "5/2 cast to double: " << (double)a / b     << endl;  // 2.5

    // ---------- 6. ASCII peek ----------
    cout << "\n'A' as number: " << (int)'A' << endl;    // 65
    cout << "'A'+1 as char: " << (char)('A' + 1) << endl; // B

    return 0;
}
