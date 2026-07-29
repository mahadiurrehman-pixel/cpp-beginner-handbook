# CHAPTER 10 — POINTERS & MEMORY

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Every house has an address.
 A pointer is just a variable that
 writes addresses down."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 9](chapter-09-strings.md) | [🏠 Home](README.md) | [Chapter 11 ➡️](chapter-11-intro-oop.md)**

---

## 📖 CHAPTER OPENING

Your street has houses (data) and every house has an address (memory location). A pointer is a friend who doesn't own a house but **knows everyone's address** — you hand them the address, they take you straight to the house and even rearrange the furniture inside. This is the chapter where you stop merely *using* memory and start *commanding* it.

### What you will learn:
- What memory addresses are (`&` — address-of operator)
- What a pointer is, and dereferencing (`*`) to reach the value
- Pointer arithmetic and the secret link between arrays & pointers
- Dynamic memory: `new` and `delete` (arrays that size themselves at runtime)
- `nullptr`, dangling pointers, and memory leaks
- References (`int&`) — the friendlier cousin — and the legendary by-reference swap

### Why this chapter matters:
Pointers explain *everything* you've noticed so far: why arrays change inside functions, why that `bool&` worked in the calculator, why C-strings behave oddly. And they're the raw material of Chapter 20's data structures. Master this and you understand C++ more deeply than most working programmers.

---

## 🔍 CONCEPT EXPLANATION

### What is memory, really?

RAM is a giant row of numbered byte-boxes. Every variable you create lives at some **address** — a number identifying its box.

```cpp
int age = 20;
```

```
RAM:        ┌─────────┬─────────┬─────────┬─────────┐
 Address:   │ 0x1000  │ 0x1004  │ 0x1008  │ 0x100C  │
 Contents:  │ age=20  │   ...   │   ...   │   ...   │
            └─────────┴─────────┴─────────┴─────────┘
```

`&age` asks: *"what's age's address?"* → `0x1000` (shown in hex).

### What is a pointer?

A **pointer** is a variable that **stores an address** instead of a normal value.

```cpp
int* p = &age;    // p holds the ADDRESS of age — p "points to" age
```

- **`*` at declaration** → "this variable holds an address" (make an `int` pointer)
- **`*` on use** → **dereference**: "go to that address and fetch/modify the value"
- **`&`** → "give me the address"

### Why do we use pointers?

1. **Share** — let a function edit the caller's variable (the swap problem finally solved)
2. **Dynamic memory** — arrays whose size is decided while running
3. **Connect** — build chains/webs of data (linked lists, trees — Chapter 20)
4. **Performance** — pass an address (8 bytes) instead of copying huge data

### How does the computer understand it?

An address is just a number whose size is fixed (8 bytes on 64-bit), no matter what it points to. Reading `*p` compiles to: *"load value from memory location held in p"*. One extra hop — that's all a pointer is.

---

## 📝 SYNTAX BOX

```cpp
// ---------- pointers ----------
int age = 20;
int* p = &age;          // p = address of age. Read: "int-pointer p"

cout << &age;           // address (0x7ffee...)      ← & = address-of
cout << p;              // same address
cout << *p;             // 20 — the VALUE at that address  ← * = dereference

*p = 25;                // writes THROUGH the pointer → age is now 25!

// ---------- pointer arithmetic (moves in TYPE-sized steps) ----------
int a[3] = {10, 20, 30};
int* q = a;             // array name ≈ pointer to a[0]
cout << *q;             // 10
cout << *(q + 1);       // 20  (q+1 = next INT, i.e. +4 bytes, not +1!)

// ---------- dynamic memory ----------
int* d = new int(42);   // allocate ONE int on the heap, init 42
delete d;               // return it. ALWAYS.
d = nullptr;            // safe habit: dead pointer points nowhere

int n;
cin >> n;
int* arr = new int[n];  // RUNTIME-sized array! impossible for normal arrays
arr[0] = 7;             // use like any array
delete[] arr;           // arrays need delete[] — brackets matter!
arr = nullptr;

// ---------- nullptr safety ----------
int* safe = nullptr;
if (safe != nullptr) cout << *safe;    // check BEFORE dereferencing

// ---------- references: permanent aliases ----------
int x = 5;
int& r = x;             // r IS x — another name, not a copy
r = 99;                 // x changed to 99. No * needed anywhere.
```

| Symbol | Meaning here |
|---|---|
| `int* p` | p stores an address of an int |
| `*p` | the value AT that address (dereference) |
| `&x` | the address of x |
| `int& r = x` | r is an alias for x (reference) |
| `new` / `delete` | allocate / free heap memory |
| `nullptr` | "points to nothing" — the safe empty value |

---

## 💻 EXAMPLE CODES

### Example 10.1 — First Contact: `&` and `*`

```cpp
// ============================================
// Example 10.1: Addresses and Dereferencing
// ============================================
// What this program does: Shows a variable, its address, a pointer.
// Concepts used: & (address-of), * (declare pointer), * (dereference)
// ============================================

#include <iostream>
using namespace std;

int main() {

    int age = 20;              // a normal int living somewhere in RAM
    int* p = &age;             // p stores age's address

    cout << "age's value:    " << age  << endl;   // 20
    cout << "age's address:  " << &age << endl;   // 0x7ff... (varies!)
    cout << "p holds:        " << p    << endl;   // same address
    cout << "*p reads:       " << *p   << endl;   // 20 — value AT p's address

    *p = 25;                   // write THROUGH the pointer
    cout << "\nAfter *p = 25:" << endl;
    cout << "age is now:     " << age  << endl;   // 25 — changed remotely!

    return 0;
}
/*
OUTPUT (addresses differ every run — normal!):
age's value:    20
age's address:  0x7ffc42b0e634
p holds:        0x7ffc42b0e634
*p reads:       20

After *p = 25:
age is now:     25

EXPLANATION:
p is like a house key labeled with an address.
*p means "use the key, open the house, look inside".
Writing *p = 25 changes the house's contents — so age changed.
*/
```

**What happened here?** You modified a variable from *outside* itself, using only its address. The two `*` meanings — "pointer declaration" and "dereference" — confuse everyone at first; context separates them.

---

### Example 10.2 — The Problem Solved: True Swap by Reference

```cpp
// ============================================
// Example 10.2: Swap — Two Ways That Work (and the One That Didn't)
// ============================================
// What this program does: Swaps caller's variables — really.
// Concepts used: pass-by-pointer, pass-by-reference vs pass-by-value
// ============================================

#include <iostream>
using namespace std;

void swapByValue(int x, int y) {          // Ch. 7: edits COPIES — useless here
    int t = x; x = y; y = t;
}

void swapByPointer(int* x, int* y) {      // receives ADDRESSES
    int t = *x;                           // read the houses
    *x = *y;                              // write into the houses
    *y = t;
}

void swapByReference(int& x, int& y) {    // receives ALIASES — cleanest!
    int t = x; x = y; y = t;              // x,y ARE the caller's variables
}

int main() {

    int a = 10, b = 20;

    swapByValue(a, b);
    cout << "By value:    a=" << a << " b=" << b << endl;   // 10, 20 (unchanged)

    swapByPointer(&a, &b);                // hand over the addresses
    cout << "By pointer:  a=" << a << " b=" << b << endl;   // 20, 10 ✅

    swapByReference(a, b);                // call looks normal, magic inside
    cout << "By reference:a=" << a << " b=" << b << endl;   // 10, 20 ✅ swapped back!

    return 0;
}
/*
EXPLANATION:
By value  → photocopies edited; originals safe (and unchanged).
By pointer→ we mailed the house keys; the function visited the houses.
By reference → x and y were never copies — they were OTHER NAMES
for the same houses. References are pointers in disguise, with
friendlier syntax. This is the & you met in Chapter 7's calculator!
*/
```

**What happened here?** The Chapter 7 limitation is officially dead: pass by **pointer** (`&` at call, `*` inside) or by **reference** (cleanest — nothing new at the call site). Both let functions edit originals.

---

### Example 10.3 — Arrays Are Pointers in Uniform

```cpp
// ============================================
// Example 10.3: Pointer Arithmetic Over an Array
// ============================================
// What this program does: Walks an array with a pointer instead of an index.
// Concepts used: array name as pointer, *(p+i) == a[i], address jumps
// ============================================

#include <iostream>
using namespace std;

int main() {

    int a[5] = {10, 20, 30, 40, 50};

    int* p = a;                    // note: NO & — the array name already
                                   // acts as the address of a[0]!

    cout << "a[0] via pointer: " << *p       << endl;   // 10
    cout << "a[1] via pointer: " << *(p + 1) << endl;   // 20
    cout << "a[2] via pointer: " << *(p + 2) << endl;   // 30

    cout << "\nWalking with p++:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Address " << p << " holds " << *p << endl;
        p++;                                         // jump to NEXT int (+4 bytes)
    }

    // The big reveal — these are THE SAME thing:
    cout << "\n*(a+3) = " << *(a + 3) << "  and a[3] = " << a[3] << endl;

    return 0;
}
/*
OUTPUT (addresses vary):
a[0] via pointer: 10
a[1] via pointer: 20
a[2] via pointer: 30

Walking with p++:
Address 0x...0 holds 10
Address 0x...4 holds 20     ← addresses jump by 4 (size of int!)
Address 0x...8 holds 30
Address 0x...c holds 40
Address 0x...0+16 holds 50

*(a+3) = 40  and a[3] = 40

EXPLANATION:
a[i] IS just sugar for *(a + i). Pointer arithmetic moves in
TYPE-sized steps: p+1 on an int* means "next int" (4 bytes forward).
THIS is why array indices start at 0: index = offset from the start.
*/
```

**What happened here?** The mystery of "arrays change inside functions" is solved: a function receives the array's **address**, so it works on the original memory. No copy was ever made.

---

### Example 10.4 — Dynamic Memory: Runtime-Sized Arrays

```cpp
// ============================================
// Example 10.4: new, delete, and the Heap
// ============================================
// What this program does: Allocates an array sized BY THE USER at runtime.
// Concepts used: new, new[], delete, delete[], nullptr, leak prevention
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "How many scores? ";
    cin  >> n;                          // size decided WHILE RUNNING!

    int* scores = new int[n];           // heap: the big flexible memory pool

    int sum = 0;
    for (int i = 0; i < n; i++) {
        cout << "Score " << i + 1 << ": ";
        cin  >> scores[i];              // dynamic array, normal array syntax
        sum += scores[i];
    }

    cout << "Average = " << (double)sum / n << endl;

    delete[] scores;                    // hand the memory back — MANDATORY
    scores = nullptr;                   // kill the address (no dangling!)

    // cout << scores[0];               // would crash: memory returned!

    return 0;
}
/*
INPUT:  3  80 90 70
OUTPUT:
Average = 80

THE TWO MEMORY NEIGHBORHOODS:
STACK  — automatic: normal variables; created & destroyed by scope {}
HEAP   — manual: new/delete; YOU control lifetime; big; flexible
EXPLANATION:
Normal arrays need compile-time size. new[] asks the heap at runtime.
But heap memory is borrowed: forget delete[] and it's a MEMORY LEAK —
the program hoards RAM until it ends. One new → one delete. Always.
*/
```

**What happened here?** You escaped the fixed-size prison of classic arrays. Every resizable thing (vectors, editors, games loading levels) is built on `new`/`delete` underneath.

---

### Example 10.5 — The Danger Zone: Leaks, Danglers, and nullptr Safety

```cpp
// ============================================
// Example 10.5: Pointer Hygiene (read carefully, run carefully)
// ============================================
// What this program does: Demonstrates the three pointer sins + repentance.
// Concepts used: memory leak, dangling pointer, nullptr guard
// ============================================

#include <iostream>
using namespace std;

void makeLeak() {
    int* p = new int[1000000];    // allocated...
    // ...function ends, p dies, but the 4MB of heap is STILL reserved.
}                                 // ← memory leak! nothing can reach it now.

int main() {

    // ---- Sin 2: dangling pointer (points at freed memory) ----
    int* p = new int(7);
    cout << "Before delete: " << *p << endl;
    delete p;
    // *p is now ILLEGAL — but p still holds the old address. Danger!
    p = nullptr;                  // repentance #1: defuse the pointer

    // ---- Safety: check before dereferencing ----
    if (p != nullptr) {
        cout << *p << endl;
    } else {
        cout << "Pointer is null — safe to skip." << endl;
    }

    // ---- Modern convenience: references can't be null or reseated ----
    int captain = 42;
    int& ref = captain;           // alias from birth to death
    ref++;
    cout << "captain via ref: " << captain << endl;   // 43

    // (uncommenting makeLeak(); in a loop would slowly eat your RAM — don't!)
    return 0;
}
/*
OUTPUT:
Before delete: 7
Pointer is null — safe to skip.
captain via ref: 43

THE THREE SINS & THEIR PENANCE:
1. LEAK       → every new needs its delete
2. DANGLING   → after delete, assign nullptr
3. WILD (uninitialized pointer) → ALWAYS initialize at birth:
     int* p = nullptr;   // not: int* p;  ← points to RANDOM address!
*/
```

**What happened here?** Pointers are power tools: amazing output, strict safety rules. The trio **nullptr at birth → check before use → delete then re-null** is professional pointer hygiene.

### Reference vs Pointer — quick verdict table

| Feature | Pointer `int*` | Reference `int&` |
|---|---|---|
| Can be "empty"/null | Yes (`nullptr`) | No — must bind at birth |
| Can point elsewhere later | Yes | No — loyal forever |
| Syntax for value | `*p` | just use the name |
| Best for | Dynamic memory, optional links, data structures | Function parameters |

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Dereferencing a wild pointer**
```cpp
int* p;              // holds a RANDOM address!
*p = 5;              // writes who-knows-where → crash or corruption
```
✅ **Fix:** `int* p = nullptr;` at birth; assign a real address before use.

**❌ Mistake 2 — Forgetting `delete` (memory leak)**
```cpp
int* a = new int[10000];
// program keeps allocating without freeing → RAM usage climbs forever
```
✅ **Fix:** For every `new`, one `delete`. Every `new[]`, one `delete[]`.

**❌ Mistake 3 — `delete` on an array without brackets**
```cpp
int* a = new int[10];
delete a;            // ❌ undefined behavior — matched the wrong allocator
```
✅ **Fix:** `delete[] a;` — brackets must mirror the allocation.

**❌ Mistake 4 — Using a pointer after delete (dangling)**
```cpp
delete p;
cout << *p;          // ❌ memory already returned
```
✅ **Fix:** `p = nullptr;` immediately after `delete`, and guard with `if (p)`.

**❌ Mistake 5 — Expecting pointer arithmetic in bytes**
```cpp
int* p = arr;
p + 1;               // NOT +1 byte — it's +1 INT (4 bytes)!
```
✅ **Fix:** No fix needed — that's the feature. `p + i` always means "i *elements* forward". (It's how `*(arr+i) == arr[i]` works.)

**❌ Mistake 6 — Confusing `int&` declaration with address-of `&`**
```cpp
int x = 5;
int& r = x;          // &: part of the TYPE → "r is a reference to int"
int* p = &x;         // &: part of the EXPRESSION → "address of x"
```
✅ **Fix:** Same symbol, two jobs. Left of `=` in a declaration → reference. In front of a variable in an expression → address-of.

---

## 🧠 CONCEPT SUMMARY TABLE

| Concept | Code | One-liner |
|---|---|---|
| Address-of | `&x` | "Where do you live?" |
| Pointer declare | `int* p = &x;` | variable that stores an address |
| Dereference | `*p` | "Go there and read/write the value" |
| Null | `int* p = nullptr;` | safe empty; check before use |
| Array ↔ pointer | `*(a+i) == a[i]` | index = offset from start |
| Heap single | `new int(5)` / `delete p` | manual lifetime |
| Heap array | `new int[n]` / `delete[] p` | runtime-sized |
| Leak | missing `delete` | hoarded RAM until exit |
| Dangling | use after `delete` | cure: `p = nullptr` |
| Reference | `int& r = x;` | permanent alias; ideal for params |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.1 ⭐
📋 Declare an int, print its value, its address, and store the
   address in a pointer; print the value through the pointer.
📥 SAMPLE: x = 42
📤 OUTPUT (address varies):
Value: 42
Address: 0x...
Via pointer: 42
💡 HINT: &x, and then *p.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.2 ⭐
📋 Write void triple(int* n) that triples the caller's variable.
   Test in main: print before & after.
📥 INPUT: 7
📤 OUTPUT:
Before: 7
After:  21
💡 HINT: *n = (*n) * 3;  call with triple(&x);
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.3 ⭐
📋 Print all 5 elements of an int array using ONLY pointer
   arithmetic (*(p+i)) — no [] anywhere.
📥 ARRAY: 2 4 6 8 10
📤 OUTPUT: 2 4 6 8 10
💡 HINT: int* p = a; loop i, print *(p+i).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.4 ⭐⭐
📋 Write int sumPtr(int* arr, int size) that sums via pointer
   walking (arr++ style), then call it from main.
📥 INPUT: array 5 10 15 20
📤 OUTPUT: Sum = 50
💡 HINT: Inside, *arr then arr++ repeatedly (arr is yours to move).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.5 ⭐⭐
📋 Rewrite minMax using REFERENCE parameters:
   void minMax(int a, int b, int& mn, int& mx);
   main prints both results.
📥 INPUT: 12 4
📤 OUTPUT: Min = 4, Max = 12
💡 HINT: One function, TWO outputs — references make it natural.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.6 ⭐⭐
📋 Ask the user for N, build a dynamic array, fill with squares
   (1,4,9...), print, then free memory properly.
📥 INPUT: 5
📤 OUTPUT: 1 4 9 16 25
💡 HINT: new int[n] … delete[] … = nullptr.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.7 ⭐⭐
📋 Reference playground: create int fuel=100; int& gauge=fuel;
   Print &fuel and &gauge (identical!), modify via gauge, show fuel.
📤 OUTPUT: identical addresses; fuel changed.
💡 HINT: A reference shares the address — proof it's an alias.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.8 ⭐⭐⭐
📋 Write a function int* createSequence(int n) that RETURNS a
   dynamic array filled with 1..n. Main prints it and deletes it.
📥 INPUT: 6
📤 OUTPUT: 1 2 3 4 5 6
💡 HINT: new inside the function, return the pointer; main owns
   the delete.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.9 ⭐⭐⭐
📋 Safe divider: write bool safeDivide(int* result, int a, int b)
   returning false if result is nullptr or b is 0; else writes
   a/b into *result and returns true. Demonstrate success & failure.
📤 OUTPUT:
10/2 = 5
Blocked: division by zero (or null result)
💡 HINT: Guard first: if (result == nullptr || b == 0) return false;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 10.10 ⭐⭐⭐
📋 Dynamic STACK-lite: read N; push N numbers into a dynamic array
   keeping a top index; then pop & print (LIFO order). Free memory.
📥 INPUT: 4 → 10 20 30 40
📤 OUTPUT: Popped: 40 30 20 10
💡 HINT: int top = -1; push: arr[++top]=x; pop: arr[top--].
```

---

## 🎯 MINI CHALLENGE — DYNAMIC SCOREBOARD 🏆

Build a program that:
1. Asks **N** players count at runtime (`new int[N]`)
2. Reads all scores, computes average **via a pointer-walking function** (no `[i]`!)
3. Finds max **by pointer** too
4. Prints: full list (reversed, by index), average, max
5. Frees memory, nulls the pointer, and prints `"Memory returned. RAM says thanks."`

Output sample:
```
Players: 4
Scores: 55 80 72 66
Reversed: 66 72 80 55
Average: 68.25
Highest: 80
Memory returned. RAM says thanks.
```

You just managed raw memory like a systems engineer. This is the C++ superpower. ⚡

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 10.1**
```cpp
#include <iostream>
using namespace std;
int main() {
    int x = 42;
    int* p = &x;
    cout << "Value: "       << x  << endl;
    cout << "Address: "     << &x << endl;
    cout << "Via pointer: " << *p << endl;
    return 0;
}
```

**✅ SOLUTION 10.2**
```cpp
#include <iostream>
using namespace std;
void triple(int* n) { *n = (*n) * 3; }

int main() {
    int x = 7;
    cout << "Before: " << x << endl;
    triple(&x);
    cout << "After:  " << x << endl;
    return 0;
}
```
💡 **PRO TIP:** Reference version reads even cleaner: `void triple(int& n){ n *= 3; }` called as `triple(x)`.

**✅ SOLUTION 10.3**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[5] = {2,4,6,8,10};
    int* p = a;
    for (int i = 0; i < 5; i++) cout << *(p + i) << " ";
    return 0;
}
```

**✅ SOLUTION 10.4**
```cpp
#include <iostream>
using namespace std;
int sumPtr(int* arr, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += *arr;      // read here
        arr++;              // step forward (parameter copy — caller's arr safe)
    }
    return total;
}
int main() {
    int a[4] = {5, 10, 15, 20};
    cout << "Sum = " << sumPtr(a, 4);
    return 0;
}
```
💡 **PRO TIP:** Moving the received pointer is safe — `arr` inside the function is a local copy of the address.

**✅ SOLUTION 10.5**
```cpp
#include <iostream>
using namespace std;
void minMax(int a, int b, int& mn, int& mx) {
    mn = (a < b) ? a : b;
    mx = (a > b) ? a : b;
}
int main() {
    int low, high;
    minMax(12, 4, low, high);
    cout << "Min = " << low << ", Max = " << high;
    return 0;
}
```
💡 **PRO TIP:** "Function returns many values" = reference out-parameters. Cleaner than abusing globals!

**✅ SOLUTION 10.6**
```cpp
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int* sq = new int[n];
    for (int i = 0; i < n; i++) sq[i] = (i + 1) * (i + 1);
    for (int i = 0; i < n; i++) cout << sq[i] << " ";
    delete[] sq;
    sq = nullptr;
    return 0;
}
```

**✅ SOLUTION 10.7**
```cpp
#include <iostream>
using namespace std;
int main() {
    int  fuel  = 100;
    int& gauge = fuel;
    cout << "&fuel  = " << &fuel  << endl;
    cout << "&gauge = " << &gauge << endl;   // SAME address — alias proof!
    gauge -= 25;
    cout << "fuel now: " << fuel << endl;    // 75
    return 0;
}
```

**✅ SOLUTION 10.8**
```cpp
#include <iostream>
using namespace std;
int* createSequence(int n) {
    int* a = new int[n];               // survives after return: it's on the HEAP
    for (int i = 0; i < n; i++) a[i] = i + 1;
    return a;
}
int main() {
    int n;
    cin >> n;
    int* seq = createSequence(n);
    for (int i = 0; i < n; i++) cout << seq[i] << " ";
    delete[] seq;                      // caller takes ownership of the delete
    seq = nullptr;
    return 0;
}
```
⚠️ **Why this works:** heap memory outlives the function (unlike locals on the stack — returning `&local` would be a fatal dangling pointer).

**✅ SOLUTION 10.9**
```cpp
#include <iostream>
using namespace std;
bool safeDivide(int* result, int a, int b) {
    if (result == nullptr || b == 0) return false;
    *result = a / b;
    return true;
}
int main() {
    int r;
    if (safeDivide(&r, 10, 2)) cout << "10/2 = " << r << endl;
    if (!safeDivide(&r, 10, 0)) cout << "Blocked: division by zero\n";
    if (!safeDivide(nullptr, 10, 2)) cout << "Blocked: null result\n";
    return 0;
}
```
💡 **PRO TIP:** "Return success + write output through a pointer" is a classic C-style API pattern — you'll meet it in real libraries.

**✅ SOLUTION 10.10**
```cpp
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int* stack = new int[n];
    int  top = -1;

    for (int i = 0; i < n; i++) {         // PUSH
        cin >> stack[++top];
    }
    cout << "Popped: ";
    while (top >= 0) {                    // POP until empty
        cout << stack[top--] << " ";
    }
    delete[] stack;
    stack = nullptr;
    return 0;
}
```
💡 **PRO TIP:** You just hand-built a stack — Chapter 20 will wrap this exact logic in a proper `Stack` class.

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
using namespace std;

double averagePtr(int* p, int n) {        // pure pointer walking
    int sum = 0;
    for (int i = 0; i < n; i++) sum += *p++;
    return (double)sum / n;
}
int maxPtr(int* p, int n) {
    int best = *p;
    for (int i = 1; i < n; i++)
        if (*(p + i) > best) best = *(p + i);
    return best;
}

int main() {
    int n;
    cout << "Players: ";
    cin  >> n;

    int* scores = new int[n];
    cout << "Scores: ";
    for (int i = 0; i < n; i++) cin >> scores[i];

    cout << "Reversed: ";
    for (int i = n - 1; i >= 0; i--) cout << scores[i] << " ";
    cout << "\nAverage: " << averagePtr(scores, n);
    cout << "\nHighest: " << maxPtr(scores, n);

    delete[] scores;
    scores = nullptr;
    cout << "\nMemory returned. RAM says thanks.\n";
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ A pointer stores an address; `&` gets addresses, `*` follows them
- ✓ `a[i] == *(a+i)` — arrays are pointer arithmetic in disguise (explains function-parameter behavior!)
- ✓ `new`/`new[]` allocate heap memory of runtime size; every one demands its `delete`/`delete[]`
- ✓ Hygiene: `nullptr` at birth, check before use, `delete` then re-null
- ✓ References (`int&`) are loyal aliases — the clean choice for function parameters

**📚 Keywords learned:** address, pointer, dereference, `nullptr`, heap vs stack, `new`, `delete`, `delete[]`, memory leak, dangling pointer, wild pointer, pointer arithmetic, reference, pass-by-reference, alias

**🔗 Next chapter preview:** **PART 3 — Object-Oriented Programming** begins. Chapter 11 shows why huge programs collapse without a new way of thinking — and how modeling code after *real-world objects* saves it. Your BankAccount becomes a citizen. 🏛️

*You faced the "hardest" chapter in C++ and walked out with the keys to the machine. Seriously — well done.* 🗝️

---

**⬅️ [Chapter 9](chapter-09-strings.md) | [🏠 Home](README.md) | [Chapter 11 ➡️](chapter-11-intro-oop.md)**
