// ============================================
// Chapter 4 Companion: operators-demo.cpp
// ============================================
// Interactive tour: cin, arithmetic, %, ++, comparisons, logic, bits.
// Compile:  g++ operators-demo.cpp -o operators
// ============================================

#include <iostream>
using namespace std;

int main() {

    // ---------- 1. cin + arithmetic ----------
    int a, b;
    cout << "Enter two integers: ";
    cin  >> a >> b;                         // e.g. 20 6

    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;    // int division: chops!
    cout << "a % b = " << a % b << endl;    // the remainder

    // ---------- 2. compound assignment + increments ----------
    int score = 100;
    score += 50;                            // 150
    score -= 30;                            // 120
    score *= 2;                             // 240
    cout << "\nscore = " << score << endl;

    int x = 5;
    // NOTE: we print x and use ++ on separate statements.
    // Modifying x AND reading it again in ONE expression is unsafe
    // (compiler warning: sequence point). Keep them apart — always.
    cout << "x++ shows: " << x++ << endl;        // 5, then x becomes 6
    cout << "x is now:  " << x   << endl;        // 6
    cout << "++x shows: " << ++x << endl;        // x becomes 7, then prints 7
    cout << "x is now:  " << x   << endl;        // 7

    // ---------- 3. comparisons + logic = bool ----------
    int age;
    char member;
    cout << "\nEnter age and membership (y/n): ";
    cin  >> age >> member;

    bool canEnter = (age >= 18) && (member == 'y');
    bool freeTrial = (age >= 18) && !(member == 'y');
    cout << "Full access (1/0): " << canEnter  << endl;
    cout << "Free trial  (1/0): " << freeTrial << endl;

    // ---------- 4. precedence ----------
    cout << "\n2 + 3 * 4 = " << 2 + 3 * 4 << endl;      // 14
    cout << "(2 + 3) * 4 = " << (2 + 3) * 4 << endl;    // 20

    // ---------- 5. bitwise fun ----------
    int n;
    cout << "\nEnter an integer for bit play: ";
    cin  >> n;
    cout << "n << 1 = " << (n << 1) << "  (doubled)"  << endl;
    cout << "n >> 1 = " << (n >> 1) << "  (halved)"   << endl;
    cout << "n & 1  = " << (n & 1)  << "  (last bit)" << endl;

    return 0;
}
