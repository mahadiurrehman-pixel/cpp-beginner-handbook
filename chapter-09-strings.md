# CHAPTER 9 — STRINGS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"A string is just an array of characters
 that learned manners — and brought a toolbox."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 8](chapter-08-arrays.md) | [🏠 Home](README.md) | [Chapter 10 ➡️](chapter-10-pointers.md)**

---

## 📖 CHAPTER OPENING

Numbers are great, but your life runs on text: names, messages, poems, passwords. In Chapter 3 `string` held your name politely. Now we open the hood: how text really lives in memory, and the rich toolbox C++ gives you to slice, search, and reshape it.

### What you will learn:
- C-style strings (char arrays + the invisible `\0` guardian)
- The modern `std::string` — safer, smarter, friendlier
- Reading words vs. full lines (`cin >>` vs `getline`)
- The string toolbox: `length`, `substr`, `find`, `insert`, `erase`, `+`
- Comparing strings and converting string ↔ number (`stoi`, `to_string`)
- Building real text-processing programs

### Why this chapter matters:
Usernames, search bars, chat apps, file formats, AI prompts — everything is string processing. This chapter quietly powers half of what software does all day.

---

## 🔍 CONCEPT EXPLANATION

### What is a string?

A **string** is a sequence of characters. In C++ you meet two species:

```cpp
char oldWay[6] = {'h','e','l','l','o','\0'};   // C-style: char array
string newWay  = "hello";                       // std::string: modern class
```

**C-style** is a raw char array ending with a hidden **null terminator `\0`** — a "STOP" sign marking where text ends. It works, but it's fragile (fixed size, manual management).

**std::string** is the modern way: a class (Chapter 12 deep-dives classes) that manages memory for you and brings dozens of ready-made tools.

### Why do we use std::string?

```cpp
string a = "Hello", b = "World";
string c = a + " " + b;    // joining text is this easy
cout << c.length();        // 11 — ask questions directly
```
No size math, no `\0` babysitting, comparisons work with `==`. 

### How does the computer understand it?

Characters are just numbers (ASCII) side by side in memory — which is why everything you know about **arrays (Chapter 8) applies**: `s[i]` reads the i-th character, loops patrol the whole string.

🔥 **REMEMBER:** Indexing starts at 0; `s[s.length()]` is out of bounds — same rules as arrays.

---

## 📝 SYNTAX BOX

```cpp
#include <string>                        // don't forget!
// ---------- creating ----------
string s1 = "Hello";                    // from a literal
string s2("World");                     // constructor style
string s3(5, '*');                      // "*****" — 5 copies of '*'
string empty;                           // "" — zero length

// ---------- input ----------
cin >> s1;                              // ONE word (stops at space!)
getline(cin, s1);                       // FULL line incl. spaces

// ---------- info & access ----------
s1.length();  s1.size();                // both = number of chars
s1[i];  s1.at(i);                       // char at index i (at() is safe-checked)
s1.empty();                             // true if ""

// ---------- modifying ----------
s1 + s2;                                // join (returns new string)
s1 += " again";                         // append onto s1
s1.append("!");                         // same, method form
s1.substr(pos, len);                    // slice: s.substr(0,3) of "Hello" → "Hel"
s1.find("ell");                         // index of match, or string::npos if absent
s1.insert(2, "XX");                     // insert at index
s1.erase(1, 2);                         // remove 2 chars starting at index 1
s1.replace(0, 1, "J");                  // "Hello" → "Jello"
s1.clear();                             // becomes ""

// ---------- comparing & converting ----------
s1 == s2;  s1 < s2;                     // alphabetical (dictionary) order
stoi("42");                             // string → int    → 42
stod("3.5");                            // string → double → 3.5
to_string(2026);                        // int    → string → "2026"
```

📌 **NOTE:** `string::npos` is a special "not found" value. Test finds with `if (s.find("x") != string::npos)`.

---

## 💻 EXAMPLE CODES

### Example 9.1 — C-Strings: Meeting the Null Terminator

```cpp
// ============================================
// Example 9.1: The Old Way (understand, then move on)
// ============================================
// What this program does: Shows char arrays, \0, and cout behavior.
// Concepts used: C-string basics — knowing this saves debugging pain
// ============================================

#include <iostream>
using namespace std;

int main() {

    char word[] = "code";               // compiler auto-adds '\0' at the end

    cout << "As string: " << word << endl;
    cout << "Size of array: " << sizeof(word) << " bytes" << endl;  // 5! (4 + \0)

    // Patrol character by character (Chapter 8 skills!)
    cout << "Characters: ";
    for (int i = 0; word[i] != '\0'; i++) {   // stop at the STOP sign
        cout << "[" << word[i] << "=" << (int)word[i] << "] ";
    }
    cout << endl;

    word[0] = 'm';                       // chars are read-write like any array
    cout << "After surgery: " << word << endl;

    return 0;
}
/*
OUTPUT:
As string: code
Size of array: 5 bytes
Characters: [c=99] [o=111] [d=100] [e=101]
After surgery: mode

EXPLANATION:
cout prints chars until it hits '\0' — remove it and cout runs off
into random memory. C-strings are the raw machinery; std::string
wraps this machinery safely. History lesson over — now the good stuff.
*/
```

**What happened here?** You saw strings as they truly are: numbered chars in a row with a `\0` guardian at the end. Modern code uses `std::string`, but debuggers and old codebases still show you this one.

---

### Example 9.2 — std::string Basics: Words vs Lines

```cpp
// ============================================
// Example 9.2: cin >> vs getline (the space problem)
// ============================================
// Concepts used: string type, length(), indexed access, two input styles
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    string first, full;

    cout << "Enter first name: ";
    cin  >> first;                         // stops at the first space

    cin.ignore(10000, '\n');               // ⚠️ throw away leftover newline!

    cout << "Enter full name: ";
    getline(cin, full);                    // reads SPACES too, until Enter

    cout << "\nfirst.length() = " << first.length() << endl;
    cout << "first[0] = "        << first[0]         << endl;
    cout << "full = \""          << full << "\""     << endl;
    cout << "Last char of full: " << full[full.length() - 1] << endl;

    return 0;
}
/*
INPUT:  Mahadi  ↵  Mahadi ur Rehman ↵
OUTPUT:
first.length() = 6
first[0] = M
full = "Mahadi ur Rehman"
Last char of full: n

EXPLANATION:
After cin >>, the Enter key stays in the input pipe — getline would
read THAT as an empty line and seem to "skip". cin.ignore(n, '\n')
flushes the leftovers. This trap catches EVERY beginner once.
*/
```

**What happened here?** `cin >>` grabs one word; `getline` grabs the whole sentence; `ignore()` mediates their feud. Remember this trio — file and menu programs depend on it.

---

### Example 9.3 — The Toolbox: substr, find, insert, erase

```cpp
// ============================================
// Example 9.3: String Surgery
// ============================================
// What this program does: Slices and edits strings with the toolbox.
// Concepts used: substr, find (+npos), insert, erase, replace, +
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    string email = "mahadi.khan@gmail.com";

    // ---- substr(pos, length): cut a piece ----
    int atPos = email.find("@");                       // 11
    if (atPos != (int)string::npos) {                  // ALWAYS check!
        cout << "Username: " << email.substr(0, atPos) << endl;
        cout << "Domain:   " << email.substr(atPos + 1) << endl;   // to the end
    }

    // ---- find from a position ----
    int dot = email.find(".", atPos);                  // dot AFTER the @
    cout << "Dot after @ at index: " << dot << endl;

    // ---- insert & erase ----
    string shout = email;
    shout.insert(0, ">>> ");                           // prepend
    shout.erase(shout.length() - 4);                   // chop last 4 (".com")
    cout << "Edited: " << shout << endl;

    // ---- replace ----
    string masked = email;
    masked.replace(0, atPos, atPos, '*');              // hide username chars
    cout << "Masked: " << masked << endl;

    return 0;
}
/*
OUTPUT:
Username: mahadi.khan
Domain:   gmail.com
Dot after @ at index: 17
Edited: >>> mahadi.khan@gmail
Masked: ***********@gmail.com

EXPLANATION:
find returns the INDEX of the match (or npos = "not found").
substr(pos, len) copies a piece; omit len to take everything to the end.
These four tools disassemble and rebuild ANY text format:
emails, URLs, dates, file names.
*/
```

**What happened here?** With `find` + `substr` you parsed an email like regex-lite. `insert`/`erase`/`replace` then edited in place — that's two-thirds of everyday text processing.

---

### Example 9.4 — Real-World: Word Counter & Vowel Stats

```cpp
// ============================================
// Example 9.4: Sentence Analyzer
// ============================================
// What this program does: Counts words, vowels, and letters in a sentence.
// Concepts used: getline, char patrol with conditions, ASCII logic
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    string line;
    cout << "Type a sentence: ";
    getline(cin, line);

    int words = 1, vowels = 0, letters = 0;

    for (int i = 0; i < (int)line.length(); i++) {
        char c = line[i];

        if (c == ' ') words++;                    // spaces separate words

        c = tolower(c);                           // 'A' → 'a' (from <cctype>)
        if (c >= 'a' && c <= 'z') {
            letters++;
            if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') vowels++;
        }
    }

    if (line.empty()) words = 0;                  // corner case: no input

    cout << "\nWords:   " << words   << endl;
    cout << "Letters:  " << letters << endl;
    cout << "Vowels:   " << vowels  << endl;
    cout << "Chars:    " << line.length() << endl;

    return 0;
}
/*
INPUT:  C Plus Plus is fun
OUTPUT:
Words:   5
Letters:  14
Vowels:   4
Chars:    17

EXPLANATION:
A string is a char array, so Chapter 6's loop+condition machinery
works unchanged. tolower() normalizes case so we check 'a' once
instead of 'a' AND 'A'. Multiple spaces would inflate word count —
can you patch that? (Hint: a space only counts a new word if the
previous char wasn't a space.)
*/
```

**What happened here?** Loops + conditions + char indexing = a real text analyzer. Everything from spell-checkers to compilers starts exactly here.

---

### Example 9.5 — Comparison & Conversion: The Login + Age Gate

```cpp
// ============================================
// Example 9.5: == compares strings; stoi/to_string convert
// ============================================
// Concepts used: string ==, dictionary order <, stoi, to_string
// ============================================

#include <iostream>
#include <string>
using namespace std;

int main() {

    // ---- comparison ----
    const string USERNAME = "mahadi";
    string entered;
    cout << "Username: ";
    cin  >> entered;

    if (entered == USERNAME) {                       // == is safe for std::string!
        cout << "Welcome back!" << endl;
    } else if (entered < USERNAME) {
        cout << "Unknown. (Alphabetically before the admin, interesting.)" << endl;
    } else {
        cout << "Unknown. Try again." << endl;
    }

    // ---- conversions ----
    string ageText;
    cout << "Enter age as text: ";
    cin  >> ageText;

    int age = stoi(ageText);                         // "19" → 19
    cout << "Next year you'll be " << age + 1 << endl;

    string id = "STU-" + to_string(2026) + "-" + to_string(age);
    cout << "Generated ID: " << id << endl;

    return 0;
}
/*
INPUT:  mahadi ↵ 19 ↵
OUTPUT:
Welcome back!
Next year you'll be 20
Generated ID: STU-2026-19

EXPLANATION:
Comparing std::string with == compares CONTENT (unlike raw arrays!).
stoi converts "42" to 42 — but it THROWS an error on letters like
"abc"; Chapter 18 teaches bulletproofing against that. to_string
builds output strings from numbers — used in every receipt, ID,
and filename generator.
*/
```

**What happened here?** `==` verified identity; numeric strings became mathable; numbers became ID text. Cross-format conversion is daily bread in real systems.

> ❓ **THINK ABOUT IT:** Why does `"Apple" < "Banana"` print 1 but `"Zoo" < "apple"` print 1 too even though 'Z' looks "bigger" than 'a'? → ASCII: uppercase letters (65-90) sort before lowercase (97-122). Case matters in dictionary order!

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — Assuming `cin >>` reads a full line**
```cpp
string full;
cin >> full;              // "Mahadi Rehman" → only "Mahadi" is stored!
```
✅ **Fix:** `getline(cin, full);` for anything with spaces.

**❌ Mistake 2 — Mixing `cin >>` and `getline` without ignore**
```cpp
int age; cin >> age;      // leaves '\n' in the pipe
getline(cin, full);       // instantly reads that '\n' → full = "" (looks "skipped"!)
```
✅ **Fix:** `cin.ignore(10000, '\n');` after `>>` before any `getline`.

**❌ Mistake 3 — Comparing char arrays with `==`**
```cpp
char a[6] = "hello", b[6] = "hello";
if (a == b) { }           // compares ADDRESSES — always false!
```
✅ **Fix:** Use `std::string` (then `==` is correct), or `strcmp(a,b) == 0` for legacy C-strings.

**❌ Mistake 4 — `s[s.length()]` and negative indexes**
```cpp
string s = "hi";
cout << s[2];             // ❌ out of bounds: valid indexes are 0,1
```
✅ **Fix:** Last char = `s[s.length() - 1]`. Or use `s.back()` / `s.front()`.

**❌ Mistake 5 — `+` between two string LITERALS**
```cpp
string s = "Hello" + " World";      // ❌ error: can't add two literals
```
✅ **Fix:** `"Hello" " World"` (adjacent literals join) or `string("Hello") + " World"`. At least ONE side of `+` must be a `string` object.

**❌ Mistake 6 — Looping with signed/unsigned mismatch swallowed**
```cpp
for (int i = 0; i < line.length(); i++)   // warning: comparing int with size_t
```
✅ **Fix:** Cast: `i < (int)line.length()` — or loop `for (char c : line)` (range-for, Ch. 19's favorite). Compile with `-Wall` like Chapter 1 taught you.

---

## 🧠 CONCEPT SUMMARY TABLE

| Task | Code | Remember |
|---|---|---|
| Read one word | `cin >> s;` | stops at space |
| Read full line | `getline(cin, s);` | after `>>`, call `cin.ignore()` |
| Length | `s.length()` | last index = length−1 |
| Char access | `s[i]` / `s.at(i)` | `at()` warns on bad index |
| Join | `s1 + s2` / `s1 += s2` | literals need a string partner |
| Slice | `s.substr(pos, len)` | omit len → to the end |
| Search | `s.find("x")` | compare with `string::npos` |
| Insert / erase | `s.insert(i,"x")` / `s.erase(i,n)` | indexes shift after edits |
| Replace | `s.replace(i,n,"x")` | n chars from index i |
| Compare | `==`, `<` | alphabetical, case-sensitive |
| Convert | `stoi`, `stod`, `to_string` | stoi throws on bad text (Ch. 18) |
| Case helper | `tolower(c)`, `toupper(c)` | from `<cctype>` |

---

## ✏️ PRACTICE PROBLEMS

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.1 ⭐
📋 Read a full name with getline; print its length and initials'
   position: first char and the char after the first space.
📥 SAMPLE INPUT: Mahadi Rehman
📤 EXPECTED OUTPUT:
Length: 13
Initials: M R
💡 HINT: s[0], and find(' ') + 1.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.2 ⭐
📋 Read two words; print them joined with a dash, and their
   combined length.
📥 SAMPLE INPUT: north star
📤 EXPECTED OUTPUT: north-star (10 chars)
💡 HINT: a + "-" + b, then .length().
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.3 ⭐
📋 Read a word; print it in ALL CAPS using a loop.
📥 SAMPLE INPUT: hello
📤 EXPECTED OUTPUT: HELLO
💡 HINT: toupper(line[i]) — works only if char is a letter.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.4 ⭐⭐
📋 Reverse a string (loop, not built-in) and print it.
📥 SAMPLE INPUT: reverse
📤 EXPECTED OUTPUT: esrever
💡 HINT: Read s[i] from end to start into a result, or
   swap in place like Problem 8.7.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.5 ⭐⭐
📋 Palindrome check for a WORD (case-insensitive): "Madam" → true.
📥 SAMPLE INPUT: Madam
📤 EXPECTED OUTPUT: Palindrome
💡 HINT: Lowercase a copy, compare s[i] with s[len-1-i].
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.6 ⭐⭐
📋 Count spaces, digits, and letters in a getline sentence.
📥 SAMPLE INPUT: Room 404 is ready
📤 EXPECTED OUTPUT: Spaces=3 Digits=3 Letters=10
💡 HINT: isdigit(c), isalpha(c), c==' ' — from <cctype>.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.7 ⭐⭐
📋 Build a username: read first + last name (getline each),
   produce "flast" (first initial lowercase + last name lowercase,
   spaces removed). Input: "Mahadi" / "Ur Rehman"
📤 EXPECTED OUTPUT: murrehman
💡 HINT: tolower(first[0]) + loop last skipping spaces.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.8 ⭐⭐⭐
📋 Censor: read a sentence and a banned word; replace EVERY
   occurrence of the banned word with *** (same length).
📥 SAMPLE INPUT: "this game is bad and bad luck too" / bad
📤 EXPECTED OUTPUT: this game is *** and *** luck too
💡 HINT: while ((pos = s.find(bad, pos)) != npos) { s.replace(pos, bad.length(), "***"); }
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.9 ⭐⭐⭐
📋 Capitalize Every Word's first letter in a getline sentence.
📥 SAMPLE INPUT: welcome to the jungle
📤 EXPECTED OUTPUT: Welcome To The Jungle
💡 HINT: Cap when i==0 or s[i-1]==' '.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 9.10 ⭐⭐⭐
📋 Password strength checker: strong = length ≥ 8 AND has a digit
   AND has uppercase AND has lowercase AND a symbol.
📥 SAMPLE INPUT: Passw0rd!
📤 EXPECTED OUTPUT: Strong password 💪
💡 HINT: Four bool flags set in one char patrol, then a big &&.
```

---

## 🎯 MINI CHALLENGE — CHAT MESSAGE FORMATTER 💬

Build a chat pre-processor that, given a message via `getline`:
1. Prints a **preview**: the first 20 characters + "..." if longer
2. Prints the message in **SHOUT form** (all caps)
3. Counts characters, words (space-safe: ignore double spaces!)
4. Censors a hardcoded banned word `"noob"` to `"n\*\*b"`
5. Prints a signature footer: `"— sent from C++ Messenger v" + to_string(1.0)` — *(careful: `to_string(1.0)` gives "1.000000"; can you trim it or use `"1.0"` directly? Decide & explain in a comment!)*

You're literally writing the middleware of a messaging app. Show off. 🚀

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 9.1**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    getline(cin, s);
    int sp = s.find(' ');
    cout << "Length: " << s.length() << endl;
    cout << "Initials: " << s[0] << " " << s[sp + 1] << endl;
    return 0;
}
```
💡 **PRO TIP:** Assumes exactly one space — robust versions check `sp != string::npos` first.

**✅ SOLUTION 9.2**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string a, b;
    cin >> a >> b;
    string joined = a + "-" + b;
    cout << joined << " (" << joined.length() << " chars)" << endl;
    return 0;
}
```

**✅ SOLUTION 9.3**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    for (int i = 0; i < (int)s.length(); i++)
        cout << (char)toupper(s[i]);
    return 0;
}
```

**✅ SOLUTION 9.4**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s, rev = "";
    cin >> s;
    for (int i = s.length() - 1; i >= 0; i--) rev += s[i];
    cout << rev << endl;
    return 0;
}
```
💡 **PRO TIP:** `rev += s[i]` appends one char — strings grow in place, unlike arrays. This is why we love them.

**✅ SOLUTION 9.5**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    cin >> s;
    string low = s;
    for (int i = 0; i < (int)low.length(); i++) low[i] = tolower(low[i]);
    bool ok = true;
    for (int i = 0; i < (int)low.length() / 2; i++)
        if (low[i] != low[low.length() - 1 - i]) { ok = false; break; }
    cout << (ok ? "Palindrome" : "Not a palindrome") << endl;
    return 0;
}
```

**✅ SOLUTION 9.6**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    getline(cin, s);
    int sp = 0, dg = 0, lt = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == ' ')        sp++;
        else if (isdigit(s[i])) dg++;
        else if (isalpha(s[i])) lt++;
    }
    cout << "Spaces=" << sp << " Digits=" << dg << " Letters=" << lt;
    return 0;
}
```

**✅ SOLUTION 9.7**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string first, last;
    getline(cin, first);
    getline(cin, last);
    string user = "";
    user += (char)tolower(first[0]);
    for (int i = 0; i < (int)last.length(); i++)
        if (last[i] != ' ') user += (char)tolower(last[i]);
    cout << user << endl;                    // m + urrehman → murrehman
    return 0;
}
```
💡 **PRO TIP:** Building a result string char-by-char (`result += c`) is the "accumulator pattern" — for text.

**✅ SOLUTION 9.8**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s, bad;
    getline(cin, s);
    getline(cin, bad);

    int pos = 0;
    while ((pos = s.find(bad, pos)) != (int)string::npos) {
        s.replace(pos, bad.length(), "***");
        pos += 3;                        // jump past the stars
    }
    cout << s << endl;
    return 0;
}
```
💡 **PRO TIP:** The classic loop shape for "replace ALL": find from `pos`, replace, advance `pos`. Missing `pos +=` → infinite loop!

**✅ SOLUTION 9.9**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string s;
    getline(cin, s);
    for (int i = 0; i < (int)s.length(); i++) {
        if (i == 0 || s[i - 1] == ' ')
            s[i] = toupper(s[i]);
    }
    cout << s << endl;
    return 0;
}
```

**✅ SOLUTION 9.10**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string p;
    getline(cin, p);
    bool up = false, low = false, dig = false, sym = false;
    for (int i = 0; i < (int)p.length(); i++) {
        char c = p[i];
        if (isupper(c))      up  = true;
        else if (islower(c)) low = true;
        else if (isdigit(c)) dig = true;
        else                 sym = true;
    }
    if (p.length() >= 8 && up && low && dig && sym)
        cout << "Strong password 💪";
    else
        cout << "Weak password — needs 8+ chars, upper, lower, digit, symbol.";
    return 0;
}
```
💡 **PRO TIP:** Four independent conditions = four flag booleans set in ONE patrol — cleaner than nested ifs deep enough to need a ladder.

**✅ MINI CHALLENGE SOLUTION**
```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string msg;
    getline(cin, msg);

    // 1. preview
    string preview = (msg.length() > 20) ? msg.substr(0, 20) + "..." : msg;
    cout << "Preview: " << preview << endl;

    // 2. shout version
    string shout = msg;
    for (int i = 0; i < (int)shout.length(); i++) shout[i] = toupper(shout[i]);
    cout << "Shout: " << shout << endl;

    // 3. counts (space-safe words)
    int words = 0;
    for (int i = 0; i < (int)msg.length(); i++)
        if (msg[i] != ' ' && (i == 0 || msg[i - 1] == ' ')) words++;
    cout << "Chars: " << msg.length() << "  Words: " << words << endl;

    // 4. censor "noob"
    string safe = msg, bad = "noob", stars = "n**b";
    int pos = 0;
    while ((pos = safe.find(bad, pos)) != (int)string::npos) {
        safe.replace(pos, bad.length(), stars);
        pos += stars.length();
    }
    cout << "Censored: " << safe << endl;

    // 5. signature — "1.0" literal chosen: to_string(1.0) → "1.000000"
    cout << "— sent from C++ Messenger v" + string("1.0") << endl;
    return 0;
}
```

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Strings = char arrays (Ch. 8!) at heart; `std::string` adds safety + tools
- ✓ `cin >>` reads a word, `getline` reads a sentence, `ignore()` heals their feud
- ✓ The toolbox: `length`, `substr`, `find`+`npos`, `insert`, `erase`, `replace`, `+`
- ✓ `==` works properly on std::string; `stoi`/`to_string` convert to and from numbers
- ✓ Char patrols with `ctype.h` helpers (`tolower`, `isdigit`...) solve text problems

**📚 Keywords learned:** null terminator `\0`, C-string, `std::string`, `getline`, `ignore`, `substr`, `find`, `string::npos`, `insert`, `erase`, `replace`, `stoi`, `stod`, `to_string`

**🔗 Next chapter preview:** Chapter 10 — **Pointers & Memory**. The chapter everyone fears... and the chapter that makes everything (arrays, function calls, memory) finally make sense. You'll see your RAM's actual addresses. 🧠

*Text bends to your will now. Next: the machine itself.* ⚡

---

**⬅️ [Chapter 8](chapter-08-arrays.md) | [🏠 Home](README.md) | [Chapter 10 ➡️](chapter-10-pointers.md)**
