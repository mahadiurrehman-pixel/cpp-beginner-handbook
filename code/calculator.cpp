// ============================================
// Chapter 7 Companion: calculator.cpp
// ============================================
// Function-powered menu calculator: Chapters 5+6+7 combined.
// Compile:  g++ calculator.cpp -o calculator
// ============================================

#include <iostream>
using namespace std;

// ---------- The math "library" — one job per function ----------
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }

// Returns result; sets ok=false on divide-by-zero
// (the bool& means callers see the change — Chapter 10 explains &)
double divide(double a, double b, bool& ok) {
    if (b == 0) { ok = false; return 0; }
    ok = true;
    return a / b;
}

void showMenu() {                      // void: action, no answer needed
    cout << "\n===== CALCULATOR =====\n";
    cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n";
    cout << "Choose: ";
}

int main() {

    int choice;

    do {
        showMenu();
        cin >> choice;

        if (choice == 5) {                      // exit path
            cout << "Thanks for calculating. Bye!\n";
            break;
        }
        if (choice < 1 || choice > 5) {         // validation path
            cout << "Please pick 1-5!\n";
            continue;                           // back to menu
        }

        double a, b;
        cout << "Enter two numbers: ";
        cin  >> a >> b;

        switch (choice) {                       // route to the function
            case 1: cout << "= " << add(a, b) << endl; break;
            case 2: cout << "= " << sub(a, b) << endl; break;
            case 3: cout << "= " << mul(a, b) << endl; break;
            case 4: {
                bool ok;
                double ans = divide(a, b, ok);
                if (ok) cout << "= " << ans << endl;
                else    cout << "Cannot divide by zero!\n";
                break;
            }
        }

    } while (true);   // the loop lives until 'break' on option 5

    return 0;
}
