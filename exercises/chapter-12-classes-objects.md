# CHAPTER 12 — CLASSES & OBJECTS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A class is a blueprint.
 An object is the house you can actually
 live in — with the blueprint as many times
 as you like."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 11](chapter-11-intro-oop.md) | [🏠 Home](README.md) | [Chapter 13 ➡️](chapter-13-constructors-destructors.md)**

---

## 📖 CHAPTER OPENING

An architect draws a blueprint once; from it, builders construct hundreds of houses — each with its own paint, residents, and door locks, but all sharing the same layout. A **class** is that blueprint for objects: write the layout once (what data, what actions), then stamp out as many independent objects as you need.

### What you will learn:
- `class` syntax in full: data members + member functions
- Access specifiers: `public`, `private` (and `protected`, a preview)
- Creating objects & the dot operator
- Getters & setters — the professional keypad to private data
- Defining functions inside vs. outside the class (`::`)
- The `this` pointer — how an object says "me"

### Why this chapter matters:
Every line of professional C++ — games, browsers, trading systems — lives inside classes. This chapter is the grammar of OOP; everything after it (constructors, inheritance, polymorphism) builds on these foundations.

---

## 🔍 CONCEPT EXPLANATION

### What are a class and an object?

- **Class** — a user-defined type describing data members (state) and member functions (behavior). It's a *design*, uses no RAM by itself.
- **Object** — an actual variable of that class type, living in memory with its own copy of the data.

```cpp
class Student {         // blueprint (uses no RAM)
    int roll;           // data member
    void show() { }     // member function (method)
};

Student ali;            // OBJECT — real memory, its own roll
Student sara;           // another object — a DIFFERENT roll
```

### Why the public/private split?

Remember Example 11.1's open wallet? Access specifiers are C++'s built-in vault doors:

| Specifier | Who can access? | Use for |
|---|---|---|
| `private:` | Only the class's own functions | **Data** (the default) |
| `public:` | Anyone with the object | **Functions** — the approved keypad |
| `protected:` | The class + its children | Chapter 14 territory |

### How does the computer understand it?

Object memory = its data members' memory, bundled. All objects of a class **share one copy of the code** (functions) but each has its **own data**. When you call `ali.show()`, C++ secretly passes ali's address so `show()` knows *whose* data to use — that secret argument has a name: **`this`**.

---

## 📝 SYNTAX BOX

```cpp
class Student {                 // ← no semicolon on this line!
private:                        // default anyway — but write it for clarity
    string name;                // 🔒 data members hidden
    double gpa = 0.0;           //     in-class initial value (C++11+)

public:                         // 🔓 the interface
    void setName(string n)  { name = n; }          // setter
    string getName()      { return name; }          // getter

    void setGpa(double g) {                        // setter WITH guard
        if (g >= 0.0 && g <= 4.0) gpa = g;
    }
    double getGpa() { return gpa; }

    void report();                                  // declared inside...
};                                // ← THE SEMICOLON. Forgetting it = classic error.

void Student::report() {           // ...defined OUTSIDE via ClassName::
    cout << getName() << " holds GPA " << getGpa() << endl;
}

int main() {
    Student s;              // create object
    s.setName("Ali");       // dot operator: object.member
    s.setGpa(3.7);
    s.report();

    Student squad[3];       // arrays of objects — totally legal
    squad[0].setName("Sara");

    // s.gpa = 99;          // ❌ ERROR — private!
}
```

| Element | Name | Rule |
|---|---|---|
| `class Student { };` | Class definition | Ends with `;` — THE most-forgotten one |
| Data members | Fields | Keep private; initialize with defaults |
| Member functions | Methods | Usually public; can read all private data |
| `::` | Scope resolution | `Student::report` = "report belonging to Student" |
| `this` | Self-pointer | Points at the object whose function is running |

---

## 💻 EXAMPLE CODES

### Example 12.1 — The Simplest Complete Class

```cpp
// ============================================
// Example 12.1: A Dog Class (state + behavior, complete)
// ============================================
// Concepts used: data members, member functions, dot operator
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Dog {
public:                          // simple example: all public for now
    string name;
    string breed;
    int    age = 0;              // default — no garbage!

    void bark() {
        cout << name << " says: Woof! Woof!" << endl;
    }

    void birthday() {
        age++;                               // the object edits ITS OWN data
        cout << name << " turned " << age << "! 🎂" << endl;
    }

    void describe() {
        cout << name << " is a " << age << "-year-old " << breed << endl;
    }
};                               // ← don't forget this semicolon

int main() {

    Dog rex;                     // object 1 — its own name, breed, age
    rex.name  = "Rex";
    rex.breed = "German Shepherd";
    rex.age   = 3;

    Dog bella;                   // object 2 — totally independent data
    bella.name  = "Bella";
    bella.breed = "Labrador";
    bella.age   = 5;

    rex.bark();
    bella.bark();
    bella.birthday();            // only Bella ages
    rex.describe();
    bella.describe();

    return 0;
}
/*
OUTPUT:
Rex says: Woof! Woof!
Bella says: Woof! Woof!
Bella turned 6! 🎂
Rex is a 3-year-old German Shepherd
Bella is a 6-year-old Labrador

EXPLANATION:
One blueprint, two independent houses. bella.birthday() changed
Bella's age and ONLY Bella's — because inside birthday(), the
bare word 'age' means "the age of whoever called me".
*/
```

**What happened here?** Each object carries its own data; shared functions operate on *whoever called them*. That's the central magic of OOP — and it's all automatic.

---

### Example 12.2 — Getters & Setters: The Safe Keypad

```cpp
// ============================================
// Example 12.2: BankAccount with Private Data
// ============================================
// Concepts used: private data, public getters/setters with validation
// ============================================

#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner  = "Unknown";
    double balance = 0.0;                  // 🔒 unreachable from main

public:
    // Setters = controlled WRITE access (with laws)
    void setOwner(string name) {
        if (name.length() >= 3) owner = name;
        else cout << "Name too short. Rejected.\n";
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited Rs. " << amount << ". New balance: "
                 << balance << endl;
        } else {
            cout << "Deposit must be positive!\n";
        }
    }

    bool withdraw(double amount) {          // returns success/failure
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Getters = controlled READ access
    double getBalance() { return balance; }
    string getOwner()   { return owner;   }
};

int main() {

    BankAccount acc;
    acc.setOwner("Ma");
    acc.setOwner("Mahadi");

    acc.deposit(5000);
    acc.deposit(-100);                        // rejected politely

    if (acc.withdraw(1500)) cout << "Withdrawal OK.\n";
    if (!acc.withdraw(99999)) cout << "Withdrawal refused: insufficient funds.\n";

    cout << acc.getOwner() << "'s balance: Rs. " << acc.getBalance() << endl;
    // acc.balance = 1000000;                 // ❌ COMPILE ERROR. Vault holds.

    return 0;
}
/*
OUTPUT:
Name too short. Rejected.
Deposited Rs. 5000. New balance: 5000
Deposit must be positive!
Withdrawal OK.
Withdrawal refused: insufficient funds.
Mahadi's balance: Rs. 3500

EXPLANATION:
This is ENCAPSULATION working: the vault (private balance) opens
only via the keypad (deposit/withdraw), and the keypad enforces
laws. Bad states (negative balance) become IMPOSSIBLE by design —
not by everyone remembering to be careful.
*/
```

**What happened here?** The class became the guardian of its own data. Notice `withdraw` returning `bool` — functions can *report* outcomes so callers can react. Chapter 18 upgrades this to exceptions.

> ✅ **GOOD PRACTICE:** Name getters `getX()`, setters `setX()`. Don't make a setter for every field — only for fields that *should* change. Read-only data = getter only.

---

### Example 12.3 — Defining Functions Outside the Class (`::`)

```cpp
// ============================================
// Example 12.3: The Professional File Layout
// ============================================
// Concepts used: declaring inside, defining outside with ClassName::
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int    pages = 0;

public:
    void setInfo(string t, string a, int p);   // DECLARATIONS inside —
    void describe();                           // class reads as a summary!
    bool isThick();
};

// ---- DEFINITIONS outside, using  ClassName::functionName ----

void Book::setInfo(string t, string a, int p) {
    title  = t;
    author = a;
    pages  = (p > 0) ? p : 1;
}

void Book::describe() {
    cout << "\"" << title << "\" by " << author
         << " (" << pages << " pages)" << endl;
}

bool Book::isThick() {
    return pages > 300;
}

int main() {

    Book b1;
    b1.setInfo("The Alchemist", "Paulo Coelho", 208);
    Book b2;
    b2.setInfo("Clean Code", "Robert Martin", 464);

    b1.describe();
    b2.describe();

    cout << (b1.isThick() ? "b1 is thick\n" : "b1 is a quick read\n");
    cout << (b2.isThick() ? "b2 is thick\n" : "b2 is a quick read\n");

    return 0;
}
/*
OUTPUT:
"The Alchemist" by Paulo Coelho (208 pages)
"Clean Code" by Robert Martin (464 pages)
b1 is a quick read
b2 is thick

EXPLANATION:
Inside the class you see the TABLE OF CONTENTS (what it can do);
outside, the full chapters (how). Big projects put declarations
in a .h header file and definitions in a .cpp file — this ::
pattern is exactly how that works.
*/
```

**What happened here?** Short classes stay in-class; meaty functions go outside with `ClassName::`. Your class definitions become scannable summaries — a professionalism superpower.

---

### Example 12.4 — Objects in Arrays & The Real-World Roster

```cpp
// ============================================
// Example 12.4: Class Roster (objects + Chapter 8 skills)
// ============================================
// Concepts used: array of objects, searching objects, member access in loops
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int    roll  = 0;
    double marks = 0.0;
public:
    void set(string n, int r, double m) { name = n; roll = r; marks = m; }
    int    getRoll()  { return roll;  }
    double getMarks() { return marks; }
    void   line() {
        cout << "Roll " << roll << " | " << name << " | " << marks << endl;
    }
};

int main() {

    Student roster[3];                          // a hallway of student objects

    roster[0].set("Ali",   101, 78.5);
    roster[1].set("Sara",  102, 91.0);
    roster[2].set("Omar",  103, 64.5);

    cout << "--- Full roster ---\n";
    for (int i = 0; i < 3; i++) roster[i].line();

    // Find topper (max-index pattern, but on OBJECTS)
    int topIdx = 0;
    for (int i = 1; i < 3; i++)
        if (roster[i].getMarks() > roster[topIdx].getMarks()) topIdx = i;

    cout << "\nTopper: ";
    roster[topIdx].line();

    // Search by roll number (the &#8470;1 real-world lookup)
    int query = 102;
    for (int i = 0; i < 3; i++) {
        if (roster[i].getRoll() == query) {
            cout << "Roll " << query << " found: ";
            roster[i].line();
        }
    }

    return 0;
}
/*
OUTPUT:
--- Full roster ---
Roll 101 | Ali | 78.5
Roll 102 | Sara | 91
Roll 103 | Omar | 64.5

Topper: Roll 102 | Sara | 91
Roll 102 found: Roll 102 | Sara | 91

EXPLANATION:
Everything from Chapter 8 (arrays, max-index, linear search)
works untouched — the elements just happen to be whole objects.
roster[i].getMarks() says: "locker i, then its keypad's getMarks".
This is the architecture of your Chapter 21 project.
*/
```

**What happened here?** Old skills + new structure = a mini database. Objects make arrays *meaningful*; arrays make objects *scalable*.

---

### Example 12.5 — The `this` Pointer: How Objects Say "Me"

```cpp
// ============================================
// Example 12.5: this — the Object's Self-Address
// ============================================
// Concepts used: this->, parameter shadowing resolution, fluency idea
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Player {
private:
    string name;
    int    score = 0;
public:
    // ⚠️ Parameter named 'name' SHADOWS the data member 'name'!
    Player& setName(string name) {
        this->name = name;          // this->name = the MEMBER; name = the parameter
        return *this;               // returning the object enables chaining
    }

    Player& addScore(int points) {
        this->score += points;      // 'this' is a POINTER to the calling object
        return *this;               // (this is why it's -> and not . )
    }

    void show() {
        cout << this->name << " has " << this->score << " points\n";
    }
};

int main() {

    Player p;
    p.setName("Ahmed").addScore(50).addScore(20);   // chained! like jQuery
    p.show();

    return 0;
}
/*
OUTPUT:
Ahmed has 70 points

EXPLANATION:
Every member function secretly receives 'this' — the address of the
object that called it. this->name means "MY name" (the member),
distinguishing it from the parameter 'name'.
Returning *this returns the object itself, so calls can chain:
obj.doA().doB().doC() — a style you'll meet in real libraries.
*/
```

**What happened here?** `this` resolves the classic name collision (`name = name` would assign the parameter to itself!) and unlocks fluent chaining. You'll see `this->` constantly in Chapter 13–15 codebases.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Forgetting the semicolon after the class**
```cpp
class Dog {
    // ...
}                            // ❌ missing ;  →  error: expected ';' after class
```
✅ **Fix:** `class Dog { ... };` — it's THE most common class typo in existence.

**❌ Mistake 2 — Accessing private members from outside**
```cpp
BankAccount acc;
acc.balance = 500;       // ❌ 'balance' is private within this context
```
✅ **Fix:** Go through the public keypad: `acc.deposit(500);`. (If the compiler slaps you, that's encapsulation *succeeding*.)

**❌ Mistake 3 — Using the class name like an object**
```cpp
Student.roll = 5;        // ❌ Student is the blueprint, not a house!
```
✅ **Fix:** `Student ali; ali.roll = 5;` — act on instances. (Exception: `static` members — Chapter 16.)

**❌ Mistake 4 — Shadowed parameters confusing assignments**
```cpp
void setName(string name) { name = name; }   // assigns parameter to itself! member untouched
```
✅ **Fix:** `this->name = name;` — or rename the parameter: `void setName(string n) { name = n; }`

**❌ Mistake 5 — Uninitialized data members**
```cpp
class Counter {
    int count;           // garbage until set!
public:
    void increment() { count++; }   // garbage + 1 = garbage
};
```
✅ **Fix:** Default at birth: `int count = 0;` (C++11+), or a constructor — next chapter's whole job.

**❌ Mistake 6 — Defining outside without `ClassName::`**
```cpp
void report() { ... }    // ❌ becomes a FREE function, not Student's
```
✅ **Fix:** `void Student::report() { ... }` — the `::` is the family surname of the function.

---

## 🧠 CONCEPT SUMMARY TABLE

| Concept | Code | Remember |
|---|---|---|
| Class definition | `class X { ... };` | semicolon after `}` ! |
| Object creation | `X obj;` | each has own data copy |
| Access | `obj.member` | dot = keypad press |
| `private:` | default for class | data lives here |
| `public:` | the interface | functions live here |
| Getter | `type getX() { return x; }` | read-only access |
| Setter | `void setX(type v) { ... }` | add validation laws |
| Outside definition | `void X::f() { }` | `::` = scope resolution |
| Array of objects | `X arr[10];` | full Ch. 8 toolkit applies |
| `this` | `this->member` | pointer to "myself"; enables chaining |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.1 ⭐
📋 Create class Person (private: name, age). Write setters with
   minimal validation (name non-empty, age 0-120) + getter-based
   introduce() printing "Hi, I'm X, age Y".
📥 SAMPLE: set("Zain", 19)
📤 OUTPUT: Hi, I'm Zain, age 19
💡 HINT: Guards inside setters; introduce() uses the members.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.2 ⭐
📋 class Rectangle (private length, width). Public: set(l,w),
   area(), perimeter(). Test with 8×5.
📤 OUTPUT: Area=40  Perimeter=26
💡 HINT: area returns length*width — members directly.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.3 ⭐
📋 class Counter (private count=0) with increment(), decrement()
   (refuse below 0), and get(). Drive it: +1,+1,-1,-1,-1, then print.
📤 OUTPUT: 0  (and one "can't go below zero" warning)
💡 HINT: The refusal is an if inside decrement().
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.4 ⭐⭐
📋 class Mobile (private brand, battery=100). charge(x)(max 100),
   use(x)(min 0), status() prints brand + battery. Define ALL
   functions OUTSIDE the class with ::.
📥 SAMPLE: use(30), charge(50), use(200) ...
📤 OUTPUT: battery correctly clamped each time.
💡 HINT: battery = min(100, battery+x); battery = max(0, battery-x);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.5 ⭐⭐
📋 class Employee (name, salary). Method yearlyBonus(percent)
   returns salary*percent/100. Create 2 employees, print each
   name + bonus for 10%.
📤 OUTPUT: e.g. Ali: 6000  (salary 60000, 10% → monthly base)
💡 HINT: Bonus computed from the MEMBER salary — no parameter.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.6 ⭐⭐
📋 class Temperature (private celsius). Setter blocks |c|>100
   ("off the chart!"); toFahrenheit() converts. Test 37 and 999.
📤 OUTPUT: 98.6 F then a rejection message.
💡 HINT: Guard in setCelsius; conversion formula from Ch. 4!
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.7 ⭐⭐
📋 class Book (title, price) + array of 4 books; print details of
   the most expensive (max-index pattern on objects).
📤 OUTPUT: the priciest title + its price.
💡 HINT: Example 12.4's topper hunt, retargeted to price.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.8 ⭐⭐⭐
📋 class Time (hours, minutes, all private). set(h,m) normalizes
   overflow (70 min → +1h 10m); show() prints "HH:MM" zero-padded;
   add(Time other) adds two times correctly.
📥 SAMPLE: 2:50 + 1:30
📤 OUTPUT: 04:20
💡 HINT: total minutes = h*60+m; rebuild & normalize with / 60
   and % 60; pad with (h<10?"0":"").
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.9 ⭐⭐⭐
📋 class Team (name, played, won). winRate%  and an array of
   3 teams; print the leaderboard sorted via a bubble-sort on
   OBJECTS by winRate descending.
📤 OUTPUT: teams listed best first.
💡 HINT: Swapping whole objects works: Team t = a[i]; a[i]=a[j]...
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 12.10 ⭐⭐⭐
📋 class PasswordBox: private password; setPassword(new) allowed
   ONLY if current is empty OR oldPassword matches (passed as
   argument); check(pw) returns bool; attempts++ on failures,
   lock at 3 (locked flag). Demo: set, wrong tries, correct try,
   change password with correct old.
📤 OUTPUT: sequence of accepted/rejected/locked messages.
💡 HINT: All the laws live INSIDE the class — main only calls.
```

---

## 🎯 MINI CHALLENGE — DIGITAL PET 🐣

Build a `class Pet` with private: `name`, `hunger` (0–10), `happiness` (0–10).
Public keypad:
- `feed()` → hunger −2 (min 0), happiness +1
- `play()` → happiness +2 (max 10), hunger +1
- `status()` → prints hunger/happiness bars: `Hunger [####------] 4/10`
- `isFine()` → returns true only if hunger ≤ 7 AND happiness ≥ 3

In `main`: create a pet, simulate 6 actions, then print a verdict: `"<name> is thriving! 🌟"` or `"<name> needs care! 🚑"`.

Your pet's mood is PRIVATE — the world can only feed it and play with it. Congratulations: you just built a proto-Tamagotchi with encapsulation. 🐾

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 12.1**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Person {
    string name;
    int    age = 0;
public:
    void set(string n, int a) {
        if (!n.empty())        name = n;
        if (a >= 0 && a <= 120) age  = a;
    }
    void introduce() { cout << "Hi, I'm " << name << ", age " << age << endl; }
};

int main() {
    Person p;
    p.set("Zain", 19);
    p.introduce();
    return 0;
}
```
💡 **PRO TIP:** One `set()` for everything is friendly UX for small classes; big classes prefer focused setters.

**✅ SOLUTION 12.2**
```cpp
#include <iostream>
using namespace std;

class Rectangle {
    double length = 1, width = 1;
public:
    void set(double l, double w) { length = l; width = w; }
    double area()      { return length * width; }
    double perimeter() { return 2 * (length + width); }
};

int main() {
    Rectangle r;
    r.set(8, 5);
    cout << "Area=" << r.area() << "  Perimeter=" << r.perimeter();
    return 0;
}
```

**✅ SOLUTION 12.3**
```cpp
#include <iostream>
using namespace std;

class Counter {
    int count = 0;
public:
    void increment() { count++; }
    void decrement() {
        if (count > 0) count--;
        else cout << "Can't go below zero!\n";
    }
    int get() { return count; }
};

int main() {
    Counter c;
    c.increment(); c.increment();
    c.decrement(); c.decrement();
    c.decrement();                 // the refused one
    cout << c.get();               // 0
    return 0;
}
```

**✅ SOLUTION 12.4**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Mobile {
    string brand;
    int    battery = 100;
public:
    void setBrand(string b);
    void charge(int x);
    void use(int x);
    void status();
};

void Mobile::setBrand(string b) { brand = b; }
void Mobile::charge(int x) { battery += x; if (battery > 100) battery = 100; }
void Mobile::use(int x)    { battery -= x; if (battery < 0)   battery = 0;   }
void Mobile::status()      { cout << brand << ": battery " << battery << "%\n"; }

int main() {
    Mobile m;
    m.setBrand("Pixel");
    m.use(30);   m.status();     // 70
    m.charge(50); m.status();    // 100 (clamped)
    m.use(200);  m.status();     // 0 (clamped)
    return 0;
}
```
💡 **PRO TIP:** Clamping inside the class means users of the class CANNOT break it — even by passing 1,000,000.

**✅ SOLUTION 12.5**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Employee {
    string name;
    double salary = 0;
public:
    void set(string n, double s) { name = n; salary = s; }
    double yearlyBonus(double percent) { return salary * percent / 100; }
    string getName() { return name; }
};

int main() {
    Employee a, b;
    a.set("Ali", 60000);
    b.set("Sara", 85000);
    cout << a.getName() << ": " << a.yearlyBonus(10) << endl;
    cout << b.getName() << ": " << b.yearlyBonus(10) << endl;
    return 0;
}
```

**✅ SOLUTION 12.6**
```cpp
#include <iostream>
using namespace std;

class Temperature {
    double celsius = 0;
public:
    void setCelsius(double c) {
        if (c >= -100 && c <= 100) celsius = c;
        else cout << "Off the chart! Rejected.\n";
    }
    double toFahrenheit() { return celsius * 9.0 / 5.0 + 32; }
};

int main() {
    Temperature t;
    t.setCelsius(37);
    cout << t.toFahrenheit() << " F\n";
    t.setCelsius(999);                          // rejected
    return 0;
}
```

**✅ SOLUTION 12.7**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;
    double price = 0;
public:
    void set(string t, double p) { title = t; price = p; }
    double getPrice() { return price; }
    void line() { cout << title << " — Rs. " << price << endl; }
};

int main() {
    Book shelf[4];
    shelf[0].set("Novel A", 800);
    shelf[1].set("Novel B", 1250);
    shelf[2].set("Novel C", 600);
    shelf[3].set("Novel D", 999);

    int top = 0;
    for (int i = 1; i < 4; i++)
        if (shelf[i].getPrice() > shelf[top].getPrice()) top = i;
    shelf[top].line();
    return 0;
}
```

**✅ SOLUTION 12.8**
```cpp
#include <iostream>
using namespace std;

class Time {
    int h = 0, m = 0;
    void normalize() { h += m / 60; m %= 60; h %= 24; }   // private helper!
public:
    void set(int hh, int mm) { h = hh; m = mm; normalize(); }
    void add(Time other) { h += other.h; m += other.m; normalize(); }
    void show() {
        cout << (h < 10 ? "0" : "") << h << ":"
             << (m < 10 ? "0" : "") << m << endl;
    }
};

int main() {
    Time a, b;
    a.set(2, 50);
    b.set(1, 30);
    a.add(b);
    a.show();                   // 04:20
    return 0;
}
```
💡 **PRO TIP:** A private helper (`normalize()`) used by many public functions = code reuse INSIDE the class. Private functions are real and useful!

**✅ SOLUTION 12.9**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Team {
    string name;
    int played = 1, won = 0;
public:
    void set(string n, int p, int w) { name = n; played = p; won = w; }
    double winRate() { return 100.0 * won / played; }
    void line() { cout << name << " — " << winRate() << "%\n"; }
};

int main() {
    Team t[3];
    t[0].set("Falcons", 10, 6);
    t[1].set("Tigers",  10, 8);
    t[2].set("Sharks",  10, 3);

    for (int pass = 0; pass < 2; pass++)          // bubble sort on objects
        for (int i = 0; i < 2 - pass; i++)
            if (t[i].winRate() < t[i + 1].winRate()) {
                Team tmp = t[i];                   // whole-object swap!
                t[i] = t[i + 1];
                t[i + 1] = tmp;
            }

    for (int i = 0; i < 3; i++) t[i].line();
    return 0;
}
/*
OUTPUT:
Tigers — 80%
Falcons — 60%
Sharks — 30%
*/
```

**✅ SOLUTION 12.10**
```cpp
#include <iostream>
#include <string>
using namespace std;

class PasswordBox {
    string saved = "";
    int    fails = 0;
    bool   locked = false;
public:
    void setPassword(string oldPw, string newPw) {
        if (locked) { cout << "Box locked!\n"; return; }
        if (saved.empty() || oldPw == saved) { saved = newPw; cout << "Password set.\n"; }
        else cout << "Old password wrong.\n";
    }
    bool check(string pw) {
        if (locked) { cout << "Locked. Too many failures.\n"; return false; }
        if (pw == saved) { fails = 0; cout << "Correct!\n"; return true; }
        fails++;
        cout << "Wrong (" << fails << "/3)\n";
        if (fails >= 3) locked = true;
        return false;
    }
};

int main() {
    PasswordBox box;
    box.setPassword("", "openSesame");      // first set: allowed
    box.check("1234");                       // 1/3
    box.check("0000");                       // 2/3
    box.check("openSesame");                 // correct — fails reset
    box.setPassword("openSesame", "newPass");// change with correct old
    box.check("newPass");                    // works
    return 0;
}
```

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Pet {
    string name;
    int hunger = 5, happiness = 5;             // 0-10 scales

    void clamp() {                             // private law-enforcer
        if (hunger < 0) hunger = 0;
        if (hunger > 10) hunger = 10;
        if (happiness < 0) happiness = 0;
        if (happiness > 10) happiness = 10;
    }
    string bar(int value) {
        string s = "[";
        for (int i = 0; i < 10; i++) s += (i < value ? "#" : "-");
        return s + "]";
    }
public:
    void setName(string n) { name = n; }
    void feed() { hunger -= 2; happiness += 1; clamp(); }
    void play() { happiness += 2; hunger += 1; clamp(); }
    void status() {
        cout << name << " | Hunger "    << bar(hunger)    << " " << hunger
             << "/10 | Joy " << bar(happiness) << " " << happiness << "/10\n";
    }
    bool isFine()  { return hunger <= 7 && happiness >= 3; }
    string getName() { return name; }
};

int main() {
    Pet pet;
    pet.setName("Tweety");
    pet.play(); pet.feed(); pet.play();
    pet.feed(); pet.play(); pet.feed();
    pet.status();

    cout << pet.getName()
         << (pet.isFine() ? " is thriving! 🌟" : " needs care! 🚑") << endl;
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Class = blueprint (no RAM); object = instance (real RAM, own data)
- ✓ Data private, functions public; the class guards its own laws
- ✓ Getters read, setters write WITH validation — the keypad to the vault
- ✓ Define outside with `ClassName::name()` for clean file layout
- ✓ `this->` disambiguates members from parameters and enables chaining

**📚 Keywords learned:** data member, member function, access specifier, `public`, `private`, getter, setter, scope resolution `::`, dot operator, `this`, object array, encapsulation (implemented!)

**🔗 Next chapter preview:** Chapter 13 — **Constructors & Destructors**. Right now your objects are born empty and need 3 setter calls to become someone. Constructors make objects **born ready** in one line — and destructors wave goodbye (and clean up). 🐣

*You now write real classes. The blueprint era has officially begun.* 🏗️

---

**⬅️ [Chapter 11](chapter-11-intro-oop.md) | [🏠 Home](README.md) | [Chapter 13 ➡️](chapter-13-constructors-destructors.md)**
