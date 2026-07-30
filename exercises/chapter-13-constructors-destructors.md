# CHAPTER 13 — CONSTRUCTORS & DESTRUCTORS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A constructor is a birth certificate.
 A destructor is the farewell speech
 that tidies up the room."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 12](chapter-12-classes-objects.md) | [🏠 Home](README.md) | [Chapter 14 ➡️](chapter-14-inheritance.md)**

---

## 📖 CHAPTER OPENING

In Chapter 12, every object was born "blank" — `Student s; s.set(...); s.setName(...);` — three more lines just to make it someone. A baby shouldn't need paperwork after birth to have a name! **Constructors** name your objects *at birth*, in the same line they're created. And when an object's life ends, the **destructor** runs its farewell routine automatically — closing files, freeing memory, logging out.

### What you will learn:
- What constructors are and why they run automatically
- Default vs. parameterized constructors; overloading them
- The copy constructor — birth by photocopy
- Constructor initializer lists (the professional syntax)
- Destructors: `~Name()`, when they fire, and the birth/death order
- Constructor vs. ordinary function — the differences that matter

### Why this chapter matters:
"Object born in a broken state" is a top source of real-world bugs. Constructors make broken births *impossible*. Destructors make cleanup *unforgettable* (because you can't forget what runs automatically).

---

## 🔍 CONCEPT EXPLANATION

### What is a constructor?

A **constructor** is a special member function that runs **automatically the moment an object is created**. Rules that make it special:

1. Its name **is exactly the class name**
2. It has **no return type** — not even `void`
3. It's usually `public`
4. It runs **once per object**, unskippably

### Why do we use them?

```cpp
// BEFORE (Ch. 12): born blank, configured later — broken state in between
Student s;
s.setInfo("Ali", 101);

// AFTER (Ch. 13): born complete — no in-between exists
Student s("Ali", 101);
```

**A class that can't be born broken is a class that can never *be* broken.** That's the philosophy.

### And destructors?

A **destructor** runs automatically when an object's life **ends** — leaving a `{ }` scope, program finishing, or `delete` on a dynamic object. Its name is `~ClassName()`, no parameters, no return type.

### How does the computer handle them?

The compiler inserts calls for you: where an object is born → call constructor; where its scope ends → call destructor. In reverse order for multiple objects: **last born, first to go** — like a stack of plates (kitchen rule: the last plate placed is the first one washed).

---

## 📝 SYNTAX BOX

```cpp
class Student {
private:
    string name;
    int    roll;
    const string SCHOOL = "City High";        // const member!

public:
    // 1️⃣ DEFAULT constructor — no parameters, auto-runs on  Student s;
    Student() {
        name = "Unnamed";
        roll = 0;
        cout << "A student was born.\n";
    }

    // 2️⃣ PARAMETERIZED constructor — runs on  Student s("Ali", 101);
    Student(string n, int r) {
        name = n;
        roll = r;
    }

    // 3️⃣ Same thing with the pro INITIALIZER LIST (const members NEED this)
    // Student(string n, int r) : name(n), roll(r), SCHOOL("City High") { }

    // 4️⃣ COPY constructor — runs on  Student b(a);  (birth by photocopy)
    Student(const Student& other) {
        name = other.name;
        roll = other.roll;
        cout << "Copied student " << name << "\n";
    }

    // 5️⃣ DESTRUCTOR — runs when the object dies. One per class.
    ~Student() {
        cout << name << " has left the building.\n";
    }

    void show() { cout << name << " (#" << roll << ")\n"; }
};
```

| Form | Birth line | Use |
|---|---|---|
| `Student()` | `Student s;` | sensible defaults |
| `Student(string,int)` | `Student s("Ali",101);` | fully specified at birth |
| `Student(const Student&)` | `Student b(a);` | duplicating objects |
| `~Student()` | *(automatic)* | cleanup on death |

🔥 **REMEMBER:** If you write ANY constructor, C++ stops giving you the free default one. Want `Student s;` to still work? Write `Student() { }` yourself.

---

## 💻 EXAMPLE CODES

### Example 13.1 — Hello, Constructor

```cpp
// ============================================
// Example 13.1: Watching a Constructor Fire Automatically
// ============================================
// Concepts used: default constructor, auto-calls on birth
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Rocket {
private:
    int fuel;
public:
    Rocket() {                          // ← class name, no return type
        fuel = 100;                     //    born READY, never born empty
        cout << "🚀 Rocket built! Fuel at " << fuel << "%\n";
    }

    void launch()  {
        fuel -= 20;
        cout << "Liftoff! Fuel left: " << fuel << "%\n";
    }
};

int main() {

    cout << "Before birth...\n";
    Rocket falcon;                      // constructor runs HERE — no call needed!
    cout << "After birth...\n";

    falcon.launch();
    falcon.launch();

    Rocket heavy[2];                    // array → constructor runs TWICE

    return 0;
}
/*
OUTPUT:
Before birth...
🚀 Rocket built! Fuel at 100%
After birth...
Liftoff! Fuel left: 80%
Liftoff! Fuel left: 60%
🚀 Rocket built! Fuel at 100%
🚀 Rocket built! Fuel at 100%

EXPLANATION:
Rocket falcon; LOOKS like a declaration, secretly calls Rocket().
fuel was NEVER garbage — not even for one microsecond. Arrays of
objects call the constructor once per element.
*/
```

**What happened here?** Birth and setup fused into a single instant. `fuel` can never be garbage because no moment exists where the object lives but the constructor hasn't finished.

---

### Example 13.2 — Parameterized + Overloading: Birth Certificates of Every Kind

```cpp
// ============================================
// Example 13.2: Many Ways to Be Born
// ============================================
// Concepts used: parameterized ctors, constructor overloading, defaults
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int    roll;
    double marks;
public:
    Student() {                                  // version ① no info at all
        name = "Unnamed"; roll = 0; marks = 0.0;
    }

    Student(string n) {                          // version ② name only
        name = n; roll = 0; marks = 0.0;
    }

    Student(string n, int r, double m) {         // version ③ full record
        name = n; roll = r; marks = m;
    }

    // Alternative style: ONE constructor with default values covers all:
    // Student(string n = "Unnamed", int r = 0, double m = 0.0)
    //     : name(n), roll(r), marks(m) { }

    void show() {
        cout << name << " | roll " << roll << " | marks " << marks << "\n";
    }
};

int main() {

    Student a;                    cout << "a: "; a.show();   // ① fires
    Student b("Sara");            cout << "b: "; b.show();   // ② fires
    Student c("Omar", 103, 91.5); cout << "c: "; c.show();   // ③ fires

    // Student bad('X');          // ❌ ERROR: no constructor takes a char
    return 0;
}
/*
OUTPUT:
a: Unnamed | roll 0 | marks 0
b: Sara | roll 0 | marks 0
c: Omar | roll 103 | marks 91.5

EXPLANATION:
Constructors overload like any function (Ch. 7): the compiler
matches the ARGUMENTS at birth to pick the right version.
The commented default-parameter form is the modern space-saver:
one constructor playing all three roles.
*/
```

**What happened here?** Overloaded constructors = multiple birth options, compiler-routed. And remember Chapter 7's default parameters? They're how pros write ONE flexible constructor instead of three.

---

### Example 13.3 — Initializer List: The Professional Syntax (and the Only One for `const`)

```cpp
// ============================================
// Example 13.3: Constructor Initializer Lists
// ============================================
// Concepts used: : member(value) list, initializing const members
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Phone {
private:
    const string brand;            // ⚠️ const — set once at birth, then LOCKED
    int battery;
public:
    // The initializer list runs BEFORE the { } body:
    Phone(string b, int charge) : brand(b), battery(charge) {
        cout << brand << " phone unboxed!\n";
        // brand = b;              // ❌ ILLEGAL here: const can't be assigned!
    }                               // it was born with its value, via the list

    void status() { cout << brand << " at " << battery << "%\n"; }
};

int main() {

    Phone a("Samsung", 80);
    Phone b("Infinix", 95);

    a.status();
    b.status();

    return 0;
}
/*
OUTPUT:
Samsung phone unboxed!
Infinix phone unboxed!
Samsung at 80%
Infinix at 95%

EXPLANATION:
: brand(b), battery(charge) — members are INITIALIZED before the
body runs. For const (and reference) members this isn't style —
it's the ONLY legal way, because they can't be assigned after
birth. Professionals use initializer lists for ALL members.
*/
```

**What happened here?** The `: member(value)` list writes the birth certificate *before the baby opens its eyes*. `const` members demand it; clean code prefers it everywhere.

> ✅ **GOOD PRACTICE:** Mirror declaration order in your initializer list (members initialize in declaration order regardless of list order — mismatched lists cause sneaky bugs and `-Wall` warnings).

---

### Example 13.4 — The Copy Constructor: Birth by Photocopy

```cpp
// ============================================
// Example 13.4: Copy Constructor in Action
// ============================================
// Concepts used: copy ctor (const Type&), when copies happen
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Passport {
private:
    string holder;
    string number;
public:
    Passport(string h, string n) : holder(h), number(n) {
        cout << "Issued to " << holder << "\n";
    }

    Passport(const Passport& other) {              // the copy shape — memorize
        holder = other.holder + " (COPY)";
        number = other.number;
        cout << "Photocopied passport of " << other.holder << "\n";
    }

    ~Passport() { cout << "Passport of " << holder << " shredded.\n"; }

    void show() { cout << holder << " — #" << number << "\n"; }
};

void inspect(Passport p) {         // ⚠️ pass-by-value = a COPY is made!
    p.show();
}

int main() {

    Passport original("Mahadi", "PK123456");
    original.show();

    Passport clone(original);      // copy ctor fires (explicit)
    inspect(original);             // copy ctor fires (function parameter!)

    cout << "--- end of main, watch the destructors ---\n";
    return 0;
}
/*
OUTPUT:
Issued to Mahadi
Mahadi — #PK123456
Photocopied passport of Mahadi      ← clone
Photocopied passport of Mahadi      ← inspect's parameter
Mahadi (COPY) — #PK123456
Passport of Mahadi (COPY) shredded. ← inspect's copy dies first!
--- end of main, watch the destructors ---
Passport of Mahadi (COPY) shredded. ← clone dies
Passport of Mahadi shredded.        ← original dies LAST

EXPLANATION:
Copies happen more than you think: Student b(a); passing objects
by value; returning objects by value. The default copy ctor
duplicates member-by-member — fine for plain data. Write your
OWN when a class owns resources (files, heap memory) that need
custom handling. Death order: last born, first shredded.
*/
```

**What happened here?** You watched invisible copies come into existence — proof that pass-by-value photocopies whole objects. (Reference parameters, Chapter 10, prevent it: `void inspect(const Passport& p)` makes NO copy and is the pro choice for big objects.)

---

### Example 13.5 — Constructor & Destructor Order: The Stack of Plates

```cpp
// ============================================
// Example 13.5: Life & Death Order (predict, then verify!)
// ============================================
// Concepts used: scope-based lifetime, reverse destruction order
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Cup {
    string label;
public:
    Cup(string l) : label(l) { cout << "🍵 " << label << " placed\n"; }
    ~Cup()                   { cout << "🧽 " << label << " washed\n";  }
};

int main() {

    Cup a("Cup-A");

    if (true) {
        Cup b("Cup-B");            // born inside the inner scope
        Cup c("Cup-C");
        cout << "   ...inside the if...\n";
    }                              // b & c die HERE, before anything else

    Cup d("Cup-D");
    cout << "--- main ends ---\n";
    return 0;
}
/*
OUTPUT:
🍵 Cup-A placed
🍵 Cup-B placed
🍵 Cup-C placed
   ...inside the if...
🧽 Cup-C washed        ← inner scope ends: C (last born) first
🧽 Cup-B washed
🍵 Cup-D placed
--- main ends ---
🧽 Cup-D washed
🧽 Cup-A washed        ← A (first born) sleeps last

EXPLANATION:
Objects die when their SCOPE closes, in REVERSE birth order —
stack of plates. This predictability is a superpower: destructors
guarantee cleanup (files closed, memory freed) at exactly the
right moment, with zero code from you.
*/
```

**What happened here?** Lifetimes follow braces; deaths follow reverse births. When Chapter 10's `new` enters the picture, remember: **only objects born by `new` die by `delete`** — stack objects clean themselves automatically.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Constructor with a return type**
```cpp
void Student() { }      // ❌ NOT a constructor — an ordinary method named Student!
```
✅ **Fix:** `Student() { }` — no return type at all. Compilers won't error; your "constructor" just never runs. Sneakiest silent bug in this chapter.

**❌ Mistake 2 — Vanished default constructor shock**
```cpp
class A {
public:
    A(int x) { }        // you wrote a ctor → free default ctor GONE
};
A a;                    // ❌ ERROR: no default constructor
```
✅ **Fix:** Add `A() { }` yourself, or use default parameters on your constructor.

**❌ Mistake 3 — Assigning a const member inside the body**
```cpp
class P {
    const int id;
public:
    P(int i) { id = i; }   // ❌ const members can't be ASSIGNED
};
```
✅ **Fix:** `P(int i) : id(i) { }` — initialize in the list.

**❌ Mistake 4 — Destructor with parameters or return type**
```cpp
~Student(int code)  // ❌ destructors take nothing
int ~Student()      // ❌ and return nothing
```
✅ **Fix:** Exactly: `~Student() { }` — one per class, no args, no type.

**❌ Mistake 5 — Freeing stack memory or double-deleting**
```cpp
Student s("Ali", 1);
delete &s;               // ❌ catastrophic: s wasn't born via new!
```
✅ **Fix:** Only `delete` what YOU `new`'d. Stack objects like `s` are destroyed automatically — that's the whole point of destructors.

**❌ Mistake 6 — Expecting the initializer list to follow YOUR order**
```cpp
class T {
    int a;
    int b;
public:
    T(int x) : b(x), a(b) { }   // ❌ a initializes FIRST (declaration order),
};                              //    reading b before b has x!
```
✅ **Fix:** Initialize in declaration order: `T(int x) : a(x), b(x) { }` — and let `-Wall` warn you about reordered lists.

---

## 🧠 CONCEPT SUMMARY TABLE

| Item | Form | Runs when? | Notes |
|---|---|---|---|
| Default ctor | `X() {...}` | `X a;` | vanishes if you write ANY ctor — re-add it |
| Parameterized | `X(int v)` | `X a(5);` | overload freely |
| Default params | `X(int v = 0)` | both above | the pro space-saver |
| Copy ctor | `X(const X& o)` | `X b(a);`, by-value params/returns | `_ + " (COPY)"` demos it |
| Initializer list | `: m(v), n(w)` | before ctor body | mandatory for `const`/`&` members |
| Destructor | `~X()` | scope end / `delete` / program end | NO params, ONE per class |
| Order | — | births forward, deaths backward | stack of plates |

**Constructor vs ordinary function:**
| | Constructor | Function |
|---|---|---|
| Name | = class name | anything |
| Return type | none (not even void) | must have one |
| Called | automatically at birth | manually |
| Times per object | once | unlimited |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.1 ⭐
📋 class Car with a default ctor printing "Car manufactured"
   and setting speed=0. Create 2 cars in main.
📤 OUTPUT: "Car manufactured" twice (no explicit calls!)
💡 HINT: Constructors need no calling — just create objects.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.2 ⭐
📋 class Book with parameterized ctor Book(title, pages) :=
   via initializer list; describe() prints both. Create with
   Book b("Dune", 412);
📤 OUTPUT: "Dune" — 412 pages
💡 HINT: : title(t), pages(p) — match those parameter names.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.3 ⭐
📋 class Laptop with ONE ctor having DEFAULT parameters
   (brand="Generic", ram=8). Create 3 laptops: no args,
   ("HP"), ("HP", 16). Print each.
📤 OUTPUT: Generic/8 — HP/8 — HP/16
💡 HINT: Defaults live in the declaration: Laptop(string b =
   "Generic", int r = 8).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.4 ⭐⭐
📋 class Box with ctor Box(width, height) and method area().
   Add a destructor printing "Box recycled". Trace 3 objects
   and predict the exact full output before running.
📤 OUTPUT: alternating births, areas, and reverse-order deaths.
💡 HINT: Last born, first recycled.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.5 ⭐⭐
📋 class Student with copy ctor that prints "Clone created".
   Trigger it TWO different ways (declaration copy + pass-by-
   value) and show the messages.
📤 OUTPUT: two "Clone created" lines from different triggers.
💡 HINT: void display(Student s) copies; so does Student b(a);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.6 ⭐⭐
📋 class Account: const member accountNo + balance. Init both
   via initializer list; deposit() adds; show() prints. Prove
   reassigning accountNo in the body fails (leave as comment).
📤 OUTPUT: account created, deposit reflected, no const edits.
💡 HINT: : accountNo(n), balance(b)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.7 ⭐⭐
📋 class Timer: ctor stores creation order number from a static
   counter (static int next = 1 — pass as a global for now),
   dtor prints "Timer #n out". Create 3 timers inside a nested
   block; then 1 outside. Show exact output.
📤 OUTPUT: inner 3 die before the outer one.
💡 HINT: It's Example 13.5 with a counter — scopes run the show.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.8 ⭐⭐⭐
📋 class GameCharacter: 3 OVERLOADED ctors — (), (name),
   (name, level, hp) — plus destructors announcing each death.
   main creates one of each in mixed scopes; predict all output.
📤 OUTPUT: 3 births + appropriately-ordered 3 deaths.
💡 HINT: Overload + lifetime practice in one file.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.9 ⭐⭐⭐
📋 class Point(x, y) with PROPER initializer list, a copy ctor,
   and a static-like trick: copy ctor increments a plain global
   int copies. Demonstrate 2 copies; print copies == 2.
📤 OUTPUT: copies counted correctly.
💡 HINT: Copies happen on Point b(a) and by-value params.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 13.10 ⭐⭐⭐
📋 class Wallet: ctor opens "wallet file" (simulate with a
   message), dtor "closes" it. Show why this pairing is safer
   than manual open/close functions by creating objects inside
   an inner scope and observing the automatic close happen even
   when you 'forget' to call any close().
📤 OUTPUT: close message appears exactly when scope ends —
   with ZERO explicit close calls.
💡 HINT: This is the RAII idea — resources tied to lifetimes.
```

---

## 🎯 MINI CHALLENGE — THE LIFECYCLE TRACER 🔍

Write a `class Tracer` that:
- Has ctors: default, `Tracer(string tag)`, copy ctor
- Has a destructor
- EVERY lifecycle event prints: `"[Tracer <tag>] born (copy) #<id>"` / `"[Tracer <tag>] died #<id>"` — where `<id>` comes from an incrementing global counter

Then write a `main` with nested scopes, an array of 2 Tracers, and one pass-by-value function call — and **predict the entire output on paper FIRST, numbering the lines**. Run. Score yourself.

Perfect prediction = you now see object lifetimes like a debugger. That's a genuinely elite skill. 🧠

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 13.1**
```cpp
#include <iostream>
using namespace std;

class Car {
    int speed;
public:
    Car() : speed(0) { cout << "Car manufactured\n"; }
};

int main() {
    Car one, two;
    return 0;
}
```
💡 **PRO TIP:** Print debugging in ctors/dtors is the best lifetime learning tool — remove later.

**✅ SOLUTION 13.2**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    int    pages;
public:
    Book(string t, int p) : title(t), pages(p) { }
    void describe() { cout << "\"" << title << "\" — " << pages << " pages\n"; }
};

int main() {
    Book b("Dune", 412);
    b.describe();
    return 0;
}
```

**✅ SOLUTION 13.3**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Laptop {
    string brand;
    int    ram;
public:
    Laptop(string b = "Generic", int r = 8) : brand(b), ram(r) { }
    void show() { cout << brand << "/" << ram << "\n"; }
};

int main() {
    Laptop a, b("HP"), c("HP", 16);
    a.show(); b.show(); c.show();
    return 0;
}
```
💡 **PRO TIP:** This one ctor replaced three — and still allows every birth style.

**✅ SOLUTION 13.4**
```cpp
#include <iostream>
using namespace std;

class Box {
    int w, h;
public:
    Box(int w, int h) : w(w), h(h) { cout << "Box born " << w << "x" << h << "\n"; }
    int  area() { return w * h; }
    ~Box() { cout << "Box " << w << "x" << h << " recycled\n"; }
};

int main() {
    Box a(2, 3), b(4, 5);
    {
        Box c(6, 7);
        cout << "c area: " << c.area() << "\n";
    }   // c recycled here
    cout << "areas: " << a.area() << ", " << b.area() << "\n";
    return 0;
}
```

**✅ SOLUTION 13.5**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
    string name;
public:
    Student(string n = "?") : name(n) { }
    Student(const Student& o) : name(o.name) { cout << "Clone created\n"; }
};

void display(Student s) { }        // by-value → copy

int main() {
    Student a("Ali");
    Student b(a);                  // trigger 1
    display(a);                    // trigger 2
    return 0;
}
```

**✅ SOLUTION 13.6**
```cpp
#include <iostream>
using namespace std;

class Account {
    const int accountNo;           // locked forever after birth
    double   balance;
public:
    Account(int n, double b) : accountNo(n), balance(b) {
        // accountNo = 999;        // ❌ uncommenting = compile error (proof!)
    }
    void deposit(double x) { balance += x; }
    void show() { cout << "Acc " << accountNo << ": Rs. " << balance << "\n"; }
};

int main() {
    Account a(1001, 5000);
    a.deposit(1500);
    a.show();
    return 0;
}
```

**✅ SOLUTION 13.7**
```cpp
#include <iostream>
using namespace std;

int nextId = 1;                    // plain global for now (static member: Ch. 16)

class Timer {
    int id;
public:
    Timer()  : id(nextId++) { cout << "Timer #" << id << " ticking\n"; }
    ~Timer() { cout << "Timer #" << id << " out\n"; }
};

int main() {
    {
        Timer t1, t2, t3;
    }   // #3 #2 #1 die here (reverse order)
    Timer t4;
    return 0;
}
```

**✅ SOLUTION 13.8**
```cpp
#include <iostream>
#include <string>
using namespace std;

class GameCharacter {
    string name; int level, hp;
public:
    GameCharacter()                      : name("NPC"),  level(1), hp(100)
        { cout << name  << " spawns\n"; }
    GameCharacter(string n)              : name(n), level(1), hp(100)
        { cout << name << " spawns\n"; }
    GameCharacter(string n, int l, int h): name(n), level(l), hp(h)
        { cout << name << " spawns (custom)\n"; }
    ~GameCharacter() { cout << name << " despawns\n"; }
};

int main() {
    GameCharacter a;
    {
        GameCharacter b("Rex");
        GameCharacter c("Nova", 5, 300);
    }
    return 0;
}
```

**✅ SOLUTION 13.9**
```cpp
#include <iostream>
using namespace std;

int copies = 0;

class Point {
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) { }
    Point(const Point& o) : x(o.x), y(o.y) { copies++; }
};

int main() {
    Point a(3, 4);
    Point b(a);
    Point c = a;
    cout << "copies == " << copies << "\n";    // 2
    return 0;
}
```

**✅ SOLUTION 13.10**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Wallet {
    string owner;
public:
    Wallet(string o) : owner(o) { cout << owner << "'s wallet opened 💼\n"; }
    ~Wallet()                 { cout << owner << "'s wallet auto-closed 🔒\n"; }
};

int main() {
    Wallet w("Raza");
    {
        Wallet temp("Guest");
        // I "forgot" to close anything…
    }   // …but temp's dtor still closed it. Even on early return / exception.
    return 0;
}
```
💡 **PRO TIP:** This pattern is called **RAII** (Resource Acquisition Is Initialization) — the #1 C++ idiom. Files, mutexes, connections: tie them to lifetimes and leaks become impossible by design.

**✅ MINI CHALLENGE (sample)**
```cpp
#include <iostream>
#include <string>
using namespace std;

int live = 0, total = 0;

class Tracer {
    string tag; int id;
public:
    Tracer() : tag("t"), id(++total)        { live++; cout << "[born] #" << id << "\n"; }
    Tracer(string t) : tag(t), id(++total)  { live++; cout << "[born " << t << "] #" << id << "\n"; }
    Tracer(const Tracer& o) : tag(o.tag), id(++total) { live++; cout << "[copy " << o.tag << "] #" << id << "\n"; }
    ~Tracer() { live--; cout << "[died " << tag << "] #" << id << "\n"; }
};

void poke(Tracer t) { cout << "  (inside poke)\n"; }

int main() {
    Tracer a("A");
    {
        Tracer pair[2];
    }
    poke(a);
    return 0;
}
```
💡 Prediction beats reading: if your paper matches the screen line-for-line, Chapter 13 is permanently yours.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Constructors run automatically at birth: class-named, no return type, overloadable
- ✓ Write ANY constructor → the free default one disappears (re-add `X(){}` if needed)
- ✓ Initializer lists (`: m(v)`) are the pro syntax — and mandatory for `const`/reference members
- ✓ Copy constructor shape: `X(const X& other)` — fires on copies, explicit or sneaky (by-value params)
- ✓ Destructor `~X()` cleans up on death; deaths run in reverse birth order — RAII makes leaks impossible

**📚 Keywords learned:** constructor, default/parameterized/copy constructor, initializer list, destructor, object lifetime, scope, RAII, deep vs shallow copy (preview)

**🔗 Next chapter preview:** Chapter 14 — **Inheritance**. Why build `Cat`, `Dog`, `Parrot` from scratch when they all eat, sleep, and breathe? Build `Animal` ONCE and let children inherit. Genetics, but for code. 👪

*Your objects now enter the world fully formed and leave it tidy. That's craftsmanship.* ⚒️

---

**⬅️ [Chapter 12](chapter-12-classes-objects.md) | [🏠 Home](README.md) | [Chapter 14 ➡️](chapter-14-inheritance.md)**
