# CHAPTER 15 — POLYMORPHISM

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Shout 'Draw yourself!' to a room of shapes —
 the circle draws a circle, the square a square.
 One command. Many behaviors."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 14](chapter-14-inheritance.md) | [🏠 Home](README.md) | [Chapter 16 ➡️](chapter-16-friend-static.md)**

---

## 📖 CHAPTER OPENING

A remote control with one button — "play" — that plays Spotify on your phone, Netflix on your TV, and a podcast in your car. Same button, right thing happens everywhere. **Polymorphism** ("many forms") is that button: one command sent to different objects, each responding in its own correct way.

### What you will learn:
- Compile-time polymorphism: function overloading + **operator overloading**
- Runtime polymorphism via `virtual` functions
- Why base-class pointers + virtual = superpower
- **Pure virtual** functions & **abstract classes** (interfaces)
- The vtable — how the magic actually works (simply)
- `virtual` destructors — the small keyword that prevents disasters

### Why this chapter matters:
Polymorphism is the pillar that makes big systems *extendable*: add a new shape/payment-method/weapon class, and existing code handles it **without being edited**. Game engines and plugin systems run on exactly this.

---

## 🔍 CONCEPT EXPLANATION

### What is polymorphism?

**Polymorphism** = "many forms": the same function *call* producing different behavior depending on the object. Two flavors:

| Flavor | Decided when | Tools | Example |
|---|---|---|---|
| **Compile-time** (static) | While compiling | Overloading, operator overloading | `add(1,2)` vs `add("a","b")` |
| **Runtime** (dynamic) | While running | `virtual` functions + base pointers | `shape->draw()` picks Circle or Square |

### Why do we use it?

Chapter 14's limiting flaw: an `Animal*` pointing at a `Dog` called **Animal's** methods, not Dog's. Polymorphism fixes that — the *actual object's* version runs, no matter what pointer type delivers the command. Build armies of different objects; command them uniformly.

### How does the computer understand it? (vtable, simply)

Marking a function `virtual` tells C++: *"resolve this call at runtime."* Each class with virtuals gets a hidden lookup table (**vtable**) — a menu of its actual function addresses. Every object secretly carries a pointer to its class's vtable. `p->speak()` becomes: *follow p to the object, find ITS class's vtable, run the address listed there.* One extra hop at runtime = correct behavior for any descendant, present or future.

---

## 📝 SYNTAX BOX

```cpp
// ---------- ① compile-time: overloading (recap, Ch. 7) ----------
int    add(int a, int b)        { return a + b; }
string add(string a, string b)  { return a + b; }   // same name, params differ

// ---------- ② compile-time: OPERATOR overloading ----------
class Vector2D {
public:
    double x, y;
    Vector2D(double x, double y) : x(x), y(y) { }
    Vector2D operator+(const Vector2D& other) const {   // teach '+' YOUR type
        return Vector2D(x + other.x, y + other.y);
    }
};
// Vector2D a(1,2), b(3,4); Vector2D c = a + b;   → (4,6)

// ---------- ③ runtime: VIRTUAL functions ----------
class Animal {
public:
    virtual void speak() { cout << "some sound\n"; }   // THE keyword
    virtual ~Animal() { }                               // (see mistake #2)
};

class Dog : public Animal {
public:
    void speak() { cout << "Woof!\n"; }                // override (exact match!)
};

// ---------- ④ PURE virtual → abstract class (interface) ----------
class Shape {
public:
    virtual double area() = 0;                         // "= 0" → no default body.
                                                       // Shape CANNOT be created.
    virtual ~Shape() { }
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) { }
    double area() { return 3.14159 * r * r; }          // MUST implement or also abstract
};

// Shape s;                 // ❌ ERROR — abstract classes can't instantiate
// Shape* p = new Circle(2); // ✅ the intended use: pointer to the contract
```

🔥 **REMEMBER:** Rules for true runtime overriding — base declares `virtual`, child uses the **exact same signature**, and the call travels through a **pointer or reference** to the base. Miss any one and you're back to Chapter 14's hiding.

---

## 💻 EXAMPLE CODES

### Example 15.1 — Operator Overloading: Teaching `+` New Tricks

```cpp
// ============================================
// Example 15.1: A Money Class That Adds Like Math
// ============================================
// Concepts used: operator+ overloading, const-correct returns, printing
// ============================================

#include <iostream>
using namespace std;

class Money {
    int rupees;
public:
    Money(int r = 0) : rupees(r) { }

    Money operator+(const Money& other) const {              // a + b
        return Money(rupees + other.rupees);
    }

    bool operator>(const Money& other) const {               // a > b
        return rupees > other.rupees;
    }

    void show() const { cout << "Rs. " << rupees << "\n"; }
};

int main() {

    Money wallet(500), bonus(250);
    Money total = wallet + bonus;         // looks like math; runs YOUR function
    total.show();                          // Rs. 750

    cout << (wallet > bonus ? "wallet wins\n" : "bonus wins\n");

    return 0;
}
/*
OUTPUT:
Rs. 750
wallet wins

EXPLANATION:
operators are just functions with heroic names: a + b really calls
a.operator+(b). Overload them so YOUR types behave like built-ins.
Compile-time polymorphism: the compiler picks the right '+' for the
types involved — no runtime cost at all.
*/
```

**What happened here?** `wallet + bonus` compiled to a function call on your class. This is why `string` lets you write `s1 + s2` — someone overloaded `+` for you.

---

### Example 15.2 — The Problem: Without `virtual` (The Wrong Voice)

```cpp
// ============================================
// Example 15.2: A Base Pointer Disrespecting Reality
// ============================================
// Concepts used: static binding — WHY we need virtual
// ============================================

#include <iostream>
using namespace std;

class Animal {
public:
    void speak() { cout << "Some generic sound\n"; }   // ⚠️ NO virtual
};

class Dog : public Animal {
public:
    void speak() { cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() { cout << "Meow!\n"; }
};

int main() {

    Animal* zoo[2];
    zoo[0] = new Dog();
    zoo[1] = new Cat();

    for (int i = 0; i < 2; i++) {
        zoo[i]->speak();            // ❗ "Some generic sound" TWICE!
    }

    delete zoo[0];
    delete zoo[1];
    return 0;
}
/*
OUTPUT:
Some generic sound
Some generic sound

EXPLANATION:
Without virtual, the compiler BINDS the call by the POINTER's type
(Animal*), not the object's type (Dog). The generic sound from a dog
is the classic symptom. Next example: one word fixes everything.
*/
```

**What happened here?** Static (compile-time) binding judged by the pointer's uniform, not the object inside. For commanding mixed object collections, that's exactly wrong.

---

### Example 15.3 — One Keyword Later: `virtual`

```cpp
// ============================================
// Example 15.3: Same Code + virtual = Correct Behavior
// ============================================
// Concepts used: virtual functions, runtime binding, base-pointer army
// ============================================

#include <iostream>
using namespace std;

class Animal {
public:
    virtual void speak() { cout << "Some generic sound\n"; }  // ✅ virtual!
    virtual ~Animal() { }                                       // virtual dtor — habit!
};

class Dog : public Animal {
public:
    void speak() { cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void speak() { cout << "Meow!\n"; }
};

int main() {

    Animal* zoo[3];
    zoo[0] = new Dog();
    zoo[1] = new Cat();
    zoo[2] = new Dog();

    for (int i = 0; i < 3; i++) {
        zoo[i]->speak();            // NOW each object answers as ITSELF
    }

    for (int i = 0; i < 3; i++) delete zoo[i];   // correct dtors via virtual ~

    return 0;
}
/*
OUTPUT:
Woof!
Meow!
Woof!

EXPLANATION:
The vtable mechanism: zoo[i] leads to the object; the object points
to ITS class's vtable; the vtable lists Dog::speak for dogs. Add
class Parrot tomorrow and this loop needs ZERO edits — that is the
polymorphism superpower: OPEN for extension, CLOSED for modification.
*/
```

**What happened here?** The loop is a conductor waving one baton; every musician plays their own instrument. New musicians join the orchestra without retraining the conductor.

---

### Example 15.4 — Pure Virtual & Abstract Classes: The Shape Contract

```cpp
// ============================================
// Example 15.4: Abstract Shape + a Gallery Loop
// ============================================
// Concepts used: pure virtual (= 0), abstract base as an interface,
//                array of base pointers, virtual destructor
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Shape {                               // ABSTRACT — a contract, not a thing
public:
    virtual double area()  = 0;             // every shape MUST define area
    virtual string name()  = 0;             // ...and a name
    virtual ~Shape() { }                    // safe deletes through base ptr
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) { }
    double area()  { return 3.14159 * r * r; }
    string name()  { return "Circle"; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double l, double w) : l(l), w(w) { }
    double area()  { return l * w; }
    string name()  { return "Rectangle"; }
};

class Triangle : public Shape {
    double b, h;
public:
    Triangle(double b, double h) : b(b), h(h) { }
    double area()  { return 0.5 * b * h; }
    string name()  { return "Triangle"; }
};

int main() {

    // Shape bad;                        // ❌ ERROR — can't instantiate abstract

    Shape* gallery[3];
    gallery[0] = new Circle(2);
    gallery[1] = new Rectangle(4, 6);
    gallery[2] = new Triangle(6, 4);

    double total = 0;
    for (int i = 0; i < 3; i++) {
        cout << gallery[i]->name() << ": " << gallery[i]->area() << "\n";
        total += gallery[i]->area();                 // uniform command, varied math
    }
    cout << "Total area: " << total << "\n";

    for (int i = 0; i < 3; i++) delete gallery[i];   // ~Shape() is virtual ✓

    return 0;
}
/*
OUTPUT:
Circle: 12.5664
Rectangle: 24
Triangle: 12
Total area: 48.5664

EXPLANATION:
= 0 makes a function pure virtual; one pure virtual makes the class
ABSTRACT — it can never be instantiated, only inherited. This is C++'s
way of enforcing a CONTRACT: "any shape joining my gallery must know its
area." Compilers then refuse any child that forgets.
*/
```

**What happened here?** Abstract classes are how teams set rules: *every payment method must implement `pay()`*, *every enemy must implement `attack()`*. The compiler becomes your contract enforcer.

---

### Example 15.5 — Real-World Combined: The Payment System

```cpp
// ============================================
// Example 15.5: Store Checkout With Pluggable Payment Methods
// ============================================
// Concepts used: abstract interface, polymorphic dispatch, operator overload,
//                a whole-mini-system with zero edits needed to extend
// ============================================

#include <iostream>
#include <string>
using namespace std;

// ---------- the CONTRACT ----------
class PaymentMethod {
public:
    virtual bool pay(double amount) = 0;   // true = success
    virtual string label()          = 0;
    virtual ~PaymentMethod() { }
};

// ---------- implementations ----------
class Cash : public PaymentMethod {
public:
    bool pay(double amount) {
        cout << "Paid Rs. " << amount << " in cash. 💵\n";
        return true;
    }
    string label() { return "Cash"; }
};

class EasyPaisa : public PaymentMethod {
    double balance;
public:
    EasyPaisa(double b) : balance(b) { }
    bool pay(double amount) {
        if (amount > balance) {
            cout << "EasyPaisa: insufficient balance! ❌\n";
            return false;
        }
        balance -= amount;
        cout << "Paid Rs. " << amount << " via EasyPaisa. Balance: "
             << balance << "\n";
        return true;
    }
    string label() { return "EasyPaisa"; }
};

class Card : public PaymentMethod {
public:
    bool pay(double amount) {
        cout << "Card charged Rs. " << amount << " (with 2% fee: "
             << amount * 0.02 << "). 💳\n";
        return true;
    }
    string label() { return "Card"; }
};

// ---------- the checkout — knows ONLY the interface ----------
void checkout(PaymentMethod& method, double amount) {
    cout << "[" << method.label() << "] ";
    method.pay(amount);
}

int main() {

    Cash      cash;
    EasyPaisa wallet(500);
    Card      card;

    checkout(cash,   300);          // works
    checkout(wallet, 300);          // works, balance drops to 200
    checkout(wallet, 300);          // refused — insufficient
    checkout(card,   300);          // works, adds fee

    // Tomorrow: class JazzCash : public PaymentMethod { ... }
    // checkout(jazzCash, 300);    ← ZERO changes to checkout()!

    return 0;
}
/*
OUTPUT:
[Cash] Paid Rs. 300 in cash. 💵
[EasyPaisa] Paid Rs. 300 via EasyPaisa. Balance: 200
[EasyPaisa] EasyPaisa: insufficient balance! ❌
[Card] Card charged Rs. 300 (with 2% fee: 6). 💳

EXPLANATION:
checkout() was written ONCE against the contract (PaymentMethod&).
Every implementation — existing or future — plugs in untouched.
This is how real systems (payments, plugins, game mods) stay
extendable for years: code against interfaces, not specifics.
*/
```

**What happened here?** Compile-time overloading (Ch. 7), operator overloading (Ex. 15.1), and runtime virtuals combined into a professional architecture. You now hold all of C++'s polymorphism.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Forgetting `virtual` in the base, overriding anyway**
```cpp
class Base { public: void go() { } };         // not virtual
class Kid : public Base { public: void go() { } };
Base* p = new Kid(); p->go();                 // runs BASE's go() 😱
```
✅ **Fix:** `virtual void go() { }` in the base. (In modern C++ `override` on the child turns this trap into a compile error — get the habit: `void go() override { }`.)

**❌ Mistake 2 — Deleting through a base pointer without a virtual destructor**
```cpp
class Base { public: ~Base() { } };
class Kid : public Base { public: ~Kid() { cout << "Kid cleaned\n"; } };
Base* p = new Kid();
delete p;                                     // ❌ Kid's dtor NEVER runs (leak!)
```
✅ **Fix:** Any class designed as a base: `virtual ~Base() { }`. Make it a reflex.

**❌ Mistake 3 — Trying to instantiate an abstract class**
```cpp
Shape s;      // ❌ error: cannot declare variable 's' to be of abstract type 'Shape'
```
✅ **Fix:** Abstract = contract only. Use pointers/references to it: `Shape* p = new Circle(2);`

**❌ Mistake 4 — Signature drift breaks the override silently**
```cpp
class Base { public: virtual void work(int x) { } };
class Kid : public Base { public: void work(double x) { } };  // NOT an override!
```
`p->work(5)` now runs Base's version. Worth than failing to compile.
✅ **Fix:** Exactly match types and const-ness, and add `override` — the compiler then verifies: `void work(int x) override`.

**❌ Mistake 5 — Object slicing**
```cpp
Kid k; Base b = k;        // ❌ b is a Base-value: kid parts SLICED OFF
b.go();                   // Base's go. The virtual system can't help VALUES.
```
✅ **Fix:** Polymorphism lives through pointers and references: `Base& b = k;`

**❌ Mistake 6 — Overloading operators bizarrely**
```cpp
Vector2D operator+(const Vector2D& other) {  // subtracts inside?! chaos
```
✅ **Fix:** Overload only with intuitive meaning (a + b should add). If you need weird behavior, write a named method. Operator overloading is read by everyone — surprises are bugs.

---

## 🧠 CONCEPT SUMMARY TABLE

| Tool | Kind | Use when |
|---|---|---|
| Function overloading | compile-time | same action, different inputs |
| `operatorX(...)` | compile-time | make custom types feel built-in |
| `virtual` | runtime | base pointers must find child behavior |
| `= 0` pure virtual | runtime | force children to implement (contract) |
| Abstract class | runtime | interfaces: many implementations behind one call |
| `virtual ~` | runtime | deleting children via base pointers |
| `override` (on child) | — (safety) | compiler-verifies true overrides |
| vtable (concept) | runtime mechanism | hidden per-class menu of real function addresses |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.1 ⭐
📋 Overload print(): int version prints "int: X", double prints
   "double: X.X", string prints "string: XX". Call all three.
📤 OUTPUT: three typed lines.
💡 HINT: Chapter 7 skill — this is compile-time polymorphism #1.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.2 ⭐
📋 class Score with operator+ (combines points) and operator>
   (compares). Show both operating on two objects.
📥 SAMPLE: Score a(80), b(120)
📤 OUTPUT: combined Score(200); (b > a) prints 1/true.
💡 HINT: Follow Money (Ex 15.1) exactly.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.3 ⭐
📋 Base Instrument virtual play() → "some tune"; children Guitar
   and Piano override. Use base POINTER array of 2 and play all.
📤 OUTPUT: "strum strum 🎸" and "plink plonk 🎹"
💡 HINT: virtual in the base; signatures match exactly.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.4 ⭐⭐
📋 Demonstrate the failure fixed by virtual: build Animal(non-virtual
   speak) → Dog with speak; call via Animal*; add as COMMENT the
   corrected virtual version. Note outputs difference in comments.
📤 OUTPUT: base message via pointer (the bug, documented).
💡 HINT: Mirror Examples 15.2 vs 15.3 side by side.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.5 ⭐⭐
📋 Abstract class Employee virtual pay() = 0; children Developer
   (hourly * hours) and Manager (fixed + bonus). payReport(Employee&)
   prints each person's pay through the interface.
📥 SAMPLE: Dev(1500/hr × 160) Mgr(200000 incl. bonus)
📤 OUTPUT: 240000 and 200000 printed via the SAME function.
💡 HINT: Function takes Employee& — interface coding like checkout().
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.6 ⭐⭐
📋 class Fraction with overloaded operator*: multiply two
   fractions (num1*num2 / den1*den2) and print "a/b" results.
📥 SAMPLE: (1/2) * (2/3)
📤 OUTPUT: 2/6
💡 HINT: operator* returns a new Fraction by value.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.7 ⭐⭐
📋 Vector2D from the syntax box + operator== (same x&y) and a NON-
   member-style print helper. Test + and == on three vectors.
📤 OUTPUT: sums and equality verdicts correct.
💡 HINT: bool operator==(const V&) const { compare both fields }.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.8 ⭐⭐⭐
📋 Abstract MediaPlayer with virtual open(), close(), play() all
   pure; class MP3Player implements all three with messages.
   Then class VideoPlayer. Polymorphic stage: base ptr array of
   2, open→play→close each. Verify no abstract instantiation.
📤 OUTPUT: ordered lifecycle lines for both players.
💡 HINT: Multiple pure virtuals = a richer contract.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.9 ⭐⭐⭐
📋 Bug-hunt file: a base pointer deletes a child whose dtor frees
   dynamic memory — WITHOUT virtual destructor. Write it as broken,
   explain the leak in comments, then write the FIXED version.
📤 OUTPUT: fixed version prints BOTH dtor messages.
💡 HINT: virtual ~Base(). Print messages to prove both dtors run.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 15.10 ⭐⭐⭐
📋 Game characters: abstract Character virtual attack()=0 + name();
   Warrior (sword 30 dmg), Archer (arrow 25 dmg), Mage (fireball
   45 dmg). Battle loop: array of 3 Character*, each attacks a
   dummy boss (pass target HP by reference down from 200). Print
   hits until HP <= 0, in array order.
📤 OUTPUT: lines like "Mage hits for 45! Boss HP: 80" ... till KO.
💡 HINT: for each in array: c->attack() returns dmg; subtract in
   main loop; cout via name().
```

---

## 🎯 MINI CHALLENGE — THE SHAPE GALLERY 2.0 🖼️

Level-up Example 15.4 into a **mini graphics pipeline**:

1. Abstract `Shape` with pure virtuals: `draw()` (prints ASCII of itself!), `area()`, `name()`
2. At least THREE implementations (`Circle`, `Rectangle`, `Triangle` — draw even crude ASCII)
3. A `Shape* gallery[5]` holding a MIX of your shapes (plus: add your own 4th shape class — e.g. `Diamond` — WITHOUT touching the loop!)
4. Loop 1: print each name + area
5. Loop 2: `draw()` each
6. Proper cleanup with virtual destructor

Success sign: adding `Diamond` required only NEW code, ZERO edits to old code. That is the Open/Closed Principle — and you just lived it. 🏛️

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 15.1**
```cpp
#include <iostream>
#include <string>
using namespace std;
void print(int x)         { cout << "int: " << x << "\n"; }
void print(double x)      { cout << "double: " << x << "\n"; }
void print(string x)      { cout << "string: " << x << "\n"; }
int main() { print(5); print(2.5); print("hey"); return 0; }
```

**✅ SOLUTION 15.2**
```cpp
#include <iostream>
using namespace std;
class Score {
    int points;
public:
    Score(int p = 0) : points(p) { }
    Score operator+(const Score& o) const { return Score(points + o.points); }
    bool  operator>(const Score& o) const { return points > o.points; }
    void show() const { cout << "Score(" << points << ")\n"; }
};
int main() {
    Score a(80), b(120);
    (a + b).show();                       // Score(200)
    cout << (b > a) << "\n";              // 1
    return 0;
}
```

**✅ SOLUTION 15.3**
```cpp
#include <iostream>
using namespace std;
class Instrument {
public: virtual void play() { cout << "some tune\n"; }
        virtual ~Instrument() { }
};
class Guitar : public Instrument { public: void play() { cout << "strum strum 🎸\n"; } };
class Piano  : public Instrument { public: void play() { cout << "plink plonk 🎹\n"; } };
int main() {
    Instrument* band[2] = { new Guitar(), new Piano() };
    for (auto i : band) i->play();
    for (auto i : band) delete i;
    return 0;
}
```
💡 **PRO TIP:** `for (auto i : band)` is the range-for (C++11) — cleaner arrays walking; Chapter 19 uses it constantly.

**✅ SOLUTION 15.4**
```cpp
#include <iostream>
using namespace std;
class Animal { public: void speak() { cout << "generic\n"; } };       // broken setup
class Dog : public Animal { public: void speak() { cout << "Woof\n"; } };

// FIXED base:  class Animal { public: virtual void speak(){...} };
// → then Animal* calls print "Woof", not "generic".

int main() {
    Animal* p = new Dog();
    p->speak();          // prints "generic" — static binding on display
    delete p;
    return 0;
}
```

**✅ SOLUTION 15.5**
```cpp
#include <iostream>
using namespace std;
class Employee {
public: virtual double pay() = 0;
        virtual ~Employee() { }
};
class Developer : public Employee {
    double rate; int hours;
public: Developer(double r, int h) : rate(r), hours(h) { }
    double pay() { return rate * hours; }
};
class Manager : public Employee {
    double fixed, bonus;
public: Manager(double f, double b) : fixed(f), bonus(b) { }
    double pay() { return fixed + bonus; }
};
void payReport(Employee& e) { cout << "Pay: Rs. " << e.pay() << "\n"; }

int main() {
    Developer d(1500, 160);
    Manager   m(180000, 20000);
    payReport(d);        // 240000
    payReport(m);        // 200000
    return 0;
}
```

**✅ SOLUTION 15.6**
```cpp
#include <iostream>
using namespace std;
class Fraction {
    int n, d;
public:
    Fraction(int n, int d) : n(n), d(d) { }
    Fraction operator*(const Fraction& o) const {
        return Fraction(n * o.n, d * o.d);
    }
    void show() const { cout << n << "/" << d << "\n"; }
};
int main() {
    Fraction a(1, 2), b(2, 3);
    (a * b).show();      // 2/6
    return 0;
}
```

**✅ SOLUTION 15.7**
```cpp
#include <iostream>
using namespace std;
class Vector2D {
public:
    double x, y;
    Vector2D(double x = 0, double y = 0) : x(x), y(y) { }
    Vector2D operator+(const Vector2D& o) const { return Vector2D(x + o.x, y + o.y); }
    bool operator==(const Vector2D& o)    const { return x == o.x && y == o.y; }
};
void show(const Vector2D& v) { cout << "(" << v.x << ", " << v.y << ")\n"; }

int main() {
    Vector2D a(1, 2), b(3, 4), c(1, 2);
    show(a + b);                          // (4, 6)
    cout << (a == c) << (a == b) << "\n"; // 1 0
    return 0;
}
```

**✅ SOLUTION 15.8**
```cpp
#include <iostream>
using namespace std;
class MediaPlayer {
public:
    virtual void open()  = 0;
    virtual void play()  = 0;
    virtual void close() = 0;
    virtual ~MediaPlayer() { }
};
class MP3Player : public MediaPlayer {
public:
    void open()  { cout << "MP3 opened\n";  }
    void play()  { cout << "MP3 playing 🎵\n"; }
    void close() { cout << "MP3 closed\n";  }
};
class VideoPlayer : public MediaPlayer {
public:
    void open()  { cout << "Video opened\n";  }
    void play()  { cout << "Video playing 🎬\n"; }
    void close() { cout << "Video closed\n";  }
};
int main() {
    MediaPlayer* stage[2] = { new MP3Player(), new VideoPlayer() };
    for (auto p : stage) { p->open(); p->play(); p->close(); delete p; }
    return 0;
}
```

**✅ SOLUTION 15.9**
```cpp
#include <iostream>
using namespace std;

// BROKEN version (commented out):
// class Base { public: ~Base() { cout << "Base dtor\n"; } };
// class Kid : public Base { public: ~Kid() { cout << "Kid freed buffer\n"; } };
// Base* p = new Kid(); delete p;  → ONLY "Base dtor" prints → buffer leaks!

// FIXED:
class Base {
public: virtual ~Base() { cout << "Base dtor\n"; }        // THE one-word fix
};
class Kid : public Base {
    int* buffer;
public:
    Kid()  : buffer(new int[10]) { }
    ~Kid() { delete[] buffer; cout << "Kid freed buffer\n"; }
};
int main() {
    Base* p = new Kid();
    delete p;               // prints: Kid freed buffer → Base dtor ✓
    return 0;
}
```

**✅ SOLUTION 15.10**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Character {
public: virtual int attack() = 0; virtual string name() = 0;
        virtual ~Character() { }
};
class Warrior : public Character {
public: int attack() { return 30; } string name() { return "Warrior"; }
};
class Archer  : public Character {
public: int attack() { return 25; } string name() { return "Archer";  }
};
class Mage    : public Character {
public: int attack() { return 45; } string name() { return "Mage";    }
};

int main() {
    Character* party[3] = { new Warrior(), new Archer(), new Mage() };
    int bossHP = 200;

    for (auto c : party) {
        if (bossHP <= 0) break;
        int dmg = c->attack();
        bossHP -= dmg;
        cout << c->name() << " hits for " << dmg << "! Boss HP: " << bossHP << "\n";
    }
    if (bossHP <= 0) cout << "Boss defeated! ⚔️\n";

    for (auto c : party) delete c;
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Compile-time polymorphism: overload functions AND operators (`a + b` can run your code)
- ✓ Runtime polymorphism needs 3 things: `virtual` in base, exact signature match, call through pointer/reference
- ✓ `= 0` makes a function pure virtual; one pure virtual makes the class abstract — a compiler-enforced contract
- ✓ Base classes get `virtual ~Destructors()` — always, as a reflex
- ✓ Code against interfaces (base types), and adding new implementations costs ZERO edits to old code

**📚 Keywords learned:** polymorphism, compile-time vs runtime binding, operator overloading, virtual function, vtable, pure virtual, abstract class, virtual destructor, object slicing, override, open/closed principle

**🔗 Next chapter preview:** Chapter 16 — **Friend Functions & Static Members**. Two specialist tools: `friend` lets trusted outsiders peek inside your privates, and `static` creates data shared by an entire class (plus the famous Singleton — a class allowed exactly ONE object). 🤝

*One baton, whole orchestra. Polymorphism is the pillar where OOP's payoffs become undeniable.* 🎼

---

**⬅️ [Chapter 14](chapter-14-inheritance.md) | [🏠 Home](README.md) | [Chapter 16 ➡️](chapter-16-friend-static.md)**
