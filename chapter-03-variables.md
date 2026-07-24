# CHAPTER 3 — VARIABLES & DATA TYPES

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A variable is just a labeled box.
 Programming is the art of arranging boxes."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 2](chapter-02-first-program.md) | [🏠 Home](README.md) | [Chapter 4 ➡️](chapter-04-operators.md)**

---

## 📖 CHAPTER OPENING

Imagine your kitchen had no containers — flour, sugar, and rice all loose on the counter. Chaos! Now imagine labeled containers: "Flour", "Sugar", "Rice". You can store things, find them instantly, and change what's inside. **Variables are containers for data**, and data types are the labels that tell the computer what *kind* of stuff goes inside.

### What you will learn:
- What a variable really is (the box analogy that never fails)
- The core data types: `int`, `float`, `double`, `char`, `bool`, `string`
- Naming rules (what's legal, what's smart)
- Constants with `const` — boxes that lock shut
- `sizeof()` — measuring your boxes
- Type conversion — when C++ changes types for you (and how to do it yourself)
- `auto` — letting C++ guess the type

### Why this chapter matters:
Every program you'll ever write stores data: scores, names, prices, temperatures. No variables = no memory = no real programs. This chapter is where your code starts *thinking*.

---

## 🔍 CONCEPT EXPLANATION

### What is a variable?

A **variable** is a named space in memory (RAM) that stores a value you can use and change.

```
MEMORY (RAM):
┌─────────────┐
│   age = 20  │   ← a box labeled "age" holding the number 20
└─────────────┘
```

Three parts to every variable:
1. **Name** — the label on the box (`age`)
2. **Type** — what kind of thing fits inside (`int` = whole numbers)
3. **Value** — what's currently inside (`20`)

### Why do we use variables?

Without variables, a program can only print fixed text. With variables, it can **remember** your name, **add up** your shopping bill, **update** your game score. Variables turn static text into living programs.

### How does the computer understand it?

When you write `int age = 20;` the compiler tells the OS: *"reserve 4 bytes in RAM, call the slot `age`, and put the binary form of 20 there."* Different types reserve different amounts of space — that's why types exist at all. A `char` needs 1 byte; a `double` needs 8. You wouldn't store rice in a matchbox or a needle in a bathtub.

🎮 **FUN FACT:** `int` is usually 4 bytes = about ±2.1 **billion**. Big enough for city populations, too small for the number of stars. (For that, C++ has `long long`.)

---

## 📝 SYNTAX BOX

### Declaring (creating) a variable:

```cpp
int age = 20;
│    │    │
│    │    └─ VALUE (optional at declaration): starting contents
│    └─ NAME: your label — letters, digits, _, can't start with digit
└─ TYPE: what kind of data (int = whole numbers)
```

### The core types:

```cpp
int    score     = 95;         // whole numbers              (4 bytes)
double gpa       = 3.75;       // decimal numbers, precise   (8 bytes)
float  price     = 19.99f;     // decimal, less precise      (4 bytes)
char   grade     = 'A';        // ONE character, single quotes (1 byte)
bool   isPassed  = true;       // only true or false         (1 byte)
string name      = "Mahadi";   // text, double quotes — needs #include <string>
```

### Common variations:

```cpp
int x;              // declare now, assign later (dangerous: contains garbage!)
int x = 5, y = 10;  // declare several of the same type in one line
const double PI = 3.14159;   // locked box — can NEVER change
auto year = 2026;            // compiler deduces: int
auto pi  = 3.14;             // compiler deduces: double
int big = (int)9.99;         // explicit conversion (cast) → becomes 9
sizeof(int)                  // → 4 (bytes); works on types and variables
```

🔥 **REMEMBER:** `'A'` (single quotes) is a `char`. `"A"` (double quotes) is a `string`. They are DIFFERENT types, and mixing up quotes causes confusing errors.

---

## 💻 EXAMPLE CODES

### Example 3.1 — Meet the Types (Simplest Possible)

```cpp
// ============================================
// Example 3.1: Every Basic Type in One Program
// ============================================
// What this program does: Declares one variable of each type and prints them.
// Concepts used: int, double, char, bool, string, cout
// ============================================

#include <iostream>
#include <string>          // needed for the string type
using namespace std;

int main() {

    int     age      = 20;         // whole number
    double  height   = 5.9;        // decimal number
    char    initial  = 'M';        // single character — SINGLE quotes
    bool    isCoder  = true;       // true or false only
    string  city     = "Karachi";  // text — DOUBLE quotes

    cout << "Age: "     << age     << endl;   // print each variable
    cout << "Height: "  << height  << endl;
    cout << "Initial: " << initial << endl;
    cout << "Is coder: " << isCoder << endl;  // bool prints as 1 (true) or 0
    cout << "City: "    << city    << endl;

    return 0;
}
/*
OUTPUT:
Age: 20
Height: 5.9
Initial: M
Is coder: 1
City: Karachi

EXPLANATION:
Each type reserved its own space in memory. Note that bool
prints as 1 (true) or 0 (false) — C++ stores booleans as numbers.
*/
```

**What happened here?** Five labeled boxes were created in RAM, filled with starter values, and `cout` printed the contents of each. The odd one out: `isCoder` printed `1` — that's just how C++ displays `true`.

---

### Example 3.2 — Variables Can Change (That's the Point!)

```cpp
// ============================================
// Example 3.2: The Changing Score
// ============================================
// What this program does: Shows a variable being updated.
// Concepts used: assignment AFTER declaration
// ============================================

#include <iostream>
using namespace std;

int main() {

    int score = 0;                          // game starts at zero
    cout << "Start:  " << score << endl;

    score = 10;                             // scored a goal! (no "int" — box exists)
    cout << "Goal!   " << score << endl;

    score = score + 5;                      // bonus points: read old, write new
    cout << "Bonus!  " << score << endl;

    return 0;
}
/*
OUTPUT:
Start:  0
Goal!   10
Bonus!  15

EXPLANATION:
score = score + 5 means: take current value (10), add 5,
store the result (15) back into the same box.
The = in C++ means "PUT INTO", not "equals" like math class.
*/
```

**What happened here?** `=` is **assignment**, not mathematical equality. Read `score = score + 5` as *"score becomes score plus 5."* The box keeps its name; only the contents change.

⚠️ **WARNING:** Write `int score = 10;` TWICE and the compiler complains (`redeclaration`). Type the type only at birth; afterwards, use the name alone.

---

### Example 3.3 — Real-World Scenario: The Shopping Bill

```cpp
// ============================================
// Example 3.3: Shopping Bill Calculator
// ============================================
// What this program does: Computes a store bill with tax.
// Concepts used: double arithmetic, meaningful names
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // --- Item prices (in PKR) ---
    double milkPrice   = 220.0;
    double breadPrice  = 150.0;
    double eggPrice    = 340.0;

    // --- Bill math ---
    double subtotal = milkPrice + breadPrice + eggPrice;   // add prices
    double tax      = subtotal * 0.05;                     // 5% tax
    double total    = subtotal + tax;                      // final amount

    // --- Print the receipt ---
    cout << "-------- QuickMart Receipt --------" << endl;
    cout << "Subtotal: Rs. " << subtotal << endl;
    cout << "Tax (5%): Rs. " << tax      << endl;
    cout << "Total:    Rs. " << total    << endl;

    return 0;
}
/*
OUTPUT:
-------- QuickMart Receipt --------
Subtotal: Rs. 710
Tax (5%): Rs. 35.5
Total:    Rs. 745.5

EXPLANATION:
Values flow BETWEEN variables: subtotal feeds tax, tax feeds total.
Naming variables well (subtotal, not s1) is what makes this readable.
*/
```

**What happened here?** Your program did *financial math* — the same logic behind every shopping app and game economy. Variables holding variables' results is the heartbeat of all software.

---

### Example 3.4 — Integer Division & Type Conversion (The Great Trap)

```cpp
// ============================================
// Example 3.4: Why 5 / 2 Is Not 2.5 (Sometimes)
// ============================================
// What this program does: Exposes integer division and fixes it with casting.
// Concepts used: implicit vs explicit type conversion
// ============================================

#include <iostream>
using namespace std;

int main() {

    int a = 5, b = 2;

    cout << "int division:     " << a / b << endl;            // 2  (decimal chopped!)
    cout << "explicit cast:    " << (double)a / b << endl;    // 2.5 (fixed!)
    cout << "both double:      " << 5.0 / 2.0 << endl;        // 2.5 (naturally)

    // Implicit conversion: C++ squeezes the double into an int silently
    int piRough = 3.14159;
    cout << "implicit chop:    " << piRough << endl;          // 3

    // Sizes of our boxes
    cout << "size of int:      " << sizeof(int)    << " bytes" << endl;
    cout << "size of double:   " << sizeof(double) << " bytes" << endl;
    cout << "size of char:     " << sizeof(char)   << " byte"  << endl;

    return 0;
}
/*
OUTPUT:
int division:     2
explicit cast:    2.5
both double:      2.5
implicit chop:    3
size of int:      4 bytes
size of double:   8 bytes
size of char:     1 byte

EXPLANATION:
int / int → C++ gives an int, throwing away the fraction.
Convert one side to double (casting: (double)a) and division
behaves like real math. Storing 3.14159 in an int silently
chops it to 3 — implicit conversion can eat your data.
*/
```

**What happened here?** Types aren't labels — they're **rules** for how values behave. The `5 / 2 = 2` trap bites every C++ beginner once. Now it can't bite you.

> ❓ **THINK ABOUT IT:** If `int / int` chops the fraction... what should `(double)(a / b)` print — 2 or 2.5? (The cast happens AFTER the division already chopped it. Test it!)

---

### Example 3.5 — const and auto: The Locked Box and the Smart Box

```cpp
// ============================================
// Example 3.5: Constants and Type Deduction
// ============================================
// What this program does: Circle geometry with a locked PI; auto types.
// Concepts used: const, auto, uppercase const naming convention
// ============================================

#include <iostream>
using namespace std;

int main() {

    const double PI = 3.14159;    // LOCKED — PI can never change now
    // PI = 3.0;                  // ❌ uncomment → compile ERROR (good!)

    auto radius = 7.0;            // compiler sees 7.0 → radius is a double
    auto sides  = 4;              // compiler sees 4   → sides is an int

    double area = PI * radius * radius;   // π r²

    cout << "Radius: "      << radius << endl;
    cout << "Circle area: " << area   << endl;
    cout << "Sides (auto): " << sides  << endl;

    return 0;
}
/*
OUTPUT:
Radius: 7
Circle area: 153.938
Sides (auto): 4

EXPLANATION:
const protects values that must never change (PI, tax rates,
game max levels). auto asks the compiler to pick the type
from the starting value — convenience, used with care.
*/
```

**What happened here?** Two helpers: `const` makes bugs **impossible** (the compiler stops you), and `auto` saves typing. Convention: constants are named in `ALL_CAPS` so everyone knows they're sacred.

> ✅ **GOOD PRACTICE:** If a value has a real-world meaning and won't change — tax rate, max attempts, company name — make it `const`. Future-you will say thanks.

---

### Example 3.6 — Combined: Student Record Card

```cpp
// ============================================
// Example 3.6: Student Record (Chapters 2+3 combined)
// ============================================
// What this program does: Builds and prints a formatted student record.
// Concepts used: all basic types, const, chaining, \t columns
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    const string SCHOOL = "City High School";   // never changes
    const int PASS_MARKS = 50;                  // passing threshold

    string  name     = "Ali Raza";
    int     rollNo   = 42;
    double  marks    = 78.5;
    char    section  = 'B';
    bool    passed   = marks >= PASS_MARKS;     // bool from a comparison!

    cout << "===== " << SCHOOL << " =====" << endl;
    cout << "Name:\t\t"     << name    << endl;
    cout << "Roll No:\t"    << rollNo  << endl;
    cout << "Section:\t"    << section << endl;
    cout << "Marks:\t\t"    << marks   << endl;
    cout << "Passed:\t\t"   << passed  << endl;   // 1 = yes, 0 = no

    return 0;
}
/*
OUTPUT:
===== City High School =====
Name:           Ali Raza
Roll No:        42
Section:        B
Marks:          78.5
Passed:         1

EXPLANATION:
marks >= PASS_MARKS produces a bool (true/false) — comparisons
MAKE boolean values. That's a preview of Chapter 4 & 5, where
these booleans start making decisions.
*/
```

**What happened here?** Every concept in the chapter — types, const, assignment, comparison-produced booleans, formatted output — working together in one realistic record.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Using a variable before giving it a value**
```cpp
int age;
cout << age;        // prints garbage: -858993460, 0, anything!
```
✅ **Fix:** `int age = 0;` — always initialize. Uninitialized variables contain whatever junk was in that RAM before.

**❌ Mistake 2 — Wrong quotes for type**
```cpp
char grade = "A";        // ❌ double quotes make a string, not a char
string name = 'Mahadi';  // ❌ single quotes hold ONE char only
```
Compiler says: `invalid conversion` / `invalid conversion from 'const char*' to 'char'`
✅ **Fix:** `char grade = 'A';` and `string name = "Mahadi";`

**❌ Mistake 3 — Integer division surprise**
```cpp
double average = (7 + 8) / 2;   // gives 7, not 7.5!
```
✅ **Fix:** `double average = (7 + 8) / 2.0;` — make at least one side a `double`.

**❌ Mistake 4 — Reassigning a const**
```cpp
const int MAX = 100;
MAX = 200;                      // ❌ that's the whole point of const!
```
Compiler says: `error: assignment of read-only variable 'MAX'`
✅ **Fix:** If it must change, don't make it `const`. If it's const, leave it alone.

**❌ Mistake 5 — Illegal names**
```cpp
int 2ndPlace = 2;     // ❌ can't start with a digit
int my score = 5;     // ❌ no spaces
int int = 3;          // ❌ 'int' is a reserved keyword
```
✅ **Fix:** `int secondPlace = 2;` — letters/digits/underscore, start with a letter, never a keyword.

**❌ Mistake 6 — Declaring the same variable twice**
```cpp
int score = 10;
int score = 20;       // ❌ error: redeclaration of 'score'
```
✅ **Fix:** After birth, drop the type: `score = 20;`

---

## 🧠 CONCEPT SUMMARY TABLE

| Type | Holds | Size (typical) | Example | Watch out |
|---|---|---|---|---|
| `int` | whole numbers | 4 bytes | `int age = 20;` | `int/int` chops fractions; range ±2.1B |
| `double` | decimals (precise) | 8 bytes | `double g = 3.75;` | The default choice for decimals |
| `float` | decimals (compact) | 4 bytes | `float p = 1.5f;` | Needs the `f` suffix |
| `char` | one character | 1 byte | `char c = 'A';` | Single quotes! |
| `bool` | true/false | 1 byte | `bool ok = true;` | Prints as 1/0 |
| `string` | text | varies | `string s = "hi";` | Needs `#include <string>` |
| `const` | locked value | — | `const double PI = 3.14;` | ALL_CAPS name convention |
| `auto` | compiler deduces | — | `auto x = 5;` | Must initialize immediately |
| `sizeof(x)` | bytes of x | — | `sizeof(int)` → 4 | Works on types & variables |
| cast | force conversion | — | `(double)a` | `(int)9.9` → 9 (chops, never rounds) |

**Naming rules:** letters, digits, `_`; must not start with a digit; no spaces; no keywords (`int`, `return`, ...). **Style:** `camelCase` for variables (`totalMarks`), `ALL_CAPS` for constants.

---

## ✏️ PRACTICE PROBLEMS

*(cin arrives in Chapter 4 — so set values inside your code; "sample input" shows what to set them to.)*

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Create variables for your name (string),
   age (int), and height in meters (double). Print them
   in a labeled list.
📥 SAMPLE VALUES: name="Sara", age=19, height=1.62
📤 EXPECTED OUTPUT:
Name: Sara
Age: 19
Height: 1.62
💡 HINT: Three declarations, three cout lines.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Store the length and width of a rectangle,
   compute its area, print it.
📥 SAMPLE VALUES: length=8, width=5
📤 EXPECTED OUTPUT: Area = 40
💡 HINT: area = length * width   (use int, or double for safety)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Store a character grade and a boolean for
   passed/failed, then print both. Observe how bool prints.
📥 SAMPLE VALUES: grade='B', passed=true
📤 EXPECTED OUTPUT:
Grade: B
Passed: 1
💡 HINT: char single quotes, bool is true/false.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: A student scored in three subjects: 78, 85, 90.
   Compute total and AVERAGE. The average must show decimals.
📤 EXPECTED OUTPUT:
Total = 253
Average = 84.3333
💡 HINT: total / 3 chops. Divide by 3.0 instead.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Compute simple interest: SI = (P × R × T) / 100
   with const for the values.
📥 SAMPLE VALUES: P=10000, R=5, T=2
📤 EXPECTED OUTPUT: Simple Interest = 1000
💡 HINT: Watch integer division — one 100.0 saves you.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Print the ASCII number of the characters
   'A', 'a', and '0' using explicit casting.
📤 EXPECTED OUTPUT:
A -> 65
a -> 97
0 -> 48
💡 HINT: (int)'A' converts the char to its numeric code.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: For a circle with radius 5.5, print area AND
   circumference. PI must be a const.
📤 EXPECTED OUTPUT (approx):
Area = 95.0332
Circumference = 34.5575
💡 HINT: area = PI*r*r, circumference = 2*PI*r
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Currency converter: convert an amount in PKR to
   USD and EUR using const exchange rates, print all three.
📥 SAMPLE VALUES: pkr=28000, USD_RATE=280, EUR_RATE=305
📤 EXPECTED OUTPUT (approx):
PKR: 28000
USD: 100
EUR: 91.8033
💡 HINT: foreign = pkr / rate — and make sure it's double math.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Temperature converter BOTH ways: convert 37°C to
   Fahrenheit, then convert 98.6°F back to Celsius (two
   separate computations in one program).
📤 EXPECTED OUTPUT (approx):
37 C = 98.6 F
98.6 F = 37 C
💡 HINT: F = C × 9/5 + 32 and C = (F − 32) × 5/9 — mind the
   integer division in 9/5!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 3.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Swap the values of two int variables WITHOUT a
   third variable. Print before and after.
📥 SAMPLE VALUES: a=10, b=20
📤 EXPECTED OUTPUT:
Before: a=10 b=20
After:  a=20 b=10
💡 HINT: a = a + b;  b = a - b;  a = a - b;  — trace it on paper!
```

---

## 🎯 MINI CHALLENGE — DIGITAL ID CARD 2.0 🪪

Remember Chapter 2's printed business card? Rebuild it — but this time **all data lives in variables**, including at least:

- One `string` (name), one `int` (ID number), one `char` (blood group), one `bool` (isMember), one `const double` (membership fee)
- Formatted bordered output with `\t` alignment
- A computed line: e.g., "Member since 2024 — that's **X** years" computed as `CURRENT_YEAR - joinedYear` (use a `const int CURRENT_YEAR = 2026;`)

**Rule:** the name "Mahadi" or any value must appear in exactly ONE place in the code (its variable). That's the whole point of variables.

You're building data-driven output — this is exactly how real apps render profiles. 🚀

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 3.1**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string name   = "Sara";
    int    age    = 19;
    double height = 1.62;

    cout << "Name: "   << name   << endl;
    cout << "Age: "    << age    << endl;
    cout << "Height: " << height << endl;
    return 0;
}
```
💡 **PRO TIP:** Aligning your declarations in columns (like above) is a small style habit that makes code noticeably cleaner.

**✅ SOLUTION 3.2**
```cpp
#include <iostream>
using namespace std;

int main() {
    int length = 8, width = 5;
    int area = length * width;
    cout << "Area = " << area << endl;
    return 0;
}
```
💡 **PRO TIP:** Declaring `length, width` on one line is legal — same type only!

**✅ SOLUTION 3.3**
```cpp
#include <iostream>
using namespace std;

int main() {
    char grade  = 'B';
    bool passed = true;

    cout << "Grade: "  << grade  << endl;
    cout << "Passed: " << passed << endl;   // prints 1
    return 0;
}
```
💡 **PRO TIP:** `cout << boolalpha;` once makes bools print `true`/`false` instead of 1/0. Neat trick for later chapters.

**✅ SOLUTION 3.4**
```cpp
#include <iostream>
using namespace std;

int main() {
    int m1 = 78, m2 = 85, m3 = 90;

    int    total   = m1 + m2 + m3;
    double average = total / 3.0;     // 3.0 keeps the decimals!

    cout << "Total = "   << total   << endl;
    cout << "Average = " << average << endl;
    return 0;
}
```
Output: `Total = 253` / `Average = 84.3333`
💡 **PRO TIP:** Only ONE operand needs to be double for the whole division to be decimal — that's the rule that matters.

**✅ SOLUTION 3.5**
```cpp
#include <iostream>
using namespace std;

int main() {
    const double P = 10000;   // principal
    const double R = 5;       // rate %
    const double T = 2;       // time (years)

    double si = (P * R * T) / 100;
    cout << "Simple Interest = " << si << endl;
    return 0;
}
```
💡 **PRO TIP:** Because P is `double`, the entire expression is decimal math — one double infects the whole formula (in a good way).

**✅ SOLUTION 3.6**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "A -> " << (int)'A' << endl;
    cout << "a -> " << (int)'a' << endl;
    cout << "0 -> " << (int)'0' << endl;
    return 0;
}
```
💡 **PRO TIP:** Every char IS a number inside (its ASCII code). That's why `char` arithmetic like `'A' + 1` → `'B'` will work in Chapter 6.

**✅ SOLUTION 3.7**
```cpp
#include <iostream>
using namespace std;

int main() {
    const double PI = 3.14159;
    double radius = 5.5;

    cout << "Area = "          << PI * radius * radius << endl;
    cout << "Circumference = " << 2 * PI * radius      << endl;
    return 0;
}
```

**✅ SOLUTION 3.8**
```cpp
#include <iostream>
using namespace std;

int main() {
    const double USD_RATE = 280.0;
    const double EUR_RATE = 305.0;
    double pkr = 28000;

    cout << "PKR: " << pkr            << endl;
    cout << "USD: " << pkr / USD_RATE << endl;
    cout << "EUR: " << pkr / EUR_RATE << endl;
    return 0;
}
```
💡 **PRO TIP:** Real finance apps use special decimal types because of float rounding — but `double` is perfect for learning.

**✅ SOLUTION 3.9**
```cpp
#include <iostream>
using namespace std;

int main() {
    double celsius    = 37.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32;

    double f2 = 98.6;
    double c2 = (f2 - 32) * 5.0 / 9.0;

    cout << celsius << " C = " << fahrenheit << " F" << endl;
    cout << f2 << " F = " << c2 << " C" << endl;
    return 0;
}
```
💡 **PRO TIP:** `9/5` alone is `1` (integer division!) — write `9.0/5.0`. This bug is silent: it compiles AND runs, just wrongly. Test with known values like 100°C = 212°F.

**✅ SOLUTION 3.10**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20;
    cout << "Before: a=" << a << " b=" << b << endl;

    a = a + b;   // a = 30  (b still 20)
    b = a - b;   // b = 10  (original a!)
    a = a - b;   // a = 20  (minus new b)

    cout << "After:  a=" << a << " b=" << b << endl;
    return 0;
}
```
Alternative (simpler, uses a third variable — usually preferred in real code):
```cpp
int temp = a; a = b; b = temp;
```
💡 **PRO TIP:** The no-temp trick is a classic interview question — but in real code, clarity beats cleverness. Use `temp`.

**✅ MINI CHALLENGE (sample answer)**
```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    const int CURRENT_YEAR = 2026;
    string   name        = "Mahadi ur Rehman";
    int      idNumber    = 1001;
    int      joinedYear  = 2024;
    char     bloodGroup  = 'O';
    bool     isMember    = true;
    const double FEE     = 999.99;

    cout << "+----------------------------------+" << endl;
    cout << "|         MEMBER ID CARD           |" << endl;
    cout << "+----------------------------------+" << endl;
    cout << "  Name:\t\t"     << name                     << endl;
    cout << "  ID No:\t"      << idNumber                 << endl;
    cout << "  Blood:\t"     << bloodGroup               << endl;
    cout << "  Member:\t"     << isMember                 << endl;
    cout << "  Tenure:\t"     << CURRENT_YEAR - joinedYear
         << " years"                                             << endl;
    cout << "  Annual Fee:\tRs. " << FEE                        << endl;
    cout << "+----------------------------------+" << endl;
    return 0;
}
```
💡 **PRO TIP:** Change `name` in ONE place and rerun — the whole card updates. That single-point-of-change is the superpower variables give you.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ A variable = type + name + value — a labeled box in RAM
- ✓ `int` whole numbers, `double` decimals, `char` one letter (single quotes), `bool` true/false, `string` text (double quotes)
- ✓ `const` locks a value forever; `auto` lets the compiler choose the type
- ✓ `int / int` chops decimals — divide with `double` for real math; casting `(double)x` does it explicitly
- ✓ Initialize every variable at birth; garbage in RAM is real garbage

**📚 Keywords learned:** `int`, `double`, `float`, `char`, `bool`, `string`, `const`, `auto`, `sizeof`, casting, assignment, ASCII, implicit/explicit conversion

**🔗 Next chapter preview:** Chapter 4 — **Operators**. You can store data now; next you'll *compute* with it — and meet `cin`, so users can finally TYPE into your programs. Interactivity begins. 🎮

*From fixed text to living data in three chapters. The machine is starting to work FOR you.* 💪

---

**⬅️ [Chapter 2](chapter-02-first-program.md) | [🏠 Home](README.md) | [Chapter 4 ➡️](chapter-04-operators.md)**
