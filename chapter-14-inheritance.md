# CHAPTER 14 — INHERITANCE

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A child inherits their parents' traits —
 then adds talents that are all their own."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 13](chapter-13-constructors-destructors.md) | [🏠 Home](README.md) | [Chapter 15 ➡️](chapter-15-polymorphism.md)**

---

## 📖 CHAPTER OPENING

You're designing a game: Player, Enemy, Boss. All three have health, a name, and a position; each fights differently. Do you write health/name/position code THREE times? Of course not — write it once in `Character`, and let `Player`, `Enemy`, and `Boss` **inherit** it, adding only their differences. Genetics for code.

### What you will learn:
- What inheritance is and the "is-a" relationship
- Base class & derived class syntax (`: public Base`)
- The four types: single, multilevel, hierarchical, multiple
- `protected` — the access level made exactly for families
- Constructor/destructor order across generations
- Method **overriding** — children rewriting inherited behavior
- Reaching the parent's version with `Base::`

### Why this chapter matters:
Inheritance is how real software avoids duplication at scale. Operating systems, game engines, and GUI frameworks are inheritance cities. Done right, changing ONE base class upgrades every descendant automatically.

---

## 🔍 CONCEPT EXPLANATION

### What is inheritance?

**Inheritance** lets a class (**derived/child**) automatically receive all data members and member functions of another class (**base/parent**), then add or change behavior.

```cpp
class Animal {                  // BASE — the shared traits
public:
    void breathe() { /*...*/ }
};

class Dog : public Animal {     // DERIVED — "a Dog IS-AN Animal"
public:
    void bark() { /*...*/ }     // only the NEW stuff
};
// Dog now has BOTH breathe() and bark().
```

### Why do we use it?

1. **No duplication** — shared code lives once
2. **Hierarchy matches reality** — Vehicle→Car→Taxi reads like the world
3. **Fix once, heal everywhere** — improve the base, children improve free

**The "is-a" test:** inherit only when the sentence makes sense — *Dog is an Animal* ✓, *Car is a Driver* ✗ (a car HAS a driver → composition, like Example 11.3's Order).

### How does the computer handle it?

A `Dog` object literally contains an `Animal` object embedded inside (its own `Animal` part) plus its extras. Construction builds base-first (parent born before child's additions make sense); destruction unwinds child-first.

---

## 📝 SYNTAX BOX

```cpp
// ---------- basic shape ----------
class Base {
protected:                      // visible to ME and my CHILDREN only
    int familyValue = 10;
public:
    void hello() { cout << "Hello from Base\n"; }
};

class Derived : public Base {   // "Derived IS-A Base" (public inheritance)
public:
    void show() {
        cout << familyValue << "\n";   // protected → usable here directly
    }
};

// ---------- constructor passing upward ----------
class Person {
protected:
    string name;
public:
    Person(string n) : name(n) { }
};

class Student : public Person {
    int roll;
public:
    Student(string n, int r) : Person(n), roll(r) { }   // feed the parent FIRST
};

// ---------- overriding + calling parent's version ----------
class Printer {
public:
    void print() { cout << "base print\n"; }
};
class FancyPrinter : public Printer {
public:
    void print() {                    // OVERRIDES parent's print
        cout << "*** ";
        Printer::print();             // reuse parent's version inside!
        cout << " ***\n";
    }
};
```

**The four types at a glance:**

```cpp
class B : public A { };                        // ① SINGLE
class C : public B { };                        // ② MULTILEVEL (A→B→C)
class D : public A { }; class E : public A { };// ③ HIERARCHICAL (A→{D,E})
class F : public X, public Y { };              // ④ MULTIPLE (two parents)
```

| Access in base | Visible in child (public inheritance)? |
|---|---|
| `public:` | Yes, as public |
| `protected:` | Yes, as protected |
| `private:` | **Invisible** — inherited but unreachable directly |

---

## 💻 EXAMPLE CODES

### Example 14.1 — Simplest Inheritance: Free Gifts

```cpp
// ============================================
// Example 14.1: Dog Gets Animal's Powers Free
// ============================================
// Concepts used: single inheritance, : public Base
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Animal {                          // BASE
protected:
    string name = "Animal";             // protected: kids can use it
public:
    void breathe() { cout << name << " breathes...\n"; }
    void eat()     { cout << name << " eats...\n";     }
};

class Dog : public Animal {             // DERIVED — gains everything above
public:
    Dog(string n) { name = n; }         // allowed: name is protected
    void bark() { cout << name << ": Woof!\n"; }
};

int main() {

    Dog rex("Rex");

    rex.breathe();      // ← inherited from Animal, zero lines written
    rex.eat();          // ← inherited
    rex.bark();         // ← Dog's own talent

    return 0;
}
/*
OUTPUT:
Rex breathes...
Rex eats...
Rex: Woof!

EXPLANATION:
rex is BOTH an Animal and a Dog in one body. All of Animal's
public/protected members came along for free. Write shared code
ONCE in the base; children spend their lines on what's unique.
*/
```

**What happened here?** Inheritance's whole promise: `Dog` wrote 3 lines and owned 3 behaviors. Imagine 20 animal classes sharing `Animal` — the savings multiply.

---

### Example 14.2 — Constructor Chain: Parent Born First

```cpp
// ============================================
// Example 14.2: Feeding Arguments Upward
// ============================================
// Concepts used: base constructor call in initializer list, ctor/dtor order
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int    age;
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "  [Person born: " << name << "]\n";
    }
    ~Person() { cout << "  [Person gone: " << name << "]\n"; }
    void introduce() { cout << "I'm " << name << ", " << age << " years old.\n"; }
};

class Student : public Person {
    int roll;
public:
    // : Person(n, a) sends arguments UP — parent part built first
    Student(string n, int a, int r) : Person(n, a), roll(r) {
        cout << "  [Student born: roll " << roll << "]\n";
    }
    ~Student() { cout << "  [Student gone]\n"; }
    void study() { cout << name << " is studying. 📚\n"; }
};

int main() {

    Student s("Ayesha", 19, 101);
    s.introduce();      // parent's method
    s.study();          // child's method

    return 0;
}
/*
OUTPUT:
  [Person born: Ayesha]
  [Student born: roll 101]
I'm Ayesha, 19 years old.
Ayesha is studying. 📚
  [Student gone]
  [Person gone: Ayesha]

EXPLANATION:
Construction: Person first, Student additions second — you can't
build the second floor before the ground floor. Destruction:
exactly reversed (child demolished first). Missing : Person(n,a)
when the base HAS no default constructor → compile error; now you
know why mysterious "no default constructor" errors appear.
*/
```

**What happened here?** The initializer list is the courier carrying birth documents *upward*. Order of ctors: grandparent → parent → child; dtors reverse.

---

### Example 14.3 — Multilevel: Three Generations

```cpp
// ============================================
// Example 14.3: Vehicle → Car → ElectricCar
// ============================================
// Concepts used: multilevel inheritance, accumulate features down the line
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Vehicle {                          // grandparent
protected:
    int wheels = 4;
public:
    void start() { cout << "Engine roaring (or whirring).\n"; }
};

class Car : public Vehicle {             // parent
public:
    void openTrunk() { cout << "Trunk open.\n"; }
};

class ElectricCar : public Car {         // child — has EVERYTHING above
    int batteryKwh = 75;
public:
    void charge() { cout << "Charging " << batteryKwh << " kWh 🔋\n"; }
    void spec()   { cout << "Electric car, " << wheels << " wheels.\n"; }
};

int main() {

    ElectricCar tesla;
    tesla.start();          // from Vehicle (grandparent)
    tesla.openTrunk();      // from Car (parent)
    tesla.charge();         // its own
    tesla.spec();

    return 0;
}
/*
OUTPUT:
Engine roaring (or whirring).
Trunk open.
Charging 75 kWh 🔋
Electric car, 4 wheels.

EXPLANATION:
Each generation adds its own floor to the building, inheriting all
below. An ElectricCar IS-A Car IS-A Vehicle. Perfectly natural
sentence chain = healthy design.
*/
```

---

### Example 14.4 — Hierarchical + Overriding: The Shape Family

```cpp
// ============================================
// Example 14.4: One Parent, Many Children (and children's own ways)
// ============================================
// Concepts used: hierarchical inheritance, method overriding, Base:: reuse
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string name = "Shape";
public:
    void describe() {                       // inherited by ALL children
        cout << name << ": area = ";
    }
    void print() { cout << "generic shape\n"; }
};

class Circle : public Shape {
    double r;
public:
    Circle(double radius) { r = radius; name = "Circle"; }
    void print() {                          // OVERRIDES parent's print
        cout << "a circle, really round\n";
    }
    double area() { return 3.14159 * r * r; }
};

class Rectangle : public Shape {
    double l, w;
public:
    Rectangle(double a, double b) { l = a; w = b; name = "Rectangle"; }
    void print() {                          // another override
        describe();                         // PLUS reuse of base method!
        cout << "four right angles\n";
    }
    double area() { return l * w; }
};

int main() {

    Circle   c(3);
    Rectangle r(4, 6);

    c.describe(); cout << c.area() << "\n";   // Circle: area = 28.2743
    r.describe(); cout << r.area() << "\n";   // Rectangle: area = 24

    c.print();      // child's version runs — parent's is HIDDEN
    r.print();      // shows describe() + its twist

    return 0;
}
/*
OUTPUT:
Circle: area = 28.2743
Rectangle: area = 24
a circle, really round
Rectangle: area = four right angles

EXPLANATION:
Two children of Shape = hierarchical inheritance. When a child
redefines a parent's method, the child's HIDES the parent's for
child objects (print() here). Shape::print() still exists — call
it explicitly when needed. TRUE runtime flexibility needs virtual
functions — that's Chapter 15's grand finale.
*/
```

**What happened here?** Overriding = children custom-fit inherited behavior. `describe()` shows the lovely pattern of building child features ON TOP of base features.

---

### Example 14.5 — Multiple Inheritance: Two Parents (Carefully!)

```cpp
// ============================================
// Example 14.5: A SmartPrinter = Printer + Scanner
// ============================================
// Concepts used: inheriting from two bases, member-name collisions
// ============================================

#include <iostream>
#include <string>
using namespace std;

class Printer {
public:
    void printDoc()  { cout << "Printing 🖨️\n"; }
    void status()    { cout << "Printer ready\n"; }
};

class Scanner {
public:
    void scanDoc()   { cout << "Scanning 📄\n"; }
    void status()    { cout << "Scanner ready\n"; }   // ⚠️ same name clash!
};

class SmartPrinter : public Printer, public Scanner {  // TWO parents
public:
    void status() {                          // resolve by overriding…
        Printer::status();                   // …while keeping both parents'
        Scanner::status();                   // versions reachable by name
    }
};

int main() {

    SmartPrinter office;
    office.printDoc();          // from Printer
    office.scanDoc();           // from Scanner
    office.status();            // the composed one

    office.Printer::status();   // explicit: dad's version only
    office.Scanner::status();   // explicit: mom's version only

    return 0;
}
/*
OUTPUT:
Printing 🖨️
Scanning 📄
Printer ready
Scanner ready
Printer ready
Scanner ready

EXPLANATION:
Multiple inheritance gives both parents' toolkits at once, but
name clashes need explicit  Parent::member  resolution. Powerful —
yet responsible for infamous complexity (the "diamond problem",
advanced topic). Use it when genuinely IS-A both; otherwise
prefer composition like Chapter 11's Order example.
*/
```

**What happened here?** `Parent::name` is the diplomatic way to settle which parent's traits you mean. When clashing names become frequent, that's the design hint that composition might be cleaner.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Forgetting `public` in the inheritance clause**
```cpp
class Dog : Animal { };     // ❌ default is PRIVATE inheritance —
                            // Animal's members shrink to private in Dog!
```
✅ **Fix:** `class Dog : public Animal { };` — "is-a" basically always means public inheritance. Private inheritance is an advanced, rare tool.

**❌ Mistake 2 — Accessing parent's private members from the child**
```cpp
class Base   { private: int secret; };
class Child : public Base {
    void f() { secret = 1; }    // ❌ private is invisible even to children
};
```
✅ **Fix:** Make it `protected:` (family access) or expose a guarded getter/setter.

**❌ Mistake 3 — Not feeding a parameterized base constructor**
```cpp
class Person  { public: Person(string n) { } };          // no default ctor
class Student : public Person { public: Student() { } }; // ❌ compile error!
```
Compiler says: `no matching function for call to 'Person::Person()'`
✅ **Fix:** `Student() : Person("?") { }` — the child MUST deliver the parent's birth documents.

**❌ Mistake 4 — Expecting virtual behavior without virtual**
```cpp
Animal* p = new Dog();
p->speak();               // calls ANIMAL's version if speak() isn't virtual!
```
✅ **Fix:** Preview of Ch. 15 — declare `virtual void speak()` in the base. Non-virtual calls through base pointers use the STATIC type (Animal), not the real object (Dog). Whole next chapter on this.

**❌ Mistake 5 — Deep inheritance chains for tiny differences**
```
Person → Worker → OfficeWorker → JuniorOfficeWorker → Intern 😵
```
✅ **Fix:** 2–3 levels is healthy; beyond that, each hop is mental overhead. Prefer adding small differences via data (a `role` string) or composition.

**❌ Mistake 6 — Accidental hiding via slightly-different signatures**
```cpp
class Base  { public: void show(int x) { } };
class Child : public Base {
public:
    void show() { }       // ⚠️ hides Base::show(int) too! base versions vanish
};
```
✅ **Fix:** Redefining ANY overload hides all same-named base overloads. Call `Base::show(5)` explicitly or add `using Base::show;` inside the child. And when overriding for polymorphism, exact `virtual` matching applies (Ch. 15).

---

## 🧠 CONCEPT SUMMARY TABLE

| Concept | Syntax | Remember |
|---|---|---|
| Inherit | `class Child : public Parent { };` | "is-a" relationship only |
| `protected` | between private & public | visible to the family |
| Base ctor call | `: Parent(args)` in init list | parent born FIRST |
| Overriding | redefine parent's method in child | child version wins for child objects |
| Parent's version | `Parent::method()` | reuse inside the override |
| Single | `B : public A` | one parent |
| Multilevel | `C : public B : public A` | ancestry chain |
| Hierarchical | `B, C, D : public A` | siblings |
| Multiple | `F : public X, public Y` | resolve clashes with `X::` / `Y::` |
| private in base | — | inherited but child-invisible |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.1 ⭐
📋 Base: Animal (breathe()). Derived: Cat (meow()). Show a Cat
   doing both.
📤 OUTPUT: "All animals breathe." + "Meow!"
💡 HINT: : public Animal, nothing else needed.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.2 ⭐
📋 Base: Vehicle with start() printing "Vehicle starting".
   Derived: Bike overriding start() to print "Bike starting"
   AND calling Vehicle's too (two lines output).
📤 OUTPUT:
Vehicle starting
Bike starting
💡 HINT: Vehicle::start(); inside the override.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.3 ⭐
📋 Hierarchical: base Appliance (brand member, ctor). Children
   Fan (spin()) and Heater (heat()). Create one of each.
📤 OUTPUT: both objects use their parent's brand + own action.
💡 HINT: Two classes both ': public Appliance'.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.4 ⭐⭐
📋 Base BankAccount (protected balance; ctor opening deposit;
   deposit(), show()). Derived SavingsAccount adding
   addInterest(rate) that grows balance by rate%.
📥 SAMPLE: open 10000, interest 5%
📤 OUTPUT: balance 10500 shown via inherited show().
💡 HINT: Child can touch protected balance directly.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.5 ⭐⭐
📋 Multilevel chain: LivingThing (alive=true) → Human (name,
   speak()) → Programmer (code()). Print construction order
   from all three ctors.
📤 OUTPUT: three "[...] born" lines, grandparent first.
💡 HINT: Chain with : Human(n) : LivingThing() etc.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.6 ⭐⭐
📋 Base Employee (name, salary; showSalary()). Derived Manager
   (bonus; showTotal() printing salary+bonus via inherited
   getter). Guard: salary setter rejects negatives.
📥 SAMPLE: ("Raza", 80000, 15000)
📤 OUTPUT: Total pay: 95000 (and negative salary rejected)
💡 HINT: getSalary() inside child; validation rules live in base.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.7 ⭐⭐
📋 Override practice: base Printer print() → "ink on paper";
   derived LaserPrinter print() → parent's line + " at 600dpi".
📤 OUTPUT:
ink on paper
 at 600dpi
💡 HINT: Printer::print(); without re-declaring members.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.8 ⭐⭐⭐
📋 Multiple inheritance: classes Camera (takePhoto()) and
   MusicPlayer (playSong()); child Smartphone inherits both +
   adds status() calling BOTH parents' summary functions
   (each parent has its own deviceInfo() printing its kind).
📤 OUTPUT: photo + song + two info lines via status().
💡 HINT: : public Camera, public MusicPlayer; use Camera::deviceInfo().
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.9 ⭐⭐⭐
📋 Constructor math chain: base Point2D(x,y) → child Point3D(x,y,z)
   with distanceToOrigin() overridden to the 3D formula; both
   print their distances for input (3,4) and (3,4,12).
📤 OUTPUT:
2D: 5
3D: 13
💡 HINT: sqrt not needed if you print squared distance — or use
   sqrt(x*x+y*y+z*z) from <cmath>. 3²+4²+12²=169=13²  ✔
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 14.10 ⭐⭐⭐
📋 Mini payroll hierarchy: base Staff (name, base salary);
   children Teacher (+subjectPay 10k) and Manager (+teamBonus
   20k), each overriding getPay() = salary + extra. Print both
   pays via a function that accepts ANY Staff-like object by
   REFERENCE and calls showPay() (non-virtual is OK here —
   compare with what Ch. 15 will make possible!).
📥 SAMPLE: Staff s("A",50000) → Teacher("B",50000) → Manager("C",50000)
📤 OUTPUT: 50000 / 60000 / 70000
💡 HINT: Each child calls Staff::getPay() then adds its extra.
```

---

## 🎯 MINI CHALLENGE — THE SCHOOL DIRECTORY 🏫

Build this hierarchy and a small `main` demo:

```
Person (name, age; describe())
 ├── Teacher (subject, salary; describe() override →
 │            Person::describe() + ", teaches <subject>")
 └── Student (roll, gpa; describe() override →
              Person::describe() + ", studies hard")
```

Demo: create 1 Teacher + 1 Student, call describe() on each. Then add a `Principal` class that inherits Teacher with an extra `officeNo` (multilevel!) and describe() printing all four facts.

Golden rule demonstrated: every `describe()` **reuses** its parent's via `Parent::describe()`, never duplicating a line. When your directory prints perfectly, inheritance has clicked permanently. 🎓

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 14.1**
```cpp
#include <iostream>
using namespace std;
class Animal { public: void breathe() { cout << "All animals breathe.\n"; } };
class Cat : public Animal { public: void meow() { cout << "Meow!\n"; } };

int main() {
    Cat c;
    c.breathe();
    c.meow();
    return 0;
}
```

**✅ SOLUTION 14.2**
```cpp
#include <iostream>
using namespace std;
class Vehicle { public: void start() { cout << "Vehicle starting\n"; } };
class Bike : public Vehicle {
public:
    void start() {
        Vehicle::start();               // the polite reuse pattern
        cout << "Bike starting\n";
    }
};
int main() { Bike b; b.start(); return 0; }
```

**✅ SOLUTION 14.3**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Appliance {
protected: string brand;
public:    Appliance(string b) : brand(b) { }
    void label() { cout << brand << " appliance\n"; }
};
class Fan : public Appliance {
public: Fan(string b) : Appliance(b) { }
    void spin() { cout << brand << " fan spinning 🌀\n"; }
};
class Heater : public Appliance {
public: Heater(string b) : Appliance(b) { }
    void heat() { cout << brand << " heater warming 🔥\n"; }
};
int main() {
    Fan f("Super Asia");   f.label(); f.spin();
    Heater h("Rinnai");    h.label(); h.heat();
    return 0;
}
```

**✅ SOLUTION 14.4**
```cpp
#include <iostream>
using namespace std;
class BankAccount {
protected: double balance;
public:
    BankAccount(double b) : balance(b) { }
    void deposit(double x) { if (x > 0) balance += x; }
    void show() { cout << "Balance: Rs. " << balance << "\n"; }
};
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(double b) : BankAccount(b) { }
    void addInterest(double rate) { balance += balance * rate / 100; }
};
int main() {
    SavingsAccount s(10000);
    s.addInterest(5);
    s.show();                 // Balance: Rs. 10500
    return 0;
}
```
💡 **PRO TIP:** `protected` keeps outsiders out but children in — precisely what it was invented for.

**✅ SOLUTION 14.5**
```cpp
#include <iostream>
#include <string>
using namespace std;
class LivingThing {
protected: bool alive = true;
public:    LivingThing() { cout << "[LivingThing born]\n"; }
};
class Human : public LivingThing {
protected: string name;
public:    Human(string n) : name(n) { cout << "[Human born]\n"; }
    void speak() { cout << name << " speaks.\n"; }
};
class Programmer : public Human {
public:    Programmer(string n) : Human(n) { cout << "[Programmer born]\n"; }
    void code() { cout << name << " writes C++.\n"; }
};
int main() {
    Programmer p("Hira");
    p.speak(); p.code();
    return 0;
}
```

**✅ SOLUTION 14.6**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Employee {
protected: string name; double salary;
public:
    Employee(string n, double s) : name(n) { setSalary(s); }
    void setSalary(double s) { if (s >= 0) salary = s; else cout << "No negatives!\n"; }
    double getSalary() { return salary; }
    void showSalary() { cout << name << ": Rs. " << salary << "\n"; }
};
class Manager : public Employee {
    double bonus;
public:
    Manager(string n, double s, double b) : Employee(n, s), bonus(b) { }
    void showTotal() { cout << name << " total: Rs. " << getSalary() + bonus << "\n"; }
};
int main() {
    Manager m("Raza", 80000, 15000);
    m.showTotal();
    m.setSalary(-1);
    return 0;
}
```

**✅ SOLUTION 14.7**
```cpp
#include <iostream>
using namespace std;
class Printer { public: void print() { cout << "ink on paper\n"; } };
class LaserPrinter : public Printer {
public:
    void print() { Printer::print(); cout << " at 600dpi\n"; }
};
int main() { LaserPrinter lp; lp.print(); return 0; }
```

**✅ SOLUTION 14.8**
```cpp
#include <iostream>
using namespace std;
class Camera {
public: void takePhoto()  { cout << "📸 shot\n"; }
        void deviceInfo() { cout << "Camera module online\n"; }
};
class MusicPlayer {
public: void playSong()   { cout << "🎵 playing\n"; }
        void deviceInfo() { cout << "Music module online\n"; }
};
class Smartphone : public Camera, public MusicPlayer {
public:
    void status() { Camera::deviceInfo(); MusicPlayer::deviceInfo(); }
};
int main() {
    Smartphone s;
    s.takePhoto(); s.playSong(); s.status();
    return 0;
}
```

**✅ SOLUTION 14.9**
```cpp
#include <iostream>
#include <cmath>
using namespace std;
class Point2D {
protected: double x, y;
public:
    Point2D(double x, double y) : x(x), y(y) { }
    double dist() { return sqrt(x * x + y * y); }
};
class Point3D : public Point2D {
    double z;
public:
    Point3D(double x, double y, double z) : Point2D(x, y), z(z) { }
    double dist() { return sqrt(x * x + y * y + z * z); }   // hides 2D version
};
int main() {
    Point2D a(3, 4);
    Point3D b(3, 4, 12);
    cout << "2D: " << a.dist() << "\n";     // 5
    cout << "3D: " << b.dist() << "\n";     // 13
    return 0;
}
```

**✅ SOLUTION 14.10**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Staff {
protected: string name; double salary;
public:
    Staff(string n, double s) : name(n), salary(s) { }
    virtual double getPay() { return salary; }      // Ch.15 preview: virtual!
    void showPay() { cout << name << ": Rs. " << getPay() << "\n"; }
};
class Teacher : public Staff {
public:
    Teacher(string n, double s) : Staff(n, s) { }
    double getPay() { return Staff::getPay() + 10000; }
};
class Manager : public Staff {
public:
    Manager(string n, double s) : Staff(n, s) { }
    double getPay() { return Staff::getPay() + 20000; }
};
int main() {
    Staff   a("A", 50000);
    Teacher b("B", 50000);
    Manager c("C", 50000);
    a.showPay();   // 50000
    b.showPay();   // 60000 — and with virtual, works through base refs too
    c.showPay();   // 70000
    return 0;
}
```
💡 **PRO TIP:** The `virtual` keyword just slipped in. Chapter 15 will explain why it's the difference between "sometimes right" and "always right".

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
#include <string>
using namespace std;
class Person {
protected: string name; int age;
public:
    Person(string n, int a) : name(n), age(a) { }
    void describe() { cout << name << ", " << age; }
};
class Teacher : public Person {
    string subject; double salary;
public:
    Teacher(string n, int a, string s, double sal)
        : Person(n, a), subject(s), salary(sal) { }
    void describe() { Person::describe(); cout << ", teaches " << subject; }
};
class Student : public Person {
    int roll; double gpa;
public:
    Student(string n, int a, int r, double g)
        : Person(n, a), roll(r), gpa(g) { }
    void describe() { Person::describe(); cout << ", studies hard (GPA " << gpa << ")"; }
};
class Principal : public Teacher {
    int officeNo;
public:
    Principal(string n, int a, string s, double sal, int o)
        : Teacher(n, a, s, sal), officeNo(o) { }
    void describe() { Teacher::describe(); cout << ", office " << officeNo; }
};
int main() {
    Teacher  t("Ms. Khan", 34, "Math", 90000);
    Student  s("Ali", 17, 101, 3.6);
    Principal p("Mr. Ahmed", 50, "Physics", 150000, 7);
    t.describe(); cout << "\n";
    s.describe(); cout << "\n";
    p.describe(); cout << "\n";
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Inheritance = "is-a" reuse: `class Child : public Parent { }`
- ✓ `protected` is family-only access; base constructors eat first via `: Parent(args)`
- ✓ Birth order: ancestors first; death: exactly reversed
- ✓ Four types: single, multilevel, hierarchical, multiple (clashes → `Parent::`)
- ✓ Overriding hides the parent version for child objects; reuse it inside with `Parent::method()`

**📚 Keywords learned:** base class, derived class, `protected`, single/multilevel/hierarchical/multiple inheritance, constructor chaining, overriding, name hiding, `Parent::method()`

**🔗 Next chapter preview:** Chapter 15 — **Polymorphism**. Here's a puzzle: `Animal* p = new Dog(); p->speak();` — which `speak()` runs? Today: the wrong one. Next: one keyword — `virtual` — and base pointers become magic wands commanding armies of different objects with a single order. 🎪

*Families of code now share their DNA responsibly. Next: they learn to behave differently under one command.* 🧬

---

**⬅️ [Chapter 13](chapter-13-constructors-destructors.md) | [🏠 Home](README.md) | [Chapter 15 ➡️](chapter-15-polymorphism.md)**
