# CHAPTER 16 — FRIEND FUNCTIONS & STATIC MEMBERS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A friend gets a key to your house.
 A static member is the family photo —
 one copy, shared by everyone."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 15](chapter-15-polymorphism.md) | [🏠 Home](README.md) | [Chapter 17 ➡️](chapter-17-file-handling.md)**

---

## 📖 CHAPTER OPENING

Your house has locked rooms (private members), but your best friend gets a spare key. And some things — like the family photo on the wall — don't belong to any single sibling; there's exactly one copy, shared by all. C++ has both: **`friend`** grants key access to trusted outsiders; **`static`** members belong to the class itself, shared by every object ever created.

### What you will learn:
- `friend` functions — outsiders with trusted access
- `friend` classes — whole trusted families
- When (and when NOT) to use friends
- `static` data members — one variable shared by all objects
- `static` member functions — tools you call without any object
- The **Singleton** pattern — the class that allows exactly ONE object

### Why this chapter matters:
`friend` is surgical trust used by operators like `<<` for printing objects; `static` powers counters, registries, shared settings, and utility classes. Together they complete your OOP toolbox before we dive into Part 4.

---

## 🔍 CONCEPT EXPLANATION

### What is a friend?

A **friend function** is a *non-member* function that a class personally trusts with access to its private/protected members.

```cpp
class Box {
    int secret = 42;
    friend void spy(Box b);        // declaration grants the trust
};
void spy(Box b) { cout << b.secret; }   // legal — friend has the key
```

### When is it actually right to use friend?

Rarely, and deliberately: when an operation genuinely involves **two** classes' internals symmetrically (like `operator<<` printing your class, or comparing two different classes). It's a scalpel, not a hammer.

### What is a static member?

```cpp
class Student {
    static int total;             // ONE box for the whole class — not per object
};
```

- A **static data member** exists once, regardless of how many objects exist (even zero!). All objects see the same one.
- A **static member function** runs without any object (`Student::getTotal()`) — so it can touch only static members (no `this`, no normal member data).

---

## 📝 SYNTAX BOX

```cpp
class Counter {
private:
    int id;                                   // normal: each object has its own
    static int total;                         // static: ONE shared by everyone

    friend void audit(const Counter& c);      // trusted outsider function
    friend class Inspector;                   // trusted outsider CLASS

public:
    Counter() { id = ++total; }               // every birth bumps the shared counter

    static int getTotal() {                   // callable as Counter::getTotal()
        return total;                         // ✅ static fn → static data only
        // return id;                         // ❌ no 'this' — can't touch members!
    }
};

// ⚠️ static data members get their ONE definition OUTSIDE the class:
int Counter::total = 0;                       // exactly once, outside, no 'static'

void audit(const Counter& c) {                // friend → can read c.id (private!)
    cout << "auditing counter #" << c.id << "\n";
}

class Inspector {                             // friend class → full access
public:
    void peek(const Counter& c) { cout << "deep id: " << c.id << "\n"; }
};
```

| Tool | Grasp |
|---|---|
| `friend` function | trusted non-member; NOT a member; no `this` |
| `friend` class | all its functions gain key access |
| static data | one copy per class; define outside once |
| static function | called via `Class::f()`; static-only access |

---

## 💻 EXAMPLE CODES

### Example 16.1 — A Friend at the Door

```cpp
// ============================================
// Example 16.1: friend Function Reading Private Data
// ============================================
// Concepts used: friend declaration, non-member access
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Diary {
    string secretEntry;                 // 🔒 strictly private
public:
    Diary(string text) : secretEntry(text) { }

    friend void trustedReader(const Diary& d);   // 🔑 hand over ONE spare key
};

void trustedReader(const Diary& d) {    // NOT a member function!
    cout << "Friend reads: \"" << d.secretEntry << "\"\n";   // legal!
}

int main() {

    Diary pages("I finally understand pointers.");
    trustedReader(pages);               // friend granted entry

    // cout << pages.secretEntry;       // ❌ main() is not a friend — stays locked
    return 0;
}
/*
OUTPUT:
Friend reads: "I finally understand pointers."

EXPLANATION:
Only functions NAMED in friend declarations get access. strangers
(main) stay locked out. Friendship is given BY the class — never
taken. Also note: friendship is not mutual and not inherited —
your friend's friends are NOT your friends.
*/
```

**What happened here?** One explicit key, given by the class, to one function. Nothing else changed about privacy.

---

### Example 16.2 — The Classic: friend `operator<<` (Print Your Objects Like Built-ins)

```cpp
// ============================================
// Example 16.2: cout << myObject — How The Pros Print
// ============================================
// Concepts used: friend operator<<, ostream&, chaining
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Student {
    string name;
    double gpa;
public:
    Student(string n, double g) : name(n), gpa(g) { }

    // grants access so the operator can read name & gpa:
    friend ostream& operator<<(ostream& out, const Student& s);
};

// return ostream& so chains (cout << a << b) keep working:
ostream& operator<<(ostream& out, const Student& s) {
    out << s.name << " (GPA " << s.gpa << ")";
    return out;
}

int main() {

    Student a("Hira", 3.8), b("Daniyal", 3.4);

    cout << a << endl;               // cout is an ostream — OUR function runs
    cout << a << " and " << b << endl;   // chaining works via the returned ostream&

    return 0;
}
/*
OUTPUT:
Hira (GPA 3.8)
Hira (GPA 3.8) and Daniyal (GPA 3.4)

EXPLANATION:
cout << s  really means  operator<<(cout, s) — a FREE function
(can't be a member: the left side is cout, not a Student!).
Since it's free, it needs friend to touch privates. This is THE
#1 legitimate everyday use of friend in real codebases.
*/
```

**What happened here?** Your custom types now print exactly like `int` does. This pattern appears in virtually every professional C++ class.

---

### Example 16.3 — Static Data: The Class-Wide Counter

```cpp
// ============================================
// Example 16.3: How Many Students Exist Right Now?
// ============================================
// Concepts used: static data member, shared across objects, outside definition
// ============================================

#include <iostream>
#include <string>
using namespace std;

class StudentRegistry {
    string name;
    static int alive;                   // ONE counter for the whole class
public:
    StudentRegistry(string n) : name(n) {
        alive++;
        cout << "➕ " << name << " enrolled. Total alive: " << alive << "\n";
    }
    ~StudentRegistry() {
        alive--;
        cout << "➖ " << name << " left. Total alive: " << alive << "\n";
    }
    static int getAlive() { return alive; }   // callable with no object
};

int StudentRegistry::alive = 0;              // the ONE outside definition — required!

int main() {

    cout << "Start: " << StudentRegistry::getAlive() << "\n";   // static fn, no object!

    {
        StudentRegistry a("Ali");
        StudentRegistry b("Sara");
        {
            StudentRegistry c("Omar");
        }                                // Omar leaves when scope ends
    }                                    // Sara, Ali leave (reverse order)

    cout << "End: " << StudentRegistry::getAlive() << "\n";
    return 0;
}
/*
OUTPUT:
Start: 0
➕ Ali enrolled. Total alive: 1
➕ Sara enrolled. Total alive: 2
➕ Omar enrolled. Total alive: 3
➖ Omar left. Total alive: 2
➖ Sara left. Total alive: 1
➖ Ali left. Total alive: 0
End: 0

EXPLANATION:
alive exists ONCE, outside any object — you saw it work before ANY
Student existed (Start: 0). Perfect use cases: instance counters,
shared configuration, registries. And the ctors/dtors from Ch. 13
keep it accurate automatically — even through exceptions.
*/
```

**What happened here?** Static + constructors + destructors = a self-maintaining census. Notice you never wrote bookkeeping in `main` — the class manages its own population.

---

### Example 16.4 — Static Member Functions: Utility Classes

```cpp
// ============================================
// Example 16.4: MathTools — A Toolbox That Needs No Object
// ============================================
// Concepts used: static member functions, Class::function() call style
// ============================================

#include <iostream>
using namespace std;

class MathTools {
public:                                 // no objects needed — pure toolbox
    static double circleArea(double r) { return 3.14159 * r * r; }
    static int    clamp(int v, int lo, int hi) {
        if (v < lo) return lo;
        if (v > hi) return hi;
        return v;
    }
    static long long factorial(int n) {
        long long r = 1;
        for (int i = 2; i <= n; i++) r *= i;
        return r;
    }
private:
    MathTools() { }                     // ⚠️ private ctor: nobody can make objects!
};

int main() {

    cout << "Circle r=7:      " << MathTools::circleArea(7)    << "\n";
    cout << "clamp(150,0,100):" << MathTools::clamp(150, 0, 100) << "\n";
    cout << "10!:             " << MathTools::factorial(10)    << "\n";

    // MathTools t;                    // ❌ ERROR — ctor is private, by design
    return 0;
}
/*
OUTPUT:
Circle r=7:      153.938
clamp(150,0,100):100
10!:             3628800

EXPLANATION:
static functions are called on the CLASS, not objects — ideal for
pure utility. The private constructor blocks pointless instantiation
("why would you make an instance of a toolbox?"). This is how
libraries present their helper namespaces.
*/
```

**What happened here?** Some classes aren't "things" — they're organized collections of tools. `static` functions + private ctor = the utility-class idiom.

---

### Example 16.5 — The Singleton: Exactly One, By Force

```cpp
// ============================================
// Example 16.5: GameSettings — One Instance To Rule It
// ============================================
// Concepts used: Singleton pattern (private ctor + static getInstance)
// ============================================

#include <iostream>
#include <string>
using namespace std;

class GameSettings {
    string difficulty = "Normal";
    int    volume     = 70;

    GameSettings() { }                  // 🔒 private ctor: main can't 'new' us

public:
    // the ONE door to the ONE object (static function, static local):
    static GameSettings& getInstance() {
        static GameSettings instance;   // created exactly once, first time here
        return instance;
    }

    // block copies too (C++11 delete syntax — declares "forbidden"):
    GameSettings(const GameSettings&) = delete;

    void setDifficulty(const string& d) { difficulty = d; }
    void setVolume(int v)              { volume = v; }
    void show() {
        cout << "Difficulty: " << difficulty << ", Volume: " << volume << "%\n";
    }
};

int main() {

    // GameSettings g;                 // ❌ private ctor — no civilians
    GameSettings& menu = GameSettings::getInstance();
    menu.show();                        // defaults

    menu.setDifficulty("Hard");

    // somewhere far away in the game engine:
    GameSettings& engine = GameSettings::getInstance();
    engine.show();                      // "Hard" — SAME object, no duplicates

    cout << (&menu == &engine ? "Same instance ✓\n" : "Duplicates! ✗\n");
    return 0;
}
/*
OUTPUT:
Difficulty: Normal, Volume: 70%
Difficulty: Hard, Volume: 70%
Same instance ✓

EXPLANATION:
Private ctor + a static accessor returning the ONLY static local
object = one instance globally, enforced by the language itself.
Perfect for settings, loggers, connection managers — things that
must not exist twice. (C++11+ guarantees thread-safe creation of
that local static, too.)
*/
```

**What happened here?** Every corner of the program shares one source of truth, and duplication is *uncompileable*, not just discouraged. That's design by grammar.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Treating friend functions as members (using `this`/object-dot)**
```cpp
void operator<<(ostream& out, const Student& s) {
    cout << this->name;      // ❌ friends aren't members — there IS no 'this'
}
```
✅ **Fix:** Access through the parameter: `s.name`. Friends are outsiders with keys, not residents.

**❌ Mistake 2 — Forgetting the outside definition of a static member**
```cpp
class X { static int count; };       // declared only
// ...and X::count gets used...
```
Linker says: `undefined reference to 'X::count'`
✅ **Fix:** `int X::count = 0;` once in a `.cpp` source file (or C++17 `inline static int count = 0;` inside the class). Note: the error is a **linker** error, not a compile error — Chapter 0's reading skills apply!

**❌ Mistake 3 — Touching instance members from a static function**
```cpp
static void report() { cout << id; }  // ❌ which object's id??
```
✅ **Fix:** Static functions see static members only. If you need instance data, make it a normal function — or pass an object in: `static void f(Counter& c) { cout << c.id; }` (works with friend, or if public).

**❌ Mistake 4 — Sprinkling friend everywhere "for convenience"**
```cpp
class A { friend class B; friend class C; friend class D; ... };
```
✅ **Fix:** Every friendship pokes a hole in encapsulation. If everything's a friend, nothing is private. Prefer getters; friend is for the rare symmetric partner (like `operator<<`).

**❌ Mistake 5 — Assuming friendship flows downhill/uphill**
```cpp
class Parent { friend class Spy; };
class Child : public Parent { };  // Spy is NOT Child's friend automatically!
```
✅ **Fix:** Friendship is declared per-class, isn't inherited, isn't mutual, isn't transitive. ("My dad's friend isn't my friend.")

**❌ Mistake 6 — Singleton copies slipping through**
```cpp
GameSettings copy = GameSettings::getInstance();   // makes a COPY — defeats it!
```
✅ **Fix:** Delete the copy constructor (`= delete`, as in Example 16.5) and always receive with `&`: `GameSettings& s = getInstance();`

---

## 🧠 CONCEPT SUMMARY TABLE

| Feature | Declared | Access power | Call/use |
|---|---|---|---|
| `friend` function | inside the class | full private/protected access | like any free function |
| `friend` class | inside the class | all its functions trusted | via its objects |
| static data member | `static int x;` (+ outside definition) | shared by ALL objects | `Class::x` or any object |
| static member fn | `static type f()` | static members only (no this) | `Class::f()` — no object |
| Singleton | private ctor + `static T& getInstance()` | exactly one instance | `Class::getInstance()` |
| `= delete` | on a function declaration | makes calling it a compile error | safety tool |

**When to use what:** printing/comparing across classes → friend. Census/registry/shared config → static data. Toolboxes → static functions. One-of-a-kind managers → Singleton.

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.1 ⭐
📋 class Wallet (private cash). Grant a friend function peek(Wallet)
   that prints the balance. Demonstrate both access and main's
   refusal to compile direct access (commented).
📤 OUTPUT: "friend peek: Rs. 2500"  (+ comment proof of privacy)
💡 HINT: friend void peek(const Wallet& w);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.2 ⭐
📋 class Point(x,y) with friend operator<< printing "(x, y)".
   Then cout << two points in ONE chain.
📤 OUTPUT: (1, 2) meets (3, 4)
💡 HINT: return the ostream& for chaining.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.3 ⭐
📋 class Car with static int produced (count+ in every ctor).
   Make 3 cars; print Car::getProduced().
📤 OUTPUT: 3
💡 HINT: static function reads static counter; define outside.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.4 ⭐⭐
📋 class TempLog (private lastReading). friend class Auditor with
   methods show(c) and reset(c). Show the auditor class accessing
   privates while main cannot.
📤 OUTPUT: Auditor prints and zeroes readings.
💡 HINT: friend class Auditor;  — ALL Auditor methods get keys.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.5 ⭐⭐
📋 class BankAccount with static double interestRate (shared!) +
   static setRate(x). Show changing the rate once affects all
   accounts' computed interest.
📥 SAMPLE: two accounts 10000 & 20000; rate 5 → 6
📤 OUTPUT: interest switches from 500/1000 to 600/1200 for BOTH.
💡 HINT: double X::interestRate = 5.0; outside.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.6 ⭐⭐
📋 Utility class StringTools (all static): shout(s) uppercases,
   countVowels(s), isEmpty(s). block instantiation privately.
📤 OUTPUT: demo of all 3 functions via Class:: calls.
💡 HINT: private ctor kills object creation.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.7 ⭐⭐
📋 friend comparison across DIFFERENT classes: class Cat (whiskers)
   and class Dog (fangs) share a friend void compareSharp(Cat c,
   Dog d) printing who's pointier. Why was friend necessary here?
   (answer in comment)
📤 OUTPUT: verdict line + explained comment.
💡 HINT: A member can access ITS class only; this reads TWO privates.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.8 ⭐⭐⭐
📋 class Logger — Singleton with log(msg) storing up to 50 messages
   (static vector-like array) and dump() printing all. Prove both
   "modules" (two functions in main) share the same log history.
📤 OUTPUT: second function's dump() shows first's entries.
💡 HINT: getInstance() shared; state lives in the one instance.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.9 ⭐⭐⭐
📋 class Stadium: static currentCapacity, static sellTickets(n) &
   refundTickets(n) with guards (0 ≤ sold ≤ capacity). Multiple
   "gates" (functions) call the statics; print ledger after each.
📤 OUTPUT: consistent shared totals no matter who sells.
💡 HINT: statics are the single source of truth; guards inside them.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 16.10 ⭐⭐⭐
📋 class Book with id auto-assigned from static nextId (1,2,3...)
   PLUS friend operator<< displaying "Bk#<id>: <title>". Create 4
   books across 2 scopes (some dying); show ids keep incrementing
   while a separate static alive counter goes up and down.
📤 OUTPUT: ids 1..4 forever unique; alive tracks births/deaths.
💡 HINT: two different statics: nextId (never--) and alive (++/--).
```

---

## 🎯 MINI CHALLENGE — COMPANY REGISTRY 🏢

Build a `class Employee` system:

1. Each `Employee` gets an auto-ID from a static counter and has private `name` + `salary`
2. Static members: `totalEmployees` (alive tracker via ctor/dtor) and `payrollTotal` (sum paid out — updated on salary changes)
3. A `friend` function `auditSalary(Employee&)` that prints the private salary (HR's master key)
4. A `friend class TaxOfficer` that can read salary AND apply a 10% deduction via a called method
5. Static function `Employee::stats()` printing headcount + total payroll — callable with ZERO employees existing

Demo in `main`: 3 hires, one resignation (scoped death), an audit, a tax visit, and stats at start & end. When your registry balances perfectly to the last rupee — the statics are honest — you're done. 📊

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 16.1**
```cpp
#include <iostream>
using namespace std;
class Wallet {
    int cash = 2500;
    friend void peek(const Wallet& w);
};
void peek(const Wallet& w) { cout << "friend peek: Rs. " << w.cash << "\n"; }

int main() {
    Wallet w;
    peek(w);
    // cout << w.cash;      // ❌ 'cash' is private within this context
    return 0;
}
```

**✅ SOLUTION 16.2**
```cpp
#include <iostream>
using namespace std;
class Point {
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) { }
    friend ostream& operator<<(ostream& out, const Point& p);
};
ostream& operator<<(ostream& out, const Point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
int main() {
    Point a(1, 2), b(3, 4);
    cout << a << " meets " << b << "\n";
    return 0;
}
```

**✅ SOLUTION 16.3**
```cpp
#include <iostream>
using namespace std;
class Car {
    static int produced;
public:
    Car() { produced++; }
    static int getProduced() { return produced; }
};
int Car::produced = 0;

int main() {
    Car a, b, c;
    cout << "Produced: " << Car::getProduced() << "\n";   // 3
    return 0;
}
```

**✅ SOLUTION 16.4**
```cpp
#include <iostream>
using namespace std;
class TempLog {
    double lastReading = 36.8;
    friend class Auditor;                     // ALL Auditor methods trusted
};
class Auditor {
public:
    void show(TempLog& t)  { cout << "read: " << t.lastReading << "\n"; }
    void reset(TempLog& t) { t.lastReading = 0; cout << "reset done\n"; }
};
int main() {
    TempLog t; Auditor a;
    a.show(t); a.reset(t); a.show(t);
    // cout << t.lastReading;                // ❌ main isn't trusted
    return 0;
}
```

**✅ SOLUTION 16.5**
```cpp
#include <iostream>
using namespace std;
class BankAccount {
    double balance;
    static double interestRate;               // percent, ONE for the bank
public:
    BankAccount(double b) : balance(b) { }
    static void setRate(double r) { interestRate = r; }
    double interest() { return balance * interestRate / 100; }
};
double BankAccount::interestRate = 5.0;

int main() {
    BankAccount a(10000), b(20000);
    cout << a.interest() << " / " << b.interest() << "\n";   // 500 / 1000
    BankAccount::setRate(6);
    cout << a.interest() << " / " << b.interest() << "\n";   // 600 / 1200
    return 0;
}
```
💡 **PRO TIP:** Shared statics beat global variables: they're named (`BankAccount::`), scoped, and modifiable through guarded static setters.

**✅ SOLUTION 16.6**
```cpp
#include <iostream>
#include <string>
using namespace std;
class StringTools {
    StringTools() { }                          // private: no instances
public:
    static string shout(string s) {
        for (auto& c : s) c = toupper(c);
        return s;
    }
    static int countVowels(string s) {
        int n = 0;
        for (char c : s) { c = tolower(c);
            if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') n++; }
        return n;
    }
    static bool isEmpty(const string& s) { return s.empty(); }
};
int main() {
    cout << StringTools::shout("hello") << "\n";        // HELLO
    cout << StringTools::countVowels("programming") << "\n"; // 3
    cout << StringTools::isEmpty("") << "\n";                // 1
    return 0;
}
```
💡 `for (auto& c : s)` — range-for by reference so edits land in s (Ch. 19 deep-dive soon!)

**✅ SOLUTION 16.7**
```cpp
#include <iostream>
using namespace std;
class Dog;                                     // forward declaration needed
class Cat {
    int whiskers;
public: Cat(int w) : whiskers(w) { }
    friend void compareSharp(Cat c, Dog d);    // friend needs Dog known later
};
class Dog {
    int fangs;
public: Dog(int f) : fangs(f) { }
    friend void compareSharp(Cat c, Dog d);
};
void compareSharp(Cat c, Dog d) {
    // NEEDED friend: ONE function must read the PRIVATES of TWO classes —
    // a member function of either could reach only its own.
    cout << (c.whiskers > d.fangs ? "Cat is pointier 🐱\n" : "Dog is pointier 🐶\n");
}
int main() {
    Cat kitty(6); Dog rex(10);
    compareSharp(kitty, rex);
    return 0;
}
```
💡 **PRO TIP:** Forward-declare (`class Dog;`) so Cat's friend line can mention Dog before Dog is defined.

**✅ SOLUTION 16.8**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Logger {
    string history[50];
    int    count = 0;
    Logger() { }
public:
    static Logger& getInstance() { static Logger L; return L; }
    Logger(const Logger&) = delete;
    void log(const string& msg) { if (count < 50) history[count++] = msg; }
    void dump() {
        cout << "--- LOG ---\n";
        for (int i = 0; i < count; i++) cout << i + 1 << ". " << history[i] << "\n";
    }
};
void moduleA() { Logger::getInstance().log("A started"); }
void moduleB() {
    Logger::getInstance().log("B finished");
    Logger::getInstance().dump();        // shows BOTH entries — shared truth
}
int main() { moduleA(); moduleB(); return 0; }
```

**✅ SOLUTION 16.9**
```cpp
#include <iostream>
using namespace std;
class Stadium {
    static int sold;
    static const int CAPACITY = 3;
public:
    static bool sellTickets(int n) {
        if (n < 0 || sold + n > CAPACITY) return false;
        sold += n; return true;
    }
    static bool refundTickets(int n) {
        if (n < 0 || n > sold) return false;
        sold -= n; return true;
    }
    static void ledger() { cout << "Sold: " << sold << "/" << CAPACITY << "\n"; }
};
int Stadium::sold = 0;

void northGate() {
    if (Stadium::sellTickets(2)) cout << "North sold 2\n";
}
void southGate() {
    if (!Stadium::sellTickets(5)) cout << "South refused 5 (capacity!)\n";
}
int main() {
    northGate();  Stadium::ledger();        // 2/3
    southGate();  Stadium::ledger();        // 2/3
    if (Stadium::refundTickets(1)) cout << "1 refund\n";
    Stadium::ledger();                      // 1/3
    return 0;
}
```

**✅ SOLUTION 16.10**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Book {
    int id; string title;
    static int nextId, alive;
public:
    Book(string t) : title(t) { id = nextId++; alive++; }
    ~Book() { alive--; }
    static void stats() {
        cout << "issued: " << nextId - 1 << ", alive: " << alive << "\n";
    }
    friend ostream& operator<<(ostream& out, const Book& b) {
        return out << "Bk#" << b.id << ": " << b.title;
    }
};
int Book::nextId = 1, Book::alive = 0;

int main() {
    Book a("Novel");
    {
        Book b("Poetry"), c("Manual");
    }                                     // 2 & 3 die — alive shrinks
    Book d("Guide");
    cout << a << "\n" << d << "\n";       // ids 1 & 4 — never reused
    Book::stats();                        // issued 4, alive 2
    return 0;
}
```

**✅ MINI CHALLENGE (core sketch)**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Employee {
    int id; string name; double salary;
    static int nextId, totalEmployees;
    static double payroll;
    friend void auditSalary(const Employee& e);
    friend class TaxOfficer;
public:
    Employee(string n, double s) : name(n), salary(s) {
        id = nextId++; totalEmployees++; payroll += salary;
    }
    ~Employee() { totalEmployees--; payroll -= salary; }
    static void stats() {
        cout << "headcount: " << totalEmployees << ", payroll: "
             << payroll << "\n";
    }
};
int Employee::nextId = 1, Employee::totalEmployees = 0;
double Employee::payroll = 0;

void auditSalary(const Employee& e) {
    cout << "AUDIT — " << e.name << " earns Rs. " << e.salary << "\n";
}
class TaxOfficer {
public:
    void visit(Employee& e) { e.salary *= 0.9; Employee::payroll /* note:
        statics edited via methods would need a setter; keep payroll
        consistent by updating here as friend */ -= e.salary * 0.1;
        cout << "Tax applied.\n"; }
};
int main() {
    Employee::stats();                    // 0 / 0 — usable pre-objects!
    {
        Employee a("Hina", 60000), b("Shahid", 75000);
        auditSalary(a);
        TaxOfficer().visit(a);
        Employee::stats();
    }
    Employee::stats();
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ `friend` = one class-issued key for a named outsider (function or class); overuse kills encapsulation — the `operator<<` print pattern is its star use
- ✓ static data = ONE copy shared by all objects; define it outside the class once (linker errors mean you forgot)
- ✓ static functions run object-less (`Class::f()`) and see static members only — no `this`
- ✓ Singleton = private ctor + `= delete`d copy + `static T& getInstance()` — ONE instance enforced by the compiler
- ✓ Friendship is personal: not inherited, not mutual, not transitive

**📚 Keywords learned:** friend function, friend class, static data member, static member function, class-level sharing, `= delete`, Singleton pattern, forward declaration

**🔗 Next chapter preview:** **PART 4 — ADVANCED CONCEPTS**. Chapter 17: **File Handling** — everything you've built dies when the program closes... until now. Save your students, accounts, and game scores to DISK, and programs finally remember. 💾

*The OOP toolbox is full. Time to make your programs immortal.* 📦

---

**⬅️ [Chapter 15](chapter-15-polymorphism.md) | [🏠 Home](README.md) | [Chapter 17 ➡️](chapter-17-file-handling.md)**
