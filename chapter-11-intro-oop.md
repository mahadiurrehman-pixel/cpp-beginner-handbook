# CHAPTER 11 — INTRODUCTION TO OOP

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Procedural code asks: 'What do I do next?'
 Object-oriented code asks: 'Who lives here?'"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 10](chapter-10-pointers.md) | [🏠 Home](README.md) | [Chapter 12 ➡️](chapter-12-classes-objects.md)**

```
           PART 3: OBJECT-ORIENTED PROGRAMMING
```

---

## 📖 CHAPTER OPENING

Imagine organizing a city by listing every action ever taken — "drive car, open shop, bake bread, close shop..." — one endless to-do list. Chaos! Real cities are organized around *things*: a bakery has ovens and bakers and bread and the ability to `bake()`. **Object-Oriented Programming (OOP)** organizes code the same way: around *objects* that hold their own data and their own actions.

### What you will learn:
- Procedural vs. OOP thinking — the mindset shift
- How real-world objects become code objects
- The 4 pillars: **Encapsulation, Abstraction, Inheritance, Polymorphism**
- Why OOP makes big programs survivable

### Why this chapter matters:
This is a *thinking* chapter. Five short examples, no new syntax overload — just the "why" before the "how". Students who skip this chapter write classes mechanically for months without knowing why. You won't be one of them.

---

## 🔍 CONCEPT EXPLANATION

### Procedural vs. OOP thinking — watch the same problem twice

**Procedural (Chapters 1–10):** data floats around loose; functions act on it from the outside.

```cpp
double balance = 5000;              // data: free-floating
void deposit(double amount, double& bal) { bal += amount; }   // function: separate
```

**OOP:** data and its functions are packaged together as a self-contained citizen.

```cpp
BankAccount acc;                    // an object: owns its balance
acc.deposit(500);                   // the object acts on ITSELF
```

### What is an object, really?

**Real-world objects have two things:**
1. **State** (what it knows): a car has color, speed, fuel
2. **Behavior** (what it does): a car can accelerate, brake, honk

```cpp
// A code object mirrors this exactly:
class Car {
    string color;        // STATE    = data members (variables)
    int    speed;
    void accelerate() { /*...*/ }    // BEHAVIOR = member functions (methods)
};
```

A **class** is the blueprint; an **object** is an actual thing built from it. Blueprint for a house → many real houses. `class Car` → `myCar`, `yourCar`, `taxi37`.

### Why do we use OOP?

As programs grow, procedural code tangles: 500 functions passing the same 20 variables around, anyone touching anything. OOP boxes related things together and **controls access** — bugs shrink from "search the whole program" to "search this one class."

---

## 📝 SYNTAX BOX — THE FOUR PILLARS IN ONE BOX

| Pillar | One-line meaning | Real-life analogy | Chapter |
|---|---|---|---|
| 🧱 **Encapsulation** | Bundle data + functions; hide the data, expose only safe buttons | A TV's insides are sealed; you use the remote | 12 |
| 🎭 **Abstraction** | Show the simple interface, hide the scary complexity | You drive a car without knowing the engine's chemistry | 12, 15 |
| 👪 **Inheritance** | Child classes reuse and extend parent classes | You inherit eye color; you add your own skills | 14 |
| 🎪 **Polymorphism** | One message, many behaviors (`draw()` works for circle AND square) | "Speak!" — a dog barks, a cat meows | 15 |

**Encapsulation** says: *my data is private; touch it through my functions only.*
**Abstraction** says: *you don't need to know HOW I do it, just WHAT I can do.*
**Inheritance** says: *don't rewrite what already exists — extend it.*
**Polymorphism** says: *the same command can mean different things to different objects.*

🎮 **FUN FACT:** C++ founder Bjarne Stroustrup originally called it "C with Classes" — classes were THE whole point of the language. You're now learning its central feature.

This chapter is about **thinking**, not typing — so the syntax box today is just a *preview*. Memorize the SHAPE; Chapters 12–16 unpack every keyword of it.

```cpp
// ============================================
// TEMPLATE 11-A: THE CLASS (preview of Chapter 12)
// A class = blueprint. An object = a house built from it.
// ============================================
class ClassName {            // the blueprint
private:                     // 🔒 hidden from the outside (Encapsulation!)
    dataType  memberVariable;

public:                      // 🚪 the safe "buttons" users may press
    returnType memberFunction(parameters) {
        // work happens in here
    }
};                           // ← that semicolon bites EVERYONE once 😅

// Variation: MAKING objects from the blueprint
ClassName thing1;            // one object
ClassName thing2;            // another — same plan, separate thing
thing1.memberFunction(args); // press a button on it
```

```cpp
// ============================================
// TEMPLATE 11-B: THE FOUR PILLARS AS 4 TINY PLAYERS
// (each gets a FULL chapter soon — this is the trailer)
// ============================================
class Secret {                         // 🧱 ENCAPSULATION
private: int code = 42;                //   locked away
public:  int read() { return code; }   //   ...via a safe window
};

class Car {                            // 🎭 ABSTRACTION
public: void drive();                  //   simple promise...
private: void mixFuelAndSpark();       //   ...scary details hidden
};

class Animal { public: void breathe(); };        // 👪 base
class Dog : public Animal { public: void bark(); }; // INHERITANCE

class Shape {                          // 🎪 POLYMORPHISM (Ch. 15)
public: virtual void draw() { }        //   virtual = "children may
};                                     //   answer differently"
```

> 📌 **NOTE:** If Templates 11-B look fuzzy, perfect — they're scaffolding for the next five chapters. Your only job today: **recognize the shape** and **name the pillar** when you see it.

---

## 💻 EXAMPLE CODES

### Example 11.1 — The Procedural Mess (Why We Needed Something Better)

```cpp
// ============================================
// Example 11.1: Banking Without OOP
// ============================================
// What this program does: Manages accounts the procedural way —
//                         notice how fragile and tangled it gets.
// Concepts used: why data + functions belong together
// ============================================

#include <iostream>
#include <string>
using namespace std;

// Scattered, unprotected data — ANY line anywhere can break it:
double balance1 = 5000, balance2 = 12000;
string owner1 = "Ali", owner2 = "Sara";

void deposit(double& balance, double amount) {        // works on ANY double& —
    balance += amount;                                // nothing stops misuse!
}

int main() {

    deposit(balance1, 500);
    deposit(balance2, -99999);    // "deposit" of negative?? nobody stops this
    balance1 = -50000;            // direct damage — no guard, no rules

    cout << owner1 << ": " << balance1 << endl;     // -45000. Oops.
    cout << owner2 << ": " << balance2 << endl;     // -87999. Bankrupt!

    return 0;
}
/*
OUTPUT:
Ali: -45000
Sara: -87999

EXPLANATION:
The data had NO OWNER and NO RULES. With 3 accounts we'd juggle 6
extra variables; with 300, the program collapses. Every real bank
system needs: a balance that CANNOT be touched except through
approved operations. That's encapsulation — coming in Ch. 12.
*/
```

**What happened here?** Raw data is a wallet left on the street. OOP puts the wallet in a safe with a keypad — you can still use your money, but only through the approved interface.

---

### Example 11.2 — The Same Problem, The OOP Way (First Class Preview)

```cpp
// ============================================
// Example 11.2: BankAccount as a Citizen (a first taste of class)
// ============================================
// What this program does: Same bank, protected design. Details in Ch. 12!
// Concepts used: class, object, private data, public functions
// ============================================

#include <iostream>
#include <string>
using namespace std;

class BankAccount {              // the BLUEPRINT
private:                          // 🔒 hidden from outside — THE SAFE
    string owner;
    double balance = 0;

public:                           // 🔓 the approved KEYPAD
    void setOwner(string name) { owner = name; }

    void deposit(double amount) {
        if (amount > 0) balance += amount;    // rules live INSIDE!
    }

    void show() const {
        cout << owner << " has Rs. " << balance << endl;
    }
};                                // ← note the semicolon (forgettable classic!)

int main() {

    BankAccount acc1, acc2;       // two OBJECTS built from one blueprint
    acc1.setOwner("Ali");
    acc2.setOwner("Sara");

    acc1.deposit(5000);
    acc1.deposit(-9999);          // ignored by the rule inside deposit()
    // acc1.balance = -50000;     // ❌ COMPILE ERROR — private! The safe holds.
    acc2.deposit(12000);

    acc1.show();
    acc2.show();

    return 0;
}
/*
OUTPUT:
Ali has Rs. 5000
Sara has Rs. 12000

EXPLANATION:
The balance is now unreachable except through deposit(), which
enforces the rules. Creating 300 accounts = 300 lines like acc1 —
NO new headaches. That's the entire promise of OOP in one example.
You'll learn every keyword here in Chapter 12 — today, just FEEL it.
*/
```

**What happened here?** Data got an owner and rules. The program didn't get longer as accounts multiplied — it got *safer*. That is OOP's sales pitch, delivered.

---

### Example 11.3 — Spotting Objects in the Wild (Design Practice in Code)

```cpp
// ============================================
// Example 11.3: Turning a Real Scenario into Objects
// ============================================
// Scenario: a food delivery app. We map the world into classes.
// Concepts used: state (data) + behavior (functions) = object design
// ============================================

#include <iostream>
#include <string>
using namespace std;

// ---------- Object 1: a Dish knows its name & price ----------
class Dish {
public:
    string name;
    double price;
    void describe() { cout << name << " — Rs. " << price << endl; }
};

// ---------- Object 2: a Rider knows location; can deliver ----------
class Rider {
public:
    string name;
    void deliver(string dish, string address) {
        cout << name << " is delivering " << dish
             << " to " << address << " 🛵" << endl;
    }
};

// ---------- Object 3: an Order JOINS other objects ----------
class Order {
public:
    Dish  dish;
    Rider rider;
    void dispatch(string address) {
        dish.describe();
        rider.deliver(dish.name, address);
    }
};

int main() {

    Order lunch;
    lunch.dish.name  = "Biryani";
    lunch.dish.price = 350;
    lunch.rider.name = "Kamran";

    lunch.dispatch("Gulshan Block 5");

    return 0;
}
/*
OUTPUT:
Biryani — Rs. 350
Kamran is delivering Biryani to Gulshan Block 5 🛵

EXPLANATION:
The DESIGN happened first: "what things exist here?" Dish, Rider,
Order. Each keeps its own little kingdom of data and duties.
When objects can CONTAIN other objects (Order has a Dish),
you can model literally anything. This is how professional
software is sketched before a single line is written.
*/
```

**What happened here?** Object-oriented design is mostly *naming things honestly*: find the nouns (objects), list what each knows (data) and does (functions). The code then writes itself.

---

### Example 11.4 — The Four Pillars in Tiny Working Sketches

```cpp
// ============================================
// Example 11.4: One Postcard From Each Pillar
// ============================================
// Concepts used: the 4 pillars, each in its tiniest form
// ============================================

#include <iostream>
#include <string>
using namespace std;

// 🧱 ENCAPSULATION — private data, public keypad
class Vault {
    int secret = 42;                    // private by default in classes
public:
    int peekSecret() { return secret; } // the ONLY legal way to look
};

// 🎭 ABSTRACTION — user calls start(); engine internals stay hidden
class Car {
    void injectFuel() { /* scary details */ }   // private helper
public:
    void start() { injectFuel(); cout << "Vroom! (don't ask how)\n"; }
};

// 👪 INHERITANCE — Bird gets Animal's powers for free
class Animal {
public:
    void breathe() { cout << "breathing...\n"; }
};
class Bird : public Animal {            // "a Bird IS AN Animal"
public:
    void fly() { cout << "flying!\n"; }
};

// 🎪 POLYMORPHISM — same message, different songs
class Dog { public: void speak() { cout << "Woof!\n"; } };
class Cat { public: void speak() { cout << "Meow!\n"; } };

int main() {

    Vault v;                    cout << "Encapsulation says: "
                                  << v.peekSecret() << endl;
    Car c;                      c.start();

    Bird b;  b.breathe();       // inherited for free!
             b.fly();

    Dog d;  d.speak();
    Cat cc; cc.speak();         // same message, different behavior

    return 0;
}
/*
OUTPUT:
Encapsulation says: 42
Vroom! (don't ask how)
breathing...
flying!
Woof!
Meow!

EXPLANATION:
Four pillars, four tiny demos. Keep this file — by the end of
Chapter 15, every line of it will feel completely natural.
*/
```

**What happened here?** The pillars aren't abstract philosophy — they're everyday code patterns with fancy names. You already have working examples of all four.

---

### Example 11.5 — Procedural vs OOP Side-by-Side: The Student Record

```cpp
// ============================================
// Example 11.5: One Problem, Two Eras
// ============================================
// Watch the SAME student-record task in both styles.
// Concepts used: the organizational payoff of OOP
// ============================================

#include <iostream>
#include <string>
using namespace std;

// ---------- Era 1: procedural ----------
void proceduralWay() {
    string n1 = "Ali";   int r1 = 1;   double m1 = 78.5;
    string n2 = "Sara";  int r2 = 2;   double m2 = 91.0;
    // ... three variables PER student. Ten students = 30 loose variables.
    cout << "[Procedural] " << n1 << " (roll " << r1 << "): " << m1 << "\n";
    cout << "[Procedural] " << n2 << " (roll " << r2 << "): " << m2 << "\n";
}

// ---------- Era 2: object-oriented ----------
class Student {
public:                                 // (we'll learn private next chapter)
    string name;
    int    roll;
    double marks;
    void report() {                     // the record REPORTS ITSELF
        cout << "[OOP] " << name << " (roll " << roll << "): " << marks << "\n";
    }
};

int main() {

    proceduralWay();

    Student s1;
    s1.name = "Ali";  s1.roll = 1;  s1.marks = 78.5;
    Student s2;
    s2.name = "Sara"; s2.roll = 2;  s2.marks = 91.0;

    s1.report();                        // data and display travel together
    s2.report();

    Student roster[100];                // an ARRAY of objects!
    cout << "Roster capacity ready for " << 100 << " students.\n";

    return 0;
}
/*
OUTPUT:
[Procedural] Ali (roll 1): 78.5
[Procedural] Sara (roll 2): 91
[OOP] Ali (roll 1): 78.5
[OOP] Sara (roll 2): 91
Roster capacity ready for 100 students.

EXPLANATION:
Same output — different future. The OOP version scales: one class
describes every student ever, arrays of Students make a school,
and 'report()' NEVER loses track of which name belongs to which
marks. That pairing bug is IMPOSSIBLE in the OOP version.
*/
```

**What happened here?** You've now *seen* both worlds on the same problem. From Chapter 12 on, we formalize everything: constructors, access specifiers, destructors, inheritance... but the mindset is already installed. 

> ❓ **THINK ABOUT IT:** In your Chapter 6 ATM and Chapter 5 mini-bank, where exactly would objects have prevented the tangle? (Hint: the `balance` variable and every function that passed it around.)

---

## ⚠️ COMMON MISTAKES SECTION (mindset edition)

**❌ Mistake 1 — "OOP = using the word `class`"**
Wrapping all your old functions and loose variables inside one giant `class Everything` is not OOP; it's procedural code living in a class-shaped house.
✅ **Fix:** OOP is about *responsibility design*: many small classes, each owning its own data and its own rules.

**❌ Mistake 2 — Making every data member public**
```cpp
class BankAccount {
public:
    double balance;      // anyone can write: acc.balance = -999999;
};
```
✅ **Fix:** Data private by default; expose only the safe operations. (Yes — Chapter 12 drills this until it's a reflex.)

**❌ Mistake 3 — The God Class**
One `class Program` with 40 unrelated functions: login, printing, math, file handling, shopping cart...
✅ **Fix:** Split by noun: `User`, `Printer`, `Cart`. If a class needs the word "and" to describe its job, it's two classes.

**❌ Mistake 4 — Skipping design, jumping into syntax**
Beginners open the editor first; professionals sketch classes on paper first.
✅ **Fix:** Nouns → classes. For a hospital app: `Patient`, `Doctor`, `Appointment`. THEN code.

**❌ Mistake 5 — Over-engineering tiny programs**
A 20-line script doesn't need five classes, an interface, and a factory.
✅ **Fix:** OOP's payoff grows with program size. Use it when structure buys safety and clarity — from this book's projects onward, it absolutely does.

---

## 🧠 CONCEPT SUMMARY TABLE

| Term | Meaning | Memory hook |
|---|---|---|
| Class | Blueprint for objects | House blueprints |
| Object | A live instance of a class | An actual house |
| State | The object's data | What it knows |
| Behavior | The object's functions | What it does |
| Encapsulation | Data sealed, accessed via functions | The safe with a keypad |
| Abstraction | Simple buttons hide complex insides | Driving ≠ engine knowledge |
| Inheritance | Children reuse parents' code | Genetics |
| Polymorphism | Same command, different behavior | "Speak!" → woof vs meow |

**When to use what:** All four pillars together = OOP. You don't choose — you blend. Chapters 12–16 teach each one's exact mechanics.

---

## ✏️ PRACTICE PROBLEMS (design-thinking edition)

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.1 ⭐
📋 List STATE (3+ data items) and BEHAVIOR (3+ functions) for a
   "Smartphone" object, as a design table (paper or comment block).
📤 EXPECTED: e.g. state: battery, model, storageLeft;
   behavior: call(), charge(), installApp()
💡 HINT: What does a phone KNOW? What does a phone DO?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.2 ⭐
📋 For a university system, name at least 5 classes (nouns only).
📤 EXPECTED: Student, Course, Professor, Classroom, Enrollment...
💡 HINT: Walk through a student registration in your head; every
   "thing" you touch is a candidate class.
━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.3 ⭐
📋 Match each pillar to a scenario (write the pillar's name):
   (a) A TV exposes buttons, not circuit boards.
   (b) class Car inherits class Vehicle's fuel logic.
   (c) print() works for Invoice, Report, Ticket.
   (d) Bank balance can't be edited directly, only via deposit().
📤 EXPECTED: (a) Abstraction (b) Inheritance (c) Polymorphism
   (d) Encapsulation
💡 HINT: Re-read the pillar table's analogies.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.4 ⭐⭐
📋 In ONE sentence each: why was Example 11.1's procedural bank
   dangerous, and what EXACTLY made Example 11.2 safe?
📤 EXPECTED: mentions private data + rule-enforcing methods.
💡 HINT: Who "owns" the balance in each version?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.5 ⭐⭐
📋 Design (state + behavior, no code) a class called "TrafficLight".
   Then explain: which pillar is at work when other code can only
   call nextState() but never write color directly?
📤 EXPECTED: design table + "Encapsulation"
💡 HINT: state: currentColor, timer... behavior: nextState()...
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.6 ⭐⭐
📋 Give two reasons arrays of objects (Student roster[100]) beat
   parallel arrays (names[100], marks[100]).
📤 EXPECTED: e.g. "fields can't get misaligned"; "methods come
   along with the data".
💡 HINT: In parallel arrays, what happens when you sort one and
   forget the other?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.7 ⭐⭐
📋 Code task: sketch class Book with public data members title,
   pages, and a describe() function; build 2 books in main and
   print both.
📤 EXPECTED OUTPUT: two describe() lines about your books.
💡 HINT: Follow Example 11.5's shape exactly.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.8 ⭐⭐⭐
📋 A beginner writes: class Shop { public: everything, 30
   functions }. Name the mistake, and split Shop into 3 focused
   classes with one job each (names + job one-liners).
📤 EXPECTED: "God class" + e.g. Inventory(stock), Cashier(billing),
   Customer(account)...
💡 HINT: Group functions by the noun they serve.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.9 ⭐⭐⭐
📋 For each pillar, invent YOUR OWN analogy (not the book's).
   One sentence each, four total.
📤 EXPECTED: any coherent original analogies.
💡 HINT: Try kitchens, smartphones, families, school.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 11.10 ⭐⭐⭐
📋 Take YOUR Chapter 22-style bank idea (or the Chapter 5 mini
   ATM) and sketch its class design: 2-3 classes, each with
   state + behavior bullets. This becomes your project blueprint.
📤 EXPECTED: e.g. Account{balance, pin | deposit, withdraw},
   Bank{accounts[] | addAccount, findAccount}...
💡 HINT: Names you choose here reappear in Chapter 22's project.
```

---

## 🎯 MINI CHALLENGE — THE ZOO BLUEPRINT 🦁

On paper or in a comment file, design a zoo management system:

- At least **4 classes** (animals? habitats? staff? tickets?)
- Each with **state** (3+ data items) and **behavior** (2+ functions)
- One relationship where a class **contains** another ("the Habitat HAS Animals")
- For each class, one line: which pillar(s) already visible in your design

Then translate ONE class into actual compilable code with a tiny `main` demo (like Example 11.3).

Great architects sketch before they pour concrete. You just did. 🏗️

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 11.1** — Sample: State → `batteryLevel`, `model`, `phoneNumber`, `storageLeft`; Behavior → `call(number)`, `charge()`, `takePhoto()`, `installApp()`.
💡 **PRO TIP:** If your "behavior" is really a noun in disguise (`musicPlayer`), it might deserve its own class.

**✅ SOLUTION 11.2** — Student, Course, Professor, Classroom, Enrollment, Library, Transcript. Any 5 nouns that genuinely exist in the system are correct.
💡 **PRO TIP:** Great filters: does the noun have data to keep? does it *do* anything? If both "no," it's probably just a field of another class.

**✅ SOLUTION 11.3** — (a) Abstraction (b) Inheritance (c) Polymorphism (d) Encapsulation.

**✅ SOLUTION 11.4** — In 11.1 the balance was a loose global: any line anywhere could set it to nonsense, and functions accepted any random double. In 11.2 the balance is private *inside* the object; the only doors in (`deposit`) contain validation rules, so bad states are simply unreachable.

**✅ SOLUTION 11.5** — Design: state → `color`, `secondsPerState`, `hasCamera`; behavior → `nextState()`, `reset()`, `showStatus()`. Pillar: **Encapsulation** — outsiders get controlled change (`nextState()`) but no direct writes to `color`.

**✅ SOLUTION 11.6** — ① Alignment: a `Student` object physically keeps name+marks together; parallel arrays can be sorted/shuffled apart by accident. ② Behavior travels with data (`roster[i].report()` works; parallel arrays have no attached functions). Bonus: passing ONE Student to a function beats passing three parallel variables.

**✅ SOLUTION 11.7**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string title;
    int    pages;
    void describe() {
        cout << "\"" << title << "\" — " << pages << " pages\n";
    }
};

int main() {
    Book b1; b1.title = "The Alchemist";        b1.pages = 208;
    Book b2; b2.title = "Clean Code";           b2.pages = 464;
    b1.describe();
    b2.describe();
    return 0;
}
```

**✅ SOLUTION 11.8** — The mistake is a **God class** (one class doing everything). Splits, e.g.: `Inventory` (stock levels, restock), `Bill` (totals, tax, print), `CustomerLedger` (customers, dues). Each owns its data and its rules.

**✅ SOLUTION 11.9** — Any coherent set earns full marks. Example set: Encapsulation = "medicine bottle with a childproof cap"; Abstraction = "ordering food — you don't interview the chef"; Inheritance = "a remix of a song keeps the original"; Polymorphism = "'delete' means different things for a photo, a file, and a contact."

**✅ SOLUTION 11.10** — Sample blueprint:
```
class Account   — state: owner, pin, balance
                  behavior: deposit(), withdraw(), verifyPin()
class Bank      — state: accounts[100], count
                  behavior: createAccount(), findAccount(), menu()
```
💡 **PRO TIP:** Keep this sketch — in Chapter 22 you'll compare it to the finished project and smile.

**✅ MINI CHALLENGE (sample code for one class)**
```cpp
#include <iostream>
#include <string>
using namespace std;

class Animal {                       // state + behavior, pillar: encapsulation
public:
    string name;
    string species;
    int    mealsPerDay;
    void feed()  { cout << name << " the " << species << " is eating 🍖\n"; }
    void sleep() { cout << name << " is sleeping 💤\n"; }
};

class Habitat {                      // CONTAINS animals
public:
    string zone;
    Animal resident;
    void showZone() {
        cout << "[" << zone << "] ";
        resident.feed();
    }
};

int main() {
    Habitat lions;
    lions.zone             = "Savanna Zone";
    lions.resident.name    = "Sheru";
    lions.resident.species = "Lion";
    lions.resident.mealsPerDay = 2;

    lions.showZone();
    lions.resident.sleep();
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ OOP organizes code around objects = state (data) + behavior (functions)
- ✓ Class = blueprint; object = the living thing built from it
- ✓ 4 pillars: Encapsulation (seal data), Abstraction (hide complexity), Inheritance (reuse), Polymorphism (one message, many behaviors)
- ✓ Design = honest nouns: list the things, then what each knows and does
- ✓ OOP's payoff is safety & scale — small programs gain little, real software gains everything

**📚 Keywords learned:** object, class, state, behavior, encapsulation, abstraction, inheritance, polymorphism, god class, object-oriented design

**🔗 Next chapter preview:** Chapter 12 — **Classes & Objects, for real**. `class` syntax in full: data members, member functions, `public`/`private`, getters & setters, the mysterious `this` pointer. The blueprint becomes a skyline. 🏙️

*The mindset chapter is behind you. Now the muscles.* 💪

---

**⬅️ [Chapter 10](chapter-10-pointers.md) | [🏠 Home](README.md) | [Chapter 12 ➡️](chapter-12-classes-objects.md)**
