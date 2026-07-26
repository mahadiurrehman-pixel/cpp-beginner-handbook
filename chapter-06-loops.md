# CHAPTER 6 — LOOPS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Do something once, you're a person.
 Do it a million times without complaining —
 now you're a computer."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 5](chapter-05-conditions.md) | [🏠 Home](README.md) | [Chapter 7 ➡️](chapter-07-functions.md)**

---

## 📖 CHAPTER OPENING

Your PE teacher says "run 10 laps." You don't need to be told ten times — you hear the instruction once and repeat it ten times, counting as you go. A **loop** is that instruction: *do this, count, repeat until done.* Computers never tire, never lose count, never complain about lap 10,000,000. This chapter turns your programs into tireless workers.

### What you will learn:
- Why loops exist (and why you can't live without them)
- `while` — repeat while a condition is true
- `do-while` — run at least once, then check
- `for` — the compact counting loop
- Nested loops — loops inside loops (patterns! tables!)
- `break` — escape a loop early
- `continue` — skip to the next round
- Infinite loops — what they are and how to avoid them
- Classic loop jobs: sums, digits, factorials, star patterns

### Why this chapter matters:
Loops + conditions = **virtually every program ever written**. Data science? Loops over rows. Games? A loop running 60 frames per second. Your next 200 problems? Solved by loops. This chapter is where your code gains superpowers.

---

## 🔍 CONCEPT EXPLANATION

### What is a loop?

A **loop** repeats a block of code while a **condition** stays true. Every loop has four parts (memorize these):

```cpp
int i = 1;          // ① START (initialization)
while (i <= 10) {   // ② CHECK (condition — tested BEFORE each round)
    cout << i;      // ③ WORK (the repeated body)
    i = i + 1;      // ④ CHANGE (moves toward ending — forget = infinite loop!)
}
```

### Why do we use loops?

Because "print numbers 1–1000" should be 4 lines, not 1000. Real programs process thousands of records, check millions of pixels, wait for valid input — all loops.

### How does the computer understand it?

```
        ┌─────────────────────────────┐
        │                             │
        ▼                             │
   CHECK condition ──false──► EXIT loop
        │ true
        ▼
   RUN body (work + change) ──────────┘
```

The CPU evaluates the condition, runs the body, and **jumps back** to the condition. That's the entire machine. The only difference between `while`, `do-while`, and `for` is *when the check happens* and *where the four parts sit*.

🔥 **REMEMBER:** If part ④ (CHANGE) never makes ② false, the loop never ends — an **infinite loop**. Your program freezes forever (or until you press `Ctrl+C`). Every C++ programmer has made one. Welcome to the club in advance.

---

## 📝 SYNTAX BOX

### The three loops — one family, three personalities:

```cpp
// 1️⃣ while — "check first, maybe never run" (0 or more times)
int i = 1;
while (i <= 5) {
    cout << i << " ";
    i++;                // the CHANGE — vital!
}

// 2️⃣ do-while — "run first, check after" (1 or more times)
int pin;
do {
    cout << "Enter PIN: ";
    cin  >> pin;
} while (pin != 1234);   // note the semicolon at the END — required!

// 3️⃣ for — "counting specialist" (all 4 parts on one line)
for (int i = 1; i <= 5; i++) {
//        START;  CHECK;  CHANGE (after each round)
    cout << i << " ";
}

// 4️⃣ Loop controls — work inside any loop
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;      // EXIT the loop completely when i hits 5
    if (i % 2 == 0) continue; // SKIP even numbers, jump to next round
    cout << i << " ";        // prints: 1 3   (5 ends everything)
}
```

### Nested loop skeleton:

```cpp
for (int row = 1; row <= 3; row++) {          // outer: rows
    for (int col = 1; col <= 4; col++) {      // inner: full cycle PER row
        cout << "* ";
    }
    cout << endl;                             // newline after each row
}
```

| Loop | Guarantees | Best for |
|---|---|---|
| `while` | Checks first | Unknown repetitions ("until user types 0") |
| `do-while` | Runs ≥ 1 time | Menus, input validation, "try again" |
| `for` | Tidy counting | Known counts (1..N, rows & columns) |

> 💡 **PRO TIP:** Rule of thumb — counting? `for`. Condition-based? `while`. Must run at least once (menus)? `do-while`.

---

## 💻 EXAMPLE CODES

### Example 6.1 — Simplest Loop: Count with `while`

```cpp
// ============================================
// Example 6.1: Count 1 to 10 with while
// ============================================
// What this program does: Prints 1..10 using the 4 loop parts.
// Concepts used: while, loop variable i, increment
// ============================================

#include <iostream>
using namespace std;

int main() {

    int i = 1;              // ① START at 1

    while (i <= 10) {       // ② CHECK before each lap
        cout << i << " ";   // ③ WORK: print current lap number
        i++;                // ④ CHANGE: move up (forever without this!)
    }

    cout << "\nDone counting!" << endl;
    return 0;
}
/*
OUTPUT:
1 2 3 4 5 6 7 8 9 10
Done counting!

EXPLANATION:
i climbs 1→10; when i becomes 11 the check fails and the loop exits.
"Done counting!" only prints AFTER the loop — it's outside the braces.
*/
```

**What happened here?** Ten outputs from one `cout`. The loop variable `i` is your lap-counter — and `i++` is what keeps the loop honest.

---

### Example 6.2 — `do-while`: The Menu That Must Run Once

```cpp
// ============================================
// Example 6.2: PIN Retry System
// ============================================
// What this program does: Asks for a PIN until it's correct (max realism: 3 tries).
// Concepts used: do-while, counter, break
// ============================================

#include <iostream>
using namespace std;

int main() {

    const int CORRECT_PIN = 1234;
    int pin, attempts = 0;

    do {
        cout << "Enter PIN: ";
        cin  >> pin;
        attempts++;                            // count this try

        if (pin != CORRECT_PIN) {
            cout << "Wrong! Attempts left: " << 3 - attempts << endl;
        }
        if (attempts == 3) {                   // security limit
            cout << "Card blocked. Contact your bank." << endl;
            break;                             // escape NOW
        }
    } while (pin != CORRECT_PIN);              // keep asking until correct

    if (pin == CORRECT_PIN) {
        cout << "Access granted. Welcome!" << endl;
    }

    return 0;
}
/*
INPUT:  0000  5555  1234
OUTPUT:
Wrong! Attempts left: 2
Wrong! Attempts left: 1
Access granted. Welcome!

EXPLANATION:
do-while asks FIRST, checks after — perfect for "try until valid".
break adds a security exit after 3 failures, copying real ATMs.
*/
```

**What happened here?** `do-while` guarantees the question is asked at least once — exactly what menus and password prompts need. Combined with `break`, you built a realistic retry-lock system.

---

### Example 6.3 — `for`: The Multiplication Table

```cpp
// ============================================
// Example 6.3: Times Table Generator
// ============================================
// What this program does: Prints the multiplication table of any number.
// Concepts used: for loop, formatted output
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Which table? ";
    cin  >> n;

    for (int i = 1; i <= 10; i++) {          // i counts 1..10 automatically
        cout << n << " x " << i << " = " << n * i << endl;
    }

    return 0;
}
/*
INPUT:  7
OUTPUT:
7 x 1 = 7
7 x 2 = 14
7 x 3 = 21
...
7 x 10 = 70

EXPLANATION:
for (START; CHECK; CHANGE) packs all loop machinery into one line.
i is born in the loop header and dies at the closing brace —
it exists ONLY inside the loop (that's called its "scope").
*/
```

**What happened here?** `for` is the counting specialist: everything about the repetition is visible in the header — no forgotten `i++` hiding at the bottom.

---

### Example 6.4 — Classic Algorithm #1: Digit Analysis with `while`

```cpp
// ============================================
// Example 6.4: Sum the Digits of ANY Number
// ============================================
// What this program does: Reads 9874, prints digit sum 28 and digit count 4.
// Concepts used: while with % and / 10 (the Chapter 4 tricks, automated!)
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "Enter a number: ";
    cin  >> n;                         // e.g. 9874

    int copy = n;                      // we'll destroy copy, keep n intact
    int digitSum = 0, digitCount = 0;  // ALWAYS start accumulators at 0

    while (copy > 0) {                 // digits remain?
        int last = copy % 10;          // peel the last digit
        digitSum += last;              // add it to our sum
        digitCount++;                  // count it
        copy /= 10;                    // drop that digit off the number
    }

    cout << n << " has " << digitCount
         << " digits with sum " << digitSum << endl;

    return 0;
}
/*
INPUT:  9874
OUTPUT:
9874 has 4 digits with sum 28

TRACE (do this on paper!):
copy=9874 → last=4, sum=4,  copy=987
copy=987  → last=7, sum=11, copy=98
copy=98   → last=8, sum=19, copy=9
copy=9    → last=9, sum=28, copy=0  → loop exits

EXPLANATION:
% 10 peels, / 10 shrinks — alternating them disassembles ANY number,
however long. This one pattern solves digit sums, reversals,
palindromes, and Armstrong numbers. It's the Swiss Army loop.
*/
```

**What happened here?** Unknown repetitions ("however many digits there are") = `while`'s home turf. Notice the **accumulator** pattern: `sum = 0` before the loop, grow it inside — used in half of all loop programs.

---

### Example 6.5 — Nested Loops: Star Patterns

```cpp
// ============================================
// Example 6.5: Right-Angle Star Triangle
// ============================================
// What this program does: Prints a triangle whose rows grow: 1..n stars.
// Concepts used: nested for loops, row/column thinking
// ============================================

#include <iostream>
using namespace std;

int main() {

    int rows;
    cout << "How many rows? ";
    cin  >> rows;                              // e.g. 5

    for (int r = 1; r <= rows; r++) {          // OUTER: which row are we on?
        for (int c = 1; c <= r; c++) {         // INNER: stars = row number
            cout << "* ";
        }
        cout << endl;                          // drop to next line after row
    }

    return 0;
}
/*
INPUT:  5
OUTPUT:
*
* *
* * *
* * * *
* * * * *

EXPLANATION:
The INNER loop runs fully for each step of the OUTER loop.
Row 1 → 1 star, row 2 → 2 stars... The magic line is
c <= r  — the inner limit depends on the outer variable.
Master that idea and EVERY pattern problem surrenders.
*/
```

**What happened here?** Two sliders working together: outer chooses the row, inner paints that row's stars. Rectangle? Inner limit fixed. Triangle? Inner limit = row. Pyramid? Add a spaces-loop first (see Problem 6.10).

> ❓ **THINK ABOUT IT:** How would you flip this triangle (5 stars down to 1)? Change just the outer loop's start/check/change. (Answer in the exercises.)

---

### Example 6.6 — `break` & `continue`: Filtered Processing

```cpp
// ============================================
// Example 6.6: Number Feed Processor
// ============================================
// What this program does: Reads numbers: adds them up, skips negatives,
// stops completely on 999 (a "sentinel" value).
// Concepts used: while(true), break, continue, sentinel pattern
// ============================================

#include <iostream>
using namespace std;

int main() {

    int total = 0;

    cout << "Enter numbers (negative = skip, 999 = finish):" << endl;

    while (true) {                       // deliberate infinite loop...
        int x;
        cin >> x;

        if (x == 999) break;             // ...with a controlled exit
        if (x < 0)    continue;          // skip negatives, ask again

        total += x;
    }

    cout << "Total of accepted numbers: " << total << endl;
    return 0;
}
/*
INPUT:  10  -3  20  -7  5  999
OUTPUT:
Total of accepted numbers: 35

EXPLANATION:
while(true) + break is the standard "loop until told to stop"
pattern. The special value 999 that ends input is a SENTINEL.
continue jumps straight to the next input, skipping total += x.
*/
```

**What happened here?** `break` = "leave the loop now"; `continue` = "skip just this round." Deliberate `while(true)` with a `break` inside is not a bug — it's a respected pattern when the exit check belongs mid-body.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Forgetting the CHANGE (infinite loop)**
```cpp
int i = 1;
while (i <= 10) {
    cout << i;        // prints 1 forever — i never grows!
}
```
✅ **Fix:** `i++;` inside the body. Program frozen? Press `Ctrl+C` in the terminal, then look for your missing increment.

**❌ Mistake 2 — Semicolon after the loop header**
```cpp
for (int i = 1; i <= 5; i++);   // ← the ; IS the entire loop body (empty!)
{
    cout << i;                   // runs ONCE, with i = 6. Confusing!
}
```
✅ **Fix:** No `;` after `for (...)` or `while (...)`. (But yes after `do-while (...)`!)

**❌ Mistake 3 — Off-by-one (`<` vs `<=`)**
```cpp
for (int i = 1; i < 10; i++)    // prints 1..9 — missing 10!
```
✅ **Fix:** Decide consciously: "I want to INCLUDE 10" → `i <= 10`. Loop counts are the #1 source of subtle bugs; test the first & last values by hand.

**❌ Mistake 4 — Accumulator not initialized**
```cpp
int sum;                        // garbage!
for (int i = 1; i <= n; i++) sum += i;   // garbage + correct = garbage
```
✅ **Fix:** `int sum = 0;` — accumulators start at a known value. Always.

**❌ Mistake 5 — Changing the loop variable inside a `for` body**
```cpp
for (int i = 1; i <= 10; i++) {
    i = i * 2;            // chaos: 1, 4, 10 ... skipping unpredictably
}
```
✅ **Fix:** In a `for`, let the header own `i`. If you must steer manually, use `while`.

**❌ Mistake 6 — Bracing only the first line**
```cpp
while (i <= 10)
    cout << i;
    i++;                  // NOT inside the loop! infinite again.
```
✅ **Fix:** Always use `{}` for loop bodies — even one-liners. Future edits won't betray you.

---

## 🧠 CONCEPT SUMMARY TABLE

| Tool | One-liner | Typical use |
|---|---|---|
| `while` | Check → run → repeat | Until a condition changes (sentinels, digits) |
| `do-while` | Run → check → repeat | Menus, retry-prompts |
| `for (s;c;ch)` | All machinery in header | Counting 1..N, patterns, tables |
| Nested loop | Full inner per outer step | 2-D things: rows×cols, tables, patterns |
| `break` | Exit the loop now | Sentinels, search-found, limits |
| `continue` | Skip to next round | Filtering (skip invalid items) |
| Accumulator | `x=0;` grow inside loop | Sums, counts, max, factorial |
| Sentinel | Special value = "stop" | 999, -1, "END" input loops |
| Infinite loop | Condition never false | Avoid with proper CHANGE — or harness with `while(true)` + `break` |

**When to use what:** Counting → `for`. "Until" conditions → `while`. Menus → `do-while`. Rows & columns → nested `for`. Mid-loop exit → `while(true)`+`break`.

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read N and print 1..N. If N is 0 or negative,
   print "Nothing to print".
📥 SAMPLE INPUT: 5
📤 EXPECTED OUTPUT: 1 2 3 4 5
💡 HINT: Guard with if, count with for.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Print the multiplication table of any number
   (like Example 6.3) but from 1 up to a LIMIT the user enters.
📥 SAMPLE INPUT: 3 4
📤 EXPECTED OUTPUT:
3 x 1 = 3 ... 3 x 4 = 12
💡 HINT: for (i=1; i<=limit; i++)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Read N, print sum of 1..N using a loop.
📥 SAMPLE INPUT: 10
📤 EXPECTED OUTPUT: Sum = 55
💡 HINT: Accumulator: int sum = 0; then sum += i;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Factorial: read N, print N! (e.g. 5! = 120).
📥 SAMPLE INPUT: 5
📤 EXPECTED OUTPUT: 5! = 120
💡 HINT: long long fact = 1; fact *= i;  (start at ONE!)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Reverse a number: read 1234, print 4321.
📥 SAMPLE INPUT: 1234
📤 EXPECTED OUTPUT: Reversed = 4321
💡 HINT: rev = rev*10 + lastDigit each round (Example 6.4's machinery)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Prime checker: read N, print "Prime" or "Not prime".
   (Prime = no divisors between 2 and N-1.)
📥 SAMPLE INPUT: 29
📤 EXPECTED OUTPUT: Prime
💡 HINT: Loop i=2..n-1; if n%i==0 → not prime, break.
   Why does i*i <= n suffice? (bonus thought)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Count how many numbers the user typed before
   entering 0, plus their average.
📥 SAMPLE INPUT: 10 20 30 0
📤 EXPECTED OUTPUT:
Count = 3
Average = 20
💡 HINT: Sentinel while-loop with two accumulators;
   guard divide-by-zero when count==0.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Palindrome number: is 1221 the same reversed?
📥 SAMPLE INPUT: 1221   (also test 123)
📤 EXPECTED OUTPUT: Palindrome  /  Not a palindrome
💡 HINT: Reuse 6.5's reversal, compare with the ORIGINAL copy.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Fibonacci: print first N terms (0 1 1 2 3 5 8...).
📥 SAMPLE INPUT: 8
📤 EXPECTED OUTPUT: 0 1 1 2 3 5 8 13
💡 HINT: Keep TWO variables a=0,b=1; each round: print a,
   then next=a+b; a=b; b=next;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 6.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Star PYRAMID of height N (centered).
📥 SAMPLE INPUT: 4
📤 EXPECTED OUTPUT:
      *
    * * *
  * * * * *
* * * * * * *
💡 HINT: Per row: inner loop for SPACES (rows - r), then inner
   loop for STARS (2r - 1). Two inners, one outer.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 🎯 MINI CHALLENGE — THE DIAMOND 💎

Combine the pyramid (6.10) with an upside-down copy of itself to print a diamond of height N:

```
INPUT: 4
OUTPUT:
      *
    * * *
  * * * * *
* * * * * * *
  * * * * *
    * * *
      *
```

Bonus round: make it **hollow** (only the border stars print). This single challenge exercises nested loops, spacing math, and loop direction control — everything in this chapter. If your diamond shines, loops are officially yours. 💪

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 6.1**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n < 1) {
        cout << "Nothing to print";
    } else {
        for (int i = 1; i <= n; i++) cout << i << " ";
    }
    return 0;
}
```
💡 **PRO TIP:** Always decide the loop bound (`<= n` vs `< n`) by testing the LAST expected value first.

**✅ SOLUTION 6.2**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, limit;
    cin >> n >> limit;
    for (int i = 1; i <= limit; i++)
        cout << n << " x " << i << " = " << n * i << endl;
    return 0;
}
```

**✅ SOLUTION 6.3**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n, sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) sum += i;
    cout << "Sum = " << sum << endl;
    return 0;
}
```
💡 **PRO TIP:** There's a formula too — `n*(n+1)/2` — but the loop is what this chapter is about. Knowing both = ace.

**✅ SOLUTION 6.4**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long fact = 1;             // multiplication starts at 1!
    for (int i = 2; i <= n; i++) fact *= i;
    cout << n << "! = " << fact << endl;
    return 0;
}
```
💡 **PRO TIP:** `long long` because 20! = 2.4×10¹⁸ already drowns an `int`. Factorials grow SCARY fast.

**✅ SOLUTION 6.5**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int rev = 0, copy = n;
    while (copy > 0) {
        rev = rev * 10 + copy % 10;   // shift rev left, append last digit
        copy /= 10;
    }
    cout << "Reversed = " << rev << endl;
    return 0;
}
```
Trace for 1234: rev = 4 → 43 → 432 → 4321.
💡 **PRO TIP:** `rev*10 + digit` builds numbers left-to-right while `%10 /10` dismantles right-to-left. Two conveyor belts, one number.

**✅ SOLUTION 6.6**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    if (n < 2) {
        cout << "Not prime";
        return 0;                    // exit main early — legal and clean!
    }
    bool isPrime = true;             // flag pattern: assume, then disprove
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) { isPrime = false; break; }
    }
    cout << (isPrime ? "Prime" : "Not prime") << endl;
    return 0;
}
```
💡 **PRO TIP (bonus answer):** If n has a divisor bigger than √n, its partner is smaller than √n — so checking up to `i*i <= n` is enough. 29 → check 2,3,4,5 only.

**✅ SOLUTION 6.7**
```cpp
#include <iostream>
using namespace std;

int main() {
    int x, count = 0, sum = 0;
    while (true) {
        cin >> x;
        if (x == 0) break;
        sum += x;
        count++;
    }
    cout << "Count = " << count << endl;
    if (count > 0) cout << "Average = " << (double)sum / count << endl;
    return 0;
}
```

**✅ SOLUTION 6.8**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int original = n, rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    cout << (rev == original ? "Palindrome" : "Not a palindrome") << endl;
    return 0;
}
```
💡 **PRO TIP:** Keep a backup (`original`) BEFORE the loop eats your variable — the destruction is permanent.

**✅ SOLUTION 6.9**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a = 0, b = 1;
    for (int i = 1; i <= n; i++) {
        cout << a << " ";
        int next = a + b;      // the new Fibonacci number
        a = b;                 // shift the window forward
        b = next;
    }
    return 0;
}
```
💡 **PRO TIP:** The two-variable "sliding window" appears in tons of sequence problems — remember the shape.

**✅ SOLUTION 6.10**
```cpp
#include <iostream>
using namespace std;

int main() {
    int rows;
    cin >> rows;
    for (int r = 1; r <= rows; r++) {
        for (int s = 1; s <= rows - r; s++) cout << "  ";   // 2 spaces
        for (int st = 1; st <= 2 * r - 1; st++) cout << "* ";
        cout << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Spaces = `rows - r`, stars = `2r - 1` (odd numbers: 1,3,5,7). Decode ANY pattern into per-row counts like this and nested loops become mechanical.

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int r = 1; r <= n; r++) {                      // top half
        for (int s = 1; s <= n - r; s++)      cout << "  ";
        for (int st = 1; st <= 2 * r - 1; st++) cout << "* ";
        cout << endl;
    }
    for (int r = n - 1; r >= 1; r--) {                  // bottom: count DOWN
        for (int s = 1; s <= n - r; s++)      cout << "  ";
        for (int st = 1; st <= 2 * r - 1; st++) cout << "* ";
        cout << endl;
    }
    return 0;
}
```
💡 **PRO TIP:** Loops can count DOWN too: `for (int r = n-1; r >= 1; r--)`. Different direction, same 4 parts.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Every loop = START, CHECK, WORK, CHANGE — forget CHANGE and enjoy your infinite loop
- ✓ `for` counts, `while` waits for conditions, `do-while` guarantees one run
- ✓ Accumulators (`sum = 0`) + loops = sums, counts, factorials, maxima
- ✓ `% 10` peels digits, `/ 10` shrinks — the classic digit loop
- ✓ `break` exits, `continue` skips; nested loops paint rows & columns

**📚 Keywords learned:** iteration, loop variable, infinite loop, `while`, `do-while`, `for`, nested loop, `break`, `continue`, sentinel, accumulator, flag

**🔗 Next chapter preview:** Chapter 7 — **Functions**. Your programs are getting long. Time to break them into named, reusable pieces — write once, call forever. This is how programs grow from 50 lines to 50,000 without collapsing. 🧱

*Loops gave your programs stamina. Next, functions will give them organization. You're building the complete toolkit.* 🔥

---

**⬅️ [Chapter 5](chapter-05-conditions.md) | [🏠 Home](README.md) | [Chapter 7 ➡️](chapter-07-functions.md)**
