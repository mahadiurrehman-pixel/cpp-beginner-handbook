# CHAPTER 4 — OPERATORS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Numbers in boxes are a filing system.
 Operators are the hands that do the work."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 3](chapter-03-variables.md) | [🏠 Home](README.md) | [Chapter 5 ➡️](chapter-05-conditions.md)**

---

## 📖 CHAPTER OPENING

A calculator with no buttons is just a paperweight. Variables alone are the same — they *hold* numbers but can't *do* anything. **Operators** are the buttons: add this, compare that, check if two things are true at once. And today you also get `cin` — the "reverse cout" that finally lets users **type into** your programs.

### What you will learn:
- Arithmetic operators `+ - * / %` (and why `%` is more useful than you think)
- Assignment shortcuts `+= -= *= /=`
- Comparison operators `== != < > <= >=` — which produce `bool`
- Logical operators `&& || !` — combining conditions
- Increment/decrement `++ --` and the tricky pre/post difference
- Bitwise operators (gentle introduction)
- Operator precedence — why `2 + 3 * 4` is 14, not 20
- `cin` — reading user input

### Why this chapter matters:
Operators are the verbs of programming. Plus, from this chapter on, **your programs become interactive** — real people can type real data and watch your program respond. That's the moment coding stops feeling like homework.

---

## 🔍 CONCEPT EXPLANATION

### What is an operator?

An **operator** is a symbol that performs an action on values (called **operands**). In `5 + 3`, `+` is the operator; `5` and `3` are operands.

### Why so many kinds?

Because programs do three kinds of work with data:
1. **Compute** — arithmetic (`+`, `-`, `*`, `/`, `%`)
2. **Decide** — comparison (`==`, `>`...) and logical (`&&`, `||`, `!`) → these make `bool` answers
3. **Manipulate bits** — bitwise (`&`, `|`, `^`, `<<`, `>>`) → the raw 1s and 0s

### How does the computer understand them?

The CPU has a tiny built-in circuit called the ALU (Arithmetic Logic Unit) that performs exactly these operations — adding, comparing, AND-ing bits — billions of times per second. When you write `a + b`, C++ compiles it into direct ALU instructions. **Operators are the closest you get to talking to the CPU itself**, which is why C++ is so fast.

### And `cin`?

`cin` ("see-in") is `cout` reversed: it reads what the user types, converts it to the variable's type, and stores it. The arrows literally point the other way:

```cpp
cout << value;   // data flows OUT of the program  (to the screen)
cin  >> value;   // data flows INTO the program    (from the keyboard)
```

🔥 **REMEMBER:** `<<` points at `cout`, `>>` points AWAY from `cin` into the variable. The arrows always show the direction data flows.

---

## 📝 SYNTAX BOX

### The operator families:

```cpp
// 1️⃣ ARITHMETIC — math on numbers
a + b    a - b    a * b    a / b    a % b    // % = remainder ("modulo")

// 2️⃣ ASSIGNMENT — put value in, with shortcuts
a = 5    a += 3    a -= 2    a *= 4    a /= 2    a %= 7
// a += 3  is shorthand for  a = a + 3

// 3️⃣ COMPARISON — YES/NO questions, result is bool
a == b   // EQUAL to        (two signs!)
a != b   // NOT equal
a > b    a < b    a >= b   a <= b

// 4️⃣ LOGICAL — combine booleans
condA && condB   // AND: true only if BOTH true
condA || condB   // OR:  true if AT LEAST ONE true
!condA           // NOT: flips true ↔ false

// 5️⃣ INCREMENT / DECREMENT
++a    // pre-increment: add 1 FIRST,  then use the value
a++    // post-increment: use the value FIRST, then add 1
--a    a--   // same idea, subtracting 1

// 6️⃣ BITWISE — operate on raw binary bits (intro level)
a & b    // bit AND     a | b   // bit OR      a ^ b   // bit XOR
a << 1   // shift left (= multiply by 2)    a >> 1   // shift right (= divide by 2)

// 7️⃣ INPUT
cin >> variable;              // read one value
cin >> x >> y >> z;           // read several in one line (space-separated)
```

### Simplified precedence table (high → low):

| Priority | Operators |
|---|---|
| 1 (first) | `()` — parentheses always win |
| 2 | `!`, `++`, `--` (unary) |
| 3 | `*`, `/`, `%` |
| 4 | `+`, `-` |
| 5 | `<<`, `>>` (shifts) |
| 6 | `<`, `<=`, `>`, `>=` |
| 7 | `==`, `!=` |
| 8 | `&&` |
| 9 | `\|\|` |
| 10 | `=`, `+=`, `-=`, ... |

> ✅ **GOOD PRACTICE:** When unsure of precedence, use parentheses. `(a + b) * c` is always right, and it reads better. Professionals parenthesize shamelessly.

---

## 💻 EXAMPLE CODES

### Example 4.1 — Hello, `cin`! (And Arithmetic)

```cpp
// ============================================
// Example 4.1: Interactive Arithmetic
// ============================================
// What this program does: Reads two numbers, prints their operations.
// Concepts used: cin >>, + - * / %
// ============================================

#include <iostream>
using namespace std;

int main() {

    int a, b;                                    // boxes waiting for input

    cout << "Enter two numbers: ";
    cin >> a >> b;                               // user types e.g.  20 6

    cout << "\n---- Results ----"          << endl;
    cout << "a + b      = " << a + b       << endl;   // addition
    cout << "a - b      = " << a - b       << endl;   // subtraction
    cout << "a * b      = " << a * b       << endl;   // multiplication
    cout << "a / b      = " << a / b       << endl;   // division (int: chops!)
    cout << "a % b      = " << a % b       << endl;   // remainder

    return 0;
}
/*
INPUT:  20 6
OUTPUT:
---- Results ----
a + b      = 26
a - b      = 14
a * b      = 120
a / b      = 3
a % b      = 2

EXPLANATION:
20/6 = 3 (int division chops .33...) and 20%6 = 2 (the leftover).
Division and modulo are siblings: one gives the quotient,
the other gives the remainder. 20 = 6*3 + 2. ✔
*/
```

**What happened here?** Your program went from monologue to **dialogue**. The modulo `%` looks odd but is superstar-useful: `n % 2` detects even/odd, `n % 10` grabs the last digit — you'll use it constantly.

⚠️ **WARNING:** Never divide by zero. `a / 0` crashes your program (or produces garbage). In Chapter 5 you'll learn to guard against it.

---

### Example 4.2 — Assignment Shortcuts & `++`/`--`

```cpp
// ============================================
// Example 4.2: Shorthand and Increments
// ============================================
// What this program does: Shows += style operators and pre/post ++.
// Concepts used: =, +=, -=, *=, ++ prefix vs postfix
// ============================================

#include <iostream>
using namespace std;

int main() {

    int points = 100;

    points += 50;     // same as points = points + 50  → 150
    points -= 20;     // subtract 20                   → 130
    points *= 2;      // double it                     → 260
    cout << "Points: " << points << endl;

    // ---- The famous pre vs post difference ----
    int x = 5;
    cout << "\nx = " << x << endl;
    cout << "x++ prints: " << x++ << endl;   // shows 5, THEN x becomes 6
    cout << "x is now:   " << x   << endl;   // 6
    cout << "++x prints: " << ++x << endl;   // x becomes 7 FIRST, shows 7
    cout << "x is now:   " << x   << endl;   // 7

    return 0;
}
/*
OUTPUT:
Points: 260

x = 5
x++ prints: 5
x is now:   6
++x prints: 7
x is now:   7

EXPLANATION:
postfix (x++) = "use me first, change me after"
prefix  (++x) = "change me first, use me after"
When ++ stands on its OWN line, both are identical —
the difference only matters mid-expression.
*/
```

**What happened here?** `x++` handed over the old value *then* incremented; `++x` incremented *then* handed over. In Chapter 6 you'll write `i++` in loops daily — its own line, where pre/post make no difference.

---

### Example 4.3 — Real-World Scenario: The Entry Gate Check

```cpp
// ============================================
// Example 4.3: Gym Entry Eligibility Checker
// ============================================
// What this program does: Reads age & membership, computes a YES/NO answer.
// Concepts used: comparison + logical operators producing bool
// ============================================

#include <iostream>
using namespace std;

int main() {

    int  age;
    char member;        // 'y' or 'n'

    cout << "Enter your age: ";
    cin  >> age;

    cout << "Are you a member? (y/n): ";
    cin  >> member;

    bool isAdult     = age >= 18;                    // comparison → bool
    bool hasMember   = (member == 'y');              // equality check → bool
    bool canEnter    = isAdult && hasMember;         // AND: both required
    bool freeTrialOK = isAdult && !hasMember;        // NOT: flips the bool

    cout << "\n--- Gate Computer ---"          << endl;
    cout << "Adult:        " << isAdult        << endl;
    cout << "Member:       " << hasMember      << endl;
    cout << "Can enter:    " << canEnter       << endl;  // 1 = yes, 0 = no
    cout << "Free trial:   " << freeTrialOK    << endl;

    return 0;
}
/*
INPUT:  21  y
OUTPUT:
--- Gate Computer ---
Adult:        1
Member:       1
Can enter:    1
Free trial:   0

EXPLANATION:
Comparisons (age >= 18) manufacture bool values, and logical
operators (&&, ||, !) combine them. Right now we only PRINT
the answers — in Chapter 5, if-statements will ACT on them.
*/
```

**What happened here?** You built decision-making logic — the same pattern behind every login screen, age gate, and permission system — using nothing but operators that evaluate to `true`/`false`.

---

### Example 4.4 — Operator Precedence Puzzle

```cpp
// ============================================
// Example 4.4: Precedence — Who Goes First?
// ============================================
// What this program does: Proves why 2 + 3 * 4 == 14, not 20.
// Concepts used: precedence, parentheses clarity
// ============================================

#include <iostream>
using namespace std;

int main() {

    cout << "2 + 3 * 4       = " << 2 + 3 * 4       << endl;  // * first → 14
    cout << "(2 + 3) * 4     = " << (2 + 3) * 4     << endl;  // () first → 20
    cout << "10 + 20 % 6     = " << 10 + 20 % 6     << endl;  // % first → 12
    cout << "100 - 50 / 10   = " << 100 - 50 / 10   << endl;  // / first → 95

    bool tricky = 5 > 3 && 2 < 10;   // comparisons before && → true && true
    cout << "5>3 && 2<10     = " << tricky          << endl;  // 1

    return 0;
}
/*
OUTPUT:
2 + 3 * 4       = 14
(2 + 3) * 4     = 20
10 + 20 % 6     = 12
100 - 50 / 10   = 95
5>3 && 2<10     = 1

EXPLANATION:
C++ doesn't read left to right — it follows precedence:
* / % before + -, comparisons before &&, && before ||.
Parentheses override everything. When in doubt: (parenthesize).
*/
```

**What happened here?** Precedence is just school math with extra operators. The safest programmer habit ever: **write the parentheses you mean** — `2 + (3 * 4)` documents intent even where optional.

---

### Example 4.5 — Bitwise Operators (Gentle First Contact)

```cpp
// ============================================
// Example 4.5: Peeking at the Bits
// ============================================
// What this program does: Shows &, |, ^, <<, >> on small numbers.
// Concepts used: bitwise operators, binary thinking
// ============================================

#include <iostream>
using namespace std;

int main() {

    int a = 6;     // binary: 110
    int b = 3;     // binary: 011

    cout << "a & b  = " << (a & b)  << endl;   // 010 = 2  (both bits 1)
    cout << "a | b  = " << (a | b)  << endl;   // 111 = 7  (any bit 1)
    cout << "a ^ b  = " << (a ^ b)  << endl;   // 101 = 5  (bits differ)
    cout << "a << 1 = " << (a << 1) << endl;   // shift left  → 12 (×2)
    cout << "a >> 1 = " << (a >> 1) << endl;   // shift right →  3 (÷2)

    return 0;
}
/*
OUTPUT:
a & b  = 2
a | b  = 7
a ^ b  = 5
a << 1 = 12
a >> 1 = 3

EXPLANATION:
Bitwise ops compare the binary digits POSITION by position:
6=110, 3=011. AND keeps positions where both are 1 → 010 = 2.
Shifting left appends a 0 in binary — which doubles the number.
*/
```

**What happened here?** Bitwise operators feel exotic, but two of them are instantly useful: `n << 1` multiplies by 2, `n >> 1` divides by 2 — at circuit speed. Graphics, networking, and embedded code live on these.

> 🎮 **FUN FACT:** The even/odd check `n % 2 == 0` works, but bitwise pros write `(n & 1) == 0` — checking just the last binary digit. Same answer, microscopic speed gain.

---

### Example 4.6 — Combined: The Two-Number Toolkit

```cpp
// ============================================
// Example 4.6: Interactive Toolkit (Chapters 2+3+4)
// ============================================
// What this program does: A formatted multi-tool math report on input.
// Concepts used: cin, arithmetic, modulo tricks, bool results, formatting
// ============================================

#include <iostream>
using namespace std;

int main() {

    const int DIVISOR = 10;          // for digit tricks
    int n;

    cout << "Enter a 3-digit number: ";
    cin  >> n;                        // e.g. 457

    int lastDigit  = n % DIVISOR;     // 457 % 10 = 7
    int noLast     = n / DIVISOR;     // 457 / 10 = 45
    bool isEven    = (n % 2 == 0);    // classic even test

    cout << "\n========= NUMBER REPORT =========" << endl;
    cout << "Number:\t\t"        << n            << endl;
    cout << "Doubled:\t"       << n * 2        << endl;
    cout << "Squared:\t"       << n * n        << endl;
    cout << "Last digit:\t"    << lastDigit    << endl;
    cout << "Without last:\t"  << noLast       << endl;
    cout << "Is even (1/0):\t" << isEven       << endl;
    cout << "================================="  << endl;

    return 0;
}
/*
INPUT:  457
OUTPUT:
========= NUMBER REPORT =========
Number:         457
Doubled:        914
Squared:        208849
Last digit:     7
Without last:   45
Is even (1/0):  0
=================================

EXPLANATION:
% 10 peels off the last digit; / 10 drops it. These two little
tricks power half the loop problems in Chapter 6 (digit sums,
reversals, palindromes). Learn them now, thank me later.
*/
```

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — `=` (assignment) confused with `==` (comparison)**
```cpp
if (x = 5) { ... }     // assigns 5 to x! then asks "is 5 true?" (always yes)
```
✅ **Fix:** Comparing? `x == 5`. Assigning? `x = 5`. This is THE most infamous C++ bug — Chapter 5 will keep rubbing it in.

**❌ Mistake 2 — Wrong arrow direction on cin**
```cpp
cin << age;            // ❌ arrows point INTO age with >>
```
Compiler says: `error: no match for 'operator<<' (...istream...)`
✅ **Fix:** `cin >> age;` — memory hook: `cin>` sounds like it, and the arrows point INTO the variable.

**❌ Mistake 3 — `%` on floating-point numbers**
```cpp
double d = 5.5 % 2;    // ❌ modulo is integer-only
```
Compiler says: `error: invalid operands of types 'double' and 'int' to binary 'operator%'`
✅ **Fix:** Use `%` only with whole-number types (`int`, `long`).

**❌ Mistake 4 — Expecting decimal results from int division**
```cpp
int marks = 85, subjects = 4;
double avg = marks / subjects;   // 21.0, not 21.25 — chopped BEFORE storing
```
✅ **Fix:** `double avg = marks / 4.0;` or `marks / (double)subjects;`

**❌ Mistake 5 — Chaining comparisons like math class**
```cpp
if (18 <= age <= 30)   // ❌ means (18 <= age) <= 30  →  (0 or 1) <= 30  → always true!
```
✅ **Fix:** `if (age >= 18 && age <= 30)` — C++ needs every comparison spelled out and joined with `&&`.

**❌ Mistake 6 — Reading input into an uninitialized plan**
```cpp
int age;
cout << age;          // garbage BEFORE cin gives it a value
cin >> age;           // fine — but many beginners print THEN read
```
✅ **Fix:** Always prompt → read → use, in that order.

---

## 🧠 CONCEPT SUMMARY TABLE

| Operator | Meaning | Example | Result |
|---|---|---|---|
| `+ - * /` | arithmetic | `7 / 2` | `3` (int chops) |
| `%` | remainder | `7 % 2` | `1` |
| `+= -= *= /=` | assign with op | `x += 3` | x = old x + 3 |
| `==` | equal? | `5 == 5` | `true` |
| `!=` | not equal? | `5 != 3` | `true` |
| `< > <= >=` | ordering | `3 > 8` | `false` |
| `&&` | AND | `t && f` | `false` |
| `\|\|` | OR | `t \|\| f` | `true` |
| `!` | NOT (flip) | `!true` | `false` |
| `++` / `--` | add/sub 1 | `i++` | i+1 |
| `& \| ^` | bit ops | `6 & 3` | `2` |
| `<< >>` | bit shifts | `6 << 1` | `12` |
| `cin >>` | read input | `cin >> age;` | stores typed value |

**When to use what:** Decisions → comparison+logical. Even/odd & digits → `%`. Counting → `++`. Multiple conditions → parenthesize and join with `&&`/`||`.

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read two integers, print their sum, difference,
   and product.
📥 SAMPLE INPUT: 8 3
📤 EXPECTED OUTPUT:
Sum = 11
Difference = 5
Product = 24
💡 HINT: cin >> a >> b; then three cout lines.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read the radius of a circle (double) and print
   its area. Use a const PI.
📥 SAMPLE INPUT: 5
📤 EXPECTED OUTPUT: Area = 78.5398
💡 HINT: area = PI * r * r
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read total seconds (int) and convert to minutes
   + remaining seconds.
📥 SAMPLE INPUT: 200
📤 EXPECTED OUTPUT: 3 minutes and 20 seconds
💡 HINT: minutes = s / 60, leftover = s % 60
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Read a 3-digit number and print the SUM of its
   digits. (No loops yet — pure / and %!)
📥 SAMPLE INPUT: 457
📤 EXPECTED OUTPUT: Digit sum = 16
💡 HINT: n%10 = last digit; n/10%10 = middle; n/100 = first.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Read Celsius (double) from the user and print
   Fahrenheit.
📥 SAMPLE INPUT: 37
📤 EXPECTED OUTPUT: 98.6 F
💡 HINT: F = C * 9.0 / 5.0 + 32   (decimals guard the math)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Swap two numbers read from the user using ONLY
   compound assignment operators (no temp variable), then
   print. (Also verify the classic temp version works.)
📥 SAMPLE INPUT: 10 20
📤 EXPECTED OUTPUT: a = 20, b = 10
💡 HINT: a += b; b = a - b; a -= b;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Read an integer n and print 1 if it's even,
   0 if odd — WITHOUT if-statements (next chapter!). Also
   print n doubled using a bit shift.
📥 SAMPLE INPUT: 7
📤 EXPECTED OUTPUT:
Even? 0
Doubled: 14
💡 HINT: even-check: (n % 2 == 0). Double: n << 1.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: BMI Calculator: read weight (kg) and height (m),
   compute BMI = weight / (height²), and print 1/0 flags:
   underweight (<18.5), normal (18.5–24.9), overweight (≥25).
📥 SAMPLE INPUT: 70 1.75
📤 EXPECTED OUTPUT (approx):
BMI = 22.8571
Underweight: 0
Normal: 1
Overweight: 0
💡 HINT: Chain comparisons with &&: bmi >= 18.5 && bmi < 25
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: A shop gives a discount if (bill > 5000) AND
   (customer is a member 'y'). Read bill and membership,
   print 1/0 whether a discount applies, plus the final bill
   (10% off if eligible — compute with bool multiplication:
   finalBill = bill - bill * 0.10 * eligible).
📥 SAMPLE INPUT: 6000 y
📤 EXPECTED OUTPUT:
Discount: 1
Final bill: 5400
💡 HINT: bool values are 1/0 — multiplying by eligible
   keeps/removes the discount. Sneaky but legal!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 4.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: "Bit Playground": read an int n, and print:
   n<<1, n>>1, n&1, n|1, n^1 — with labels. For input 12,
   explain (as comments in your code) WHY each answer is so.
📥 SAMPLE INPUT: 12
📤 EXPECTED OUTPUT:
n << 1 = 24
n >> 1 = 6
n & 1  = 0
n | 1  = 13
n ^ 1  = 13
💡 HINT: 12 = 1100 in binary. Draw the bits for each op.
```

---

## 🎯 MINI CHALLENGE — SMART HOME CONTROLLER 🏠🤖

Read these inputs from the "house":
- `temperature` (int, °C)
- `isNight` (char `y`/`n`)
- `motionDetected` (char `y`/`n`)

Then print a control panel of 1/0 flags:
| Output | Rule |
|---|---|
| `AC ON` | temperature > 30 |
| `Lights ON` | isNight AND motionDetected |
| `Alarm ON` | isNight AND NOT motionDetected AND temperature < 10 (weird sensor rule — just follow it!) |

```
INPUT EXAMPLE:  34 y y
OUTPUT:
AC ON:      1
Lights ON:  1
Alarm ON:   0
```

You've just written the decision core of a real IoT device — with chapter-4 tools only. Tomorrow's smart homes run on exactly this logic. 🌟

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 4.1**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    cout << "Sum = "        << a + b << endl;
    cout << "Difference = " << a - b << endl;
    cout << "Product = "    << a * b << endl;
    return 0;
}
```
💡 **PRO TIP:** Prompt users (`cout << "Enter two numbers: ";`) before every `cin` — silent programs feel broken to humans.

**✅ SOLUTION 4.2**
```cpp
#include <iostream>
using namespace std;

int main() {
    const double PI = 3.14159;
    double r;
    cin >> r;
    cout << "Area = " << PI * r * r << endl;
    return 0;
}
```

**✅ SOLUTION 4.3**
```cpp
#include <iostream>
using namespace std;

int main() {
    int s;
    cin >> s;
    cout << s / 60 << " minutes and " << s % 60 << " seconds" << endl;
    return 0;
}
```
💡 **PRO TIP:** `/` and `%` are inverse teammates: any "split into groups + leftover" problem wants both.

**✅ SOLUTION 4.4**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;                     // 457
    int d1 = n % 10;              // 7
    int d2 = (n / 10) % 10;       // 5
    int d3 = n / 100;             // 4
    cout << "Digit sum = " << d1 + d2 + d3 << endl;
    return 0;
}
```
💡 **PRO TIP:** Chapter 6 will generalize this to ANY number of digits with a humble `while` loop.

**✅ SOLUTION 4.5**
```cpp
#include <iostream>
using namespace std;

int main() {
    double c;
    cin >> c;
    cout << c * 9.0 / 5.0 + 32 << " F" << endl;
    return 0;
}
```

**✅ SOLUTION 4.6**
```cpp
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;      // 10 20
    a += b;             // a = 30
    b = a - b;          // b = 10 ← original a!
    a -= b;             // a = 20
    cout << "a = " << a << ", b = " << b << endl;
    return 0;
}
```
💡 **PRO TIP:** Elegant, but the temp-variable swap (`int t=a; a=b; b=t;`) is clearer and safer — prefer it in real projects.

**✅ SOLUTION 4.7**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cout << "Even? "      << (n % 2 == 0) << endl;
    cout << "Doubled: "   << (n << 1)     << endl;
    return 0;
}
```

**✅ SOLUTION 4.8**
```cpp
#include <iostream>
using namespace std;

int main() {
    double weight, height;
    cin >> weight >> height;

    double bmi = weight / (height * height);

    cout << "BMI = "        << bmi                              << endl;
    cout << "Underweight: " << (bmi < 18.5)                     << endl;
    cout << "Normal: "      << (bmi >= 18.5 && bmi < 25.0)      << endl;
    cout << "Overweight: "  << (bmi >= 25.0)                    << endl;
    return 0;
}
```
💡 **PRO TIP:** Printing 1/0 flags is a primitive preview — next chapter you'll print actual messages like "Normal weight ✔" using `if`.

**✅ SOLUTION 4.9**
```cpp
#include <iostream>
using namespace std;

int main() {
    double bill;
    char   member;
    cin >> bill >> member;

    bool   eligible   = (bill > 5000) && (member == 'y');
    double finalBill  = bill - bill * 0.10 * eligible;   // bool → 0/1 math

    cout << "Discount: "   << eligible  << endl;
    cout << "Final bill: " << finalBill << endl;
    return 0;
}
```
💡 **PRO TIP:** Multiplying by a bool is a fun trick, but next chapter's `if` version is more readable. Know the trick; prefer the clear version.

**✅ SOLUTION 4.10**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;    // 12 = 1100 in binary

    cout << "n << 1 = " << (n << 1) << endl;  // 1100 → 11000 = 24 (doubled)
    cout << "n >> 1 = " << (n >> 1) << endl;  // 1100 → 110   = 6  (halved)
    cout << "n & 1  = " << (n & 1)  << endl;  // last bit 0 → 0 (12 is even)
    cout << "n | 1  = " << (n | 1)  << endl;  // 1100|0001 → 1101 = 13
    cout << "n ^ 1  = " << (n ^ 1)  << endl;  // flip last bit → 1101 = 13
    return 0;
}
```

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
using namespace std;

int main() {
    int  temperature;
    char isNight, motion;
    cin >> temperature >> isNight >> motion;

    bool night  = (isNight == 'y');
    bool moved  = (motion  == 'y');

    bool acOn     = temperature > 30;
    bool lightsOn = night && moved;
    bool alarmOn  = night && !moved && (temperature < 10);

    cout << "AC ON:      " << acOn     << endl;
    cout << "Lights ON:  " << lightsOn << endl;
    cout << "Alarm ON:   " << alarmOn  << endl;
    return 0;
}
```
💡 **PRO TIP:** Converting `char` inputs to named bools (`night`, `moved`) BEFORE writing the rules keeps the rules readable. Name your intermediate bools — it's a professional habit.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ `%` gives remainders — the secret weapon for even/odd and digit tricks
- ✓ `=` assigns, `==` compares — confusing them is bug #1
- ✓ Comparisons and logic build `bool`; `&&` needs both true, `||` needs one
- ✓ `int` division chops decimals; precedence puts `* / %` above `+ -` — parenthesize when unsure
- ✓ `cin >> x` reads input; arrows show the direction data flows

**📚 Keywords learned:** operator, operand, modulo, compound assignment, increment/decrement, comparison, logical AND/OR/NOT, bitwise, precedence, `cin`

**🔗 Next chapter preview:** Chapter 5 — **Conditional Statements**. Right now your programs can only *print* yes/no answers. Next, they'll **act** on them: different paths, different outcomes, real decisions. Your programs are about to get intelligent. 🧠

*Interactive input, real math, yes/no logic — in four chapters flat. You're not a beginner anymore; you're a programmer with training wheels.* 🚴

---

**⬅️ [Chapter 3](chapter-03-variables.md) | [🏠 Home](README.md) | [Chapter 5 ➡️](chapter-05-conditions.md)**
