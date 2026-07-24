# CHAPTER 2 — YOUR FIRST C++ PROGRAM

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A journey of a thousand miles begins
 with a single step — or in our case,
 a single cout statement."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 1](chapter-01-setup.md) | [🏠 Home](README.md) | [Chapter 3 ➡️](chapter-03-variables.md)**

---

## 📖 CHAPTER OPENING

In 1974, Brian Kernighan wrote a tiny program that printed "hello, world" — and accidentally started a tradition. Fifty years later, every programmer's journey still begins the same way. Today it's your turn to join that club.

### What you will learn:
- The structure of **every** C++ program (one template to rule them all)
- What `#include`, `main()`, `cout`, and `return 0` actually do
- How to print text, numbers, and multiple things at once
- Comments — notes to your future self
- Escape sequences (`\n`, `\t`, `\\`, `\"`) for formatting output
- Professional formatting habits that make your code readable

### Why this chapter matters:
Everything in C++ — from a calculator to a video game — is built on the skeleton you learn today. Master this chapter and every future chapter is "just more of the same." Plus: clean output formatting is secretly a job skill.

---

## 🔍 CONCEPT EXPLANATION

### What is a C++ program?

A C++ program is a list of **statements** (instructions) inside a special function called `main()`. The computer runs them **top to bottom**, like a very obedient robot reading a to-do list.

### Why is it structured this way?

Because programs get BIG. Games have millions of lines. So C++ enforces structure: libraries are imported at the top, code lives inside named blocks, and every instruction ends explicitly with `;`. Structure is what keeps 5-line programs and 5-million-line programs both manageable.

### How does the computer run it?

```
You press "Run"
   → Operating System searches for main()
   → Executes statements inside { } one by one, top to bottom
   → cout instructions send characters to the screen
   → return 0 tells the OS "finished successfully"
   → Program closes
```

🔥 **REMEMBER:** There must be **exactly one** `main()` in a program. It's the front door. No `main` = nowhere to start = linker error.

---

## 📝 SYNTAX BOX

### The Universal Template — memorize this:

```cpp
#include <iostream>     // ① Import input/output tools (cout, cin)
using namespace std;    // ② Shortcut: cout instead of std::cout

int main() {            // ③ Program STARTS here. Always.

    cout << "Text" << endl;   // ④ A STATEMENT — ends with semicolon!

    return 0;           // ⑤ Tell OS: "everything went fine"
}                       // ⑥ Closing brace — end of main
```

| Part | Full name | Explanation |
|---|---|---|
| `#include <iostream>` | Preprocessor directive | "Before compiling, paste in the iostream library." `iostream` = **I**nput/**O**utput **stream** — contains `cout` (print) and `cin` (read). |
| `using namespace std;` | Namespace usage | `std` = "standard". Without this you'd write `std::cout` everywhere. For now, always include it. |
| `int main()` | Main function | The entry point. `int` = it gives back an **int**eger when done. `( )` because it's a function (Chapter 7). |
| `{ }` | Braces | A **block**. Everything between them belongs to `main`. Every `{` needs one `}`. |
| `cout` | Console output | Pronounced "see-out". Sends data to the screen. |
| `<<` | Insertion operator | "Send this INTO cout." Chains: `cout << a << b;` |
| `"..."` | String literal | Text to print, ALWAYS in double quotes. |
| `endl` | End line | Moves to the next line, like pressing Enter. |
| `;` | Semicolon | Ends a statement. THE most-forgotten character in C++. |
| `return 0;` | Return statement | Hands the number `0` to the OS: 0 = success, non-zero = something went wrong. |

### Common variations:

```cpp
std::cout << "Hi";              // without "using namespace std;"
cout << "Hi\n";                 // \n instead of endl (newline character)
return EXIT_SUCCESS;            // fancy version of return 0 (rare in this book)
```

> 🎮 **FUN FACT:** `cout` isn't a keyword — it's an **object** defined in `iostream`. That's why forgetting `#include <iostream>` makes the compiler ask *"cout? never heard of it."*

---

## 💻 EXAMPLE CODES

### Example 2.1 — Hello World (The Tradition)

```cpp
// ============================================
// Example 2.1: Hello, World!
// ============================================
// What this program does: Prints one greeting line.
// Concepts used: program template, cout, endl, return
// ============================================

#include <iostream>    // Line 1: bring in printing tools
using namespace std;   // Line 2: shortcut for standard names

int main() {           // Line 3: program starts here

    // Line 5: send text to the screen, then a newline
    cout << "Hello, World!" << endl;

    return 0;          // Line 7: report success to the OS
}                      // Line 8: main ends here
/*
OUTPUT:
Hello, World!

EXPLANATION:
Execution began at main(), the cout statement pushed
"Hello, World!" into the console stream, endl added a
newline, and return 0 ended the program cleanly.
*/
```

**What happened here?** Fifty years of tradition in five lines. Every line is explained in the Syntax Box above — re-read it until you could explain this program to a friend. Seriously, teaching is the best test of understanding.

---

### Example 2.2 — Comments (Notes the Compiler Ignores)

```cpp
// ============================================
// Example 2.2: Two Kinds of Comments
// ============================================
// What this program does: Prints two lines; shows comment styles.
// Concepts used: // single-line and /* */ multi-line comments
// ============================================

#include <iostream>
using namespace std;

int main() {

    // This is a SINGLE-LINE comment.
    // Everything after // on a line is invisible to the compiler.

    cout << "Line 1" << endl;   // Comments can also sit after code.

    /* This is a MULTI-LINE comment.
       It spans as many lines as you want.
       Great for longer explanations. */

    cout << "Line 2" << endl;

    return 0;   /* multi-line comments can squeeze onto one line too */
}
/*
OUTPUT:
Line 1
Line 2

EXPLANATION:
Comments change NOTHING about the output. They exist purely
for humans — and "humans" includes YOU, six months from now,
staring at your own code asking "what was I thinking?"
*/
```

**What happened here?** The compiler threw away every comment before translating. Only the two `cout` statements produced output. Comment your code like you'll have amnesia tomorrow — you kind of will.

---

### Example 2.3 — Printing Many Things (Chaining `<<`)

```cpp
// ============================================
// Example 2.3: Multiple Output & Chaining
// ============================================
// What this program does: Prints a mini profile using chaining.
// Concepts used: multiple cout, chaining <<, printing numbers
// ============================================

#include <iostream>
using namespace std;

int main() {

    // Three separate statements = three separate lines
    cout << "My name is: Mahadi" << endl;
    cout << "I am learning: C++" << endl;
    cout << "My goal is: become a developer" << endl;

    // ONE statement, many pieces — chain them with <<
    cout << "Two" << " things " << "chained together!" << endl;

    // Numbers don't need quotes; text does
    cout << "My favorite number: " << 42 << endl;
    cout << "Math inside cout: 7 x 6 = " << 7 * 6 << endl;  // C++ calculates!

    return 0;
}
/*
OUTPUT:
My name is: Mahadi
I am learning: C++
My goal is: become a developer
Two things chained together!
My favorite number: 42
Math inside cout: 7 x 6 = 42

EXPLANATION:
<< works like a conveyor belt: each item rides into cout
in order. Text needs quotes; numbers don't. C++ even
evaluates 7 * 6 before printing.
*/
```

**What happened here?** The insertion operator `<<` chained text, numbers, and even a *calculation* into one smooth output line. Think of `cout` as a conveyor belt to your screen.

---

### Example 2.4 — Escape Sequences (Printing the Unprintable)

```cpp
// ============================================
// Example 2.4: Escape Sequences
// ============================================
// What this program does: Uses \n \t \\ \" inside text.
// Concepts used: escape characters start with backslash \
// ============================================

#include <iostream>
using namespace std;

int main() {

    // \n = new line (alternative to endl)
    cout << "Line 1\nLine 2\nLine 3" << endl;

    // \t = tab — great for columns!
    cout << "Name:\tMahadi" << endl;
    cout << "City:\tKarachi" << endl;

    // \\ = one real backslash (a single \ starts an escape!)
    cout << "Path: C:\\Users\\Mahadi" << endl;

    // \" = a real double-quote inside a quoted string
    cout << "He said \"C++ is fun!\"" << endl;

    return 0;
}
/*
OUTPUT:
Line 1
Line 2
Line 3
Name:   Mahadi
City:   Karachi
Path: C:\Users\Mahadi
He said "C++ is fun!"

EXPLANATION:
The backslash \ means "the next character is special."
\n newline, \t tab, \\ literal backslash, \" literal quote.
Without \", the quote would have ENDED the string early.
*/
```

**What happened here?** Escape sequences let you sneak special characters into text. The two most-used: `\n` (newline) and `\t` (tab) — you'll use `\t` constantly for tidy columns.

---

### Example 2.5 — Good vs Bad Formatting

```cpp
// ============================================
// Example 2.5: Formatting Is a Habit
// ============================================
// Both programs below compile and run identically.
// Only ONE of them will get you hired/be forgiven.
// ============================================

// ❌ BAD (compiles fine, burns the eyes):
#include<iostream>
using namespace std;
int main(){cout<<"Hello";cout<<"World";return 0;}

// ✅ GOOD — readable, professional:
#include <iostream>
using namespace std;

int main() {

    cout << "Hello" << endl;    // one statement per line
    cout << "World" << endl;    // indented 4 spaces inside braces

    return 0;
}
/*
FORMATTING RULES TO LIVE BY:
1. One statement per line
2. Indent everything inside { } by 4 spaces (or 1 tab)
3. Spaces around operators:  x = 5   not   x=5
4. Blank lines between logical sections
5. Braces aligned so you can SEE where blocks begin/end

EXPLANATION:
The compiler ignores all whitespace. Formatting is 100%
for humans — and code is read 10x more than it's written.
*/
```

> ✅ **GOOD PRACTICE:** In VS Code, press `Shift+Alt+F` to auto-format the whole file. Use it often while building the manual habit.

---

### Example 2.6 — Putting It All Together: A Formatted Report

```cpp
// ============================================
// Example 2.6: A Neat Little Report (Chapter 0+1+2 combined)
// ============================================
// What this program does: Prints a formatted daily report.
// Concepts used: template, chaining, \t, \n, comments, formatting
// ============================================

#include <iostream>
using namespace std;

int main() {

    // --- Header ---
    cout << "================================" << endl;
    cout << "       DAILY STUDY REPORT       " << endl;
    cout << "================================" << endl;

    // --- Body (tab-aligned columns) ---
    cout << "Student:\tMahadi"          << endl;
    cout << "Subject:\tC++ Basics"       << endl;
    cout << "Chapter:\t2"                << endl;
    cout << "Hours:\t\t2"                 << endl;   // \t\t = two tabs

    // --- Footer ---
    cout << "\nGreat work today!" << endl;   // \n before text = blank line above

    return 0;
}
/*
OUTPUT:
================================
       DAILY STUDY REPORT
================================
Student:        Mahadi
Subject:        C++ Basics
Chapter:        2
Hours:          2

Great work today!

EXPLANATION:
Real programs are just... many small, understandable lines
in a sensible order. That's the whole secret.
*/
```

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Missing semicolon**
```cpp
cout << "Hello"     // ← compiler error!
```
Compiler says: `error: expected ';' before 'return'`
✅ **Fix:** `cout << "Hello";` — every statement ends with `;`. When the error line looks fine, check the line ABOVE it.

**❌ Mistake 2 — Wrong capitalization (C++ is case-sensitive!)**
```cpp
Cout << "Hello";    // ❌ capital C
Int Main() { }      // ❌ doubly wrong
```
Compiler says: `error: 'Cout' was not declared in this scope`
✅ **Fix:** `cout`, `int`, `main` — all lowercase, always. `Cout`, `COUT`, and `cout` are three different names to C++.

**❌ Mistake 3 — Forgetting `#include <iostream>`**
```cpp
using namespace std;
int main() { cout << "Hi"; }   // ❌ where does cout come from?
```
Compiler says: `error: 'cout' was not declared in this scope`
✅ **Fix:** `#include <iostream>` as the first line. *"Not declared in this scope"* → check includes & spelling.

**❌ Mistake 4 — Text without quotes**
```cpp
cout << Hello World;      // ❌ compiler thinks these are variable names
```
Compiler says: `error: 'Hello' was not declared in this scope`
✅ **Fix:** `cout << "Hello World";` — text in double quotes; numbers without.

**❌ Mistake 5 — Mismatched or missing braces**
```cpp
int main() {
    cout << "Hi";
    return 0;
    // ❌ vanished closing brace!
```
Compiler says: `error: expected '}' at end of input`
✅ **Fix:** Every `{` gets a `}`. VS Code highlights the matching partner — click a brace and check.

**❌ Mistake 6 — Quoting escape sequences wrong (backslash vs forward slash)**
```cpp
cout << "Hello/nWorld";   // ❌ /n prints literally as "/n"
```
Output: `Hello/nWorld`
✅ **Fix:** Backslash: `\n`. Memory trick: backslash leans BACK.

---

## 🧠 CONCEPT SUMMARY TABLE

| Item | Purpose | Example |
|---|---|---|
| `#include <iostream>` | Import I/O tools | First line, almost always |
| `using namespace std;` | Avoid `std::` everywhere | Second line |
| `int main()` | Program entry point | Exactly one per program |
| `{ }` | Group code into a block | `{ ... }` |
| `cout << x` | Print to console | `cout << "Hi";` |
| `endl` | Newline | `<< endl` |
| `\n` | Newline (string version) | `"...\n"` |
| `\t` | Tab (column alignment) | `"\t"` |
| `\\` | Literal backslash | `"C:\\Users"` |
| `\"` | Literal quote | `"say \"hi\""` |
| `//` | Single-line comment | `// note` |
| `/* */` | Multi-line comment | `/* notes */` |
| `return 0;` | "Success" signal to OS | Last line of main |

**When to use what:** `endl` when building lines one-by-one (clearer); `\n` when a newline is mid-text or you care about tiny performance. Comments: everywhere your code isn't instantly obvious.

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Print your name, city, and favorite hobby,
   each on its own line.
📤 EXPECTED OUTPUT:
Name: Mahadi
City: Karachi
Hobby: Coding
💡 HINT: Three cout statements, each ending with endl.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Print this box of stars exactly:
📤 EXPECTED OUTPUT:
**********
*  C++   *
**********
💡 HINT: Three lines; the middle one has spaces between *.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Print three math facts with answers computed
   by C++ (not typed by you):  5 + 3,  10 - 4,  6 * 7.
📤 EXPECTED OUTPUT:
5 + 3 = 8
10 - 4 = 6
6 * 7 = 42
💡 HINT: Chain: cout << "5 + 3 = " << 5 + 3 << endl;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Print a coffee-shop receipt using \t for
   aligned columns:
📤 EXPECTED OUTPUT:
============================
        COFFEE SHOP
============================
Item            Price
Coffee          Rs. 150
Sandwich        Rs. 200
----------------------------
TOTAL           Rs. 350
============================
💡 HINT: "Coffee\t\tRs. 150" — experiment with one vs two tabs.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Print this EXACT dialogue, quotes included:
📤 EXPECTED OUTPUT:
Teacher: "Why is C++ fun?"
Student: "Because cout never says no!"
💡 HINT: Escaping quotes: \" starts and ends each quote pair.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Print an upside-down triangle of # symbols:
📤 EXPECTED OUTPUT:
#####
####
###
##
#
💡 HINT: Five cout lines, each one character shorter.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Print a weekly schedule table using \t:
📤 EXPECTED OUTPUT:
Day          Time      Task
Monday       9 AM      C++ Study
Wednesday    6 PM      Practice
Friday       8 PM      Revision
💡 HINT: Tabs align columns; count tab stops carefully.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Print an ATM welcome screen with borders,
   menu options, and a footer:
📤 EXPECTED OUTPUT: (something like)
========================================
         KARACHI NATIONAL BANK
========================================
   Welcome! Please select:
   1. Check Balance
   2. Withdraw Cash
   3. Deposit
   4. Exit
----------------------------------------
   Helpline: 0800-12345
========================================
💡 HINT: Build top border, then content lines, then footer.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Print a chessboard row-pair pattern 4 lines tall:
📤 EXPECTED OUTPUT:
#.#.#.#.
.#.#.#.#
#.#.#.#.
.#.#.#.#
💡 HINT: Only two unique lines — odd lines start with #,
   even with a dot.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 2.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Print a formatted "certificate" with your name,
   course, and a date, using borders and centered-ish text:
📤 EXPECTED OUTPUT: (something like)
**********************************
*        CERTIFICATE             *
*      of Achievement            *
*                                *
*  Awarded to:  Mahadi           *
*  Course:      C++ Foundations  *
*  Date:        22 July 2026     *
**********************************
💡 HINT: Draw the border line once, copy it for top & bottom,
   use spaces to push text toward the middle.
```

---

## 🎯 MINI CHALLENGE — ASCII ART HOUSE 🏠

Draw a house with `cout` — at least 10 lines tall — including a **roof**, **walls**, a **door**, and a **window**:

```
        /\
       /  \
      /    \
     /______\
    |  ____  |
    | |    | |
    | |____| |
    |________|
```

Rules: only `cout` statements; escape backslashes correctly (`\\` in code prints ONE `\`); creativity encouraged — add a chimney, a sun, smoke rings. This tests `cout`, escapes, and careful spacing.

**You just started Chapter 2 and you're already an artist. Don't stop.** 🎨

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 2.1**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Name: Mahadi" << endl;
    cout << "City: Karachi" << endl;
    cout << "Hobby: Coding" << endl;
    return 0;
}
```
💡 **PRO TIP:** Chapter 3 lets you store these in *variables* and change them in one place.

**✅ SOLUTION 2.2**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "**********" << endl;
    cout << "*  C++   *" << endl;
    cout << "**********" << endl;
    return 0;
}
```
💡 **PRO TIP:** Count characters in the top border first, then pad the middle line to match the width exactly.

**✅ SOLUTION 2.3**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "5 + 3 = " << 5 + 3 << endl;
    cout << "10 - 4 = " << 10 - 4 << endl;
    cout << "6 * 7 = " << 6 * 7 << endl;
    return 0;
}
```
💡 **PRO TIP:** C++ evaluates the math BEFORE printing. The text part keeps its quotes; the math part doesn't.

**✅ SOLUTION 2.4**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "============================" << endl;
    cout << "        COFFEE SHOP         " << endl;
    cout << "============================" << endl;
    cout << "Item\t\tPrice"      << endl;
    cout << "Coffee\t\tRs. 150"    << endl;
    cout << "Sandwich\tRs. 200"    << endl;
    cout << "----------------------------" << endl;
    cout << "TOTAL\t\tRs. 350"     << endl;
    cout << "============================" << endl;
    return 0;
}
```
💡 **PRO TIP:** A tab jumps to the next multiple of 8 columns. "Sandwich" is longer than "Coffee", so it needs one fewer `\t`.

**✅ SOLUTION 2.5**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Teacher: \"Why is C++ fun?\"" << endl;
    cout << "Student: \"Because cout never says no!\"" << endl;
    return 0;
}
```
💡 **PRO TIP:** `\"` displays a quote without ending the string. First earns you the joke, second prints it.

**✅ SOLUTION 2.6**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "#####" << endl;
    cout << "####"  << endl;
    cout << "###"   << endl;
    cout << "##"    << endl;
    cout << "#"     << endl;
    return 0;
}
```
💡 **PRO TIP:** In Chapter 6, ONE loop will print this for any size. Hard-coding today so automation amazes you later.

**✅ SOLUTION 2.7**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Day\t\tTime\t\tTask"        << endl;
    cout << "Monday\t\t9 AM\t\tC++ Study"  << endl;
    cout << "Wednesday\t6 PM\t\tPractice"  << endl;
    cout << "Friday\t\t8 PM\t\tRevision"  << endl;
    return 0;
}
```

**✅ SOLUTION 2.8**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "         KARACHI NATIONAL BANK          " << endl;
    cout << "========================================" << endl;
    cout << "   Welcome! Please select:"               << endl;
    cout << "   1. Check Balance"                      << endl;
    cout << "   2. Withdraw Cash"                      << endl;
    cout << "   3. Deposit"                            << endl;
    cout << "   4. Exit"                               << endl;
    cout << "----------------------------------------" << endl;
    cout << "   Helpline: 0800-12345"                  << endl;
    cout << "========================================" << endl;
    return 0;
}
```
💡 **PRO TIP:** In Chapter 5 & 6 this fake menu becomes a REAL menu that responds to user input. Come back and upgrade it then!

**✅ SOLUTION 2.9**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "#.#.#.#." << endl;
    cout << ".#.#.#.#" << endl;
    cout << "#.#.#.#." << endl;
    cout << ".#.#.#.#" << endl;
    return 0;
}
```

**✅ SOLUTION 2.10** — One possible version:
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "**********************************" << endl;
    cout << "*        CERTIFICATE             *" << endl;
    cout << "*      of Achievement            *" << endl;
    cout << "*                                *" << endl;
    cout << "*  Awarded to:  Mahadi           *" << endl;
    cout << "*  Course:      C++ Foundations  *" << endl;
    cout << "*  Date:        22 July 2026     *" << endl;
    cout << "**********************************" << endl;
    return 0;
}
```
💡 **PRO TIP:** Alignment by hand is tedious — in Chapter 6 (loops) and Chapter 9 (strings) you'll generate borders automatically.

**✅ MINI CHALLENGE (sample answer)**
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "        /\\"        << endl;   // \\ prints ONE backslash
    cout << "       /  \\"       << endl;
    cout << "      /    \\"      << endl;
    cout << "     /______\\"     << endl;
    cout << "    |  ____  |"    << endl;
    cout << "    | |    | |"    << endl;
    cout << "    | |____| |"    << endl;
    cout << "    |________|"    << endl;
    return 0;
}
```
💡 **PRO TIP:** The trap in this challenge is `\\`. If your roof prints as `/\` with double backslashes, you forgot to escape them.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ `#include <iostream>` + `using namespace std;` + `int main() { ... return 0; }` = your permanent template
- ✓ `cout <<` prints; chain multiple items with more `<<`
- ✓ Text needs `"quotes"`, numbers don't, and `;` ends every statement
- ✓ `\n` newline, `\t` tab, `\\` backslash, `\"` quote — escapes start with backslash
- ✓ C++ is case-sensitive; braces come in pairs; comments are free — use them generously

**📚 Keywords learned:** `#include`, `iostream`, `namespace`, `std`, `main`, `cout`, `<<`, `endl`, `return`, escape sequence, statement

**🔗 Next chapter preview:** Chapter 3 — **Variables**. Right now your programs can only print fixed text. Next, they'll *store* information, *remember* it, and *change* it. That's when programs start feeling alive.

*You are now officially a programmer — you have written, compiled, and run C++ programs. Welcome to the club. 🎉*

---

**⬅️ [Chapter 1](chapter-01-setup.md) | [🏠 Home](README.md) | [Chapter 3 ➡️](chapter-03-variables.md)**
