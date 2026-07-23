# CHAPTER 1 — SETTING UP YOUR C++ ENVIRONMENT

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Before a painter paints, they set up their canvas.
 Before a programmer codes, they set up their tools."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 0](chapter-00-before-we-begin.md) | [🏠 Home](README.md) | [Chapter 2 ➡️](chapter-02-first-program.md)**

---

## 📖 CHAPTER OPENING

A chef needs a kitchen. A pilot needs a cockpit. A programmer needs an **environment** — the editor where you write code and the compiler that turns it into running programs. Today, we build yours.

### What you will learn:
- The two ways to code C++ (online vs. installed)
- Installing VS Code + a C++ compiler on Windows, Mac, and Linux
- The best online compilers if you want to start in 30 seconds
- Writing, compiling, and running your first `.cpp` file
- The developer workflow you'll use for the rest of your life

### Why this chapter matters:
Every minute spent fighting your tools is a minute not learning C++. Set it up once, correctly, now — and never think about it again. Also: "can you compile and run code from the terminal?" is a real job skill, not just a book exercise.

---

## 🔍 CONCEPT EXPLANATION

### What are we even installing?

Three different things beginners confuse:

| Tool | What it is | Analogy |
|---|---|---|
| **Editor (VS Code)** | Where you TYPE code | Microsoft Word, but for code |
| **Compiler (g++/MinGW)** | Translates code → executable | The printing press for your book |
| **IDE** | Editor + compiler + extras in one | A full office with everything |

VS Code is the editor. g++ is the compiler. Together they're your environment.

### Why do we need them?

Your computer can't run `.cpp` text files directly — remember Chapter 0: it only runs binary executables. Something must translate. That's the compiler's whole job.

### How does the computer understand it?

When you type `g++ hello.cpp -o hello`, the compiler reads your file, checks every rule of C++, and if the code is legal, writes a new file (`hello` / `hello.exe`) containing machine code. Running that file loads it into RAM and the CPU executes it.

```
  ┌─────────────┐
  │  You write  │
  │  .cpp file  │
  └──────┬──────┘
         ▼
  ┌─────────────┐
  │  Compiler   │   ←── If errors: compiler tells you, fix them
  │  (g++)      │
  └──────┬──────┘
         ▼
  ┌─────────────┐
  │ Executable  │
  │  (binary)   │
  └──────┬──────┘
         ▼
  ┌─────────────┐
  │   Output!   │
  └─────────────┘
```

---

## 📝 SYNTAX BOX — Terminal Commands You'll Live With

```bash
g++ filename.cpp -o programname
│    │           │   └─ what to NAME the executable
│    │           └─ "-o" means "output name"
│    └─ your C++ source file
└─ the compiler itself
```

```bash
./programname        # Mac / Linux: run it   (./ means "in this folder")
programname          # Windows cmd: run it   (no ./ needed)
```

**Common variations:**
```bash
g++ hello.cpp                 # compiles to default name: a.exe / a.out
g++ -Wall hello.cpp -o hello  # -Wall = show ALL warnings (recommended!)
g++ --version                 # check compiler is installed
```

📌 **NOTE:** From now on in this book, whenever you see `g++ file.cpp -o file` and `./file` — you already know what they mean. Two commands. That's the entire command-line skill for this book.

---

## 💻 EXAMPLE CODES

### Example 1.1 — The Easiest Path: Online Compiler (Zero Installation)

**OnlineGDB (recommended for beginners):**
1. Go to `www.onlinegdb.com`
2. Select **C++** from the language dropdown
3. Delete any existing code
4. Type this exact program:

```cpp
// ============================================
// Example 1.1: Hello from the Browser
// ============================================
// What this program does: Verifies your coding environment works.
// Concepts used: writing code in an online editor, pressing Run
// ============================================

#include <iostream>
using namespace std;

int main() {

    cout << "My C++ journey begins!" << endl;   // If you see this, setup works

    return 0;
}
/*
OUTPUT:
My C++ journey begins!

EXPLANATION:
The website ran a compiler FOR you, on their server.
You wrote code, pressed Run, and saw output — that IS programming.
*/
```

**Other solid online options:** **Replit** (`replit.com`, free account, saves your projects), **Programiz** (`programiz.com/cpp-programming/online-compiler/` — no account needed).

**What happened here?** You got a complete C++ environment with zero installation. Perfect for practice. The only catches: you need internet, and big projects are awkward in a browser — which is why we also install locally.

---

### Example 1.2 — Windows Setup (VS Code + MinGW)

**Step 1 — Install VS Code:**
1. Go to `code.visualstudio.com` → Download for Windows
2. Run installer ✓ "Add to PATH" ✓ "Create desktop icon"
3. Launch VS Code

**Step 2 — Install MinGW (the g++ compiler for Windows):**
1. Download MinGW-w64 (search "MinGW-w64 download" — the `winlibs` or `mingw-w64` build)
2. Install/extract with: Architecture **x86_64**, Threads **posix**, Exception **seh**
3. Note the `bin` folder, usually `C:\mingw64\bin`
4. Add it to PATH: Windows search → *"Environment Variables"* → System variables → **Path** → Edit → New → paste `C:\mingw64\bin` → OK everything

**Step 3 — Verify:** open Command Prompt and type:

```bash
g++ --version
```
```
EXPECTED OUTPUT:
g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 13.x.x
...
```
If you see a version number — 🎉 your Windows machine now speaks C++.

**Step 4 — VS Code extensions:** press `Ctrl+Shift+X`, install **"C/C++"** (by Microsoft) and **"Code Runner"**.

---

### Example 1.3 — Mac & Linux Setup

**Mac:**
```bash
# Open Terminal (Applications → Utilities → Terminal) and run:
xcode-select --install
# A popup installs Apple’s developer tools (includes a compiler).
# Then verify:
g++ --version
```
Then download VS Code for Mac and install the same "C/C++" extension.

**Linux (Ubuntu/Debian):**
```bash
sudo apt update
sudo apt install g++        # install the compiler
g++ --version               # verify
```
VS Code: download the `.deb` from `code.visualstudio.com` and double-click to install.

**What happened here?** On Mac and Linux the compiler is usually one command away. Whatever your OS, the goal line is identical: **`g++ --version` prints a version.**

---

### Example 1.4 — Write → Compile → Run Locally (The Real Deal)

1. Create a folder: `Desktop/MyCppCode`
2. Open VS Code → **File → Open Folder** → select `MyCppCode`
3. New file → name it exactly: `setup_test.cpp`
4. Type this:

```cpp
// ============================================
// Example 1.4: The Setup Victory Program
// ============================================
// What this program does: Confirms you can compile & run locally.
// Concepts used: saving .cpp files, terminal compile, running exe
// ============================================

#include <iostream>
using namespace std;

int main() {

    // If you can see this output, your ENTIRE setup works:
    cout << "================================" << endl;
    cout << "  SETUP COMPLETE. I am a C++   " << endl;
    cout << "  programmer now.               " << endl;
    cout << "================================" << endl;

    return 0;
}
```
5. Open the terminal inside VS Code (`` Ctrl+` ``)
6. Compile and run:
```bash
g++ setup_test.cpp -o setup_test
./setup_test        # Windows: just type  setup_test
```
```
OUTPUT:
================================
  SETUP COMPLETE. I am a C++
  programmer now.
================================
```

**What happened here?** You performed the complete professional workflow on your own machine: editor → terminal → compiler → executable → output. This is *exactly* how working developers do it.

---

### Example 1.5 — Deliberately Breaking It (Error Practice From the Terminal)

Let's meet a terminal error on purpose, where it can't hurt us:

```cpp
// ============================================
// Example 1.5: Break It On Purpose
// ============================================
// What this program does: NOTHING — we broke it deliberately.
// Save as broken.cpp, compile, and READ the error out loud.
// ============================================

#include <iostream>
using namespace std;

int main() {

    cout << "I never had a chance to run." << endl   // ← missing ; (on purpose!)

    return 0;
}
```
```bash
g++ broken.cpp -o broken
```
```
WHAT YOU SEE:
broken.cpp: In function 'int main()':
broken.cpp:10:5: error: expected ';' before 'return'
```
Now fix the semicolon, recompile, and run it successfully.

**What happened here?** You experienced an error→fix→success loop *deliberately*. That loop is programming. Notice: after fixing, you just press ↑ (up arrow) in the terminal to repeat your last command — a tiny habit that saves hours.

> ✅ **GOOD PRACTICE:** Compile often. Write 3 lines, compile. Write 5 more, compile. Finding one fresh error beats finding ten stacked ones.

---

## ⚠️ COMMON MISTAKES SECTION

**❌ Mistake 1 — File saved as `.txt` instead of `.cpp`**
Windows hides extensions by default, so you get `hello.cpp.txt` without knowing.
Compiler output: `g++: error: hello.cpp: No such file or directory`
✅ **Fix:** In File Explorer → View → ✓ "File name extensions". Name files `name.cpp`.

**❌ Mistake 2 — `'g++' is not recognized as an internal or external command`**
The PATH wasn't set (Windows) or the compiler isn't installed.
✅ **Fix:** Re-do the PATH steps, then **close and reopen** the terminal. Still failing? Carefully re-check the `bin` folder path — it must end in `\bin`.

**❌ Mistake 3 — Editing the file, compiling, seeing old behavior.**
You forgot to SAVE before compiling. The compiler reads the file *on disk*, not your unsaved editor tab.
✅ **Fix:** `Ctrl+S` before every compile. Enable VS Code's *Auto Save* (File → Auto Save).

**❌ Mistake 4 — Terminal in the wrong folder.**
`g++: error: hello.cpp: No such file or directory` even though the file exists.
✅ **Fix:** Use VS Code's integrated terminal (it opens in your project folder), or `cd` to the folder first. `dir` (Windows) / `ls` (Mac/Linux) shows what the terminal can see.

**❌ Mistake 5 — Running `./hello` on Windows cmd.**
`'..' is not recognized...` — the `./` prefix is Mac/Linux style.
✅ **Fix:** On Windows cmd just type the program name: `hello`. (In PowerShell you need `.\hello`.)

---

## 🧠 CONCEPT SUMMARY TABLE

| Concept | Meaning | Command / Action |
|---|---|---|
| Editor | Where you type code | VS Code |
| Compiler | Translates .cpp → executable | `g++` |
| Source file | Your code, plain text | `anything.cpp` |
| Executable | Runnable binary program | produced by compiler |
| Compile | Build the program | `g++ file.cpp -o prog` |
| Run | Execute it | `./prog` (Mac/Linux), `prog` (Windows) |
| PATH | OS's list of tool locations | must include compiler's `bin` |
| Online compiler | Compiler in a website | OnlineGDB, Replit, Programiz |
| Verify install | Should print version | `g++ --version` |

**When to use what:** Online compiler → quick practice, this book's exercises on the go. Local setup → projects, offline work, anything serious. Compile with `-Wall` → always, once you're comfortable.

---

## ✏️ PRACTICE PROBLEMS

These are *doing* tasks more than coding tasks — complete each, then self-check against the expected result in the solutions.

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.1
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Open an online compiler, run Example 1.1,
   and change the message to your name + city.
📤 EXPECTED OUTPUT: e.g.  Mahadi from Karachi begins!
💡 HINT: Only change the text inside the quotes.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.2
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Run g++ --version and write down your version.
   (Online-only readers: find the compiler version the site uses.)
📤 EXPECTED OUTPUT: A version line, e.g. g++ 13.2.0
💡 HINT: Windows users must open cmd AFTER setting PATH.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.3
🎯 DIFFICULTY: ⭐
📋 PROBLEM: Create a file named today.cpp that prints
   today's day and date. Compile and run it.
📤 EXPECTED OUTPUT: Today is Tuesday, 22 July 2026.
💡 HINT: Copy Example 1.4's structure; change one line.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.4
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Compile WITHOUT -o:  g++ today.cpp
   What file was created? What is it called on Windows
   vs Mac/Linux? Run it.
📤 EXPECTED OUTPUT: a.exe (Windows) / a.out (Mac/Linux),
   program runs fine when executed.
💡 HINT: "a" is the historic default name.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.5
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Compile with -Wall on a program containing
   an unused variable. Observe the warning. Fix it.
📤 EXPECTED OUTPUT: warning: unused variable 'x' [-Wunused-variable]
💡 HINT: int x = 5;  then never use x.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.6
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: Reproduce Mistake #4: try compiling from the
   wrong folder, read the error, then cd correctly and succeed.
📤 EXPECTED OUTPUT: First "No such file", then success.
💡 HINT: Use ls / dir to check where you are.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.7
🎯 DIFFICULTY: ⭐⭐
📋 PROBLEM: In VS Code, create a folder project1, add
   two .cpp files, compile each into two differently-named
   executables, and run both.
📤 EXPECTED: two programs, two outputs.
💡 HINT: g++ one.cpp -o one   g++ two.cpp -o two
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.8
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Full workflow from memory: close everything,
   create a new folder + file + compile + run WITHOUT
   looking at this chapter. Note every step you forgot.
📤 EXPECTED: Program runs; your "forgot" list written down.
💡 HINT: Most people forget to save or to cd.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.9
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Help a friend (real or imaginary) debug:
   "'g++' is not recognized". Write the 3-step checklist
   you'd give them.
📤 EXPECTED: A short checklist.
💡 HINT: Installed? PATH set? Terminal reopened?
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Problem 1.10
🎯 DIFFICULTY: ⭐⭐⭐
📋 PROBLEM: Draw the write→compile→run pipeline for a
   program named grades.cpp WITHOUT copying from the book.
📤 EXPECTED: Your own diagram with the two commands labeled.
💡 HINT: Four boxes minimum: file, compiler, executable, output.
```

---

## 🎯 MINI CHALLENGE — "SETUP SCAVENGER HUNT" 🏁

Complete all five checkpoints to prove your environment is battle-ready:

1. ✅ A folder called `cpp-journey` exists on your machine
2. ✅ Inside it, a file `checkpoint.cpp` prints your name and "READY"
3. ✅ You compiled it FROM THE TERMINAL with `g++ checkpoint.cpp -o checkpoint`
4. ✅ You ran it and saw your name
5. ✅ You introduced one error on purpose, read the message, fixed it

Do it in under 10 minutes? Excellent. Took 40? Also excellent — you now know exactly which steps need reps. Either way, **your environment is real now.** 💪

---

## 📚 SOLUTIONS SECTION

**✅ SOLUTION 1.1–1.3** — These are hands-on tasks; success is self-evident (the output appears). For 1.3, minimal code:
```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Today is Tuesday, 22 July 2026." << endl;
    return 0;
}
```
💡 **PRO TIP:** Hard-coding text is fine today. In Chapter 4 you'll make programs that *compute* things — much more fun.

**✅ SOLUTION 1.4** — Without `-o`, g++ names the executable `a.exe` (Windows) or `a.out` (Mac/Linux). Run with `a` / `./a.out`.
💡 **PRO TIP:** Always use `-o` with a meaningful name. `a.exe` files pile up and confuse everyone.

**✅ SOLUTION 1.5** — With `-Wall`, g++ warns about things that are legal but suspicious (unused variables, uninitialized reads). Warnings don't stop compilation — but treat them as errors-in-waiting.
💡 **PRO TIP:** Professional teams often compile with `-Wall -Werror`, which *turns warnings into errors*. Strict teachers make strong students.

**✅ SOLUTION 1.6–1.7** — Self-checking workflow tasks. The key habit: `ls`/`dir` before `g++` so you know what the terminal sees.

**✅ SOLUTION 1.8** — The honest "forgot list" is the answer. Common entries: forgot to save, forgot `-o` name, ran `./x` on Windows.
💡 **PRO TIP:** Repeat this drill until it's boring. Boring = automatic = professional.

**✅ SOLUTION 1.9** — Checklist: ① Is g++ installed at all? (`C:\mingw64\bin\g++.exe` exists / `which g++` prints a path) ② Is that `bin` folder in the PATH environment variable? ③ Did you close & reopen the terminal after editing PATH? 90% of cases are #3.

**✅ SOLUTION 1.10** — Any diagram containing: `grades.cpp` → `g++` → `grades.exe` → output, with `g++ grades.cpp -o grades` and `./grades` labeled, earns full marks.
💡 **PRO TIP:** If you can't draw it, you don't yet understand it — drawing is a brutally honest test.

---

## 🔗 CHAPTER SUMMARY

🔥 **REMEMBER:**
- ✓ Editor (VS Code) = write; compiler (g++) = translate; executable = run
- ✓ `.cpp` = C++ source file extension — always
- ✓ `g++ file.cpp -o prog` then `./prog` — the only two commands you need daily
- ✓ `'g++' not recognized` → PATH problem; re-open the terminal after fixing
- ✓ Online compilers are perfect for practice; local setup is for real work

**📚 Keywords learned:** IDE, editor, compiler, PATH, terminal/command prompt, source file, executable, `-o`, `-Wall`, integrated terminal

**🔗 Next chapter preview:** Chapter 2 — we write your first real program and dissect **every single character** of it: `#include`, `main`, `cout`, `return 0`, comments, and the semicolon that ruins weekends. 🎉

*Your environment is ready. Most people never get this far — they quit at installation. You didn't.* 🚀

---

**⬅️ [Chapter 0](chapter-00-before-we-begin.md) | [🏠 Home](README.md) | [Chapter 2 ➡️](chapter-02-first-program.md)**
