# CHAPTER 7 — FUNCTIONS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A function is a recipe: write it once,
 cook with it a thousand times."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 6](chapter-06-loops.md) | [🏠 Home](README.md) | [Chapter 8 ➡️](chapter-08-arrays.md)**

---

## 📖 CHAPTER OPENING

Imagine rewriting the recipe for chai from scratch every morning — measuring instructions, boiling steps, everything. Instead, you write it ONCE, stick it on the fridge, and say "make chai" forever after. A **function** is exactly that: a named recipe of code you define once and **call** anytime.

### What you will learn:
- What functions are and why every real program is built from them
- Declaration vs. definition (the promise vs. the delivery)
- Parameters & arguments — passing ingredients in
- Return values — getting results back
- `void` functions — doing work without answering
- **Function overloading** — same name, different ingredients
- **Default parameters** — ingredients with backup values
- **Recursion** — functions that call themselves (mind-bender #1)
- Scope — where variables exist and where they don't

### Why this chapter matters:
This is the most important structural skill in all of programming. Functions let you break giant problems into small, testable, reusable pieces. Chapter 7 is the last chapter of "writing programs" — everything after it is **engineering software**.

---

## 🔍 CONCEPT EXPLANATION

### What is a function?

A **function** is a named block of code that performs one job. It can receive inputs (**parameters**), do work, and hand back one result (**return value**).

```
        ┌─────────────────────────────┐
 inputs │      int add(a, b)          │ output
  5, 3 ─┼──►   { return a + b; }   ───┼──► 8
        └─────────────────────────────┘
```

### Why do we use functions?

1. **Reuse** — write once, call a hundred times (no copy-paste)
2. **Organization** — `main()` reads like a summary, not a swamp
3. **Testing** — check each piece alone
4. **Teamwork** — everyone builds different functions, then assemble

### How does the computer understand it?

When you *call* a function, the CPU pauses `main`, **jumps** to the function's code with the argument values copied into the parameters, runs it, and on `return` **jumps back** to exactly where it left off — carrying the returned value like a lunchbox. The CPU keeps a "return address" in a special structure called the **call stack** (Chapter 10 makes this literal).

### Declaration vs. Definition — the promise and the delivery:

```cpp
int add(int a, int b);          // DECLARATION (prototype): "this exists"
                                // lets main call it BEFORE it's defined.

int main() {
    cout << add(5, 3);          // CALL: works because of the promise
}

int add(int a, int b) {         // DEFINITION: the actual recipe
    return a + b;
}
```

🔥 **REMEMBER:** If you define a function AFTER `main`, you must declare it before `main`. Otherwise the compiler meets `add(5, 3)` and says *"add? never heard of it."*

---

## 📝 SYNTAX BOX

### Anatomy of a function:

```cpp
int add(int a, int b) {          // HEADER: returnType name(parameters)
    return a + b;                // BODY: work + return the result
}                                // ← no semicolon after definition!

// Calling it:
int result = add(5, 3);          // ARGUMENTS 5,3 — copied INTO a,b
```

| Part | Name | Rule |
|---|---|---|
| `int` (first) | **Return type** | Type of the answer handed back; `void` = hands back nothing |
| `add` | **Function name** | Same rules as variables; verbs work great (`printLine`, `calcArea`) |
| `(int a, int b)` | **Parameters** | Named inputs; each needs its own type |
| `return x;` | **Return statement** | Sends value back AND exits the function immediately |
| `add(5, 3)` | **Call (arguments)** | The actual values fed in, in order |

### The variations:

```cpp
// 1️⃣ void function — works, returns nothing
void greet() {
    cout << "Hello!" << endl;
}

// 2️⃣ parameters with return
int square(int n) {
    return n * n;
}

// 3️⃣ OVERLOADING — same name, different parameter types/counts
double area(double r)          { return 3.14159 * r * r; }   // circle
int    area(int l, int w)      { return l * w; }             // rectangle

// 4️⃣ DEFAULT PARAMETERS — backup values when caller provides fewer
void greetUser(string name = "Guest", int stars = 1) {
    for (int i = 0; i < stars; i++) cout << "⭐";
    cout << " Welcome, " << name << "!" << endl;
}
// greetUser();          → uses both defaults
// greetUser("Sara");    → name="Sara", stars=1
// greetUser("Sara", 3); → both provided

// 5️⃣ RECURSION — a function calling itself (needs a base case!)
int factorial(int n) {
    if (n <= 1) return 1;            // ① BASE CASE — the exit door
    return n * factorial(n - 1);     // ② move toward the base case
}

// 6️⃣ SCOPE — where variables exist
int globalScore = 100;          // GLOBAL: visible everywhere (use sparingly!)

void demo() {
    int localX = 5;             // LOCAL: lives & dies inside demo()
}
```

> ⚠️ **WARNING:** Parameters are **copies**. `void fix(int x) { x = 99; }` does NOT change the caller's variable — it edits a photocopy. Changing the original requires references/pointers (Chapter 10). This surprises every beginner; now it won't surprise you.

---

## 💻 EXAMPLE CODES

### Example 7.1 — The Simplest Function (Hello World level)

```cpp
// ============================================
// Example 7.1: Your First Function
// ============================================
// What this program does: Defines greet() and calls it three times.
// Concepts used: void function, definition above main, calling
// ============================================

#include <iostream>
using namespace std;

void greet() {                       // definition: no inputs, no return
    cout << "Hello from the function!" << endl;
}

int main() {

    greet();          // call 1  → jumps up, prints, returns here
    greet();          // call 2
    greet();          // call 3 — recipe used 3 times, written once!

    cout << "Back in main." << endl;
    return 0;
}
/*
OUTPUT:
Hello from the function!
Hello from the function!
Hello from the function!
Back in main.

EXPLANATION:
Each greet() CALL makes the CPU detour into the function body,
execute it, then resume exactly after the call. Write once, run anywhere.
*/
```

**What happened here?** Three lines of execution became one reusable recipe. Notice `greet` is defined **before** `main`, so no separate declaration is needed.

---

### Example 7.2 — Parameters In, Result Out

```cpp
// ============================================
// Example 7.2: add() and square() — Real Answers
// ============================================
// What this program does: Functions with inputs and return values.
// Concepts used: parameters, return type, prototype declaration
// ============================================

#include <iostream>
using namespace std;

int    add(int a, int b);         // DECLARATIONS (prototypes) first,
int    square(int n);             // so main can call them today...

int main() {

    int x = 7, y = 8;

    cout << x << " + " << y << " = " << add(x, y)     << endl;
    cout << "Square of " << x << " = " << square(x)   << endl;
    cout << "add() result + 100 = " << add(5, 5) + 100 << endl; // returned values
                                                                 // are just VALUES

    return 0;
}

// ...and the DEFINITIONS delivered below, as promised.
int add(int a, int b) {
    return a + b;                 // result travels back to the caller
}

int square(int n) {
    return n * n;
}
/*
OUTPUT:
7 + 8 = 15
Square of 7 = 49
add() result + 100 = 110

EXPLANATION:
add(5, 5) evaluates TO 10 — anywhere an int fits, a function call
that returns int fits too. Prototypes at top, definitions at bottom
is the standard layout of clean C++ files.
*/
```

**What happened here?** Functions became **int-producing machines** you can drop into any expression. This is 90% of everyday function usage.

---

### Example 7.3 — Real-World Scenario: The Registration Validator

```cpp
// ============================================
// Example 7.3: Age Gate for a Website Signup
// ============================================
// What this program does: A bool function decides; main acts on the answer.
// Concepts used: bool return type, function used INSIDE an if, validation loop
// ============================================

#include <iostream>
using namespace std;

bool isValidAge(int age) {          // returns true/false — a YES/NO machine
    return age >= 13 && age <= 120; // one expression, one bool — elegant!
}

int main() {

    int age;

    do {
        cout << "Enter your age (13-120): ";
        cin  >> age;
        if (!isValidAge(age)) {                     // calling INSIDE a condition
            cout << "Nope. Try again." << endl;
        }
    } while (!isValidAge(age));                     // and inside a loop condition!

    cout << "Welcome aboard! Age verified: " << age << endl;
    return 0;
}
/*
INPUT:  7  200  19
OUTPUT:
Nope. Try again.
Nope. Try again.
Welcome aboard! Age verified: 19

EXPLANATION:
isValidAge() packages a rule ONCE; both the if and the while reuse it.
Change the rule to 16+? Edit ONE line. That's the power of functions —
the alternative is hunting every duplicated check through your program.
*/
```

**What happened here?** A bool-returning function behaves exactly like a condition anywhere conditions live: `if`, `while`, `for`. One rule, one function, zero duplication.

---

### Example 7.4 — Overloading: One Name, Many Shapes

```cpp
// ============================================
// Example 7.4: Area — Overloaded for Circle, Square, Rectangle
// ============================================
// What this program does: Three functions named area(), different parameters.
// Concepts used: function overloading, default parameter
// ============================================

#include <iostream>
using namespace std;

double area(double radius) {                       // version ① circle
    return 3.14159 * radius * radius;
}

int area(int side) {                               // version ② square
    return side * side;
}

double area(double length, double width) {         // version ③ rectangle
    return length * width;
}

double area(double base, double height, bool isTriangle) {  // version ④ triangle
    return 0.5 * base * height;
}

int main() {

    cout << "Circle r=3:      " << area(3.0)          << endl;  // ① double → circle
    cout << "Square s=5:      " << area(5)            << endl;  // ② int → square
    cout << "Rectangle 4x6:   " << area(4.0, 6.0)     << endl;  // ③ two doubles
    cout << "Triangle b=4,h=6:" << area(4.0, 6.0, true) << endl; // ④ three params

    return 0;
}
/*
OUTPUT:
Circle r=3:      28.2743
Square s=5:      25
Rectangle 4x6:   24
Triangle b=4,h=6:12

EXPLANATION:
The compiler picks the version by matching the ARGUMENT TYPES/COUNT —
that's overloading. area(3.0) → double → circle. area(5) → int → square.
You give callers one friendly name; C++ handles the routing.
*/
```

**What happened here?** Overloading is compile-time decision making (a sneak peek of Chapter 15's "compile-time polymorphism"). One name, several implementations, chosen automatically by the argument list.

📌 **NOTE:** The *return type alone* doesn't distinguish overloads — `int f()` and `double f()` can't coexist. The **parameters** must differ.

---

### Example 7.5 — Recursion: The Self-Calling Staircase

```cpp
// ============================================
// Example 7.5: Factorial, the Recursive Way
// ============================================
// What this program does: Computes 5! with a function calling itself,
//                          and shows depth as it goes.
// Concepts used: recursion, base case, call stack intuition
// ============================================

#include <iostream>
using namespace std;

int factorial(int n) {
    if (n <= 1) {                       // ① BASE CASE — stop condition
        return 1;                       //    (no deeper calls from here)
    }
    return n * factorial(n - 1);        // ② shrink the problem, call self
}

int main() {

    cout << "5! = " << factorial(5) << endl;
    cout << "7! = " << factorial(7) << endl;
    return 0;
}
/*
OUTPUT:
5! = 120
7! = 5040

HOW IT UNROLLS (factorial(5)):
  = 5 * factorial(4)
  = 5 * 4 * factorial(3)
  = 5 * 4 * 3 * factorial(2)
  = 5 * 4 * 3 * 2 * factorial(1)
  = 5 * 4 * 3 * 2 * 1            ← base case finally answers!
  = 120

EXPLANATION:
Every recursive call PAUSES the current one and stacks a new copy
with its own n. When factorial(1) returns 1, the paused calls
resume one by one, multiplying on the way back up.
*/
```

**What happened here?** Recursion = big problem → smaller identical problems → trivial problem (base case) → answers bubble back up. The two ingredients are non-negotiable: **base case** (exit) and **progress toward it** (`n-1`). Without either, you get infinite recursion and a *stack overflow* crash.

> ❓ **THINK ABOUT IT:** Is the loop version of factorial (Problem 6.4) or this recursive one easier to read? Iteration and recursion can always do each other's jobs — choosing is taste + context.

---

### Example 7.6 — Scope: Where Do Variables Live?

```cpp
// ============================================
// Example 7.6: Local vs Global Scope
// ============================================
// What this program does: Demonstrates variable lifetimes and shadowing.
// Concepts used: global variable, local variables, function scope
// ============================================

#include <iostream>
using namespace std;

int score = 100;                     // GLOBAL — visible in every function

void levelUp() {
    score += 50;                     // functions CAN touch the global
    int bonus = 20;                  // LOCAL — born here, dies here
    cout << "Inside levelUp: score=" << score
         << " bonus=" << bonus << endl;
}

int main() {

    int score = 10;                  // LOCAL main variable — SHADOWS the global!
    cout << "In main: local score=" << score << endl;   // prints 10 (local wins)

    levelUp();                       // uses the GLOBAL score: 100→150
    cout << "Global score now: " << ::score << endl;    // :: = "the global one"

    // cout << bonus;                // ❌ ERROR: bonus died when levelUp() ended

    for (int i = 0; i < 1; i++) {
        int hidden = 5;              // exists only inside this for-block
    }
    // cout << hidden;               // ❌ ERROR: out of scope

    return 0;
}
/*
OUTPUT:
In main: local score=10
Inside levelUp: score=150 bonus=20
Global score now: 150

EXPLANATION:
Variables exist only inside their { } — that's SCOPE.
A local name beats a global name inside its own home (shadowing).
Globals work, but overusing them makes debugging miserable:
any function anywhere could have changed them. Prefer parameters!
*/
```

**What happened here?** Scope is the "neighborhood" a variable lives in — its own braces. Locals are safe (nobody else can touch them); globals are convenient but dangerous. Modern C++ practice: pass data via parameters, keep globals near zero.

---

### Example 7.7 — Combined: The Function-Powered Calculator

```cpp
// ============================================
// Example 7.7: Menu Calculator (Chapters 5 + 6 + 7 united)
// ============================================
// What this program does: A loop menu whose options call clean functions.
// Concepts used: prototypes, parameters/returns, do-while, switch, validation
// ============================================

#include <iostream>
using namespace std;

double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double divide(double a, double b, bool& ok) {     // & makes ok changeable —
    if (b == 0) { ok = false; return 0; }         // Chapter 10 explains; today,
    ok = true;                                    // just accept the magic ✨
    return a / b;
}

int main() {

    int choice;
    do {
        cout << "\n=== CALCULATOR ===\n";
        cout << "1. Add  2. Subtract  3. Multiply  4. Divide  5. Exit\n> ";
        cin  >> choice;

        if (choice == 5) { cout << "Bye!\n"; break; }
        if (choice < 1 || choice > 5) { cout << "Pick 1-5!\n"; continue; }

        double a, b;
        cout << "Two numbers: ";
        cin  >> a >> b;

        switch (choice) {
            case 1: cout << "Answer: " << add(a, b) << endl; break;
            case 2: cout << "Answer: " << sub(a, b) << endl; break;
            case 3: cout << "Answer: " << mul(a, b) << endl; break;
            case 4: {
                bool ok;
                double ans = divide(a, b, ok);
                if (ok) cout << "Answer: " << ans    << endl;
                else    cout << "Cannot divide by zero!" << endl;
                break;
            }
        }
    } while (true);

    return 0;
}
/*
SAMPLE RUN:
=== CALCULATOR ===
1. Add  2. Subtract  3. Multiply  4. Divide  5. Exit
> 4
Two numbers: 10 0
Cannot divide by zero!

EXPLANATION:
main() is now a DIRECTOR — it reads choices and delegates to functions.
Every mathematical rule lives in exactly ONE named place.
This architecture is how we'll build the Part 5 projects.
*/
```

**What happened here?** Every chapter converged: functions (7) + menu loop (6) + switch (5) + input (4) + variables (3). You now write *organized software*.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Forgetting to return in a non-void function**
```cpp
int max(int a, int b) {
    if (a > b) return a;
    // ❌ no return when b >= a — undefined garbage on that path!
}
```
Compiler says: `warning: control reaches end of non-void function`
✅ **Fix:** Every path must return: `if (a > b) return a; return b;`

**❌ Mistake 2 — Calling before the compiler knows the function**
```cpp
int main() { greet(); }          // ❌ 'greet' was not declared
void greet() { cout << "Hi"; }   // defined too late, no prototype
```
✅ **Fix:** Add `void greet();` above main (or move the definition up).

**❌ Mistake 3 — Semicolon after the definition header**
```cpp
int add(int a, int b);           // ← prototype: semicolon CORRECT
int add(int a, int b); {         // ← definition with semicolon: ERROR
```
✅ **Fix:** Prototypes end with `;`. Definition headers never do.

**❌ Mistake 4 — Expecting parameter changes to reach the caller**
```cpp
void doubleIt(int x) { x = x * 2; }
int main() { int n = 5; doubleIt(n); cout << n; }   // prints 5, not 10!
```
✅ **Fix:** Return the result: `int doubleIt(int x) { return x*2; }` — or learn references in Chapter 10.

**❌ Mistake 5 — Recursion without a base case**
```cpp
int f(int n) { return n * f(n - 1); }   // never stops → "stack overflow" crash
```
✅ **Fix:** Base case first, progress toward it:
```cpp
int f(int n) { if (n <= 1) return 1; return n * f(n - 1); }
```

**❌ Mistake 6 — Duplicate parameter types / mismatched calls**
```cpp
double area(double a, b) { }      // ❌ b has NO type — every param needs its own
area(3);                          // ❌ wrong number of arguments
```
Compiler says: `error: too few arguments to function`
✅ **Fix:** `double area(double a, double b)` and call with matching count & types.

---

## 🧠 CONCEPT SUMMARY TABLE

| Concept | Meaning | Remember |
|---|---|---|
| Function | Named, reusable code block | Recipe analogy |
| Declaration/prototype | Promise it exists | Ends with `;` |
| Definition | The actual code | Header has NO `;` |
| Parameter | Named input (a copy) | Pass-by-value: originals safe |
| Argument | Value given at call | Order + types must match |
| `return` | Sends result back, exits | Non-void needs it on every path |
| `void` | No return value | For actions, not answers |
| Overloading | Same name, different params | Compiler matches by arguments |
| Default params | Backup values | Must be the RIGHTMOST params |
| Recursion | Function calls itself | Base case + progress = mandatory |
| Local variable | Lives inside { } | Safe, preferred |
| Global variable | Lives everywhere | Dangerous; minimize |
| Shadowing | Local name hides global | `::name` reaches the global |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Write void printLine(char c, int n) that prints
   n copies of c on one line. Call it to print a border of 20 '='.
📥 SAMPLE CALL: printLine('=', 20);
📤 EXPECTED OUTPUT: ====================
💡 HINT: A for loop INSIDE the function.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Write int cube(int n) returning n³. Read a number
   in main and print its cube.
📥 SAMPLE INPUT: 4
📤 EXPECTED OUTPUT: 64
💡 HINT: return n * n * n;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Write bool isEven(int n). In main, read N and
   print "Even"/"Odd" USING your function's answer.
📥 SAMPLE INPUT: 7
📤 EXPECTED OUTPUT: Odd
💡 HINT: return (n % 2 == 0);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Write int max3(int a, int b, int c) returning the
   largest of three, WITHOUT if-statements 4 layers deep —
   reuse a helper int max2(int, int).
📥 SAMPLE INPUT: 12 45 23
📤 EXPECTED OUTPUT: 45
💡 HINT: return max2(max2(a, b), c); — functions calling functions!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Write long long power(int base, int exp) using a
   loop (no built-ins). Handle exp=0 → 1.
📥 SAMPLE INPUT: 2 10
📤 EXPECTED OUTPUT: 1024
💡 HINT: Accumulator starts at 1, multiply exp times.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Write bool isPrime(int n) (from Ch. 6 logic), then
   print ALL primes between 1 and 100 by CALLING it in a loop.
📤 EXPECTED OUTPUT: 2 3 5 7 11 13 ... 97
💡 HINT: for(i=2..100) if(isPrime(i)) cout << i;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Write double bill(double amount, double taxRate = 0.05)
   using a default 5% tax. Print bills for: 1000 (default tax),
   1000 at 0.16.
📤 EXPECTED OUTPUT:
1050
1160
💡 HINT: return amount * (1 + taxRate);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Recursion: write int sumDigits(int n) that returns
   the digit sum RECURSIVELY (no loops, no strings).
📥 SAMPLE INPUT: 9874
📤 EXPECTED OUTPUT: 28
💡 HINT: Base: n==0 → 0. Else: n%10 + sumDigits(n/10).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Overload a function called describe: one version
   takes an int and prints "Integer: X (even/odd)", another
   takes a double and prints "Decimal: X.X", a third takes a
   char and prints "Character: X".
📥 SAMPLE INPUT: describe(7); describe(3.5); describe('Z');
📤 EXPECTED OUTPUT:
Integer: 7 (odd)
Decimal: 3.5
Character: Z
💡 HINT: Three definitions, one name; the call picks by type.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 7.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Build a mini password system: bool setPassword(int pin)
   stores a pin IF it's exactly 4 digits (return success); and
   bool login(int attempt) compares against it. Use ONE global
   (the stored pin — justified here), and a main loop giving the
   user 3 login attempts.
📥 SAMPLE INPUT: set 5678 → attempts: 1111, 5678
📤 EXPECTED OUTPUT:
Password set!
Wrong PIN (2 left)
Login successful!
💡 HINT: Global int savedPin; both functions use it; main loops
   with break on success.
```

---

## 🎯 MINI CHALLENGE — BUILD YOUR OWN MATH LIBRARY 📐

Create a personal toolbox of functions, then a `main()` that demonstrates each:

```cpp
// Required arsenal:
bool isPrime(int n);
bool isPalindrome(int n);        // reuse Ch.6 reversal INSIDE (helper function!)
int  reverseNum(int n);
long long power(int b, int e);
int  gcd(int a, int b);          // Greatest Common Divisor — classic Euclid:
                                 // while(b != 0){ int t=b; b=a%b; a=t; } return a;
int  sumDigits(int n);           // recursion from 7.8
```

Then print a report:
```
== MY MATH LIBRARY ==
isPrime(29)?       1
reverseNum(1234)   4321
power(3, 4)        81
gcd(48, 36)        12
sumDigits(987)     24
isPalindrome(1221) 1
```

Every professional writes little libraries like this; today you started yours. Put it in a file called `mymath.cpp` — you'll reuse it in Part 5 projects. 🔧

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 7.1**
```cpp
#include <iostream>
using namespace std;

void printLine(char c, int n) {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}

int main() {
    printLine('=', 20);
    printLine('-', 10);
    return 0;
}
```
💡 **PRO TIP:** Functions that print (actions) → `void`. Functions that compute (answers) → return a value. Ask: "do I need the result, or just the effect?"

**✅ SOLUTION 7.2**
```cpp
#include <iostream>
using namespace std;

int cube(int n) { return n * n * n; }

int main() {
    int n;
    cin >> n;
    cout << cube(n) << endl;
    return 0;
}
```

**✅ SOLUTION 7.3**
```cpp
#include <iostream>
using namespace std;

bool isEven(int n) { return n % 2 == 0; }

int main() {
    int n;
    cin >> n;
    cout << (isEven(n) ? "Even" : "Odd") << endl;
    return 0;
}
```
💡 **PRO TIP:** `return n % 2 == 0;` beats `if(...) return true; else return false;` — the comparison IS already a bool.

**✅ SOLUTION 7.4**
```cpp
#include <iostream>
using namespace std;

int max2(int a, int b) { return (a > b) ? a : b; }
int max3(int a, int b, int c) { return max2(max2(a, b), c); }

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << max3(a, b, c) << endl;
    return 0;
}
```
💡 **PRO TIP:** Composing small functions into bigger ones is THE professional technique. Small + correct + reusable wins over clever every time.

**✅ SOLUTION 7.5**
```cpp
#include <iostream>
using namespace std;

long long power(int base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;               // exp=0 → loop skipped → 1 ✔
}

int main() {
    int b, e;
    cin >> b >> e;
    cout << power(b, e) << endl;
    return 0;
}
```

**✅ SOLUTION 7.6**
```cpp
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;   // immediate exit — no flag needed
    return true;
}

int main() {
    for (int i = 2; i <= 100; i++)
        if (isPrime(i)) cout << i << " ";
    return 0;
}
```
💡 **PRO TIP:** Early `return false` inside the loop replaces the flag+break combo from Ch. 6 — functions give you cleaner exits.

**✅ SOLUTION 7.7**
```cpp
#include <iostream>
using namespace std;

double bill(double amount, double taxRate = 0.05) {
    return amount * (1 + taxRate);
}

int main() {
    cout << bill(1000)        << endl;   // default 5%
    cout << bill(1000, 0.16)  << endl;   // custom 16%
    return 0;
}
```
⚠️ **Rule reminder:** Defaults must sit on the right: `f(int a, int b = 5)` ✔ — `f(int a = 5, int b)` ❌.

**✅ SOLUTION 7.8**
```cpp
#include <iostream>
using namespace std;

int sumDigits(int n) {
    if (n == 0) return 0;              // base case
    return n % 10 + sumDigits(n / 10); // last digit + sum of the rest
}

int main() {
    int n;
    cin >> n;
    cout << sumDigits(n) << endl;
    return 0;
}
```
Trace: 9874 → 4 + sumDigits(987) → 4 + 7 + sumDigits(98) → 4+7+8+9+0 = 28.
💡 **PRO TIP:** "Last digit + answer for the rest" — many recursion problems decompose exactly this way.

**✅ SOLUTION 7.9**
```cpp
#include <iostream>
using namespace std;

void describe(int x)    { cout << "Integer: "   << x << (x % 2 == 0 ? " (even)" : " (odd)") << endl; }
void describe(double x) { cout << "Decimal: "   << x << endl; }
void describe(char x)   { cout << "Character: " << x << endl; }

int main() {
    describe(7);
    describe(3.5);
    describe('Z');
    return 0;
}
```

**✅ SOLUTION 7.10**
```cpp
#include <iostream>
using namespace std;

int savedPin = -1;                 // the one justified global

bool setPassword(int pin) {
    if (pin >= 1000 && pin <= 9999) { savedPin = pin; return true; }
    return false;
}

bool login(int attempt) { return attempt == savedPin; }

int main() {
    int pin;
    cout << "Set a 4-digit PIN: ";
    cin  >> pin;
    if (!setPassword(pin)) { cout << "Must be 4 digits!\n"; return 0; }
    cout << "Password set!\n";

    for (int left = 3; left > 0; left--) {
        int attempt;
        cout << "Enter PIN: ";
        cin  >> attempt;
        if (login(attempt)) { cout << "Login successful!\n"; return 0; }
        if (left > 1) cout << "Wrong PIN (" << left - 1 << " left)\n";
    }
    cout << "Account locked.\n";
    return 0;
}
```
💡 **PRO TIP:** One shared global is okay for a tiny example — Part 3's classes will teach you the *proper* way to share state safely.

**✅ MINI CHALLENGE SOLUTION** (`mymath.cpp` — also in `code/`)
```cpp
#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int reverseNum(int n) {
    int rev = 0;
    while (n > 0) { rev = rev * 10 + n % 10; n /= 10; }
    return rev;
}

bool isPalindrome(int n) { return n == reverseNum(n); }   // reuse!

long long power(int b, int e) {
    long long r = 1;
    for (int i = 0; i < e; i++) r *= b;
    return r;
}

int gcd(int a, int b) {
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}

int sumDigits(int n) {
    if (n == 0) return 0;
    return n % 10 + sumDigits(n / 10);
}

int main() {
    cout << "== MY MATH LIBRARY ==\n";
    cout << "isPrime(29)?       " << isPrime(29)       << endl;
    cout << "reverseNum(1234)   " << reverseNum(1234)  << endl;
    cout << "power(3, 4)        " << power(3, 4)       << endl;
    cout << "gcd(48, 36)        " << gcd(48, 36)       << endl;
    cout << "sumDigits(987)     " << sumDigits(987)    << endl;
    cout << "isPalindrome(1221) " << isPalindrome(1221) << endl;
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Functions = named recipes: define once, call anywhere; `main` should read like a summary
- ✓ Parameters are copies — return values to get results out (references come in Chapter 10)
- ✓ Prototype before `main`, definition wherever you like; every non-void path must return
- ✓ Overloading = same name different parameters; defaults = rightmost safety values
- ✓ Recursion = base case + progress toward it; locals beat globals, always

**📚 Keywords learned:** function, declaration, definition, prototype, parameter, argument, return type, `void`, overloading, default parameter, recursion, base case, call stack, scope, local, global, shadowing

**🔗 Next chapter preview:** **Part 2 — Working with Data.** Chapter 8, **Arrays**, teaches you to store not one value but a *thousand* — lists of scores, tables of data, whole rosters — and search, sort, and analyze them. Your data is about to multiply. 📊

*Part 1 COMPLETE. 🎓 You now know: programs, variables, operators, decisions, loops, and functions — every sentence of code in the world is built from these. Take a breath. You're ready for Part 2.*

---

**⬅️ [Chapter 6](chapter-06-loops.md) | [🏠 Home](README.md) | [Chapter 8 ➡️](chapter-08-arrays.md)**
