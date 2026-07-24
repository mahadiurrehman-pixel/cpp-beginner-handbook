// ============================================
// Chapter 2 Companion: hello-world.cpp
// ============================================
// The first program every programmer writes.
// Compile:  g++ hello-world.cpp -o hello
// Run:      ./hello        (Windows: hello)
// ============================================

#include <iostream>    // brings in cout (printing) and cin (reading)
using namespace std;   // shortcut so we can write cout, not std::cout

int main() {           // every C++ program starts here, always

    // The classic greeting — welcome to the club!
    cout << "Hello, World!" << endl;

    // A second line proving statements run top to bottom:
    cout << "I am Mahadi's student, and I can write C++." << endl;

    return 0;          // tell the operating system: success!
}
