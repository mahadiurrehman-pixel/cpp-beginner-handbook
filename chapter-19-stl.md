# CHAPTER 19 — STL: THE STANDARD TEMPLATE LIBRARY

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Why forge the hammer when the toolbox —
 tested by millions — is already in your hands?"
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 18](chapter-18-exception-handling.md) | [🏠 Home](README.md) | [Chapter 20 ➡️](chapter-20-data-structures.md)**

---

## 📖 CHAPTER OPENING

In Chapter 8 you built arrays by hand; in Chapter 20 you'll build stacks and lists from scratch. That learning is priceless. But in *real life*, professionals don't rebuild — they use the **STL**: battle-tested, lightning-fast containers and algorithms shipped free with C++. One line `sort(v.begin(), v.end())` replaces your entire bubble sort. Today you get the keys to the professional toolbox.

### What you will learn:
- What the STL is (containers + iterators + algorithms)
- `vector` — the array that grows
- `stack`, `queue` — LIFO & FIFO
- `set`, `map` — uniqueness and key→value dictionaries
- Iterators — the universal "position" concept
- Algorithms: `sort`, `find`, `count`, `reverse`, `min/max_element`

### Why this chapter matters:
STL is the single biggest productivity jump in C++. Competitive programmers live in it; interviewers expect it; your projects become shorter AND stronger instantly.

---

## 🔍 CONCEPT EXPLANATION

### What is the STL?

The **Standard Template Library** = ready-made, generic (works with ANY type) building blocks, in three parts:

1. **Containers** — boxes that hold things (`vector`, `map`, `set`, ...)
2. **Iterators** — "bookmarks" pointing at positions inside containers
3. **Algorithms** — verbs that work ON containers through iterators (`sort`, `find`, ...)

```cpp
vector<int> v = {5, 2, 8};        // container (holds ints)
sort(v.begin(), v.end());         // algorithm using TWO iterator bookmarks
```

### Why do we use it?

Hand-rolled structures must be re-debugged forever; STL structures are correct, fast, and known by every C++ reader on Earth.

### How does the computer understand it?

STL is *template* code — the compiler stamps out an `int`-flavored or `string`-flavored copy of the machinery at compile time (that's why you write `vector<int>` — the type goes in angle brackets, and the error messages get... enthusiastic).

---

## 📝 SYNTAX BOX

```cpp
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>            // sort, find, count, reverse...

// ---------- vector: the growing array ----------
vector<int> v = {5, 2, 8};
v.push_back(1);                 // add to end → {5,2,8,1}
v.size();                       // 4
v[2];                           // 8 (fast, unchecked!)     v.at(2) → checked, throws
v.pop_back();                   // remove last → {5,2,8}
v.empty(); v.clear();           // test / wipe
for (int x : v) cout << x;      // RANGE-FOR: visit each element

// ---------- sort + friends ----------
sort(v.begin(), v.end());                       // ascending
sort(v.begin(), v.end(), greater<int>());       // descending
reverse(v.begin(), v.end());
auto it = find(v.begin(), v.end(), 8);          // → iterator, or v.end() if absent
int n = count(v.begin(), v.end(), 2);           // occurrences
*min_element(v.begin(), v.end());               // the min VALUE
*max_element(v.begin(), v.end());

// ---------- stack: LIFO (plates) ----------
stack<string> s;
s.push("A"); s.push("B");       // A bottom, B on top
s.top();                        // "B" (peek)
s.pop();                        // removes B — no return!

// ---------- queue: FIFO (ticket line) ----------
queue<string> q;
q.push("A"); q.push("B");
q.front();                      // "A"
q.pop();                        // removes A

// ---------- set: unique + sorted ----------
set<int> st = {5, 1, 5, 3};
// st is {1, 3, 5} — duplicates dropped, auto-sorted
st.insert(4);
st.count(3);                    // 1 if present else 0
for (int x : st) ...            // comes out SORTED

// ---------- map: key → value dictionary ----------
map<string, int> score;
score["Ali"] = 90;              // insert/overwrite
score["Sara"] = 95;
score.count("Ali");             // 1 if key exists (check BEFORE using [] )
for (auto& p : score)           // pairs come out sorted by KEY
    cout << p.first << ": " << p.second;
```

| Container | Superpower | Trade-off |
|---|---|---|
| `vector` | grow/shrink, instant `v[i]` | middle insert/erase is slow |
| `stack`/`queue` | one-end discipline | no indexed access at all |
| `set` | unique + sorted | no duplicates allowed |
| `map` | key→value lookup | keys must be unique |

---

## 💻 EXAMPLE CODES

### Example 19.1 — vector: The Array You Always Wanted

```cpp
// ============================================
// Example 19.1: vector Basics — Goodbye, Fixed Sizes
// ============================================
// Concepts used: vector, push_back, size, range-for, pop_back
// ============================================

#include <iostream>
#include <vector>
using namespace std;

int main() {

    vector<int> scores;                 // born EMPTY — no size needed!

    scores.push_back(85);               // grow on demand
    scores.push_back(92);
    scores.push_back(70);
    scores.push_back(99);

    cout << "We have " << scores.size() << " scores:\n";

    // classic index loop still works:
    for (int i = 0; i < (int)scores.size(); i++)
        cout << "  [" << i << "] = " << scores[i] << "\n";

    // the modern, can't-go-out-of-bounds way:
    cout << "Same, via range-for: ";
    for (int s : scores) cout << s << " ";

    scores.pop_back();                  // removes the 99
    cout << "\nAfter pop_back: ";
    for (int s : scores) cout << s << " ";
    cout << "\n";

    vector<string> names = {"Ali", "Sara"};   // vectors hold ANY type
    names.push_back("Omar");
    for (const string& n : names) cout << n << " ";   // const&: no copies (Ch.10!)

    return 0;
}
/*
OUTPUT:
We have 4 scores:
  [0] = 85
  [1] = 92
  [2] = 70
  [3] = 99
Same, via range-for: 85 92 70 99
After pop_back: 85 92 70
Ali Sara Omar

EXPLANATION:
vector manages dynamic memory (Ch. 10's new/delete) FOR you —
grows, shrinks, and frees itself on scope exit. Zero leaks,
zero size math. This single class retired most raw-array code.
*/
```

**What happened here?** Every Chapter 8 limitation (fixed size, manual tracking, leak risk) dissolved. **Default to `vector` from now on**; use raw arrays only when a problem demands one explicitly.

---

### Example 19.2 — Algorithms: One-Liners That Replace Chapters

```cpp
// ============================================
// Example 19.2: The Algorithm Arsenal
// ============================================
// Concepts used: sort, greater, reverse, find, count, min/max_element
// ============================================

#include <iostream>
#include <vector>
#include <algorithm>                    // the verbs live here
using namespace std;

void show(const string& label, const vector<int>& v) {
    cout << label << ": ";
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {

    vector<int> a = {42, 17, 93, 8, 55, 21, 93, 33};

    show("original     ", a);

    sort(a.begin(), a.end());                             // ascending — ONE LINE
    show("sorted asc   ", a);

    sort(a.begin(), a.end(), greater<int>());             // descending
    show("sorted desc  ", a);

    reverse(a.begin(), a.end());                          // flip it back
    show("reversed     ", a);

    auto it = find(a.begin(), a.end(), 55);               // locate a value
    if (it != a.end()) cout << "55 found at index " << (it - a.begin()) << "\n";
    else               cout << "55 missing\n";

    cout << "93 appears " << count(a.begin(), a.end(), 93) << " times\n";
    cout << "min = " << *min_element(a.begin(), a.end())
         << ", max = "   << *max_element(a.begin(), a.end()) << "\n";

    return 0;
}
/*
OUTPUT:
original     : 42 17 93 8 55 21 93 33
sorted asc   : 8 17 21 33 42 55 93 93
sorted desc  : 93 93 55 42 33 21 17 8
reversed     : 8 17 21 33 42 55 93 93
55 found at index 4
93 appears 2 times
min = 8, max = 93

EXPLANATION:
begin()/end() are ITERATOR BOOKMARKS: begin points at the first
element, end at one-PAST the last (so [begin, end) covers all).
find returns end() to signal "absent". it - begin turns an iterator
into a plain index. Everything Ch. 8 did by hand — industrialized.
*/
```

**What happened here?** `<algorithm>` turned bubble-sort chapters into readable one-liners with years of optimization behind them.

---

### Example 19.3 — Stack & Queue: The Two Disciplines

```cpp
// ============================================
// Example 19.3: Plates vs. Ticket Line
// ============================================
// Concepts used: stack (LIFO), queue (FIFO), push/pop/top/front
// ============================================

#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

int main() {

    // ---------- STACK: undo-history style (last in, FIRST out) ----------
    stack<string> actions;
    actions.push("typed 'H'");
    actions.push("typed 'i'");
    actions.push("deleted '!'");

    cout << "UNDO SEQUENCE:\n";
    while (!actions.empty()) {
        cout << "  undo: " << actions.top() << "\n";   // peek the newest
        actions.pop();                                  // then remove it
    }

    // ---------- QUEUE: printer-line style (first in, FIRST out) ----------
    queue<string> printer;
    printer.push("resume.pdf");
    printer.push("photo.png");
    printer.push("notes.txt");

    cout << "\nPRINT ORDER:\n";
    while (!printer.empty()) {
        cout << "  printing: " << printer.front() << "\n";  // oldest first
        printer.pop();
    }

    return 0;
}
/*
OUTPUT:
UNDO SEQUENCE:
  undo: deleted '!'
  undo: typed 'i'
  undo: typed 'H'

PRINT ORDER:
  printing: resume.pdf
  printing: photo.png
  printing: notes.txt

EXPLANATION:
These "adapters" FORBID random access — that's the point.
Stack answers "what was the LATEST thing?" (undo, browser back,
call stack from Ch. 7!). Queue answers "who's NEXT?" (task lines,
print spoolers, breadth-first search in later CS). Both loop-pattern:
while (!x.empty()) { peek; pop; }
*/
```

**What happened here?** Undo systems and job queues in 20 lines. The containers refuse unsafe usage by design — no `[i]` exists to misuse.

> 🎮 **FUN FACT:** The C++ *function call stack* from Chapter 7 is literally a `stack`: each call pushes a "frame" (locals + return address); each return pops it. That's why deep recursion = "STACK overflow"!

---

### Example 19.4 — Set & Map: The Word Analyzer

```cpp
// ============================================
// Example 19.4: Unique Words + Frequency Counter
// ============================================
// Concepts used: set (unique sorted), map (key→value), pair iteration
// ============================================

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
using namespace std;

int main() {

    vector<string> words = {"orange", "apple", "banana",
                            "apple", "orange", "apple"};

    // ---------- SET: what are the DISTINCT words? (sorted!) ----------
    set<string> uniqueWords(words.begin(), words.end());  // built from the vector

    cout << "Unique words (" << uniqueWords.size() << "): ";
    for (const string& w : uniqueWords) cout << w << " ";   // auto-sorted A→Z

    // ---------- MAP: how many times each? ----------
    map<string, int> freq;
    for (const string& w : words) {
        freq[w]++;        // map[] auto-creates missing keys with 0, then ++
    }

    cout << "\nFrequencies:\n";
    for (const auto& p : freq)                          // p is a PAIR
        cout << "  " << p.first << " → " << p.second << "\n";

    // safe lookup:
    string query = "kiwi";
    if (freq.count(query)) cout << query << " seen " << freq[query] << "x\n";
    else                   cout << query << " never seen.\n";

    return 0;
}
/*
OUTPUT:
Unique words (3): apple banana orange
Frequencies:
  apple → 3
  banana → 1
  orange → 2
kiwi never seen.

EXPLANATION:
set silently solved "remove duplicates AND sort" (a Ch. 8 multi-
loop problem). map made counting dictionary-trivial. Both keep
themselves sorted by key (alphabetical here) at all times.
⚠️ freq[query] on a missing key would CREATE it (with 0) — that's
why .count() check comes first when querying.
*/
```

**What happened here?** `map[key]++` might be the most productive five characters in applied C++. Database-less lookups, indexes, caches — all based on this pattern.

---

### Example 19.5 — Combined: The Leaderboard

```cpp
// ============================================
// Example 19.5: Top Scores — vector + sort + a small decision system
// ============================================
// Concepts used: vector of objects, custom comparator with sort,
//                find_if idea via loop, map-free leaderboard
// ============================================

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Player {                     // struct: class with public default —
    string name;                    // handy for tiny data bundles
    int    score;
};

// comparator: tells sort HOW to compare two Players (true = a before b)
bool better(const Player& a, const Player& b) {
    return a.score > b.score;       // descending by score
}

int main() {

    vector<Player> board;
    int n;
    cout << "How many players? ";
    cin  >> n;

    for (int i = 0; i < n; i++) {
        Player p;
        cout << "name score: ";
        cin  >> p.name >> p.score;
        board.push_back(p);
    }

    sort(board.begin(), board.end(), better);         // YOUR rule, STL's engine

    cout << "\n🏆 LEADERBOARD 🏆\n";
    for (int i = 0; i < (int)board.size(); i++) {
        cout << " " << (i + 1) << ". " << board[i].name
             << " — " << board[i].score;
        if (i == 0) cout << "  🥇";
        if (i == 1) cout << "  🥈";
        if (i == 2) cout << "  🥉";
        cout << "\n";
    }

    return 0;
}
/*
INPUT:  4  /  Ali 78  Sara 95  Omar 95  Zain 60
OUTPUT:
🏆 LEADERBOARD 🏆
 1. Sara — 95  🥇
 2. Omar — 95  🥈
 3. Ali — 78  🥉
 4. Zain — 60

EXPLANATION:
sort's third argument is ANY function returning "should a come
before b" — plug in custom rules for YOUR types. struct with public
members + a comparator function = the everyday data-sorting duo.
Chapter 22's project will sort accounts exactly this way.
*/
```

**What happened here?** The STL shape of "professional small app": container of structs + custom comparator + formatted loop. Master this and you master 70% of utility program patterns.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — `v[i]` on a size-beyond vector**
```cpp
vector<int> v = {1, 2, 3};
cout << v[10];        // ❌ undefined behavior. No error. Silence.
```
✅ **Fix:** `v.at(10)` throws `out_of_range` (catch it — Ch. 18!), or iterate with range-for which can never escape bounds.

**❌ Mistake 2 — `top()`/`front()` on an empty stack/queue**
```cpp
stack<int> s;
cout << s.top();      // 💥 undefined behavior
```
✅ **Fix:** `if (!s.empty()) cout << s.top();`

**❌ Mistake 3 — Querying maps with `[]` (accidentally CREATING keys)**
```cpp
map<string,int> m;
if (m["ghost"] == 0) { }   // ❌ just INSERTED "ghost"→0 into the map!
```
✅ **Fix:** Check membership with `m.count("ghost")` (or `m.find(k) != m.end()`), then read with `m.at("ghost")` (throws if absent).

**❌ Mistake 4 — Erasing while range-looping the same container**
```cpp
for (int x : v)
    if (x == bad) v.erase(...);     // 💥 iterators invalidated mid-loop — crash/rubbish
```
✅ **Fix:** The safe habit: collect items into a new vector, or learn `remove`+`erase` idiom later. For now: build-new instead of edit-in-place.

**❌ Mistake 5 — Expecting `set` to keep INPUT order**
```cpp
set<int> s = {9, 1, 5};
for (int x : s) cout << x;     // prints 1 5 9 — NOT the 9 1 5 you typed
```
✅ **Fix:** `set` is always sorted & unique. Need order-preserving uniqueness? Scan into a `vector`, skipping already-present values.

**❌ Mistake 6 — `sort` on a container without begin/end sense**
```cpp
stack<int> s;
sort(s.begin(), s.end());      // ❌ stacks have NO begin()/end() — by design
```
✅ **Fix:** Only sequence containers (vector, deque, list-ish) iterate. Copy data to a vector if sorting is genuinely needed.

---

## 🧠 CONCEPT SUMMARY TABLE

| Tool | Header | Code sketch | Use |
|---|---|---|---|
| vector | `<vector>` | `vector<int> v; v.push_back(x);` | default container of choice |
| range-for | — | `for (int x : v)` | safe full patrol |
| stack | `<stack>` | `push/top/pop` | undo, backtracking, LIFO |
| queue | `<queue>` | `push/front/pop` | waiting lines, FIFO |
| set | `<set>` | sorted unique values | dedupe + order |
| map | `<map>` | `m[key] = value; m.count(k)` | dictionaries, caches, freq |
| sort | `<algorithm>` | `sort(v.begin(), v.end(), cmp?)` | asc/desc/custom instantly |
| find/count | `<algorithm>` | `find(b,e,x) != v.end()` | membership & tallies |
| reverse | `<algorithm>` | `reverse(b,e)` | flip |
| min/max_element | `<algorithm>` | `*min_element(b,e)` | extrema values |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.1 ⭐
📋 Read N from user, then N ints into a vector via push_back;
   print them reversed via reverse() + range-for.
📥 INPUT: 4 → 1 2 3 4
📤 OUTPUT: 4 3 2 1
💡 HINT: two acts: input loop, then reverse+print loop.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.2 ⭐
📋 Use min_element and max_element on a vector of 6 entered ints;
   print both and their difference (the RANGE).
📥 INPUT: 4 9 2 9 7 3
📤 OUTPUT: min=2 max=9 range=7
💡 HINT: * dereferences the returned iterator.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.3 ⭐
📋 Load words into a set<string>; report distinct count and the
   alphabetically-first word. Input (one line): pear fig apple fig
📤 OUTPUT: distinct=3, first=apple
💡 HINT: *s.begin() is the smallest.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.4 ⭐⭐
📋 Phonebook with map<string,string>: menu Add / Find / ListAll
   sorted / Count / Exit. Duplicate names overwrite politely
   ("updated").
📥 SAMPLE: Add Ali 0300 → Add Sara 0321 → Find Ali → ListAll
📤 OUTPUT: found number; alphabetical full listing; count=2.
💡 HINT: count() before find; loop prints p.first/p.second.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.5 ⭐⭐
📋 Stack-based string reverser WITHOUT using string reversal:
   push each CHAR of input, pop all into result. Proof it works
   for "hello" → "olleh". Explain why LIFO reverses (comment).
📥 INPUT: hello
📤 OUTPUT: olleh
💡 HINT: LIFO = last char pushed is first popped.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.6 ⭐⭐
📋 Queue simulator: 5 customers join ("C1".."C5"); serve 2;
   a VIP jumps the line by being served next via front check;
   print final line state after 3 total served.
📤 OUTPUT: served order C1, C2, C3; remaining: C4 C5.
💡 HINT: FIFO — push 5, pop-loop 3 times, then display rest.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.7 ⭐⭐
📋 Duplicates report: given a vector of 8 ints, using ONLY a set
   (and its insertion behavior), print which values appeared MORE
   than once. Input: 4 2 7 2 4 4 9 7
📤 OUTPUT: repeats: 4 2 7
💡 HINT: keep set seen; if insert fails (already there), log repeat.
   (pair from s.insert: .second false = was present)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.8 ⭐⭐⭐
📋 Word-frequency with map on a full getline sentence — split into
   words manually (Ch. 9 skill), freq-count each, then print the
   TOP 2 most frequent words.
📥 INPUT: the cat and the dog and the bird
📤 OUTPUT: the:3  and:2
💡 HINT: map counts first; then hunt top-2 via two max-passes or
   copy pairs to a vector + custom sort like Example 19.5.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.9 ⭐⭐⭐
📋 "Bracket balance" with a stack: read a string of (){}[], push
   on opener, pop on closer (matching type else UNBALANCED), end
   must be EMPTY. ("{[()]}" balanced; "{[(])}" not)
📥 INPUT: {[()]}
📤 OUTPUT: Balanced ✓
💡 HINT: map closer→opener; on closer check stack top matches.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 19.10 ⭐⭐⭐
📋 Student registry 2.0: vector<Student{name, marks}>; menu with
   add / list SORTED by marks desc / search by name / stats
   (avg, max via algorithm) / exit. Use a custom comparator and
   at least 3 <algorithm> functions.
📤 OUTPUT: full working registry session.
💡 HINT: basically Example 19.5 grown one notch — you own this.
```

---

## 🎯 MINI CHALLENGE — THE NOTE-TAKING ENGINE 🗒️

Build a tag-based note keeper using MULTIPLE STL tools at once:

```
MENU: 1 Add note  2 List notes  3 Search by word  4 Tag cloud  5 Exit
```

- `vector<string> notes` — the raw storage
- Search: any note `find(q) != npos` (Ch. 17's trick)
- **Tag cloud**: scan all notes, collect words into a `map<string,int>` of frequencies; show words with count ≥ 2, sorted naturally by your map
- BONUS: `set<string>` collects unique word count: `"vocabulary size: N"`

Stretch goal that will make you grin: save notes to file (Ch. 17 persistence) and load at start. Suddenly it's a real app — built entirely from your toolbox. 🧰✨

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 19.1**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) { int x; cin >> x; v.push_back(x); }
    reverse(v.begin(), v.end());
    for (int x : v) cout << x << " ";
    return 0;
}
```

**✅ SOLUTION 19.2**
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<int> v(6);
    for (int& x : v) cin >> x;
    int lo = *min_element(v.begin(), v.end());
    int hi = *max_element(v.begin(), v.end());
    cout << "min=" << lo << " max=" << hi << " range=" << hi - lo;
    return 0;
}
```
💡 `for (int& x : v)` — reference lets the loop WRITE into the vector directly.

**✅ SOLUTION 19.3**
```cpp
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main() {
    set<string> s;
    string w;
    while (cin >> w) s.insert(w);
    cout << "distinct=" << s.size() << ", first=" << *s.begin();
    return 0;
}
```

**✅ SOLUTION 19.4**
```cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
    map<string, string> book;
    int ch;
    do {
        cout << "\n1.Add 2.Find 3.List 4.Count 5.Exit\n> ";
        cin >> ch;
        if (ch == 1) {
            string n, num;
            cout << "name number: ";
            cin >> n >> num;
            cout << (book.count(n) ? "updated ✓\n" : "added ✓\n");
            book[n] = num;
        } else if (ch == 2) {
            string n;
            cin >> n;
            if (book.count(n)) cout << n << " → " << book[n] << "\n";
            else               cout << "not found\n";
        } else if (ch == 3) {
            for (auto& p : book) cout << p.first << " → " << p.second << "\n";
        } else if (ch == 4) {
            cout << "contacts: " << book.size() << "\n";
        }
    } while (ch != 5);
    return 0;
}
```

**✅ SOLUTION 19.5**
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    stack<char> st;
    for (char c : s) st.push(c);          // h e l l o (o on top)

    string out = "";
    while (!st.empty()) {                  // LIFO: 'o' leaves first
        out += st.top();
        st.pop();
    }
    cout << out;                           // olleh — stack reverses order
    return 0;
}
```

**✅ SOLUTION 19.6**
```cpp
#include <iostream>
#include <queue>
#include <string>
using namespace std;
int main() {
    queue<string> line;
    for (int i = 1; i <= 5; i++) line.push("C" + to_string(i));

    for (int i = 0; i < 3; i++) {                 // serve 3
        cout << line.front() << " served. ";
        line.pop();
    }
    cout << "\nremaining: ";
    while (!line.empty()) { cout << line.front() << " "; line.pop(); }
    return 0;
}
```

**✅ SOLUTION 19.7**
```cpp
#include <iostream>
#include <set>
using namespace std;
int main() {
    int a[8] = {4, 2, 7, 2, 4, 4, 9, 7};
    set<int> seen, repeats;
    for (int x : a) {
        auto result = seen.insert(x);      // .second == false → already present
        if (!result.second) repeats.insert(x);
    }
    cout << "repeats: ";
    for (int x : repeats) cout << x << " ";
    return 0;
}
```
💡 `set::insert` returns a `pair<iterator, bool>` — the bool is your "was it new?" flag.

**✅ SOLUTION 19.8**
```cpp
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool byCountDesc(const pair<string,int>& a, const pair<string,int>& b) {
    return a.second > b.second;
}

int main() {
    string line;
    getline(cin, line);

    map<string,int> freq;
    string word = "";
    for (char c : line) {
        if (c == ' ') { if (!word.empty()) freq[word]++; word = ""; }
        else word += c;
    }
    if (!word.empty()) freq[word]++;

    // pairs → vector for custom sort by count:
    vector<pair<string,int>> items(freq.begin(), freq.end());
    sort(items.begin(), items.end(), byCountDesc);

    for (int i = 0; i < 2 && i < (int)items.size(); i++)
        cout << items[i].first << ":" << items[i].second << "  ";
    return 0;
}
```

**✅ SOLUTION 19.9**
```cpp
#include <iostream>
#include <stack>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    stack<char> st;
    bool ok = true;

    for (char c : s) {
        if (c=='(' || c=='{' || c=='[') st.push(c);
        else {
            if (st.empty()) { ok = false; break; }
            char open = st.top(); st.pop();
            if ((c==')' && open!='(') || (c=='}' && open!='{') ||
                (c==']' && open!='[')) { ok = false; break; }
        }
    }
    if (!st.empty()) ok = false;
    cout << (ok ? "Balanced ✓" : "Unbalanced ✗");
    return 0;
}
```
💡 **PRO TIP:** This is genuinely how compilers check your own bracket-matching — you just wrote a mini-compiler pass!

**✅ SOLUTION 19.10** — Combine Examples 19.2 & 19.5: registry vector, `sort(..., byMarksDesc)`, `find_if` or loop for name search, accumulate for average, `max_element` for top. (Full registry pattern also powers Chapter 21's project — peek there after attempting!)

**✅ MINI CHALLENGE (core loop sketch)**
```cpp
// add:    getline → notes.push_back(text)
// list:   range-for with numbering
// search: for (auto& n : notes) if (n.find(q) != string::npos) print
// cloud:  split each note on spaces → map<string,int> freq; print count>=2
// vocab:  set<string> all; each word insert; print all.size()
// save:   Ch. 17 ofstream on exit, ifstream load at start
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ STL = containers (boxes) + iterators (bookmarks) + algorithms (verbs), all type-generic
- ✓ `vector` replaces raw arrays almost everywhere: grows, knows its size, cleans itself
- ✓ stack=LIFO, queue=FIFO — discipline adapters; set=unique+sorted; map=key→value
- ✓ `sort(v.begin(), v.end(), cmp?)` + find/count/reverse/minmax = one-line superpowers
- ✓ Guard empties before top/front, count() maps before [], and never edit-while-rangefor

**📚 Keywords learned:** STL, container, iterator, `vector`, `stack`, `queue`, `set`, `map`, `pair`, range-for, `sort`, `greater<>()`, `find`, `count`, `min_element`, comparator

**🔗 Next chapter preview:** Chapter 20 — **Basic Data Structures**. We look UNDER the STL's hood: build linked lists, stacks, and queues by hand, compare sorting algorithms, and meet Big-O — so you understand *why* your STL choices are fast. Last fundamentals chapter before the Projects! ⚙️

*You just upgraded from hand tools to power tools. Never build manually what the STL perfected.* 🚀

---

**⬅️ [Chapter 18](chapter-18-exception-handling.md) | [🏠 Home](README.md) | [Chapter 20 ➡️](chapter-20-data-structures.md)**
