# CHAPTER 5 — CONDITIONAL STATEMENTS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Every choice you've ever made —
 if this, then that — is an if-statement
 your brain has been running for years."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 4](chapter-04-operators.md) | [🏠 Home](README.md) | [Chapter 6 ➡️](chapter-06-loops.md)**

---

## 📖 CHAPTER OPENING

This morning your brain ran dozens of if-statements: *IF it's raining, take an umbrella. IF it's Monday, wear a uniform. ELSE IF it's the weekend, sleep in.* You think in conditions every minute of your life. Today, your programs learn to do the same.

### What you will learn:
- `if` — run code only when a condition is true
- `if-else` — two paths, always take one
- `if / else if / else` — the multi-path ladder
- Nested `if` — decisions inside decisions
- `switch-case` — clean menus for many exact choices
- The ternary `?:` — one-line decisions
- Building real decision-making programs (grade systems, menus, eligibility)

### Why this chapter matters:
Until now, every program ran straight down, same path, every time. Conditions break that — now your program **reacts** to data differently each run. This is the birth of "smart" software: games that respond, apps that validate, ATMs that refuse.

---

## 🔍 CONCEPT EXPLANATION

### What is a conditional statement?

A **conditional** lets a program **choose** whether to run a block of code based on a **condition** — an expression that evaluates to `true` or `false` (Chapter 4's comparison/logical operators, remember?).

### Why do we use it?

Because real problems have branches: marks above 50 → pass; below → fail. Password matches → let them in; else → deny. A program without conditions is a calculator with one fixed answer.

### How does the computer understand it?

At the `if`, the CPU **evaluates the condition first** (it becomes a bool). If `true` → jump into the block; if `false` → skip it (or take the `else` block). Think of a railway switch: the train (execution) arrives, the condition chooses which track to send it down — but never both.

```
            ┌─ condition true ─→  { if-block }      ─┐
execution ──┤                                        ├──→ continue below
            └─ condition false ─→ { else-block }    ─┘
```

🔥 **REMEMBER:** The condition must produce a **bool**. `if (marks >= 50)` ✔. Also remember: `if (marks = 50)` compiles but assigns — the classic trap from Chapter 4, now in its natural habitat.

---

## 📝 SYNTAX BOX

### Pattern 1 — `if` alone (do something only when true):

```cpp
if (condition) {          // no semicolon here!
    // runs ONLY if condition is true
}
// (program continues either way)
```

### Pattern 2 — `if / else` (exactly one path runs):

```cpp
if (condition) {
    // true path
} else {
    // false path
}
```

### Pattern 3 — the `else if` ladder (first true condition wins):

```cpp
if (marks >= 90) {
    cout << "A";
} else if (marks >= 80) {   // checked ONLY if the first was false
    cout << "B";
} else if (marks >= 70) {
    cout << "C";
} else {
    cout << "F";            // catch-all when nothing matched
}
```

### Pattern 4 — nested `if`:

```cpp
if (age >= 18) {
    if (hasLicense) {       // only reached when age >= 18
        cout << "You can drive";
    }
}
```

### Pattern 5 — `switch` (many EXACT matches of ONE value):

```cpp
switch (choice) {                 // int/char value
    case 1:                       // choice == 1 ?
        cout << "Balance";
        break;                    // ← REQUIRED or it falls through!
    case 2:
        cout << "Withdraw";
        break;
    default:                      // runs if no case matched
        cout << "Invalid option";
}
```

### Pattern 6 — ternary (one-line if/else):

```cpp
string result = (marks >= 50) ? "Pass" : "Fail";
//           condition ? value-if-true : value-if-false
```

| Keyword | Meaning |
|---|---|
| `if` | Test a condition |
| `else` | Runs when the condition was false |
| `else if` | Test another condition only if previous ones failed |
| `switch / case / default` | Match one value against exact options |
| `break` | Exit the switch (forget it → fall-through chaos) |
| `? :` | Inline if/else that PRODUCES a value |

---

## 💻 EXAMPLE CODES

### Example 5.1 — The Simplest `if`

```cpp
// ============================================
// Example 5.1: Positive Number Detector
// ============================================
// What this program does: Congratulates only when the number is positive.
// Concepts used: single if (no else needed)
// ============================================

#include <iostream>
using namespace std;

int main() {

    int number;
    cout << "Enter a number: ";
    cin  >> number;

    if (number > 0) {                              // gate opens only if true
        cout << "That's positive! Good vibes." << endl;
    }

    cout << "Program finished." << endl;           // runs no matter what

    return 0;
}
/*
INPUT:  7
OUTPUT:
That's positive! Good vibes.
Program finished.

(With input -4, only "Program finished." prints.)

EXPLANATION:
The if-block is a gate: number > 0 holds it open.
The final cout sits OUTSIDE the gate — unconditional.
*/
```

**What happened here?** Code finally has an *option* — run this part, maybe. The last line proves ordinary flow continues after the gate either way.

---

### Example 5.2 — `if / else`: Even or Odd

```cpp
// ============================================
// Example 5.2: Even or Odd
// ============================================
// What this program does: Prints exactly one verdict per input.
// Concepts used: if-else, % trick from Chapter 4
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Enter an integer: ";
    cin  >> n;

    if (n % 2 == 0) {                        // remainder zero → even
        cout << n << " is EVEN." << endl;
    } else {                                  // otherwise → odd
        cout << n << " is ODD."  << endl;
    }

    return 0;
}
/*
INPUT:  42       INPUT:  7
OUTPUT:          OUTPUT:
42 is EVEN.      7 is ODD.

EXPLANATION:
A number is even exactly when n % 2 == 0.
if/else guarantees ONE branch runs — never both, never neither.
*/
```

**What happened here?** The railway switch in its purest form: two tracks, condition picks one, every run.

---

### Example 5.3 — Real-World Scenario: The Grading Machine

```cpp
// ============================================
// Example 5.3: Student Grade Calculator
// ============================================
// What this program does: Converts marks to letter grades via else-if ladder.
// Concepts used: else-if ladder, input validation, order matters
// ============================================

#include <iostream>
using namespace std;

int main() {

    double marks;
    cout << "Enter marks (0-100): ";
    cin  >> marks;

    if (marks < 0 || marks > 100) {              // validation FIRST
        cout << "Invalid marks! Range is 0-100." << endl;
    } else if (marks >= 90) {
        cout << "Grade: A+  — Outstanding!"      << endl;
    } else if (marks >= 80) {
        cout << "Grade: A   — Excellent!"        << endl;
    } else if (marks >= 70) {
        cout << "Grade: B   — Good job!"         << endl;
    } else if (marks >= 60) {
        cout << "Grade: C   — Fair."             << endl;
    } else if (marks >= 50) {
        cout << "Grade: D   — Just passed."      << endl;
    } else {
        cout << "Grade: F   — Try again. You can!" << endl;
    }

    return 0;
}
/*
INPUT:  85
OUTPUT:
Grade: A   — Excellent!

INPUT:  150
OUTPUT:
Invalid marks! Range is 0-100.

EXPLANATION:
The ladder checks top to bottom; the FIRST true condition wins
and the rest are skipped. That's why descending order works:
marks=85 fails >=90, passes >=80, and never even sees the rest.
*/
```

**What happened here?** An else-if ladder is a *priority filter* — check the strictest/highest condition first. Reverse the order and every passing student becomes a "D" (the `>=50` branch would swallow everyone). **Order. Matters.**

> ❓ **THINK ABOUT IT:** Why can't you write `else if (80 <= marks <= 90)`? (Chapter 4, Mistake #5 — every comparison must be spelled out and joined with `&&`.)

---

### Example 5.4 — Nested `if` + `switch`: The ATM Menu

```cpp
// ============================================
// Example 5.4: Mini ATM (menus + guarding checks)
// ============================================
// What this program does: PIN check, then a switch menu with balance logic.
// Concepts used: nested if, switch with break, if inside case
// ============================================

#include <iostream>
using namespace std;

int main() {

    const int    CORRECT_PIN = 1234;                    // locked, as it should be
    double       balance     = 5000.0;                  // starting balance (Rs.)
    int          pin, choice;
    double       amount;

    cout << "Enter PIN: ";
    cin  >> pin;

    if (pin != CORRECT_PIN) {                           // outer gate
        cout << "Wrong PIN. Card blocked. (Kidding. Try again!)" << endl;
    } else {
        cout << "\n1. Balance   2. Withdraw   3. Exit\nChoice: ";
        cin  >> choice;

        switch (choice) {                               // route by exact value
            case 1:
                cout << "Balance: Rs. " << balance << endl;
                break;                                  // never forget!
            case 2:
                cout << "Amount: ";
                cin  >> amount;
                if (amount <= balance && amount > 0) {  // nested guard
                    balance -= amount;
                    cout << "Take Rs. " << amount
                         << ". New balance: Rs. " << balance << endl;
                } else {
                    cout << "Insufficient funds / bad amount." << endl;
                }
                break;
            case 3:
                cout << "Thank you. Goodbye!" << endl;
                break;
            default:
                cout << "No such option." << endl;
        }
    }

    return 0;
}
/*
INPUT:  1234  →  2  →  1500
OUTPUT:
Take Rs. 1500. New balance: Rs. 3500

INPUT:  9999
OUTPUT:
Wrong PIN. Card blocked. (Kidding. Try again!)

EXPLANATION:
if = the bouncer (wrong PIN? nothing else runs).
switch = the receptionist (routes to the right desk).
break = leaving the desk (forget it and you wander
into the next desk's case too — the famous fall-through).
*/
```

**What happened here?** You wrote the skeleton of real banking software: authenticate → show menu → validate → transact. This pattern reappears in your Chapter 22 bank project — at full scale.

---

### Example 5.5 — Ternary Operator: One-Line Decisions

```cpp
// ============================================
// Example 5.5: Ternary — The Decision Shortcut
// ============================================
// What this program does: Uses ?: for compact true/false assignments.
// Concepts used: ternary operator, nested ternary (with care)
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    int age;
    cout << "Enter age: ";
    cin  >> age;

    // One line instead of a four-line if/else:
    string category = (age >= 18) ? "Adult" : "Minor";
    cout << "Category: " << category << endl;

    int a = 15, b = 27;
    int bigger = (a > b) ? a : b;      // returns a VALUE, not a statement
    cout << "Bigger number: " << bigger << endl;

    // Nested ternary — legal, but readable only when tiny:
    string sign = (age > 0) ? "positive" : (age < 0) ? "negative" : "zero";
    cout << "Age is " << sign << endl;

    return 0;
}
/*
INPUT:  16
OUTPUT:
Category: Minor
Bigger number: 27
Age is positive

EXPLANATION:
(condition) ? A : B  is an EXPRESSION — it produces a value,
so it can sit inside assignments and cout.
Use it for short either/or choices; use if/else for anything big.
*/
```

**What happened here?** Ternary shines when you'd write a 4-line if/else just to choose between **two values**. If your ternary needs squinting, it should have been an if.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — `=` instead of `==` inside the condition**
```cpp
if (pin = 1234) { ... }      // sets pin to 1234; condition becomes "1234" → true ALWAYS
```
✅ **Fix:** `if (pin == 1234)`. Compilers with `-Wall` warn: `suggest parentheses around assignment used as truth value`. Heed it.

**❌ Mistake 2 — Semicolon right after `if (...)`**
```cpp
if (marks >= 50);            // ← empty statement! The block below is NOT conditional
{
    cout << "Pass";          // runs ALWAYS
}
```
✅ **Fix:** Never put `;` between the `if (...)` and its `{ ... }`.

**❌ Mistake 3 — Missing `break` in a switch**
```cpp
switch (choice) {
    case 1:
        cout << "One";       // choice=1 prints "One"...
    case 2:
        cout << "Two";       // ...AND "Two" too — falls through!
        break;
}
```
✅ **Fix:** End every case with `break;` unless fall-through is intentional (rare, and comment it).

**❌ Mistake 4 — Ladder order ignoring priority**
```cpp
if (marks >= 50)       cout << "D";
else if (marks >= 90)  cout << "A+";   // never reached! >=50 catches everything first
```
✅ **Fix:** Order from most specific (highest) to least, like Example 5.3.

**❌ Mistake 5 — The dangling else**
```cpp
if (a > 0)
    if (b > 0)
        cout << "both positive";
else                                 // attaches to the INNER if, not outer!
    cout << "a not positive";        // ← the message lies about when it runs
```
✅ **Fix:** Use braces so `else` loyalty is explicit:
```cpp
if (a > 0) {
    if (b > 0) { cout << "both positive"; }
} else {
    cout << "a not positive";
}
```

**❌ Mistake 6 — Comparing switch against ranges or strings**
```cpp
switch (marks) { case 90 ... 100: } // ❌ not valid C++
switch (name)  { case "Ali": }      // ❌ strings not allowed
```
✅ **Fix:** `switch` works with `int`, `char`, `enum` — exact values only. Ranges → else-if ladder; strings → if/else with `==`.

---

## 🧠 CONCEPT SUMMARY TABLE

| Construct | Best for | Watch out |
|---|---|---|
| `if` | Optional single action | No `;` after the condition |
| `if / else` | Exactly-one-of-two paths | `else` never has its own condition |
| `else if` ladder | Ranges, priorities, grades | Order highest → lowest |
| Nested `if` | Guards within guards (PIN → action) | Braces keep else's loyalty clear |
| `switch` | Menus, exact `int`/`char` matches | Always `break;` |
| `? :` ternary | Choosing between two VALUES | Keep it short or use if/else |
| `default:` | Catch-all in switch | Optional but recommended |

**When to use what:** Two outcomes → if/else. Score ranges → ladder. Menu options → switch. Quick value pick → ternary. Login-like guard → nested if.

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read an age. Print "Can vote" if age >= 18,
   else "Too young to vote".
📥 SAMPLE INPUT: 20        (also test: 15)
📤 EXPECTED OUTPUT: Can vote
💡 HINT: Basic if/else with >=.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read a number, print "Positive", "Negative",
   or "Zero".
📥 SAMPLE INPUT: -7
📤 EXPECTED OUTPUT: Negative
💡 HINT: Three branches — if / else if / else.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read a lowercase character; print "Vowel" if
   it's a/e/i/o/u, otherwise "Consonant".
📥 SAMPLE INPUT: e
📤 EXPECTED OUTPUT: Vowel
💡 HINT: c=='a' || c=='e' || ... — five equalities joined by ||
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Read three numbers, print the LARGEST.
📥 SAMPLE INPUT: 12 45 23
📤 EXPECTED OUTPUT: Largest = 45
💡 HINT: if (a>=b && a>=c) ... or nested ifs.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Leap year check: a year is leap if divisible
   by 400, OR (divisible by 4 AND NOT by 100).
📥 SAMPLE INPUT: 2024 → Leap year | 1900 → Not a leap year
📤 EXPECTED OUTPUT: Leap year
💡 HINT: (y%400==0) || (y%4==0 && y%100!=0)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Read marks (0-100), print the grade letter
   AND a motivational line. Reject marks outside 0-100.
   90+ A / 80+ B / 70+ C / 60+ D / below F.
📥 SAMPLE INPUT: 76
📤 EXPECTED OUTPUT:
Grade: C
Keep climbing — B is close!
💡 HINT: Ladder + validation branch first.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Simple calculator: read two numbers and an
   operator char (+ - * /). Use switch. Guard division-by-zero.
📥 SAMPLE INPUT: 12 4 /
📤 EXPECTED OUTPUT: 12 / 4 = 3
💡 HINT: case '/': if (b != 0) ... else "Cannot divide by zero"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Triangle analyzer: read 3 sides. First check
   validity (each side < sum of other two), then classify:
   Equilateral / Isosceles / Scalene.
📥 SAMPLE INPUT: 5 5 5
📤 EXPECTED OUTPUT: Valid triangle: Equilateral
💡 HINT: Nested: outer if for validity, inner ladder for type.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Electricity bill: units ≤100 → Rs.5/unit;
   101–300 → Rs.7/unit (for ALL units); >300 → Rs.10/unit,
   plus a fixed Rs.150 surcharge when total exceeds Rs.2000.
   Print the final bill.
📥 SAMPLE INPUT: 250
📤 EXPECTED OUTPUT: Bill = Rs. 1750
💡 HINT: Compute rate by ladder, then apply surcharge with an if.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 5.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Day-of-week converter: read 1-7 and print the
   day via switch, plus "Weekend!" for 6 & 7 (use intentional
   fall-through), "Invalid" otherwise.
📥 SAMPLE INPUT: 6
📤 EXPECTED OUTPUT:
Saturday
Weekend!
💡 HINT: case 6: case 7: share the Weekend cout via fall-through.
```

---

## 🎯 MINI CHALLENGE — ROCK 🪨 PAPER 📄 SCISSORS ✂️ (2 Players)

Player 1 and Player 2 each enter a letter: `r` (rock), `p` (paper), or `s` (scissors). Your program prints who wins and why:

```
INPUT:  r s
OUTPUT:
Player 1 wins! Rock crushes Scissors.
```

Requirements:
- Handle invalid letters politely (`"Unknown move!"`)
- Handle draws (`"Draw! Great minds think alike."`)
- Print the REASON (rock crushes scissors / paper covers rock / scissors cut paper)

There's a satisfying long-if version and a smart nested version. Write either one — then try the other. When you beat this, you've beaten decision logic itself. 🏆

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 5.1**
```cpp
#include <iostream>
using namespace std;

int main() {
    int age;
    cin >> age;
    if (age >= 18) {
        cout << "Can vote" << endl;
    } else {
        cout << "Too young to vote" << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Could also be a ternary: `cout << (age >= 18 ? "Can vote" : "Too young to vote");` — same logic, fewer lines.

**✅ SOLUTION 5.2**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n > 0)      cout << "Positive" << endl;
    else if (n < 0) cout << "Negative" << endl;
    else            cout << "Zero"     << endl;
    return 0;
}
```
💡 **PRO TIP:** Order doesn't matter here because all three conditions are mutually exclusive — unlike grade ladders.

**✅ SOLUTION 5.3**
```cpp
#include <iostream>
using namespace std;

int main() {
    char c;
    cin >> c;
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') {
        cout << "Vowel" << endl;
    } else {
        cout << "Consonant" << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Uppercase support: add `|| c=='A' || ...` — or in Chapter 9 you'll meet `tolower()` and check once.

**✅ SOLUTION 5.4**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    if (a >= b && a >= c)      cout << "Largest = " << a << endl;
    else if (b >= a && b >= c) cout << "Largest = " << b << endl;
    else                       cout << "Largest = " << c << endl;
    return 0;
}
```
💡 **PRO TIP:** `>=` (not `>`) in all conditions keeps ties from slipping through to a wrong answer.

**✅ SOLUTION 5.5**
```cpp
#include <iostream>
using namespace std;

int main() {
    int year;
    cin >> year;

    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) {
        cout << year << " is a leap year." << endl;
    } else {
        cout << year << " is not a leap year." << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** 2000 = leap (÷400), 1900 = not (÷100 but not ÷400). Test edge years — interviewers love this one.

**✅ SOLUTION 5.6**
```cpp
#include <iostream>
using namespace std;

int main() {
    int marks;
    cin >> marks;

    if (marks < 0 || marks > 100)      cout << "Invalid marks!"   << endl;
    else if (marks >= 90) cout << "Grade: A\nPhenomenal!"                << endl;
    else if (marks >= 80) cout << "Grade: B\nExcellent work!"            << endl;
    else if (marks >= 70) cout << "Grade: C\nKeep climbing — B is close!" << endl;
    else if (marks >= 60) cout << "Grade: D\nYou passed. Now push more."  << endl;
    else                  cout << "Grade: F\nFailure is fuel. Retry!"     << endl;
    return 0;
}
```

**✅ SOLUTION 5.7**
```cpp
#include <iostream>
using namespace std;

int main() {
    double a, b;
    char   op;
    cin >> a >> b >> op;

    switch (op) {
        case '+': cout << a << " + " << b << " = " << a + b << endl; break;
        case '-': cout << a << " - " << b << " = " << a - b << endl; break;
        case '*': cout << a << " * " << b << " = " << a * b << endl; break;
        case '/':
            if (b != 0) cout << a << " / " << b << " = " << a / b << endl;
            else        cout << "Cannot divide by zero" << endl;
            break;
        default:  cout << "Unknown operator" << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** In Chapter 7, each case becomes a **function call** — that's how professional calculators are organized.

**✅ SOLUTION 5.8**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    if (a + b > c && b + c > a && a + c > b) {      // validity first
        if (a == b && b == c)      cout << "Valid triangle: Equilateral" << endl;
        else if (a==b || b==c || a==c) cout << "Valid triangle: Isosceles" << endl;
        else                       cout << "Valid triangle: Scalene"     << endl;
    } else {
        cout << "Not a valid triangle" << endl;
    }
    return 0;
}
```

**✅ SOLUTION 5.9**
```cpp
#include <iostream>
using namespace std;

int main() {
    int units;
    cin >> units;

    double rate;
    if (units <= 100)      rate = 5;
    else if (units <= 300) rate = 7;
    else                   rate = 10;

    double bill = units * rate;
    if (bill > 2000) bill += 150;      // surcharge

    cout << "Bill = Rs. " << bill << endl;
    return 0;
}
```
💡 **PRO TIP:** Declaring `rate`/`bill` BEFORE the ladder and assigning inside avoids repeating the whole computation per branch.

**✅ SOLUTION 5.10**
```cpp
#include <iostream>
using namespace std;

int main() {
    int day;
    cin >> day;

    switch (day) {
        case 1: cout << "Monday"    << endl; break;
        case 2: cout << "Tuesday"   << endl; break;
        case 3: cout << "Wednesday" << endl; break;
        case 4: cout << "Thursday"  << endl; break;
        case 5: cout << "Friday"    << endl; break;
        case 6: cout << "Saturday"  << endl;   // INTENTIONAL fall-through:
        case 7: cout << "Sunday"    << endl;
                cout << "Weekend!"  << endl; break;
        default: cout << "Invalid"  << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Deliberate fall-through is legal and useful — always comment `// fall-through` so teammates (and future you) know it's not a forgotten `break`.

**✅ MINI CHALLENGE (one clean version)**
```cpp
#include <iostream>
using namespace std;

int main() {
    char p1, p2;
    cin >> p1 >> p2;

    bool valid1 = (p1=='r' || p1=='p' || p1=='s');
    bool valid2 = (p2=='r' || p2=='p' || p2=='s');

    if (!valid1 || !valid2) {
        cout << "Unknown move!" << endl;
    } else if (p1 == p2) {
        cout << "Draw! Great minds think alike." << endl;
    } else if ((p1=='r' && p2=='s') || (p1=='p' && p2=='r') ||
               (p1=='s' && p2=='p')) {
        cout << "Player 1 wins!";
        if (p1=='r') cout << " Rock crushes Scissors."     << endl;
        if (p1=='p') cout << " Paper covers Rock."         << endl;
        if (p1=='s') cout << " Scissors cut Paper."        << endl;
    } else {
        cout << "Player 2 wins!" << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Notice the win conditions are just 3 pairs — turn logic into a small truth table whenever a game feels tangled.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Conditions are bools from Chapter 4 — comparisons and logic, finally acting
- ✓ if = gate, if/else = fork, else-if ladder = priority filter (order matters!), switch = exact-match menu, `?:` = value picker
- ✓ Never `;` after `if(...)`, never `=` inside conditions, never forget `break`
- ✓ Validate input FIRST (the bouncer pattern), then process
- ✓ switch handles int/char exact matches; ranges and strings need if/else

**📚 Keywords learned:** `if`, `else`, `else if`, nested if, `switch`, `case`, `break`, `default`, ternary `?:`, fall-through, input validation

**🔗 Next chapter preview:** Chapter 6 — **Loops**. Right now, repeating something 100 times means writing it 100 times. That's about to become one line. Prepare to never manually repeat yourself again. 🔁

*Decisions make programs smart. Tomorrow, repetition makes them tireless.* 💪

---

**⬅️ [Chapter 4](chapter-04-operators.md) | [🏠 Home](README.md) | [Chapter 6 ➡️](chapter-06-loops.md)**
