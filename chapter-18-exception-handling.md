# CHAPTER 18 — EXCEPTION HANDLING

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Plan for the storm while building the ship —
 not when the waves are already overhead."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 17](chapter-17-file-handling.md) | [🏠 Home](README.md) | [Chapter 19 ➡️](chapter-19-stl.md)**

---

## 📖 CHAPTER OPENING

A user types "abc" where your program expected a number. A file you're reading was just deleted. A division meets a zero. Until now, these meant crash, garbage, or awkward `if` spaghetti everywhere. **Exceptions** give you a professional system: notice the disaster (`throw`), have a rescue team standing by (`catch`), and keep the program alive.

### What you will learn:
- What exceptions are — and why they're better than hope
- `try`, `throw`, `catch` — the three-part system
- Multiple catch blocks for different disasters
- The catch-all `catch(...)`
- Standard exceptions (`runtime_error`, `invalid_argument`) and building **custom** ones
- Best practices: what to throw, when to catch, and when NOT to use exceptions at all

### Why this chapter matters:
Real users are creative chaos agents. Programs that survive them are programs people trust. Exception safety is the difference between a school demo and production software — and this book's final projects use it everywhere.

---

## 🔍 CONCEPT EXPLANATION

### What is an exception?

An **exception** is an emergency signal an object/function can fire when something it can't handle happens. The signal travels up the call chain looking for a handler:

```cpp
try {                        // 🚧 "attempt the risky work here"
    // ... risky code ...
    throw 20;               // 🚨 fire the emergency signal (any value!)
}
catch (int e) {              // 🚒 rescue team for 'int' signals
    // handle it — program SURVIVES and continues
}
```

If nothing catches it → the program terminates with a crash message. A caught exception = a handled disaster = a living program.

### Why not just use `if` everywhere?

You can — for nearby, expected problems (and you should! `if` remains the right tool for validation). But consider: `A()` calls `B()` calls `C()` calls `D()`, and `D` hits a disaster. With `if`, every layer must detect-and-forward the error — messy. With exceptions, `D` throws and the signal zips straight past B and C to wherever the rescue team waits. **Separation of "normal logic" and "disaster logic."**

### How does the computer understand it?

On `throw`, C++ unwinds the call stack: exits the current function (running destructors — RAII from Chapter 13 still protects you!), steps up the caller chain until it finds a matching `catch`, and jumps straight into it. All stack objects along the way are cleaned up properly.

---

## 📝 SYNTAX BOX

```cpp
try {
    // risky operations
    if (badThing) throw runtime_error("describe the disaster");
    if (badNum)   throw 404;                    // you can throw ANY type
    if (badText)  throw string("oops");
}
catch (int code) {                    // matches thrown ints
    cout << "numeric error: " << code;
}
catch (const string& msg) {           // matches thrown strings
    cout << "text error: " << msg;
}
catch (const runtime_error& e) {      // standard exception family
    cout << e.what();                 // .what() returns the message
}
catch (...) {                         // 🕸️ catch-ALL — must be LAST
    cout << "something unknown exploded";
}
// program continues here, alive
```

**The standard exception family** (from `<stdexcept>`):

```cpp
throw runtime_error("file vanished");        // things that fail while running
throw invalid_argument("age can't be -5");   // caller passed nonsense
throw out_of_range("index 99 in size-10");   // container overreach
throw overflow_error("number too big");      // numeric overflow
```

**Custom exception class:**

```cpp
class BankException : public runtime_error {
public:
    BankException(const string& msg) : runtime_error(msg) { }
};
throw BankException("Withdrawal exceeds balance");
```

| Rule | Why |
|---|---|
| Catch by `const Type&` | avoids copying, catches derived classes of standard exceptions |
| Specific catches BEFORE `catch(...)` | order matters — first match wins |
| Throw objects (like runtime_error) | strings/ints work, but objects carry meaning: `.what()` |
| Don't swallow silently | `catch (...) { }` with an empty body hides disasters |

---

## 💻 EXAMPLE CODES

### Example 18.1 — The Simplest Safety Net

```cpp
// ============================================
// Example 18.1: Safe Division — Before and After
// ============================================
// Concepts used: try, throw, single catch
// ============================================

#include <iostream>
using namespace std;

double safeDivide(double a, double b) {
    if (b == 0) {
        throw 1;                        // 🚨 emergency signal (int type here)
    }                                   // function exits IMMEDIATELY
    return a / b;
}

int main() {

    double x = 10, y;
    cout << "Divide 10 by? ";
    cin  >> y;

    try {                                   // 🚧 risky call inside try
        double result = safeDivide(x, y);
        cout << "Answer: " << result << "\n";
        cout << "This line only prints on success.\n";
    }
    catch (int errorCode) {                 // 🚒 matching rescue team
        cout << "Blocked! Division by zero isn't legal math. (code "
             << errorCode << ")\n";
    }

    cout << "Program is still alive and well. ✓\n";
    return 0;
}
/*
INPUT:  0
OUTPUT:
Blocked! Division by zero isn't legal math. (code 1)
Program is still alive and well. ✓

INPUT: 4 → Answer: 2.5 + the alive line

EXPLANATION:
without try/catch, 10/0 becomes garbage or a crash. WITH it, throw
JUMPS out of safeDivide to the catch, skipping every line between.
The program moved past a fatal error like it was a speed bump.
*/
```

**What happened here?** `throw` is a one-way emergency exit out of any function; `catch` is the ground crew. The last `cout` proving survival is the entire point.

---

### Example 18.2 — Multiple Catch Blocks: Different Disasters, Different Rescue

```cpp
// ============================================
// Example 18.2: An Age Validator With Specialized Rescue Teams
// ============================================
// Concepts used: multiple catch types, catch(...), catch order
// ============================================

#include <iostream>
#include <string>
using namespace std;

int parseAge(const string& input) {
    // manual digit check first: "abc" isn't a number at all
    for (char c : input)
        if (!isdigit(c)) throw string("non-numeric");        // type #1

    int age = stoi(input);                                    // now safe
    if (age < 0)    throw -1;                                 // type #2 (int)
    if (age < 13)   throw runtime_error("too young");         // type #3
    if (age > 120)  throw runtime_error("unlikely age");      // type #3 again
    return age;
}

int main() {

    string text;
    cout << "Enter your age: ";
    getline(cin, text);

    try {
        int age = parseAge(text);
        cout << "Registered, age " << age << ". Welcome!\n";
    }
    catch (const string& msg) {                  // 🚒 for strings
        cout << "Please type digits only (" << msg << ").\n";
    }
    catch (int code) {                           // 🚒 for ints
        cout << "Negative ages are in sci-fi only. (code " << code << ")\n";
    }
    catch (const runtime_error& e) {             // 🚒 for std exceptions
        cout << "Registration issue: " << e.what() << "\n";
    }
    catch (...) {                                // 🕸️ anything else — LAST!
        cout << "Unknown disaster contained.\n";
    }

    cout << "(program continues...)\n";
    return 0;
}
/*
INPUT: abc   → Please type digits only (non-numeric).
INPUT: -7    → Negative ages are in sci-fi only. (code -1)
INPUT: 5     → Registration issue: too young
INPUT: 30    → Registered, age 30. Welcome!

EXPLANATION:
C++ matches the catch by the thrown TYPE, checking blocks top to
bottom, first match wins. Put specific types first, catch(...)
always last — a catch-all sitting on top would eat everything.
*/
```

**What happened here?** One risky function, three kinds of emergencies, targeted responses for each — and the surviving program walks on.

---

### Example 18.3 — Real-World: The Bulletproof Bank Withdrawal

```cpp
// ============================================
// Example 18.3: Custom BankException in a Real Class
// ============================================
// Concepts used: custom exception (extends runtime_error), object throw
// ============================================

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ---------- your own named disaster type ----------
class BankException : public runtime_error {
public:
    BankException(const string& msg) : runtime_error(msg) { }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b) : balance(b) { }

    void withdraw(double amount) {
        if (amount <= 0)
            throw BankException("Withdrawal must be positive, got: "
                                + to_string(amount));
        if (amount > balance)
            throw BankException("Insufficient funds: tried "
                                + to_string(amount) + " with balance "
                                + to_string(balance));
        balance -= amount;
        cout << "Withdrawn. Balance: " << balance << "\n";
    }
};

int main() {

    BankAccount acc(1000);

    double tries[3] = { 500, 1200, -50 };      // one good, two disasters

    for (int i = 0; i < 3; i++) {
        try {
            acc.withdraw(tries[i]);
        }
        catch (const BankException& e) {              // custom caught precisely
            cout << "🏦 Bank refused: " << e.what() << "\n";
        }
    }

    cout << "Account system never went down. ✓\n";
    return 0;
}
/*
OUTPUT:
Withdrawn. Balance: 500
🏦 Bank refused: Insufficient funds: tried 1200 with balance 500
🏦 Bank refused: Withdrawal must be positive, got: -50
Account system never went down. ✓

EXPLANATION:
Subclassing runtime_error gives you .what() formatting for free and
lets you ONE catch cover all your domain errors. The loop survives
each refusal and keeps serving the next request — EXACTLY how real
ATMs never crash from bad input.
*/
```

**What happened here?** Error policy lives inside the class (it *throws*), error presentation lives outside (main *catches*). This split is professional architecture.

---

### Example 18.4 — Files + Exceptions: The Missing-File Survivor

```cpp
// ============================================
// Example 18.4: Loading Data From a File That Might Not Exist
// ============================================
// Concepts used: runtime_error with built-in family, graceful fallback
// ============================================

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;

int loadHighScore(const string& filename) {
    ifstream in(filename);
    if (!in.is_open())
        throw runtime_error("Save file '" + filename + "' not found.");

    int score;
    if (!(in >> score))                              // file exists but is broken
        throw runtime_error("Save file is corrupted.");

    return score;
}

int main() {

    int highScore;

    try {
        highScore = loadHighScore("highscore.txt");
        cout << "Loaded previous high score: " << highScore << "\n";
    }
    catch (const runtime_error& e) {
        cout << "Warning: " << e.what() << "\n";
        cout << "Starting fresh with score 0.\n";
        highScore = 0;                                // graceful fallback!
    }

    cout << "Game starts with high score: " << highScore << "\n";
    return 0;
}
/*
OUTPUT (no such file):
Warning: Save file 'highscore.txt' not found.
Starting fresh with score 0.
Game starts with high score: 0

EXPLANATION:
The function doesn't TRY to be clever — it just reports clearly.
The CALLER decides the policy (default to 0). "Throw locally,
decide globally" — the exception-decision separation every
reliable app uses. Chapter 23's game uses this exact loader!
*/
```

**What happened here?** Notice the alternative — checking `is_open` with `if` at the call site is *also* fine here. Exceptions shine when the decision belongs far from the detection. Both tools; choose per situation (see best practices below).

---

### Example 18.5 — Exceptions Traveling Through Call Chains

```cpp
// ============================================
// Example 18.5: throw at Depth 3, catch at Depth 0
// ============================================
// Concepts used: exception propagation, stack unwinding visuals, RAII note
// ============================================

#include <iostream>
#include <stdexcept>
using namespace std;

void layerC() {
    cout << "   C: doing risky work...\n";
    throw runtime_error("catastrophe at layer C!");
    cout << "   C: never prints — throw already left.\n";
}

void layerB() {                        // NO try/catch here — just passes through
    cout << "  B enters.\n";
    layerC();
    cout << "  B exits — never prints either (unwound through B).\n";
}

void layerA() {
    cout << " A enters.\n";
    layerB();
    cout << " A exits — unwound too.\n";
}

int main() {

    try {
        cout << "main: starting the chain.\n";
        layerA();
    }
    catch (const runtime_error& e) {
        cout << "main caught (from three layers deep!): " << e.what() << "\n";
    }

    cout << "main: normal ending. ✓\n";
    return 0;
}
/*
OUTPUT:
main: starting the chain.
 A enters.
  B enters.
   C: doing risky work...
main caught (from three layers deep!): catastrophe at layer C!
main: normal ending. ✓

EXPLANATION:
The exception skipped B and A entirely — no detection code there,
no forwarding mess. Any destructors of objects living in A/B/C STILL
ran on the way out (stack unwinding respects RAII, Ch. 13: memory
and files stay safe). This is why deep libraries use exceptions:
report where it happens, HANDLE where policy lives.
*/
```

**What happened here?** Normal logic stayed clean at every level; disaster logic existed only at the ends. That's the *why* of exceptions in one example.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Throwing and never catching**
```cpp
int main() {
    throw runtime_error("boom");   // 💥 terminate called after throwing ...
}
```
✅ **Fix:** Any code path that can throw needs a matching `catch` somewhere up the chain — or the program IS the bug.

**❌ Mistake 2 — `catch(...)` placed first**
```cpp
try { risky(); }
catch (...) { cout << "any"; }          // catches EVERYTHING first!
catch (int e) { cout << "int"; }        // ← never reached; some compilers error
```
✅ **Fix:** Most specific catches first; `catch(...)` dead last.

**❌ Mistake 3 — Catching by value (slicing)**
```cpp
catch (runtime_error e) { cout << e.what(); }  // copies — and slices derived exceptions!
```
✅ **Fix:** `catch (const runtime_error& e)` — reference keeps the full object AND avoids copying.

**❌ Mistake 4 — Using exceptions for NORMAL control flow**
```cpp
try { name = userInput(); length = name.length(); }
catch (...) { /* "user entered empty" */ }      // 😵 predictable, local, expected
```
✅ **Fix:** Expected, frequent, local conditions → `if`. Exceptions are for *exceptional* events — they cost performance and obscurity when spammed.

**❌ Mistake 5 — The empty catch (swallowing)**
```cpp
catch (...) { }     // disaster happened, program pretends it didn't 😶
```
✅ **Fix:** At minimum, log it. Someone someday will hunt a silent data corruption into this block for weeks.

**❌ Mistake 6 — Throwing from a destructor (Ch. 13 friend warning)**
```cpp
~File() { if (!saved) throw runtime_error("unsaved!"); }  // during stack unwinding?
```
If this fires while ANOTHER exception is already unwinding, the program terminates immediately.
✅ **Fix:** Destructors must NEVER throw. Handle cleanup failures quietly (log them, or offer a `close()` method that may throw instead).

---

## 🧠 CONCEPT SUMMARY TABLE

| Element | Shape | Remember |
|---|---|---|
| `try { }` | wraps risky code | zero cost until a throw happens |
| `throw value;` | fire signal | any type; objects best; exits function instantly |
| `catch (const T& e)` | one per T to handle | matched by TYPE, first match wins |
| `catch (...)` | the safety net | always LAST |
| standard throws | `runtime_error`, `invalid_argument`, `out_of_range` | from `<stdexcept>`; speak via `.what()` |
| custom exception | `: public runtime_error` | named domain disasters |
| unwinding | automatic | destructors still run — RAII ally |
| When NOT to use | expected/local/frequent conditions | those are `if`'s job |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.1 ⭐
📋 safeSqrt(x): throws invalid_argument("negative") for x<0,
   else returns sqrt from <cmath>. main tries inputs 9 and -4.
📤 OUTPUT: 3, then a caught warning — and program survives.
💡 HINT: throw inside helper, catch in main.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.2 ⭐
📋 Read index + print arr[i] from a 5-element array; throw
   out_of_range if i ∉ [0,4]; catch and say which valid range is.
📥 INPUT: 9
📤 OUTPUT: "Index 9 is out of bounds! Valid: 0-4"
💡 HINT: you throw manually — arrays don't do it for you.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.3 ⭐
📋 Write try/catch around stoi(userText) — stoi ITSELF throws
   invalid_argument on "abc". Don't pre-check; let it throw;
   catch and loop until a valid number arrives.
📥 INPUT: abc → 12a → 42
📤 OUTPUT: two "digits only!" retries, then "You typed: 42"
💡 HINT: catch (const invalid_argument&) — can live inside a loop.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.4 ⭐⭐
📋 Three-type dispatcher: throw int (fatal code), string (warning),
   runtime_error (operational). Catch each separately with distinct
   messages, prove order matters via comment for catch(...).
📤 OUTPUT: three different handlers fire correctly for 3 demos.
💡 HINT: Example 18.2's skeleton, your messages.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.5 ⭐⭐
📋 GradeValidator: class with setMarks(m) that throws
   out_of_range("marks must be 0-100") otherwise stores. Loop 3
   attempts catching per attempt; count successes.
📤 OUTPUT: successes count; invalid lines named with .what().
💡 HINT: Ch. 12 validation, upgraded from printing to throwing.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.6 ⭐⭐
📋 Load config: read "volume=NN" from settings.txt; manually throw
   runtime_error on missing file OR missing '=' OR non-numeric value.
   Catch with fallback volume=50. Three scenarios tested via
   comments on how to break each.
📤 OUTPUT: value or the fallback line explaining itself.
💡 HINT: Example 18.4 + string parsing from Ch. 17.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.7 ⭐⭐
📋 Depth-chain: f1→f2→f3 where f3 throws string("deep trouble").
   Only main catches. Add cout traces entering each function —
   show unwinding skips their exits.
📤 OUTPUT: enter lines, then catch — no exit lines.
💡 HINT: Example 18.5 starter template.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.8 ⭐⭐⭐
📋 Custom exception duo: OverdraftException AND SniperException(bad
   amount < 0) both extend runtime_error; Account.withdraw throws
   the right one; main catches OverdraftException FIRST then
   runtime_error parent — proving child-class catches still work
   through parent references.
📤 OUTPUT: distinct handling per disaster; parent catch demonstrated.
💡 HINT: matching is by assignability — derived matches base catch.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.9 ⭐⭐⭐
📋 resilientAvg(vector... arrays edition): ask N, read N numbers,
   but treat non-numeric tokens as EXCEPTIONS (stoi-based read);
   skip invalid ones, count successes, print average of the good ones
   or throw domain error "no valid numbers" if zero successes (and
   catch THAT in main).
📥 INPUT: 5 → 10 abc 20 x 30
📤 OUTPUT: 3 accepted → average 20; plus survival of bad tokens.
💡 HINT: nested try inside the input loop + outer try in main.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 18.10 ⭐⭐⭐
📋 ATM menu revisited (Ch. 5/6!) — but EVERY illegal move (bad PIN
   3×, bad menu choice, over-withdraw, negative amounts) is an
   exception type; a single main loop shows friendly recoveries and
   NEVER crashes. Balance persistence optional.
📤 OUTPUT: a full session transcript surviving every abuse thrown.
💡 HINT: your whole book so far, converging. Take your time —
   this is a mini-project, not a problem.
```

---

## 🎯 MINI CHALLENGE — THE UNCRASHABLE CALCULATOR 🛡️

Upgrade your Chapter 7 calculator into a fortress:

1. Input via string + `stoi`/`stod` under surveillance — `"abc"` can't kill it
2. Division by zero throws a **custom** `DivideByZeroException`
3. Menu choices outside 1-5 throw `out_of_range`, caught gently
4. Wrap each operation in its own try; the menu loop itself never dies
5. On EVERY exception, print a numbered incident log: `"⚠ Incident #3 caught: <message>"`
6. Brag at exit: `"Survived <K> invalid operations. Zero crashes. 🏆"`

Victory condition: deliberately attack your calculator with every bad input you can imagine — it yawns politely and continues. THAT is production-grade behavior. 💪

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 18.1**
```cpp
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;
double safeSqrt(double x) {
    if (x < 0) throw invalid_argument("negative input to sqrt");
    return sqrt(x);
}
int main() {
    for (double v : {9.0, -4.0}) {
        try { cout << safeSqrt(v) << "\n"; }
        catch (const invalid_argument& e) { cout << "Caught: " << e.what() << "\n"; }
    }
    cout << "alive ✓\n";
    return 0;
}
```
💡 `for (double v : {9.0, -4.0})` — range-for over an initializer list; neat demo tool.

**✅ SOLUTION 18.2**
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;
int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int i;
    cin >> i;
    try {
        if (i < 0 || i > 4) throw out_of_range(to_string(i));
        cout << "value: " << a[i];
    }
    catch (const out_of_range& e) {
        cout << "Index " << e.what() << " is out of bounds! Valid: 0-4";
    }
    return 0;
}
```
💡 **PRO TIP:** `vector`'s `.at(i)` does this throw natively — Chapter 19!

**✅ SOLUTION 18.3**
```cpp
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
int main() {
    string text;
    while (true) {
        getline(cin, text);
        try {
            int n = stoi(text);
            cout << "You typed: " << n;
            break;
        }
        catch (const invalid_argument&) { cout << "digits only!\n"; }
    }
    return 0;
}
```
⚠️ Watch it: `stoi("12a")` returns 12 without complaint (stops at 'a') — stricter check: verify the whole string consumed, or pre-validate digits like Example 18.2.

**✅ SOLUTION 18.4**
```cpp
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
void demo(int which) {
    if (which == 1) throw 500;
    if (which == 2) throw string("low disk space");
    throw runtime_error("network hiccup");
}
int main() {
    for (int i = 1; i <= 3; i++) {
        try { demo(i); }
        catch (int code)                { cout << "FATAL code " << code << "\n"; }
        catch (const string& msg)       { cout << "warning: " << msg << "\n"; }
        catch (const runtime_error& e)  { cout << "operational: " << e.what() << "\n"; }
        // catch(...) would go HERE — after all named types.
    }
    return 0;
}
```

**✅ SOLUTION 18.5**
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;
class GradeBook {
    int marks = -1;
public:
    void setMarks(int m) {
        if (m < 0 || m > 100) throw out_of_range("marks must be 0-100");
        marks = m;
    }
};
int main() {
    GradeBook g;
    int inputs[3] = {85, 150, 92}, ok = 0;
    for (int m : inputs) {
        try { g.setMarks(m); ok++; }
        catch (const out_of_range& e) { cout << "rejected " << m << ": " << e.what() << "\n"; }
    }
    cout << "accepted: " << ok << "/3";
    return 0;
}
```

**✅ SOLUTION 18.6**
```cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;
int loadVolume() {
    ifstream in("settings.txt");
    if (!in.is_open()) throw runtime_error("settings.txt missing");
    string line; getline(in, line);
    int e = line.find('=');
    if (e == (int)string::npos) throw runtime_error("bad format, no '=' found");
    try { return stoi(line.substr(e + 1)); }
    catch (const invalid_argument&) { throw runtime_error("volume not numeric"); }
}
int main() {
    int volume;
    try { volume = loadVolume(); }
    catch (const runtime_error& e) {
        cout << "using default volume=50 (" << e.what() << ")\n";
        volume = 50;
    }
    cout << "volume: " << volume;
    return 0;
}
```
Test scenarios: delete the file; store "volume"; store "volume=loud". Each break is named by the thrown message. 🎯

**✅ SOLUTION 18.7**
```cpp
#include <iostream>
#include <string>
using namespace std;
void f3() { cout << "f3 enter\n"; throw string("deep trouble"); cout << "f3 exit\n"; }
void f2() { cout << "f2 enter\n"; f3(); cout << "f2 exit\n"; }
void f1() { cout << "f1 enter\n"; f2(); cout << "f1 exit\n"; }
int main() {
    try { f1(); }
    catch (const string& s) { cout << "main caught: " << s << "\n"; }
    return 0;
}
```

**✅ SOLUTION 18.8**
```cpp
#include <iostream>
#include <stdexcept>
using namespace std;
class OverdraftException : public runtime_error {
public: OverdraftException(const string& m) : runtime_error(m) { }
};
class BadAmountException : public runtime_error {
public: BadAmountException(const string& m) : runtime_error(m) { }
};
class Account {
    double balance;
public:
    Account(double b) : balance(b) { }
    void withdraw(double x) {
        if (x < 0)        throw BadAmountException("negative amount");
        if (x > balance)  throw OverdraftException("exceeds balance");
        balance -= x; cout << "ok, balance " << balance << "\n";
    }
};
int main() {
    Account a(300);
    for (double x : {100.0, 500.0, -20.0}) {
        try { a.withdraw(x); }
        catch (const OverdraftException& e) { cout << "OVERDRAFT: " << e.what() << "\n"; }
        catch (const runtime_error& e)      { cout << "GENERIC & family: " << e.what() << "\n"; }
    }
    return 0;
}
```
💡 The BadAmount caught by the *parent* catch — proof that derived exceptions match base-class catches.

**✅ SOLUTION 18.9**
```cpp
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
int main() {
    int n;
    cin >> n;

    int sum = 0, good = 0;
    for (int i = 0; i < n; i++) {
        string tok;
        cin >> tok;
        try { sum += stoi(tok); good++; }
        catch (const invalid_argument&) { cout << "  skip '" << tok << "'\n"; }
    }

    try {
        if (good == 0) throw runtime_error("no valid numbers");
        cout << good << " accepted, average = " << (double)sum / good;
    }
    catch (const runtime_error& e) { cout << "fatal: " << e.what(); }
    return 0;
}
```

**✅ SOLUTION 18.10 / MINI CHALLENGE (compact merged example)**
```cpp
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class CalcError : public runtime_error {
public: CalcError(const string& m) : runtime_error(m) { }
};

int incidents = 0;

double readNumber(const string& label) {
    string s;
    cout << label;
    getline(cin, s);
    try { return stod(s); }
    catch (...) { throw CalcError("'" + s + "' isn't a number"); }
}

int main() {
    int choice = 0;
    do {
        cout << "\n1.Add 2.Sub 3.Mul 4.Div 5.Exit\n> ";
        string line;
        getline(cin, line);
        try {
            choice = stoi(line);
            if (choice < 1 || choice > 5) throw out_of_range("menu");
            if (choice == 5) break;

            double a = readNumber("a: ");
            double b = readNumber("b: ");
            switch (choice) {
                case 1: cout << "= " << a + b << "\n"; break;
                case 2: cout << "= " << a - b << "\n"; break;
                case 3: cout << "= " << a * b << "\n"; break;
                case 4:
                    if (b == 0) throw CalcError("division by zero");
                    cout << "= " << a / b << "\n"; break;
            }
        }
        catch (...) {
            incidents++;
            cout << "⚠ Incident #" << incidents << ": bad input, recovered.\n";
        }
    } while (true);

    cout << "Survived " << incidents << " invalid operations. Zero crashes. 🏆\n";
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ `try` = risky zone, `throw` = fire alarm, `catch` = rescue team — program lives on
- ✓ Catch by `const Type&`; specific types first, `catch(...)` last
- ✓ Throw objects (`runtime_error` + children) — `.what()` speaks; custom classes name domain disasters
- ✓ Exceptions travel up call chains cleanly; destructors still run (RAII keeps you safe)
- ✓ `if` handles the EXPECTED; exceptions handle the EXCEPTIONAL — don't swap their jobs

**📚 Keywords learned:** exception, `try`, `throw`, `catch`, `catch(...)`, stack unwinding, `runtime_error`, `invalid_argument`, `out_of_range`, `.what()`, custom exception, exception safety

**🔗 Next chapter preview:** Chapter 19 — **STL**: ready-made superpowers. `vector` (arrays that grow), `map` (dictionaries!), `set`, `stack`, `queue`, plus `sort()` in ONE line. Everything you hand-built in Chapters 8 & 20 — already perfected and waiting for you. 📦

*Your programs can now take a punch. Time to give them a toolbox.* 🧰

---

**⬅️ [Chapter 17](chapter-17-file-handling.md) | [🏠 Home](README.md) | [Chapter 19 ➡️](chapter-19-stl.md)**
