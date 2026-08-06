# CHAPTER 20 — BASIC DATA STRUCTURES

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Knowing how the engine works is what
 separates the driver from the mechanic."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 19](chapter-19-stl.md) | [🏠 Home](README.md) | [Chapter 21 ➡️](chapter-21-project-student-system.md)**

---

## 📖 CHAPTER OPENING

Chapter 19 gave you the finished power tools. Now we open the hood: build a **linked list** from pointers with our bare hands, forge stacks and queues from arrays, race three sorting algorithms against each other, and learn **Big-O** — the language computer scientists use to say *"this gets slow, fast."* This is the chapter that turns library users into engineers.

### What you will learn:
- Linked lists — pointer-chained nodes (build your first from scratch!)
- Stack and Queue implemented with plain arrays
- Bubble, Selection, Insertion sort — compared honestly
- Binary Search — the "divide and conquer" superstar
- Big-O intuition — O(1), O(n), O(n²), O(log n) with real numbers

### Why this chapter matters:
Interviews ask these structures by name; CS courses assume them; and after seeing how a list lives in memory, the STL stops being magic and starts being *yours*.

---

## 🔍 CONCEPT EXPLANATION

### What is a data structure?

A **data structure** is a deliberate way of organizing data so certain operations are fast. Arrays = instant index access, terrible mid-insertion. Linked lists = instant end-insertion, no index access at all. There's no "best" — there's best **for the job**.

### The lineup for today:

1. **Linked list** — a chain of nodes where each node holds data + the address of the next node (Ch. 10 pointers, finally in their true home)
2. **Stack** — array + `top` pointer (you built a mini one in Problem 10.10!)
3. **Queue** — array + `front`/`rear` pointers
4. **Sorting algorithms** — systematic ways to order data
5. **Binary search** — searching by halving

### Big-O in one breath

Big-O describes how work grows as data (n) grows:

| Complexity | Name | Feels like (n = 1,000,000) |
|---|---|---|
| O(1) | constant | 1 step — array[i], stack push |
| O(log n) | logarithmic | ~20 steps — binary search |
| O(n) | linear | 1,000,000 steps — simple scan |
| O(n log n) | "sort-fast" | ~20,000,000 — good sorts (STL's sort) |
| O(n²) | quadratic | 1,000,000,000,000 — bubble sort. Yikes. |

---

## 📝 SYNTAX BOX

```cpp
// ---------- LINKED LIST ----------
struct Node {
    int  data;
    Node* next;              // pointer to the next node (nullptr = end)
};

Node* head = nullptr;        // list is just a pointer to its first node!

Node* n = new Node{5, nullptr};     // one new node holding 5
n->next = head;                     // point it at the old first node
head = n;                           // it becomes the new head (prepend)

// ---------- STACK (array) ----------
int stackArr[100], top = -1;
stackArr[++top] = x;         // push
int val = stackArr[top--];   // pop

// ---------- QUEUE (array) ----------
int queueArr[100], front = 0, rear = -1;
queueArr[++rear] = x;        // enqueue
int val = queueArr[front++]; // dequeue

// ---------- BUBBLE SORT (recap Ch. 8) ----------
for (int p = 0; p < n-1; p++)
    for (int i = 0; i < n-1-p; i++)
        if (a[i] > a[i+1]) swap(a[i], a[i+1]);

// ---------- SELECTION SORT ----------
for (int i = 0; i < n-1; i++) {
    int minIdx = i;
    for (int j = i+1; j < n; j++)
        if (a[j] < a[minIdx]) minIdx = j;      // find the minimum of the rest
    swap(a[i], a[minIdx]);                     // put it at position i
}

// ---------- INSERTION SORT ----------
for (int i = 1; i < n; i++) {
    int key = a[i], j = i - 1;
    while (j >= 0 && a[j] > key) { a[j+1] = a[j]; j--; }   // shift left
    a[j+1] = key;                                          // drop the key in
}

// ---------- BINARY SEARCH (sorted arrays only!) ----------
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (a[mid] == key)         → found at mid
    else if (a[mid] < key) lo = mid + 1;    // key lives to the right
    else                   hi = mid - 1;    // key lives to the left
}
```

---

## 💻 EXAMPLE CODES

### Example 20.1 — Building a Linked List With Bare Hands

```cpp
// ============================================
// Example 20.1: Your First Linked List (birth, walk, destroy)
// ============================================
// Concepts used: Node struct, head pointer, prepend, traversal, cleanup
// ============================================

#include <iostream>
using namespace std;

struct Node {
    int   data;
    Node* next;                // link to the NEXT node in the chain
};

void prepend(Node*& head, int value) {    // Node*& = we CHANGE caller's head
    Node* fresh = new Node{value, head};  // new node points at old head
    head = fresh;                         // head now starts at the new node
}

void printChain(Node* head) {
    Node* walker = head;                  // NEVER move head itself — backup!
    while (walker != nullptr) {
        cout << "[" << walker->data << "] ➜ ";
        walker = walker->next;            // follow the link forward
    }
    cout << "nullptr (end)\n";
}

void destroyChain(Node*& head) {          // every new needs its delete!
    while (head != nullptr) {
        Node* doomed = head;              // remember the condemned
        head = head->next;                // step head forward BEFORE deleting
        delete doomed;
    }
}

int main() {

    Node* head = nullptr;                  // an empty list IS a null pointer

    prepend(head, 30);
    prepend(head, 20);
    prepend(head, 10);

    cout << "Chain after 3 prepends:\n";
    printChain(head);

    destroyChain(head);
    cout << "After destroy, head == " << (head == nullptr ? "nullptr ✓" : "?") << "\n";

    return 0;
}
/*
OUTPUT:
Chain after 3 prepends:
[10] ➜ [20] ➜ [30] ➜ nullptr (end)
After destroy, head == nullptr ✓

EXPLANATION:
A linked list isn't a container you declare — it's an AGREEMENT:
"each node knows the next node's address." Prepending is O(1):
new node → point at old head → become head. Traversal is O(n):
no shortcut but walking. destroyChain matters — heap nodes never
die by themselves (Chapter 10's leak police is watching 👮).
*/
```

**What happened here?** No STL, just pointers and discipline — yet a functioning, growable list. This is what `list<T>` contains inside.

---

### Example 20.2 — Stack & Queue From One Array Each

```cpp
// ============================================
// Example 20.2: Hand-built Stack and Queue With Guard Rails
// ============================================
// Concepts used: top/front/rear indices, overflow & underflow checks
// ============================================

#include <iostream>
#include <string>
using namespace std;

// ---------------- STACK (LIFO) ----------------
class MyStack {
    string a[5];
    int top = -1;
public:
    bool push(const string& x) {
        if (top == 4) { cout << "  STACK OVERFLOW (full!)\n"; return false; }
        a[++top] = x;
        return true;
    }
    bool pop() {
        if (top == -1) { cout << "  STACK UNDERFLOW (empty!)\n"; return false; }
        top--;
        return true;
    }
    string peek() { return top >= 0 ? a[top] : "(empty)"; }
};

// ---------------- QUEUE (FIFO) ----------------
class MyQueue {
    string a[5];
    int front = 0, rear = -1, count = 0;
public:
    bool enqueue(const string& x) {
        if (count == 5) { cout << "  QUEUE FULL!\n"; return false; }
        rear = (rear + 1) % 5;              // ⭐ circular wrap-around!
        a[rear] = x;
        count++;
        return true;
    }
    bool dequeue() {
        if (count == 0) { cout << "  QUEUE EMPTY!\n"; return false; }
        front = (front + 1) % 5;
        count--;
        return true;
    }
    string peek() { return count > 0 ? a[front] : "(empty)"; }
};

int main() {

    MyStack s;
    s.push("page-1"); s.push("page-2"); s.push("page-3");
    cout << "stack top: " << s.peek() << "\n";      // page-3 (newest)
    s.pop(); s.pop(); s.pop();
    s.pop();                                         // UNDERFLOW demo

    MyQueue q;
    q.enqueue("C1"); q.enqueue("C2"); q.enqueue("C3");
    cout << "queue front: " << q.peek() << "\n";    // C1 (oldest)
    q.dequeue();
    q.enqueue("C4");                                 // wraps internally
    cout << "queue front now: " << q.peek() << "\n"; // C2

    return 0;
}
/*
OUTPUT:
stack top: page-3
  STACK UNDERFLOW (empty!)
queue front: C1
queue front now: C2

EXPLANATION:
Stack: one moving pointer (top), both ops on the same end. Queue:
two pointers and a count — plus the % capacity trick that turns a
plain array into a CIRCLE (circular queue) so freed front slots are
reused. Underflow/overflow guards = what the real std:: containers
handle for you with exceptions.
*/
```

**What happened here?** Discipline structures make sense as code once you see their indices move. The `%` wrap is the single cleverest line in this chapter.

---

### Example 20.3 — The Three Sorts, One Battlefield

```cpp
// ============================================
// Example 20.3: Bubble vs Selection vs Insertion (with step counters!)
// ============================================
// Concepts used: all three algorithms, comparison counting = speed evidence
// ============================================

#include <iostream>
#include <algorithm>
using namespace std;

void show(const string& name, int a[], int n, long long cmps) {
    cout << name << ": ";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "  (" << cmps << " comparisons)\n";
}

int main() {

    int orig[10] = {9, 3, 7, 1, 8, 2, 6, 4, 10, 5};
    int n = 10;

    // ---------- BUBBLE ----------
    int a[10];
    copy(orig, orig + n, a);
    long long cmp = 0;
    for (int p = 0; p < n - 1; p++)
        for (int i = 0; i < n - 1 - p; i++) {
            cmp++;
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        }
    show("bubble   ", a, n, cmp);

    // ---------- SELECTION ----------
    copy(orig, orig + n, a);
    cmp = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            cmp++;
            if (a[j] < a[minIdx]) minIdx = j;
        }
        swap(a[i], a[minIdx]);
    }
    show("selection", a, n, cmp);

    // ---------- INSERTION ----------
    copy(orig, orig + n, a);
    cmp = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while (j >= 0) {
            cmp++;
            if (a[j] > key) { a[j + 1] = a[j]; j--; }
            else break;
        }
        a[j + 1] = key;
    }
    show("insertion", a, n, cmp);

    return 0;
}
/*
OUTPUT:
bubble   : 1 2 3 4 5 6 7 8 9 10   (45 comparisons)
selection: 1 2 3 4 5 6 7 8 9 10   (45 comparisons)
insertion: 1 2 3 4 5 6 7 8 9 10   (45 comparisons worst-case-ish here)

EXPLANATION:
bubble:  neighbors swap toward the end, pass by pass  — O(n²)
selection: pick the minimum, drop it at the front     — O(n²)
insertion: grow a sorted left-hand corner             — O(n²) worst,
                                                       O(n) on nearly-sorted!
All three lose to STL's sort (O(n log n)) on big data —
but you can now explain EXACTLY why, and code them blindfolded
in an interview.
*/
```

**What happened here?** Their superpower isn't speed — it's transparency: each teaches a mindset (swapping, selecting, inserting) that returns in harder algorithms later.

---

### Example 20.4 — Binary Search: The Halving Machine

```cpp
// ============================================
// Example 20.4: Search 1,000,000 Items in ~20 Steps
// ============================================
// Concepts used: binary search, sorted prerequisite, live step tracing
// ============================================

#include <iostream>
using namespace std;

int binarySearch(int a[], int n, int key) {
    int lo = 0, hi = n - 1, steps = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        steps++;
        cout << "  step " << steps << ": checking a[" << mid << "] = " << a[mid] << "\n";
        if (a[mid] == key) { cout << "  (" << steps << " steps)\n"; return mid; }
        if (a[mid] < key) lo = mid + 1;   // discard the LEFT half
        else              hi = mid - 1;   // discard the RIGHT half
    }
    cout << "  not found (" << steps << " steps)\n";
    return -1;
}

int main() {

    int a[10] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};

    cout << "Searching for 23:\n";
    int idx = binarySearch(a, 10, 23);
    if (idx != -1) cout << "Found at index " << idx << " ✓\n";

    cout << "\nSearching for 100 (absent):\n";
    binarySearch(a, 10, 100);

    // a LINEAR search would take up to 10 steps here — and 1,000,000
    // for a million items. Binary search: ~20 steps for a million.
    return 0;
}
/*
OUTPUT:
Searching for 23:
  step 1: checking a[4] = 16
  step 2: checking a[6] = 38
  step 3: checking a[5] = 23
  (3 steps)
Found at index 5 ✓

Searching for 100 (absent):
  step 1: checking a[4] = 16
  step 2: checking a[7] = 56
  step 3: checking a[8] = 72
  step 4: checking a[9] = 91
  not found (4 steps)

EXPLANATION:
SORTED data unlocks halving: look at the middle, throw away half
the universe, repeat. O(log n): doubling the data adds only ONE
step. ⚠️ Non-negotiable prerequisite: data MUST be sorted — binary
search on unsorted data returns confident garbage.
*/
```

**What happened here?** The most important search on earth — library catalogues, databases, and `lower_bound()` all work this way. And its logic is just `if` inside `while` — your Chapter 6 tools.

---

### Example 20.5 — Big-O Demo You Can Feel

```cpp
// ============================================
// Example 20.5: Watch Complexity in Real Numbers
// ============================================
// Concepts used: counting operations across algorithms as n grows
// ============================================

#include <iostream>
using namespace std;

int main() {

    // O(n): find max — must look at everything once
    // O(n²): all pairs — n nested in n
    // O(log n): binary search steps

    for (int n = 100; n <= 1000000; n *= 100) {

        long long linearSteps = n;              // one pass

        long long quadraticSteps = (long long)n * n;   // nested passes

        long long logSteps = 0;                 // halvings until 1
        for (int x = n; x > 1; x /= 2) logSteps++;

        cout << "n = " << n << "\n";
        cout << "  O(n)   scan steps:      " << linearSteps    << "\n";
        cout << "  O(log n) binary steps:  " << logSteps       << "\n";
        cout << "  O(n²)  pair steps:      " << quadraticSteps << "\n";
        cout << "  → at 1 billion ops/sec, O(n²) takes ~"
             << quadraticSteps / 1000000000.0 << " seconds\n\n";
    }

    return 0;
}
/*
OUTPUT (abridged):
n = 100
  O(n)   scan steps:      100
  O(log n) binary steps:  6
  O(n²)  pair steps:      10000
  → at 1 billion ops/sec, O(n²) takes ~1e-05 seconds

n = 1000000
  O(n)   scan steps:      1000000
  O(log n) binary steps:  19
  O(n²)  pair steps:      1000000000000
  → at 1 billion ops/sec, O(n²) takes ~1000 seconds

EXPLANATION:
Same problem SIZE-JUMP, three destinies. A million items: linear
= a second, log = instant, quadratic = 17 minutes. Big-O isn't
math homework — it's "will my program finish before the heat
death of my laptop?"
*/
```

**What happened here?** You can now translate algorithm names into real time estimates — the entire practical point of complexity theory.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Moving `head` directly while traversing**
```cpp
while (head != nullptr) { cout << head->data; head = head->next; }
// head is now nullptr — the LIST'S FRONT door is lost forever (leak!)
```
✅ **Fix:** Always walk with a backup: `Node* w = head;` and move `w`.

**❌ Mistake 2 — Forgetting to free list nodes**
```cpp
destroyChain:  delete head;      // kills only node #1 — the rest leak!
```
✅ **Fix:** The Example 20.1 loop: save `next` BEFORE `delete` of each node.

**❌ Mistake 3 — `new` node where `head` still needed**
```cpp
head = new Node{value, nullptr};  // old chain abandoned — everything lost
```
(when intending prepend)
✅ **Fix:** `head = new Node{value, head};` — link to the previous head in the same breath.

**❌ Mistake 4 — Binary search on unsorted data**
```cpp
int a[5] = {50, 10, 90, 30, 70};
binarySearch(a, 5, 30);          // returns nonsense with total confidence
```
✅ **Fix:** Sort first (or use linear search). Binary search's contract: sorted input.

**❌ Mistake 5 — Queue without wrap-around (wasting freed space)**
```cpp
rear++;            // hits capacity while front slots sit empty → fake "FULL"
```
✅ **Fix:** `% capacity` (Example 20.2's circular trick) — or count-based fullness as shown.

**❌ Mistake 6 — `mid = (lo + hi) / 2` overflow (prologue to pro habits)**
```cpp
int mid = (lo + hi) / 2;         // lo+hi can overflow int on giant arrays!
```
✅ **Fix:** `int mid = lo + (hi - lo) / 2;` — same value, never overflows. (Real interview tidbit — a bug that lived in Java's own library for 9 years.)

---

## 🧠 CONCEPT SUMMARY TABLE

| Structure / Algo | Operation | Cost | Your takeaway |
|---|---|---|---|
| Array access | `a[i]` | O(1) | unbeatable for index reads |
| Linked list | prepend / traverse | O(1) / O(n) | great ends, ugly middles |
| Stack (array) | push/pop | O(1) | guard overflow/underflow |
| Queue (circular) | enq/deq | O(1) | `% n` wrap reuses space |
| Bubble sort | sort | O(n²) | teaching classic |
| Selection sort | sort | O(n²) | fewest swaps |
| Insertion sort | sort | O(n²), ~O(n) nearly-sorted | great on almost-sorted data |
| Binary search | search | O(log n) | needs SORTED data |
| Linear search | search | O(n) | works on anything |
| STL sort | sort | O(n log n) | the production choice |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.1 ⭐
📋 Build a 3-node linked list by hand with values 7, 14, 21
   (no functions — straight pointer lines in main), print chain.
📤 OUTPUT: [7] ➜ [14] ➜ [21] ➜ nullptr
💡 HINT: n1->next = n2; n2->next = n3; n3->next = nullptr;
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.2 ⭐
📋 MyStack of ints with push/pop/peek + guards; push 10,20,30;
   pop twice; print peek; attempt a 6th... wait, size is 3 — pop
   once more then UNDERFLOW demo.
📤 OUTPUT: peek 10, then underflow message.
💡 HINT: Example 20.2 with strings→ints.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.3 ⭐
📋 Selection sort DESCENDING on 6 entered ints; print after each pass.
📥 INPUT: 3 1 4 1 5 9? use: 30 10 50 20 60 40
📤 OUTPUT: passes ending at: 60 50 40 30 20 10
💡 HINT: track maxIdx instead and flip comparison.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.4 ⭐⭐
📋 Palindrome word check USING a stack you built (push chars,
   then compare popping vs forward walking).
📥 INPUT: level → Palindrome | hello → Not
📤 OUTPUT: verdict line.
💡 HINT: popped sequence must equal input sequence for palindromes.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.5 ⭐⭐
📋 Binary search FIRST-OCCURRENCE variant: sorted array with
   duplicates {1,2,2,2,4}; find index of the FIRST 2 (=1).
📤 OUTPUT: 1 (not 2 or 3!)
💡 HINT: when found, save candidate then search LEFT further
   (hi = mid - 1, remember answer).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.6 ⭐⭐
📋 Queue post-office: capacity 3 circular; enqueue A,B,C, dequeue 1,
   enqueue D (must WRAP), print state front→rear correctly.
📤 OUTPUT: B C D (with wrapped internals working)
💡 HINT: print loop uses (front + i) % capacity walking count items.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.7 ⭐⭐
📋 Count list size: prepend 5 values to a linked list then count
   nodes via traversal; print 5. Then find max in the list.
📤 OUTPUT: size=5, max=<largest>
💡 HINT: same walker loop, two accumulators across two walks.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.8 ⭐⭐⭐
📋 Insertion sort on an ALMOST-SORTED array (only one element out
   of place) and count its shifts vs Bubble's comparison count on
   the same data — prove insertion's near-O(n) advantage with numbers.
📥 INPUT: 1 2 3 9 4 5 6 7 8  (sorted except 9)
📤 OUTPUT: insertion shifts: ~1-2 vs bubble comparisons: 36
💡 HINT: count a[j+1] = a[j] executions in insertion's while.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.9 ⭐⭐⭐
📋 Linked-list value search with INDEX reporting: find value V,
   print its 0-based position or "absent"; then INSERT a new node
   right after it (pointer surgery!), reprint chain.
📥 SAMPLE: list 10→20→30, V=20, insert 25
📤 OUTPUT: found at 1; chain: 10→20→25→30
💡 HINT: fresh->next = found->next; found->next = fresh;
   (order of those two lines is THE classic interview gotcha!)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 20.10 ⭐⭐⭐
📋 Benchmark your own sort: time (via counting comparisons in a
   counter variable) STL sort vs your bubble sort on the SAME
   random-filled vector of 1000 ints. Print both counters.
📤 OUTPUT: bubble ≈ 499,500 comparisons; std::sort ≈ ~10-20k
💡 HINT: vector + rand()%1000 fill (Ch. 23 headers); count inside
   a hand-rolled loop; for STL just state its O(n log n) ≈ n*log2(n).
```

---

## 🎯 MINI CHALLENGE — THE PLAYLIST MANAGER 🎵

Build a playlist with a **linked list** (yes, by hand — the STL is banned for this one):

```
1 Add song (to the END — append!)
2 Play all (traverse, printing "▶ song k")
3 Count songs
4 Exit (with FULL memory cleanup!)
```

- Node: `{string title; Node* next;}`
- Append means walking to the last node — maintain a `tail` pointer to make it O(1)! (What changes needed appending be O(1)? Discover it.)
- Exit prints "freed N nodes. clean exit ✓" — every `new` accounted for.

When your playlist both survives a brute-force quiz on lists AND leaks zero bytes, you've graduated from a list user to a list *engineer*. 🎓

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 20.1**
```cpp
#include <iostream>
using namespace std;
struct Node { int data; Node* next; };

int main() {
    Node* n3 = new Node{21, nullptr};
    Node* n2 = new Node{14, n3};
    Node* n1 = new Node{7, n2};
    Node* head = n1;

    for (Node* w = head; w != nullptr; w = w->next)
        cout << "[" << w->data << "] ➜ ";
    cout << "nullptr\n";

    delete n1; delete n2; delete n3;   // stack order fine (no deps during delete)
    return 0;
}
```

**✅ SOLUTION 20.2**
```cpp
#include <iostream>
using namespace std;
class MyStack {
    int a[3]; int top = -1;
public:
    bool push(int x) {
        if (top == 2) { cout << "OVERFLOW\n"; return false; }
        a[++top] = x; return true;
    }
    bool pop() {
        if (top == -1) { cout << "UNDERFLOW\n"; return false; }
        top--; return true;
    }
    int peek() { return top >= 0 ? a[top] : -1; }
};
int main() {
    MyStack s;
    s.push(10); s.push(20); s.push(30);
    s.pop(); s.pop();
    cout << "peek: " << s.peek() << "\n";   // 10
    s.pop(); s.pop();                        // last pop → UNDERFLOW
    return 0;
}
```

**✅ SOLUTION 20.3**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[6] = {30, 10, 50, 20, 60, 40}, n = 6;
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] > a[maxIdx]) maxIdx = j;
        swap(a[i], a[maxIdx]);
        cout << "after pass " << i + 1 << ": ";
        for (int k = 0; k < n; k++) cout << a[k] << " ";
        cout << "\n";
    }
    return 0;
}
```

**✅ SOLUTION 20.4**
```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main() {
    string s;
    cin >> s;
    stack<char> st;
    for (char c : s) st.push(c);
    bool ok = true;
    for (char c : s) {                    // forward vs popped-reverse
        if (c != st.top()) { ok = false; break; }
        st.pop();
    }
    cout << (ok ? "Palindrome" : "Not a palindrome");
    return 0;
}
```

**✅ SOLUTION 20.5**
```cpp
#include <iostream>
using namespace std;
int firstOccurrence(int a[], int n, int key) {
    int lo = 0, hi = n - 1, answer = -1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;         // overflow-safe midpoint!
        if (a[mid] == key) { answer = mid; hi = mid - 1; }   // keep hunting LEFT
        else if (a[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return answer;
}
int main() {
    int a[5] = {1, 2, 2, 2, 4};
    cout << "first 2 at index: " << firstOccurrence(a, 5, 2);   // 1
    return 0;
}
```
💡 **PRO TIP:** This "found it, but keep searching" variant is asked in nearly every serious binary-search interview set.

**✅ SOLUTION 20.6**
```cpp
#include <iostream>
using namespace std;
class CircQueue {
    char a[3]; int front = 0, rear = -1, count = 0;
public:
    bool enqueue(char x) {
        if (count == 3) return false;
        rear = (rear + 1) % 3;
        a[rear] = x; count++; return true;
    }
    bool dequeue() {
        if (count == 0) return false;
        front = (front + 1) % 3; count--; return true;
    }
    void print() {
        for (int i = 0; i < count; i++)
            cout << a[(front + i) % 3] << " ";
        cout << "\n";
    }
};
int main() {
    CircQueue q;
    q.enqueue('A'); q.enqueue('B'); q.enqueue('C');
    q.dequeue();
    q.enqueue('D');                  // wraps rear: (2+1)%3 = 0 ✓
    q.print();                       // B C D
    return 0;
}
```

**✅ SOLUTION 20.7**
```cpp
#include <iostream>
using namespace std;
struct Node { int data; Node* next; };
void prepend(Node*& h, int v) { h = new Node{v, h}; }

int main() {
    Node* head = nullptr;
    prepend(head, 42); prepend(head, 7); prepend(head, 91);
    prepend(head, 13); prepend(head, 58);

    int size = 0, mx = 0; bool first = true;
    for (Node* w = head; w; w = w->next) {
        size++;
        if (first) { mx = w->data; first = false; }
        else if (w->data > mx) mx = w->data;
    }
    cout << "size=" << size << ", max=" << mx << "\n";
    while (head) { Node* d = head; head = head->next; delete d; }
    return 0;
}
```

**✅ SOLUTION 20.8**
```cpp
#include <iostream>
using namespace std;
int main() {
    int a[9] = {1, 2, 3, 9, 4, 5, 6, 7, 8}, n = 9;

    int b[9]; copy(a, a + n, b);
    long long shifts = 0;
    for (int i = 1; i < n; i++) {
        int key = b[i], j = i - 1;
        while (j >= 0 && b[j] > key) { b[j + 1] = b[j]; shifts++; j--; }
        b[j + 1] = key;
    }

    long long cmps = 0;
    for (int p = 0; p < n - 1; p++)
        for (int i = 0; i < n - 1 - p; i++) cmps++;

    cout << "insertion shifts: " << shifts
         << " vs bubble comparisons: " << cmps << "\n";
    // ~1 shift vs 36 comparisons — insertion LOVES order.
    return 0;
}
```

**✅ SOLUTION 20.9**
```cpp
#include <iostream>
using namespace std;
struct Node { int data; Node* next; };
void prepend(Node*& h, int v) { h = new Node{v, h}; }
void print(Node* h) {
    for (Node* w = h; w; w = w->next) cout << w->data << "→";
    cout << "null\n";
}
int main() {
    Node* head = nullptr;
    prepend(head, 30); prepend(head, 20); prepend(head, 10);

    Node* found = head; int idx = 0, v = 20;
    while (found && found->data != v) { found = found->next; idx++; }

    if (!found) { cout << "absent\n"; }
    else {
        cout << "found at " << idx << "\n";
        // insertion surgery — ORDER MATTERS:
        Node* fresh  = new Node{25, found->next};   // ① fresh grabs found's link
        found->next  = fresh;                       // ② then found connects to fresh
    }
    print(head);                                    // 10→20→25→30→null
    while (head) { Node* d = head; head = head->next; delete d; }
    return 0;
}
```
💡 Swap those two surgical lines and the whole tail of the list vanishes. Interviewers *love* this question.

**✅ SOLUTION 20.10**
```cpp
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
int main() {
    vector<int> v(1000);
    for (int& x : v) x = rand() % 1000;

    long long cmp = 0;
    vector<int> b = v;
    for (int p = 0; p < (int)b.size() - 1; p++)
        for (int i = 0; i < (int)b.size() - 1 - p; i++) {
            cmp++;
            if (b[i] > b[i + 1]) swap(b[i], b[i + 1]);
        }

    sort(v.begin(), v.end());               // O(n log n) internally

    long long estFast = 1000 * 10;          // n * log2(n) ≈ 1000 * 10
    cout << "bubble comparisons: " << cmp << "\n";        // ~499500
    cout << "std::sort estimate (n log2 n): ~" << estFast << "\n";
    return 0;
}
```

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Node { string title; Node* next; };

class Playlist {
    Node* head = nullptr;
    Node* tail = nullptr;         // ⭐ tail pointer = O(1) appends!
public:
    void addSong(const string& t) {
        Node* fresh = new Node{t, nullptr};
        if (!head)  head = tail = fresh;
        else        { tail->next = fresh; tail = fresh; }
    }
    void playAll() {
        int k = 1;
        for (Node* w = head; w; w = w->next)
            cout << "▶ " << k++ << ". " << w->title << "\n";
    }
    int count() {
        int n = 0;
        for (Node* w = head; w; w = w->next) n++;
        return n;
    }
    int destroy() {
        int freed = 0;
        while (head) { Node* d = head; head = head->next; delete d; freed++; }
        tail = nullptr;
        return freed;
    }
};

int main() {
    Playlist pl;
    pl.addSong("Circles");
    pl.addSong("Midnight City");
    pl.addSong("Numb");
    pl.playAll();
    cout << "songs: " << pl.count() << "\n";
    cout << "freed " << pl.destroy() << " nodes. clean exit ✓\n";
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Linked list = chain of `Node{data, next}`; never move `head` directly; free every node
- ✓ Stack & queue from arrays need index pointers + overflow/underflow guards; circular queues use `%`
- ✓ Bubble/selection/insertion are all O(n²) — learn them for understanding, use `std::sort` for production
- ✓ Binary search halves to O(log n) but DEMANDS sorted data; `mid = lo + (hi - lo)/2`
- ✓ Big-O = growth language: at n = a million, O(log n) ≈ 20 steps while O(n²) ≈ 1000 seconds

**📚 Keywords learned:** linked list, node, head/tail, traversal, circular queue, bubble/selection/insertion sort, binary search, Big-O: O(1), O(log n), O(n), O(n log n), O(n²), pointer surgery

**🔗 Next chapter preview:** **PART 5 — PROJECTS!** 🎉 Chapter 21: the **Student Management System** — classes, files, searches, sorting: everything from Chapters 1–20 assembled into your first real application. This is what you've been training for.

*You're done learning tools. Time to build with ALL of them.* 🏗️

---

**⬅️ [Chapter 19](chapter-19-stl.md) | [🏠 Home](README.md) | [Chapter 21 ➡️](chapter-21-project-student-system.md)**
