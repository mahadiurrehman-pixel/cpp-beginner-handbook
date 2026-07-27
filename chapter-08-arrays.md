# CHAPTER 8 — ARRAYS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"One variable is a locker.
 An array is a whole hallway of them —
 with numbers on the doors."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 7](chapter-07-functions.md) | [🏠 Home](README.md) | [Chapter 9 ➡️](chapter-09-strings.md)**

```
                PART 2: WORKING WITH DATA
```

---

## 📖 CHAPTER OPENING

A school has 40 students. Do you create `int marks1, marks2, marks3... marks40`? Forty variable names, forty lines of input, forty lines to find the average? Of course not. You'd build lockers: one hallway, one name ("marks"), numbered doors. **An array is exactly that hallway** — one name, many numbered slots.

### What you will learn:
- What an array is and why programming is impossible at scale without it
- Declaring, initializing, and accessing 1D arrays (indexing starts at 0!)
- Processing arrays with loops — the dream team
- Searching, sorting, max/min/sum/average — the classic operations
- 2D arrays — tables, matrices, grids
- Passing arrays to functions

### Why this chapter matters:
Every list your programs will ever touch — scores, contacts, pixels, transactions — lives in an array (or its smarter cousin, the Chapter 19 `vector`). Loops gave you repetition; arrays tell loops *what to repeat over*.

---

## 🔍 CONCEPT EXPLANATION

### What is an array?

An **array** is a collection of elements of the **same type**, stored **side by side** in memory, accessed by a numeric **index** starting at **0**.

```
int marks[5] = {70, 85, 90, 65, 88};

Index:      [0]   [1]   [2]   [3]   [4]
Value:       70    85    90    65    88
             ↑first          ↑last (index = size - 1)
```

- One name (`marks`), five slots.
- **Index = door number.** First door is 0, last door is `size - 1`.
- `marks[2]` reads the 3rd locker: `90`.

### Why do we use arrays?

Because data comes in groups. One variable per value stops working after about... three values. Arrays + loops = process 5 values or 5 million with the same code shape.

### How does the computer understand it?

The compiler reserves one **continuous block** of RAM: `5 ints × 4 bytes = 20 bytes` in a row. `marks[i]` means "start at the block's beginning, skip `i` slots, read there." That's why indexing is instant — it's just address math. (Chapter 10 will show you the actual addresses!)

🔥 **REMEMBER:** C++ does NOT check indices. `marks[7]` on a 5-slot array compiles and reads random memory — silent disaster called **out-of-bounds access**. Guard your indices yourself.

---

## 📝 SYNTAX BOX

```cpp
// 1️⃣ Declaration (empty lockers — garbage inside!)
int marks[5];                        // 5 ints, undefined values

// 2️⃣ Declaration + initialization (the good habit)
int marks[5] = {70, 85, 90, 65, 88};
int zeros[100] = {0};                // first = 0, ALL the rest auto-zero!
int days[]   = {31, 28, 31};         // size deduced: 3

// 3️⃣ Access / modify (index starts at 0)
marks[0] = 95;                       // write
cout << marks[4];                    // read last slot of a 5-array

// 4️⃣ Array + loop (the standard patrol)
for (int i = 0; i < 5; i++) {
    cout << marks[i] << " ";         // visit every locker
}

// 5️⃣ Array size
int n = sizeof(marks) / sizeof(marks[0]);   // 20 bytes / 4 bytes = 5

// 6️⃣ 2D array (rows × columns = a table)
int grid[2][3] = {
    {1, 2, 3},                       // row 0
    {4, 5, 6}                        // row 1
};
cout << grid[1][2];                  // row 1, col 2 → 6

// 7️⃣ Passing to functions — always send size along!
void printAll(int arr[], int size) {      // arr[] = "an int array"
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
}
```

| Rule | Explanation |
|---|---|
| Index range | `0` to `size - 1`. `arr[size]` is out of bounds! |
| Same type | An int array holds only ints |
| Fixed size | Classic arrays can't grow (vectors in Ch. 19 can) |
| Loops partner | `for (int i = 0; i < size; i++)` is muscle memory |

---

## 💻 EXAMPLE CODES

### Example 8.1 — Simplest: Declare, Fill, Print

```cpp
// ============================================
// Example 8.1: A Row of Lockers
// ============================================
// What this program does: Creates an array, shows indexing.
// Concepts used: declaration, initialization, index access
// ============================================

#include <iostream>
using namespace std;

int main() {

    int scores[5] = {70, 85, 90, 65, 88};    // 5 lockers, filled

    cout << "First score: "  << scores[0] << endl;   // index 0 = FIRST
    cout << "Third score: "  << scores[2] << endl;
    cout << "Last score:  "  << scores[4] << endl;   // size-1 = LAST

    scores[1] = 99;                                  // change locker #1
    cout << "New second:   " << scores[1] << endl;

    // Patrol the whole hallway:
    cout << "\nAll scores: ";
    for (int i = 0; i < 5; i++) {
        cout << scores[i] << " ";
    }
    cout << endl;

    return 0;
}
/*
OUTPUT:
First score: 70
Third score: 90
Last score:  88
New second:   99

All scores: 70 99 90 65 88

EXPLANATION:
scores[0] is the FIRST element — programming counts from 0 because
the index means "how many steps from the start". The for-loop
with i as the index visits every slot automatically.
*/
```

**What happened here?** One name held five numbers, indexes addressed each one precisely, and a humble loop printed them all. This is the pattern for the entire chapter.

---

### Example 8.2 — Input N Values + Sum & Average

```cpp
// ============================================
// Example 8.2: The Statistics Machine
// ============================================
// What this program does: Reads up to 100 numbers, reports sum & average.
// Concepts used: array input loop, accumulators over arrays
// ============================================

#include <iostream>
using namespace std;

int main() {

    int n;
    cout << "How many numbers (max 100)? ";
    cin  >> n;

    int data[100];                      // reserve the max; use only n slots

    int sum = 0;                        // accumulator (Ch. 6 reflex)
    for (int i = 0; i < n; i++) {
        cout << "Value " << i + 1 << ": ";
        cin  >> data[i];                // read directly INTO locker i
        sum += data[i];                 // or accumulate right here
    }

    cout << "\nSum     = " << sum << endl;
    cout << "Average = " << (double)sum / n << endl;   // Ch. 3: no chopping!

    return 0;
}
/*
INPUT:  4   10 20 30 40
OUTPUT:
Sum     = 100
Average = 25

EXPLANATION:
The loop variable i does double duty: slot number AND prompt number.
Reserve a big-enough array, track the real count in n —
the standard pre-vector pattern.
*/
```

**What happened here?** Indexes made user input land in the right lockers automatically. The loop never changes — only `n` changes. That's scalability.

---

### Example 8.3 — Real-World: Hottest & Coldest Day

```cpp
// ============================================
// Example 8.3: Weekly Temperature Report (max/min + index)
// ============================================
// What this program does: Finds hottest and coldest temps AND their days.
// Concepts used: running max/min with index tracking, array of labels
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    string days[7]  = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    int    temps[7] = {33, 35, 31, 38, 40, 36, 34};

    int maxIdx = 0, minIdx = 0;            // assume day 0, then disprove

    for (int i = 1; i < 7; i++) {
        if (temps[i] > temps[maxIdx]) maxIdx = i;   // new champion found
        if (temps[i] < temps[minIdx]) minIdx = i;
    }

    cout << "Hottest: " << days[maxIdx] << " (" << temps[maxIdx] << "C)" << endl;
    cout << "Coldest: " << days[minIdx] << " (" << temps[minIdx] << "C)" << endl;

    return 0;
}
/*
OUTPUT:
Hottest: Fri (40C)
Coldest: Wed (31C)

EXPLANATION:
Instead of tracking the VALUE, we track the INDEX of the champion —
from index we can recover everything: temps[maxIdx] and days[maxIdx].
"Assume the first, compare with the rest" is the universal
max/min pattern. Memorize its shape.
*/
```

**What happened here?** Two parallel arrays (`days` and `temps`) stayed in sync through one index — a first taste of structured data. And tracking *positions* instead of values is a pro move you'll use on leaderboards.

---

### Example 8.4 — Search & Bubble Sort

```cpp
// ============================================
// Example 8.4: Find It, Then Sort It
// ============================================
// What this program does: Linear search, then bubble sort ascending.
// Concepts used: search with index flag, nested loops, swapping
// ============================================

#include <iostream>
using namespace std;

int main() {

    int a[8] = {42, 17, 93, 8, 55, 21, 70, 33};
    int n = 8;

    // ---- Linear search ----
    int key;
    cout << "Search for: ";
    cin  >> key;

    int foundAt = -1;                          // -1 means "not found yet"
    for (int i = 0; i < n; i++) {
        if (a[i] == key) { foundAt = i; break; }   // stop at first match
    }

    if (foundAt != -1) cout << key << " found at index " << foundAt << endl;
    else               cout << key << " not found."    << endl;

    // ---- Bubble sort: big values "bubble" to the end ----
    for (int pass = 0; pass < n - 1; pass++) {          // n-1 passes
        for (int i = 0; i < n - 1 - pass; i++) {        // compare neighbors
            if (a[i] > a[i + 1]) {                      // out of order?
                int temp = a[i];                        // classic 3-line swap
                a[i]     = a[i + 1];
                a[i + 1] = temp;
            }
        }
    }

    cout << "Sorted: ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;

    return 0;
}
/*
INPUT:  55
OUTPUT:
55 found at index 4
Sorted: 8 17 21 33 42 55 70 93

EXPLANATION:
Linear search checks lockers one by one — simple, works on any array.
Bubble sort compares neighbors and swaps when out of order;
after each pass the largest unsorted value settles at the end,
which is why the inner loop shrinks: i < n-1-pass.
*/
```

**What happened here?** `break` ended the search early; nested loops performed repeated neighbor-swaps. Sorting is *the* foundational data skill — Chapter 20 compares better algorithms, and Chapter 19 gives you `sort()` for free.

---

### Example 8.5 — 2D Array: The Seating Chart

```cpp
// ============================================
// Example 8.5: Classroom Grid (2D arrays)
// ============================================
// What this program does: Stores a 3x4 marks table; prints row totals.
// Concepts used: 2D declaration, nested loops, grid[i][j]
// ============================================

#include <iostream>
using namespace std;

int main() {

    // 3 students × 4 subjects
    int marks[3][4] = {
        {80, 75, 90, 85},        // student 0
        {60, 70, 65, 72},        // student 1
        {90, 88, 94, 91}         // student 2
    };

    for (int s = 0; s < 3; s++) {              // outer: WHICH student (row)
        int total = 0;
        for (int sub = 0; sub < 4; sub++) {    // inner: walk that row
            total += marks[s][sub];
        }
        cout << "Student " << s + 1 << " total: " << total << endl;
    }

    // Bonus: value at row 1, col 2
    cout << "\nStudent 2, Subject 3 scored: " << marks[1][2] << endl;

    return 0;
}
/*
OUTPUT:
Student 1 total: 330
Student 2 total: 267
Student 3 total: 363

Student 2, Subject 3 scored: 65

EXPLANATION:
grid[row][col] — row first, always. Nested loops over a 2D array
are EXACTLY the star-pattern loops from Chapter 6, upgraded to
process real data. Rows were students here; they'd be pixels in
an image, or board squares in a game.
*/
```

**What happened here?** One table, one name, two indices. Images, chess boards, spreadsheets, game maps — all 2D arrays underneath.

---

### Example 8.6 — Arrays as Function Parameters

```cpp
// ============================================
// Example 8.6: printAll() and findMax() — Functions Meet Arrays
// ============================================
// Concepts used: passing array + size, functions modifying array contents
// ============================================

#include <iostream>
using namespace std;

void printAll(const int arr[], int size) {          // const = read-only promise
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int findMax(const int arr[], int size) {
    int best = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > best) best = arr[i];
    return best;
}

void doubleAll(int arr[], int size) {               // edits the ORIGINAL array!
    for (int i = 0; i < size; i++) arr[i] *= 2;
}

int main() {

    int data[5] = {3, 9, 1, 7, 4};

    printAll(data, 5);                       // 3 9 1 7 4
    cout << "Max: " << findMax(data, 5) << endl;

    doubleAll(data, 5);
    printAll(data, 5);                       // 6 18 2 14 8  ← changed for real!

    return 0;
}
/*
OUTPUT:
3 9 1 7 4
Max: 9
6 18 2 14 8

EXPLANATION:
⚠️ Arrays are NOT copied when passed — the function works on the
ORIGINAL lockers (Chapter 10 explains the pointer reason).
Great for performance, dangerous for surprises. Use const when
the function only reads. And ALWAYS pass the size separately —
inside a function, sizeof(tricks) no longer works.
*/
```

**What happened here?** `doubleAll` changed the original array — very different from Chapter 7's copy-behavior with plain ints! Add `const` for read-only functions and you'll never be ambushed.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — `arr[size]` out-of-bounds**
```cpp
int a[5] = {1,2,3,4,5};
cout << a[5];        // ❌ valid indices: 0-4. a[5] reads random memory!
```
✅ **Fix:** Last index = `size - 1`. **No compiler error appears** — this bug is silent. Always check loop bounds.

**❌ Mistake 2 — Using uninitialized arrays**
```cpp
int a[10];
cout << a[0];        // garbage — lockers weren't emptied first
```
✅ **Fix:** `int a[10] = {0};` — initializes ALL slots to 0 in one shot.

**❌ Mistake 3 — `sizeof` size-trick inside functions**
```cpp
void show(int arr[]) {
    int n = sizeof(arr) / sizeof(arr[0]);   // ❌ arr decayed — wrong n!
}
```
✅ **Fix:** Pass size as a parameter (see Example 8.6). Do the `sizeof` math only where the array was born.

**❌ Mistake 4 — Copying/comparing arrays like variables**
```cpp
int a[3] = {1,2,3}, b[3];
b = a;                  // ❌ compile error: arrays aren't assignable
if (a == b) { }         // ❌ compiles but compares ADDRESSES, not contents
```
✅ **Fix:** Copy element-by-element with a loop; compare with a loop too. (Chapter 19's `vector` fixes both.)

**❌ Mistake 5 — Loop starting at 1 without adjusting**
```cpp
for (int i = 1; i <= 5; i++) cout << a[i];   // skips a[0], reads a[5] garbage
```
✅ **Fix:** `for (int i = 0; i < 5; i++)`. Humans count from 1; C++ arrays count from 0. Translate.

**❌ Mistake 6 — Swapping 2D indices (row/col confusion)**
```cpp
grid[2][3];            // means ROW 2, COL 3 — not (x=3, y=2)
```
✅ **Fix:** Say it aloud: "rows first, then columns" — `grid[r][c]`.

---

## 🧠 CONCEPT SUMMARY TABLE

| Task | Code | Note |
|---|---|---|
| Declare | `int a[10];` | garbage inside! |
| Init all-zero | `int a[10] = {0};` | fills everything |
| Init list | `int a[] = {3,1,4};` | size auto = 3 |
| Access | `a[i]` | valid: 0..size-1 |
| Get size | `sizeof(a)/sizeof(a[0])` | only where declared |
| Patrol | `for(i=0;i<size;i++)` | the standard loop |
| Search | loop + `if(a[i]==key)` | linear; index `-1` = not found |
| Max/Min | assume index 0, compare rest | track INDEX, not value |
| Sort (bubble) | neighbor compare & swap | O(n²) — Ch. 20 for more |
| 2D | `int g[ROWS][COLS];` | `g[r][c]`, nested loops |
| To function | `f(int arr[], int size)` | not copied! pass size |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.1 ⭐
📋 Read 5 numbers into an array, print them in REVERSE order.
📥 SAMPLE INPUT: 1 2 3 4 5
📤 EXPECTED OUTPUT: 5 4 3 2 1
💡 HINT: Loop i from size-1 down to 0.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.2 ⭐
📋 Read 8 numbers; print sum and average (2 decimals).
📥 SAMPLE INPUT: 10 20 30 40 50 60 70 80
📤 EXPECTED OUTPUT: Sum=360  Avg=45
💡 HINT: Accumulate during or after input.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.3 ⭐
📋 Read 6 numbers; count how many are even vs odd.
📥 SAMPLE INPUT: 2 7 8 3 10 5
📤 EXPECTED OUTPUT: Even=3  Odd=3
💡 HINT: a[i] % 2 == 0 inside the patrol.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.4 ⭐⭐
📋 Find the MAXIMUM value and the index of its FIRST occurrence.
📥 SAMPLE INPUT: 4 9 2 9 7
📤 EXPECTED OUTPUT: Max=9 at index 1
💡 HINT: Use > (not >=) so ties keep the earliest index.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.5 ⭐⭐
📋 Read N and a key; print ALL indices where key appears,
   or "Not found". Input: n=6, arr=3 1 3 3 5 3, key=3
📤 EXPECTED OUTPUT: Found at indices: 0 2 3 5
💡 HINT: No break this time — print inside the loop, count matches.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.6 ⭐⭐
📋 Copy array A into array B, then print both side by side
   to prove they're equal. (Remember: loops, not =!)
📥 SAMPLE INPUT: 5 1 4 2 8
📤 EXPECTED OUTPUT:
A: 5 1 4 2 8
B: 5 1 4 2 8
💡 HINT: One patrol: b[i] = a[i];
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.7 ⭐⭐
📋 Reverse an array IN PLACE (no second array), then print it.
📥 SAMPLE INPUT: 1 2 3 4 5
📤 EXPECTED OUTPUT: 5 4 3 2 1
💡 HINT: Swap a[i] with a[n-1-i], but only while i < n/2.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.8 ⭐⭐⭐
📋 Find the SECOND LARGEST number in an array of 6 distinct values.
📥 SAMPLE INPUT: 10 50 30 40 20 60
📤 EXPECTED OUTPUT: Second largest = 50
💡 HINT: Track largest and secondLargest in one patrol —
   when new largest found, old largest becomes second.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.9 ⭐⭐⭐
📋 Print the SUM of the main diagonal of a 3×3 matrix.
📥 SAMPLE (matrix hardcoded): 1 2 3 / 4 5 6 / 7 8 9
📤 EXPECTED OUTPUT: Diagonal sum = 15
💡 HINT: Diagonal elements are m[i][i].
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 8.10 ⭐⭐⭐
📋 Bubble sort DESCENDING, printing the array after EACH pass.
📥 SAMPLE INPUT: 5 3 8 1 9 2
📤 EXPECTED OUTPUT (passes shown):
Pass 1: 8 5 9 3 2 1   ... etc until
Final:  9 8 5 3 2 1
💡 HINT: Flip the comparison to a[i] < a[i+1]; print after each pass loop.
```

---

## 🎯 MINI CHALLENGE — CLASS RESULT ANALYZER 🏫

Build a program that:
1. Reads the number of students (max 50) and each student's marks (0–100)
2. Prints a full report: **highest, lowest, average (2 dp), and pass count (≥50)**
3. Prints a **grade distribution**: counts of A(90+), B(80+), C(60+), D(50+), F(<50)
4. Shows the **topper's seat number** (index + 1)

```
SAMPLE RUN:
Students: 5
Marks: 78 45 92 60 38
--- REPORT ---
Highest: 92 (Seat #3)    Lowest: 38
Average: 62.60           Passed: 3 / 5
A:1  B:0  C:2  D:0  F:2
```

All 10 problems trained you for this. One array, many patrols, one proud report. 🏆

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 8.1**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[5];
    for (int i = 0; i < 5; i++) cin >> a[i];
    for (int i = 4; i >= 0; i--) cout << a[i] << " ";
    return 0;
}
```
💡 **PRO TIP:** Looping backwards (`i >= 0; i--`) is a whole second direction of array skill.

**✅ SOLUTION 8.2**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[8], sum = 0;
    for (int i = 0; i < 8; i++) { cin >> a[i]; sum += a[i]; }
    cout << "Sum=" << sum << "  Avg=" << (double)sum / 8;
    return 0;
}
```

**✅ SOLUTION 8.3**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[6], even = 0, odd = 0;
    for (int i = 0; i < 6; i++) {
        cin >> a[i];
        (a[i] % 2 == 0) ? even++ : odd++;          // mini decision!
    }
    cout << "Even=" << even << "  Odd=" << odd;
    return 0;
}
```
💡 **PRO TIP:** The ternary works as a statement too — though an `if/else` is clearer for teammates.

**✅ SOLUTION 8.4**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[5];
    for (int i = 0; i < 5; i++) cin >> a[i];
    int maxIdx = 0;
    for (int i = 1; i < 5; i++)
        if (a[i] > a[maxIdx]) maxIdx = i;   // > keeps FIRST on ties
    cout << "Max=" << a[maxIdx] << " at index " << maxIdx;
    return 0;
}
```

**✅ SOLUTION 8.5**
```cpp
#include <iostream>
using namespace std;
int main() {
    int n, key, count = 0;
    cin >> n;
    int a[100];
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> key;
    cout << "Found at indices: ";
    for (int i = 0; i < n; i++)
        if (a[i] == key) { cout << i << " "; count++; }
    if (count == 0) cout << "Not found";
    return 0;
}
```

**✅ SOLUTION 8.6**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[4], b[4], n = 4;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) b[i] = a[i];      // the copy loop
    cout << "A: "; for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\nB: "; for (int i = 0; i < n; i++) cout << b[i] << " ";
    return 0;
}
```
💡 **PRO TIP:** Legal one-liner alternative for raw arrays: `copy(a, a+n, b);` from `<algorithm>` — a preview of Chapter 19.

**✅ SOLUTION 8.7**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[5] = {1,2,3,4,5}, n = 5;
    for (int i = 0; i < n / 2; i++) {
        int t = a[i];
        a[i] = a[n - 1 - i];
        a[n - 1 - i] = t;
    }
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    return 0;
}
```
💡 **PRO TIP:** Stop at `n/2` — swap the middle element with itself and you've swapped everything twice (back to original!).

**✅ SOLUTION 8.8**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[6];
    for (int i = 0; i < 6; i++) cin >> a[i];
    int first = a[0], second = a[1];
    if (second > first) { int t = first; first = second; second = t; }
    for (int i = 2; i < 6; i++) {
        if (a[i] > first)       { second = first; first = a[i]; }
        else if (a[i] > second) { second = a[i]; }
    }
    cout << "Second largest = " << second;
    return 0;
}
```
💡 **PRO TIP:** Alternative: bubble-sort a copy descending, print element [1]. Slower but simpler — knowing both is the pro move.

**✅ SOLUTION 8.9**
```cpp
#include <iostream>
using namespace std;
int main() {
    int m[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int sum = 0;
    for (int i = 0; i < 3; i++) sum += m[i][i];   // (0,0)(1,1)(2,2)
    cout << "Diagonal sum = " << sum;             // 1+5+9 = 15
    return 0;
}
```
💡 **PRO TIP:** The OTHER diagonal is `m[i][n-1-i]`. Both together in one loop = classic exam question.

**✅ SOLUTION 8.10**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int pass = 0; pass < n - 1; pass++) {
        for (int i = 0; i < n - 1 - pass; i++) {
            if (a[i] < a[i + 1]) {          // flipped → descending
                int t = a[i]; a[i] = a[i+1]; a[i+1] = t;
            }
        }
        cout << "Pass " << pass + 1 << ": ";
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}
```

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
using namespace std;
int main() {
    int n, m[50];
    cout << "Students: "; cin >> n;
    for (int i = 0; i < n; i++) cin >> m[i];

    int hi = 0, lo = 0, sum = 0, pass = 0, g[5] = {0};  // g: A B C D F
    for (int i = 0; i < n; i++) {
        sum += m[i];
        if (m[i] > m[hi]) hi = i;
        if (m[i] < m[lo]) lo = i;
        if (m[i] >= 50) pass++;
        if      (m[i] >= 90) g[0]++;
        else if (m[i] >= 80) g[1]++;
        else if (m[i] >= 60) g[2]++;
        else if (m[i] >= 50) g[3]++;
        else                 g[4]++;
    }

    cout << "--- REPORT ---\n";
    cout << "Highest: " << m[hi] << " (Seat #" << hi + 1 << ")\n";
    cout << "Lowest:  " << m[lo] << "\n";
    cout << "Average: " << (double)sum / n << "\n";
    cout << "Passed:  " << pass << " / " << n << "\n";
    cout << "A:" << g[0] << " B:" << g[1] << " C:" << g[2]
         << " D:" << g[3] << " F:" << g[4] << endl;
    return 0;
}
```
💡 **PRO TIP:** Notice? The analyzer is just Example 8.3 + 8.2 + a grade ladder walking the same array. Big programs = small patterns composed.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Arrays = one name, many same-type slots; index runs 0 → size−1
- ✓ Out-of-bounds is a SILENT bug — C++ won't save you
- ✓ Arrays passed to functions are NOT copied; always pass size too
- ✓ Master the patrol patterns: sum, max-index, search, reverse, bubble sort
- ✓ 2D arrays = rows first `g[r][c]` + nested loops (your Ch. 6 skill, upgraded)

**📚 Keywords learned:** array, index, subscript `[]`, initialization lists, linear search, bubble sort, 2D array, out-of-bounds, parallel arrays, `const` parameters

**🔗 Next chapter preview:** Chapter 9 — **Strings**. Text is just... an array of characters! Which means you already halfway know strings. Meet `std::string` and its toolbox: find, cut, replace, compare — your word processor in code. 🔤

*From lockers to hallways to whole buildings of data. Your programs just got memory.* 💪

---

**⬅️ [Chapter 7](chapter-07-functions.md) | [🏠 Home](README.md) | [Chapter 9 ➡️](chapter-09-strings.md)**
