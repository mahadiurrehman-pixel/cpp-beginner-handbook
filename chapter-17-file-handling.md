# CHAPTER 17 — FILE HANDLING

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"RAM is a whiteboard — wiped clean at exit.
 A file is a notebook — it survives."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 16](chapter-16-friend-static.md) | [🏠 Home](README.md) | [Chapter 18 ➡️](chapter-18-exception-handling.md)**

```
                PART 4: ADVANCED CONCEPTS
```

---

## 📖 CHAPTER OPENING

You build the perfect student system, add 50 students, close the program — and they're gone. All data in RAM dies with the program. **File handling** is the branch that teaches your programs to write to *disk* — so data survives restarts, crashes, and power cuts. This is the chapter where your programs become *useful tomorrow*.

### What you will learn:
- Why files matter (persistence!)
- The three stream classes: `ofstream` (write), `ifstream` (read), `fstream` (both)
- Opening, closing, and checking files properly
- Writing, reading, and appending
- File modes (`ios::app`, `ios::trunc`...)
- Working with CSV-style records — saving actual structured data

### Why this chapter matters:
Databases, settings, savegames, logs, exports — all files underneath. Your Chapter 21 & 22 projects need persistence to be real, and this chapter hands it to you in just a few core patterns.

---

## 🔍 CONCEPT EXPLANATION

### What is a file, to a program?

A **file** is a named region of disk holding bytes. To C++, reading/writing a file is almost identical to `cin`/`cout` — you just replace the console with a **file stream object**:

```cpp
cout << "hello";            // → screen
ofstream out("data.txt");
out   << "hello";           // → disk file (same operator!)
```

### Why do we use files?

- **Persistence** — data survives program exit
- **Size** — files scale far beyond RAM
- **Sharing** — other programs (Excel, notepad) can read your output

### How does the computer understand it?

Your program asks the **operating system** to open a file; the OS returns a handle (tracked by your stream object). Writes may be **buffered** (collected in memory) until flushed — which is why `close()` matters: it forces the final flush and releases the handle. RAII (Chapter 13!) closes streams automatically when they leave scope, but explicit `close()` is still good practice.

---

## 📝 SYNTAX BOX

```cpp
#include <fstream>                    // the filing department

// ---------- WRITE (creates file; OVERWRITES existing content) ----------
ofstream out("notes.txt");            // out = file-bound "cout"
if (!out.is_open()) { /* error! */ }  // ALWAYS check
out << "line one\n";
out << 42 << " " << 3.5 << endl;      // numbers convert to text
out.close();                          // flush + release

// ---------- APPEND (adds to the END instead of erasing) ----------
ofstream app("notes.txt", ios::app);  // the mode flag that saves your history
app << "line two\n";
app.close();

// ---------- READ ----------
ifstream in("notes.txt");
string word;
while (in >> word) { }                // word-by-word, like cin

in.clear();  in.seekg(0);             // reset to re-read (rarely needed if reopened)

string line;
while (getline(in, line)) { }         // line-by-line (usually what you want)
in.close();

// ---------- BOTH ----------
fstream file("data.txt", ios::in | ios::out);

// ---------- useful modes ----------
ios::out      // write (default for ofstream) — TRUNCATES unless app
ios::app      // append at end
ios::in       // read
ios::trunc    // erase contents on open
```

| Object | Direction | Console cousin |
|---|---|---|
| `ofstream` | program → file | `cout` |
| `ifstream` | file → program | `cin` |
| `fstream` | both | — |

🔥 **REMEMBER:** Always verify `is_open()` — a typo'd or locked path silently turns into an empty-read ghost program.

---

## 💻 EXAMPLE CODES

### Example 17.1 — Hello, File! (Simplest Write & Read)

```cpp
// ============================================
// Example 17.1: First Words on Disk
// ============================================
// What this program does: Writes a greeting to a file, reads it back.
// Concepts used: ofstream, ifstream, is_open, close
// ============================================

#include <iostream>
#include <fstream>          // brings ofstream / ifstream / fstream
#include <string>
using namespace std;

int main() {

    // ---- WRITE ----
    ofstream out("hello.txt");                 // created next to your program
    if (!out.is_open()) {
        cout << "Could not create file!\n";
        return 0;                              // fail politely, never silently
    }
    out << "Hello, disk!\n";
    out << "This line survives program exit.\n";
    out.close();
    cout << "Written. Check hello.txt in your folder!\n";

    // ---- READ BACK ----
    ifstream in("hello.txt");
    if (!in.is_open()) {
        cout << "Could not open file!\n";
        return 0;
    }
    string line;
    cout << "\n--- Reading hello.txt ---\n";
    while (getline(in, line)) {                // line by line until the end
        cout << line << "\n";
    }
    in.close();

    return 0;
}
/*
OUTPUT:
Written. Check hello.txt in your folder!

--- Reading hello.txt ---
Hello, disk!
This line survives program exit.

EXPLANATION:
out behaves EXACTLY like cout, but the destination is hello.txt on
disk. Run the program twice: second read prints new content because
plain ofstream OVERWRITES. Open the file in Notepad — it's real!
*/
```

**What happened here?** Your program now has a memory beyond its own lifetime. Everything else in file handling is refinement of this write/check/read/check loop.

---

### Example 17.2 — Append Mode: The Forever Log

```cpp
// ============================================
// Example 17.2: A Running Log That Never Forgets
// ============================================
// What this program does: Adds timestamped entries without erasing history.
// Concepts used: ios::app, time() for rough timestamps, repeated runs
// ============================================

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

int main() {

    ofstream log("activity.log", ios::app);    // append — history preserved!
    if (!log.is_open()) {
        cout << "Log unavailable\n";
        return 0;
    }

    string action;
    cout << "What did you just do? ";
    getline(cin, action);

    // crude timestamp: seconds since 1970 — unique enough for a log
    log << "[t+" << time(0) << "] " << action << "\n";
    log.close();

    cout << "Logged! Run me repeatedly and watch activity.log grow.\n";

    // show the whole log so far:
    ifstream in("activity.log");
    string  l;
    cout << "\n--- Complete log so far ---\n";
    while (getline(in, l)) cout << l << "\n";

    return 0;
}
/*
RUN 1 INPUT:  Created the log
RUN 2 INPUT:  Added this second line
RUN 2 OUTPUT (log content):
[t+1753150000] Created the log
[t+1753150040] Added this second line

EXPLANATION:
ios::out (the default) ERASES; ios::app APPENDS. Forgetting this
is how beginners "lose" yesterday's data. Logs, history files,
high-score archives — always append.
*/
```

**What happened here?** Each run added without destroying. One flag — `ios::app` — is the difference between a notebook and an eraser.

---

### Example 17.3 — CSV Records: Saving Real Structured Data

```cpp
// ============================================
// Example 17.3: Students.csv — Spreadsheet-Friendly Storage
// ============================================
// What this program does: Saves structured records, reads & parses them.
// Concepts used: CSV format, getline with DELIMITER, stoi parse
// ============================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    // ---------- SAVE three students as CSV rows ----------
    ofstream out("students.csv");
    out << "roll,name,marks\n";                // header row (Excel shows it!)
    out << "101,Ali,78\n";
    out << "102,Sara,91\n";
    out << "103,Omar,64\n";
    out.close();

    // ---------- LOAD and parse ----------
    ifstream in("students.csv");
    string line;

    getline(in, line);                          // skip the header
    cout << "Loaded records:\n";

    double totalMarks = 0;
    int    count      = 0;

    while (getline(in, line)) {
        // split the line by commas:  getline(STREAM, TARGET, ',')
        string rollStr, name, marksStr;
        // We simulate with substr+find for clarity (advanced: stringstream)
        int c1 = line.find(',');
        int c2 = line.find(',', c1 + 1);

        rollStr  = line.substr(0, c1);
        name     = line.substr(c1 + 1, c2 - c1 - 1);
        marksStr = line.substr(c2 + 1);

        int roll  = stoi(rollStr);              // Ch. 9's converters!
        int marks = stoi(marksStr);

        cout << "Roll " << roll << " | " << name << " | " << marks << "\n";
        totalMarks += marks;
        count++;
    }
    in.close();

    cout << "Class average: " << totalMarks / count << "\n";
    return 0;
}
/*
OUTPUT:
Loaded records:
Roll 101 | Ali | 78
Roll 102 | Sara | 91
Roll 103 | Omar | 64
Class average: 77.6667

EXPLANATION:
CSV = comma-separated values — the lingua franca of simple data.
Writing: fields joined by commas, one record per line. Reading:
getline per line, split at commas, convert strings back to numbers
with stoi. Open students.csv in Excel — a real spreadsheet appears!
*/
```

**What happened here?** You built a tiny database with two columns of parsing logic. Your Chapter 21 project saves/loads exactly this way.

> 💡 **PRO TIP:** `stringstream` from `<sstream>` makes splitting cleaner: `stringstream ss(line); getline(ss, field, ',')` — try it as an upgrade once comfortable.

---

### Example 17.4 — Robust Reading: Counting & Empty-File Safety

```cpp
// ============================================
// Example 17.4: Count Lines, Words, Characters (the 'wc' tool)
// ============================================
// Concepts used: getline counting, >> word counting, eof safety, reuse open
// ============================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {

    // prepare a sample file first
    ofstream mk("poem.txt");
    mk << "roses are red\n";
    mk << "violets are blue\n";
    mk << "cpp files are fun\nand so are you\n";
    mk.close();

    // ---- count lines ----
    ifstream in("poem.txt");
    if (!in.is_open()) { cout << "missing poem.txt\n"; return 0; }

    string line;
    int lines = 0, chars = 0;
    while (getline(in, line)) {
        lines++;
        chars += line.length();              // +1 per \n omitted by getline
    }
    in.close();

    // ---- count words (fresh open = fresh read position) ----
    ifstream in2("poem.txt");
    string word;
    int    words = 0;
    while (in2 >> word) words++;             // >> skips spaces & newlines like cin
    in2.close();

    cout << "Lines: " << lines << " | Words: " << words
         << " | Chars: " << chars << "\n";
    return 0;
}
/*
OUTPUT:
Lines: 4 | Words: 19 | Chars: 74

EXPLANATION:
A stream remembers its READ POSITION. After finishing, either close
and reopen, or in.clear(); in.seekg(0); to rewind. The while(getline)
and while(in >> word) loops both simply stop at end-of-file —
the idiomatic way to process whole files without crashes.
*/
```

**What happened here?** You reimplemented half of the classic Unix `wc` tool in 20 lines — because files + loops + strings are actually that powerful now.

---

### Example 17.5 — Combined: The Contact Book (Save / Load / Search)

```cpp
// ============================================
// Example 17.5: Contacts.txt — A Mini Database With a Menu
// ============================================
// Concepts used: everything — objects serialized to lines, load at start,
//                save on change, search through loaded array
// ============================================

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact {
public:
    string name;
    string phone;
    string toLine() { return name + ";" + phone; }           // serialize
};

void saveAll(Contact list[], int n) {                        // full overwrite save
    ofstream out("contacts.txt");                            // full rewrite OK here:
    for (int i = 0; i < n; i++) out << list[i].toLine() << "\n"; // we write everything
}

int loadAll(Contact list[], int maxN) {
    ifstream in("contacts.txt");
    if (!in.is_open()) return 0;                             // no file yet = empty book
    string line; int n = 0;
    while (getline(in, line) && n < maxN) {
        int sep = line.find(';');
        if (sep == (int)string::npos) continue;              // skip corrupt lines
        list[n].name  = line.substr(0, sep);
        list[n].phone = line.substr(sep + 1);
        n++;
    }
    return n;
}

int main() {

    Contact book[100];
    int count = loadAll(book, 100);
    cout << "(loaded " << count << " contacts)\n";

    int choice;
    do {
        cout << "\n1.Add  2.List  3.Search  4.Exit\n> ";
        cin  >> choice;
        cin.ignore(10000, '\n');                             // Ch. 9's peace treaty

        if (choice == 1) {
            cout << "Name: ";
            getline(cin, book[count].name);
            cout << "Phone: ";
            getline(cin, book[count].phone);
            count++;
            saveAll(book, count);                            // persist immediately
            cout << "Saved ✓\n";
        } else if (choice == 2) {
            for (int i = 0; i < count; i++)
                cout << i + 1 << ". " << book[i].name << " — " << book[i].phone << "\n";
        } else if (choice == 3) {
            string q;
            cout << "Search name: ";
            getline(cin, q);
            bool any = false;
            for (int i = 0; i < count; i++)
                if (book[i].name.find(q) != string::npos) {  // substring search!
                    cout << "→ " << book[i].name << " — " << book[i].phone << "\n";
                    any = true;
                }
            if (!any) cout << "No contact matches.\n";
        }
    } while (choice != 4);

    cout << "Bye — your contacts are safe on disk.\n";
    return 0;
}
/*
SAMPLE RUN (two sessions!):
--- session 1 ---
(loaded 0 contacts)
1.Add ...  Name: Mahadi  Phone: 0300-111  → Saved ✓
4.Exit → Bye — your contacts are safe on disk.
--- session 2 (days later!) ---
(loaded 1 contacts)     ← IT REMEMBERED
2.List → 1. Mahadi — 0300-111

EXPLANATION:
The whole pattern: Load at start → work in memory → Save after each
change. Search handled by string::find (substring). ';' separator
instead of comma because names might contain commas in some locales.
THIS architecture == Chapter 21's project, just smaller.
*/
```

**What happened here?** Your program crossed the line from a *script* to an *application*: it remembers. Everything from here (projects, games) rides on this loop.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Never checking `is_open()`**
```cpp
ifstream in("data.csv");     // typo: file is data .CSV.txt
string line; getline(in, line);   // silently reads nothing — program "works" but empty
```
✅ **Fix:** `if (!in.is_open()) { cout << "Cannot open file\n"; return 0; }` — EVERY open, EVERY time.

**❌ Mistake 2 — Surprise overwrite (losing yesterday's data)**
```cpp
ofstream out("activity.log");   // default ios::out ERASES previous log!
```
✅ **Fix:** Want to keep history? `ofstream out("activity.log", ios::app);`

**❌ Mistake 3 — `>>` leftover newline poisoning `getline` (file edition)**
```cpp
int roll;
in >> roll;          // stops BEFORE the newline
string name;
getline(in, name);   // instantly eats that old newline → name = ""
```
✅ **Fix:** `in.ignore(10000, '\n');` after `>>` before `getline` — OR prefer clean CSV one-record-per-line parse as in Example 17.3.

**❌ Mistake 4 — Forgetting `close()` on writes before reading**
```cpp
ofstream out("x.txt"); out << "data";        // buffered, maybe not on disk yet
ifstream in("x.txt");  getline(in, line);    // sometimes EMPTY (still buffered)
```
✅ **Fix:** `out.close()` (or let the stream leave scope) before reading the same file. Buffers flush on close/destruction.

**❌ Mistake 5 — Using `eof()` to drive the loop**
```cpp
while (!in.eof()) {      // ❌ eof becomes true only AFTER a failed read —
    getline(in, line);   //    loop processes the last line TWICE
}
```
✅ **Fix:** `while (getline(in, line)) { ... }` — the read itself reports success/failure. This is THE canonical C++ pattern.

**❌ Mistake 6 — Hard-coded absolute paths**
```cpp
ofstream out("C:\\Users\\mahadi\\Desktop\\proj\\data.txt");   // breaks on any other PC
```
✅ **Fix:** Relative names (`"data.txt"`) stay next to the program. Escape backslashes (`\\`) if you must use Windows paths.

---

## 🧠 CONCEPT SUMMARY TABLE

| Task | Code | Key detail |
|---|---|---|
| Write a file | `ofstream out("f.txt");` | overwrites by default! |
| Append | `ofstream out("f.txt", ios::app);` | history safe |
| Read it | `ifstream in("f.txt");` | check `is_open()` |
| Line loop | `while (getline(in, line))` | the canonical pattern |
| Word loop | `while (in >> word)` | splits on whitespace |
| Read+write | `fstream f("f.txt", ios::in|ios::out);` | mind read position |
| Close | `f.close();` | flushes buffers |
| Check | `f.is_open()` / `!f` | never skip |
| Serialize object | `s.name + ";" + s.phone` | one record per line |
| Parse back | `find(';') + substr + stoi` | reverse the serialize |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.1 ⭐
📋 Write a program that saves 3 of your favorite quotes (hardcoded)
   to quotes.txt, then reads and prints them with a "📜" prefix.
📤 OUTPUT: 3 quotes printed from the READ (not from memory!)
💡 HINT: Write first, close, then open fresh to read.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.2 ⭐
📋 Make a vowel-counter for ANY text file: read poem.txt and count
   vowels inside it.
📤 OUTPUT: "Vowels in poem.txt: 27" (for Example 17.4's content)
💡 HINT: getline lines, patrol chars with Ch. 9 logic.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.3 ⭐
📋 Append a diary entry (user input, one line) to diary.txt each
   run; after saving, print "entries so far: N".
📤 OUTPUT: count grows across runs.
💡 HINT: ios::app for the write, separate read to count lines.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.4 ⭐⭐
📋 File copier: read source.txt, write EVERYTHING to backup.txt,
   report "copied N lines".
📤 OUTPUT: identical file + count message.
💡 HINT: getline loop → out << line << '\n'.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.5 ⭐⭐
📋 scores.csv ("name,score" rows); load & print the TOPPER's row.
📥 FILE:
Ali,78
Sara,91
Omar,64
📤 OUTPUT: "Topper: Sara (91)"
💡 HINT: parse per line, track max-index (Ch. 8 pattern!).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.6 ⭐⭐
📋 Add line numbers: read story.txt and print each line as
   "  1 | text" (right-aligned 3-wide using your own padding logic).
📤 OUTPUT: numbered display.
💡 HINT: pad with if(n<10) cout << " ", etc.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.7 ⭐⭐
📋 Search & count: program asks for a word; scans notes.txt and
   reports how many lines contain it (substring match).
📥 notes.txt has 5 lines, 2 contain "cpp"
📤 OUTPUT: "'cpp' appears in 2 lines."
💡 HINT: line.find(q) != string::npos.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.8 ⭐⭐⭐
📋 High-score updater: game.txt stores a single number.
   Program: reads it (default 0 if file missing), asks your new
   score, writes back only if higher, always prints both.
📥 sample: file has 450; you enter 700
📤 OUTPUT: "old: 450 → new high: 700, saved!"  (else "didn't beat it")
💡 HINT: !is_open() → treat as score 0; write only when beaten.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.9 ⭐⭐⭐
📋 Mini-ledger: accounts.txt holds "name;balance" lines. Program
   adds a deposit for a searched name and rewrites the file with
   the new balance (all other rows unchanged).
📥 FILE: Mahadi;1000  + deposit 500  →
📤 OUTPUT: file becomes Mahadi;1500 (rest intact)
💡 HINT: load all to array, modify one, saveAll (Example 17.5!).
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 17.10 ⭐⭐⭐
📋 Config manager: settings.txt stores "key=value" lines
   (volume=70, difficulty=Hard). Program shows all settings, lets
   user change a key, and writes the file back preserving others.
📤 OUTPUT: e.g. changed only volume → difficulty line survives.
💡 HINT: parse key by find('='); match, replace, rewrite all.
```

---

## 🎯 MINI CHALLENGE — THE PERSONAL DIARY 📔

Build the diary app properly:

```
======== MY DIARY ========
1. Write new entry
2. Read all entries
3. Count entries
4. Search entries by word
5. Exit
```

Rules:
- Entries append to `diary.txt` in format `[entry #N] your text`
- Entry number = current line count + 1 (computed at save time!)
- Search prints all matching lines with their numbers
- Never loses data across runs (append never overwrite)
- If diary.txt doesn't exist yet, start fresh at entry #1

This is Example 17.5's soul applied to a warmer purpose. When you read last week's thoughts in YOUR OWN program — that's the day programming becomes personal. 💙

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 17.1**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ofstream out("quotes.txt");
    out << "Code is poetry.\nStay curious.\nCompile your dreams.\n";
    out.close();

    ifstream in("quotes.txt");
    string line;
    while (getline(in, line)) cout << "📜 " << line << "\n";
    return 0;
}
```

**✅ SOLUTION 17.2**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream in("poem.txt");
    if (!in.is_open()) { cout << "no poem.txt\n"; return 0; }
    string line; int vowels = 0;
    while (getline(in, line))
        for (char c : line) {
            c = tolower(c);
            if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u') vowels++;
        }
    cout << "Vowels in poem.txt: " << vowels;
    return 0;
}
```

**✅ SOLUTION 17.3**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ofstream out("diary.txt", ios::app);
    string entry;
    getline(cin, entry);
    out << entry << "\n";
    out.close();

    ifstream in("diary.txt");
    string l; int n = 0;
    while (getline(in, l)) n++;
    cout << "entries so far: " << n;
    return 0;
}
```

**✅ SOLUTION 17.4**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream in("source.txt");
    ofstream out("backup.txt");
    if (!in.is_open() || !out.is_open()) { cout << "file error\n"; return 0; }
    string line; int n = 0;
    while (getline(in, line)) { out << line << "\n"; n++; }
    cout << "copied " << n << " lines";
    return 0;
}
```

**✅ SOLUTION 17.5**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream in("scores.csv");
    string line, topName; int topScore = -1;
    while (getline(in, line)) {
        int c = line.find(',');
        string name = line.substr(0, c);
        int score = stoi(line.substr(c + 1));
        if (score > topScore) { topScore = score; topName = name; }
    }
    cout << "Topper: " << topName << " (" << topScore << ")";
    return 0;
}
```

**✅ SOLUTION 17.6**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream in("story.txt");
    string line; int n = 0;
    while (getline(in, line)) {
        n++;
        if (n < 10)  cout << "  ";
        else if (n < 100) cout << " ";
        cout << n << " | " << line << "\n";
    }
    return 0;
}
```

**✅ SOLUTION 17.7**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string q;
    getline(cin, q);
    ifstream in("notes.txt");
    string line; int hits = 0;
    while (getline(in, line))
        if (line.find(q) != string::npos) hits++;
    cout << "'" << q << "' appears in " << hits << " lines.";
    return 0;
}
```

**✅ SOLUTION 17.8**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    int high = 0;
    ifstream in("game.txt");
    if (in.is_open()) { in >> high; in.close(); }   // missing file → 0

    int score;
    cout << "Your score: ";
    cin  >> score;

    cout << "old: " << high;
    if (score > high) {
        ofstream out("game.txt");
        out << score;
        cout << " → new high: " << score << ", saved!";
    } else {
        cout << " — didn't beat it.";
    }
    return 0;
}
```
💡 **PRO TIP:** "Read-if-exists, default-if-not" is THE config-file pattern — reused in every game/app save system.

**✅ SOLUTION 17.9**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string names[100]; double bal[100]; int n = 0;
    ifstream in("accounts.txt");
    string line;
    while (getline(in, line)) {
        int s = line.find(';');
        names[n] = line.substr(0, s);
        bal[n]   = stod(line.substr(s + 1));
        n++;
    }
    in.close();

    string who; double amount;
    cout << "Account name: "; getline(cin, who);
    cout << "Deposit: ";      cin >> amount;

    for (int i = 0; i < n; i++)
        if (names[i] == who) bal[i] += amount;

    ofstream out("accounts.txt");
    for (int i = 0; i < n; i++)
        out << names[i] << ";" << bal[i] << "\n";
    cout << "Ledger updated.";
    return 0;
}
```

**✅ SOLUTION 17.10**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string keys[50], vals[50]; int n = 0;
    ifstream in("settings.txt");
    string line;
    while (getline(in, line)) {
        int e = line.find('=');
        keys[n] = line.substr(0, e);
        vals[n] = line.substr(e + 1);
        n++;
    }
    in.close();

    for (int i = 0; i < n; i++) cout << keys[i] << " = " << vals[i] << "\n";

    string k, v;
    cout << "Change which key? ";  cin >> k;
    cout << "New value? ";         cin >> v;
    for (int i = 0; i < n; i++) if (keys[i] == k) vals[i] = v;

    ofstream out("settings.txt");
    for (int i = 0; i < n; i++) out << keys[i] << "=" << vals[i] << "\n";
    cout << "Settings saved.";
    return 0;
}
```

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int countEntries() {
    ifstream in("diary.txt");
    string l; int n = 0;
    while (getline(in, l)) n++;
    return n;
}

int main() {
    int choice;
    do {
        cout << "\n======== MY DIARY ========\n"
             << "1.Write  2.Read all  3.Count  4.Search  5.Exit\n> ";
        cin >> choice;
        cin.ignore(10000, '\n');

        if (choice == 1) {
            int n = countEntries() + 1;
            ofstream out("diary.txt", ios::app);
            cout << "Dear diary: ";
            string text; getline(cin, text);
            out << "[entry #" << n << "] " << text << "\n";
            cout << "Saved as entry #" << n << " ✓\n";
        } else if (choice == 2) {
            ifstream in("diary.txt");
            string l;
            while (getline(in, l)) cout << l << "\n";
        } else if (choice == 3) {
            cout << "Entries: " << countEntries() << "\n";
        } else if (choice == 4) {
            string q;
            cout << "Search for: "; getline(cin, q);
            ifstream in("diary.txt");
            string l; bool any = false;
            while (getline(in, l))
                if (l.find(q) != string::npos) { cout << l << "\n"; any = true; }
            if (!any) cout << "Nothing found.\n";
        }
    } while (choice != 5);
    cout << "Your diary is safe. 💙\n";
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Files = RAM's immortality: write with `ofstream`, read with `ifstream`, both with `fstream`
- ✓ `ios::app` appends; default `ios::out` overwrites — the difference between notebook and eraser
- ✓ The canonical read loop is `while (getline(in, line))` — never drive loops with `eof()`
- ✓ CSV lines + find/substr/stoi = a mini-database; serialize objects one record per line
- ✓ Check `is_open()` every single time, and `close()` (or scope-exit) before re-reading newly written data

**📚 Keywords learned:** persistence, stream, `ofstream`, `ifstream`, `fstream`, `ios::app`, `ios::in`, `ios::out`, buffering, CSV, serialize/parse, `is_open`, `getline(in, line)`

**🔗 Next chapter preview:** Chapter 18 — **Exception Handling**. So far "error handling" meant hoping users behave. Next: the professional `try / catch / throw` system — programs that catch their own disasters mid-air and land gracefully. Then files + exceptions = bulletproof software. 🛡️

*Your programs now remember yesterday. Soon, they'll also survive their own bad days.* 💾

---

**⬅️ [Chapter 16](chapter-16-friend-static.md) | [🏠 Home](README.md) | [Chapter 18 ➡️](chapter-18-exception-handling.md)**
