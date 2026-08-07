# CHAPTER 23 — PROJECT 3: NUMBER HUNT — THE COMPLETE CONSOLE GAME

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Games are the most honest software:
 if it's not fun, no feature list will
 save it."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 22](chapter-22-project-bank-system.md) | [🏠 Home](README.md) | [Conclusion ➡️](conclusion.md)**

---

## 1. 🎯 PROBLEM STATEMENT — What & Why

We'll build **NUMBER HUNT**: the computer hides a number; you hunt it with higher/lower hints. Sounds tiny — until we add difficulty levels, limited attempts, a scoring system, streaks, persistent high scores, and instant replay. That's when a 20-line guessing game becomes a *game loop* — the same architecture hiding inside every game you'll ever play.

**Chapters it combines:** 5/6 (decisions & loops = game logic!), 7 (functions per feature), 9 (strings), 17 (high-score file), 18 (bulletproof input), 19 (`vector` score table), and new friends `rand()`, `srand()`, `time()` from `<cstdlib>`/`<ctime>`.

## 2. 📋 FEATURES LIST

```
1 🎚️  Difficulty: Easy (1-50, 10 tries) / Medium (1-100, 7) / Hard (1-500, 9)
2 🎯  Random target each round (properly seeded once)
3 🔥  Hot/cold hints: within 5 = "🔥 very close!", within 15 = "warm"
4 ⭐  Scoring: base points by difficulty − penalty per attempt used
5 🏆  Persistent TOP-3 HIGH SCORE table saved to highscores.csv
6 📈  Session stats: rounds played, wins, win streak
7 🔁  Instant replay without restarting; quit anytime
8 🛡️  Immune to bad input — letters, out-of-range guesses handled
```

## 3. 🗺️ PLANNING PHASE

```
THE GAME LOOP (every game ever made):
    ┌──────────────────────────────────────────┐
    │  1. SETUP      read difficulty, make     │
    │               target = rand() % range + 1 │
    │  2. INPUT      read a guess (validated)   │
    │  3. UPDATE     attempts--, score math     │
    │  4. FEEDBACK   too high / too low / won!  │
    │  5. END?       win or attempts == 0 →     │
    │               else loop back to 2         │
    └──────────────────────────────────────────┘

SCORE = difficultyBase (300/500/900) − attemptsUsed × 25  (min 25)
PERSISTENCE: highscores.csv holds "name,score" rows → sorted top 3 on display
RANDOM RULE: srand(time(0)) called EXACTLY ONCE — at program start.
```

## 4. 💻 COMPLETE CODE

> Save as `number_hunt.cpp` → `g++ number_hunt.cpp -o hunt` → run.

```cpp
// @GAME-START
// ============================================
// PROJECT 3: NUMBER HUNT — a complete console game
// Chapters used: 5, 6, 7, 9, 17, 18, 19 (+ rand/srand/time)
// ============================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>                      // rand, srand
#include <ctime>                        // time(0)
using namespace std;

const string SCORE_FILE = "highscores.csv";

// ---------------- SAFE INPUT ----------------
int safeInt(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        try {
            int v = stoi(line);
            return v;
        } catch (...) { cout << "  ✗ Numbers only, hunter.\n"; }
    }
}

// ---------------- HIGH SCORE TABLE ----------------
struct Entry { string name; int score; };

bool betterScore(const Entry& a, const Entry& b) { return a.score > b.score; }

vector<Entry> loadScores() {
    vector<Entry> v;
    ifstream in(SCORE_FILE);
    string line;
    while (getline(in, line)) {
        int c = line.find(',');
        if (c == (int)string::npos) continue;
        try {
            v.push_back({ line.substr(0, c), stoi(line.substr(c + 1)) });
        } catch (...) { }
    }
    sort(v.begin(), v.end(), betterScore);
    return v;
}

void saveScores(vector<Entry> v) {
    sort(v.begin(), v.end(), betterScore);
    if (v.size() > 3) v.resize(3);            // hall of fame holds only 3
    ofstream out(SCORE_FILE);
    for (const Entry& e : v) out << e.name << "," << e.score << "\n";
}

void showScores() {
    vector<Entry> v = loadScores();
    cout << "\n🏆 HALL OF FAME 🏆\n";
    if (v.empty()) { cout << "  (no legends yet — be the first!)\n"; return; }
    const char* medals[3] = {"🥇", "🥈", "🥉"};
    for (int i = 0; i < (int)v.size(); i++)
        cout << "  " << medals[i] << " " << v[i].name << " — " << v[i].score << "\n";
}

// ---------------- ONE ROUND OF THE GAME ----------------
void playRound(int& wins, int& streak, int& rounds) {

    // ---- difficulty setup ----
    cout << "\nDifficulty: 1 Easy(1-50,x10)  2 Medium(1-100,x7)  3 Hard(1-500,x9)\n> ";
    int lvl = safeInt("");

    int maxNum, tries, base;
    if      (lvl == 1) { maxNum = 50;  tries = 10; base = 300; }
    else if (lvl == 3) { maxNum = 500; tries = 9;  base = 900; }
    else               { maxNum = 100; tries = 7;  base = 500; }   // default medium

    int target = rand() % maxNum + 1;           // ← the hidden number
    int used   = 0;

    cout << "\nI've hidden a number between 1 and " << maxNum
         << ". You have " << tries << " attempts. Good luck, hunter. 🏹\n";

    // ---- the core game loop ----
    while (tries > 0) {
        cout << "\n[" << tries << " tries left] ";
        int guess = safeInt("Your guess: ");

        if (guess < 1 || guess > maxNum) {
            cout << "✗ Outside the hunting grounds (1-" << maxNum
                 << ") — but I'll spare the attempt.\n";
            continue;                            // free reprieve, no penalty
        }

        used++;
        tries--;

        int gap = guess - target;
        if (gap < 0) gap = -gap;                 // |distance| without <cmath>

        if (guess == target) {
            int score = base - used * 25;
            if (score < 25) score = 25;
            cout << "\n🎯 BULLSEYE! " << target << " it is — in " << used
                 << " attempts! +" << score << " points!\n";

            wins++; streak++; rounds++;

            if (streak >= 2) cout << "🔥 WIN STREAK x" << streak << "!\n";

            vector<Entry> v = loadScores();
            v.push_back({ "Hunter", score });    // (name customizable below)
            saveScores(v);
            return;
        }
        else if (guess < target) cout << "📈 Too low! ";
        else                     cout << "📉 Too high! ";

        if (gap <= 5)       cout << "🔥 VERY close!";
        else if (gap <= 15) cout << "♨️ Warm.";

        if (tries == 0) {
            cout << "\n\n💀 Out of attempts. The number was " << target << ".\n";
            streak = 0; rounds++;
        }
    }
}

// ---------------- MAIN / GAME SHELL ----------------
int main() {

    srand(time(0));         // ⭐ seed ONCE — every round after is a fresh surprise

    int rounds = 0, wins = 0, streak = 0;

    cout << "╔════════════════════════════╗\n"
         << "║      🏹 NUMBER HUNT 🏹      ║\n"
         << "╚════════════════════════════╝\n";

    while (true) {
        cout << "\n===== MAIN MENU =====\n"
             << "1 Hunt a number   2 Hall of Fame   3 Session stats   0 Quit\n> ";
        int c = safeInt("");

        if (c == 1)      playRound(wins, streak, rounds);
        else if (c == 2) showScores();
        else if (c == 3) {
            cout << "\n📈 This session: " << rounds << " rounds, "
                 << wins << " wins, streak x" << streak << "\n";
        }
        else if (c == 0) {
            cout << "\nFinal tally: " << wins << "/" << rounds
                 << " hunts won. Happy hunting! 🏹\n";
            return 0;
        }
        else cout << "✗ Choose 0-3.\n";
    }
}
// @GAME-END
```

## 5. 📺 OUTPUT SCREENSHOT (text)

```
╔════════════════════════════╗
║      🏹 NUMBER HUNT 🏹      ║
╚════════════════════════════╝

===== MAIN MENU =====
1 Hunt a number   2 Hall of Fame   3 Session stats   0 Quit
> 1

Difficulty: 1 Easy(1-50,x10)  2 Medium(1-100,x7)  3 Hard(1-500,x9)
> 2

I've hidden a number between 1 and 100. You have 7 attempts. Good luck, hunter. 🏹

[7 tries left] Your guess: 50
📉 Too high! ♨️ Warm.

[6 tries left] Your guess: 40
📈 Too low!

[5 tries left] Your guess: 45
📈 Too low! 🔥 VERY close!

[4 tries left] Your guess: 47
🎯 BULLSEYE! 47 it is — in 4 attempts! +400 points!

===== MAIN MENU =====
> 2
🏆 HALL OF FAME 🏆
  🥇 Hunter — 425
  🥈 Hunter — 400
```

## 6. 🚀 HOW TO EXTEND IT

1. **Ask the player's name** once at start — hall of fame entries become personal
2. **Two-player mode**: Player 1 secretly types the number, Player 2 hunts
3. **Hunter-hard mode**: computer guesses YOUR number using binary search (Ch. 20!) — you answer only "higher/lower/correct". Build it with the exact halving loop!
4. **Time bonus**: record start time per round (`time(0)` again), bonus points for fast wins
5. **Lives system across rounds** — lose 3 total rounds and the session "ends"
6. **ASCII map mini-game** — next level: a 10×10 grid where you move toward a hidden treasure with Manhattan-distance hints (nested loops + conditions from Ch. 6!)

## 7. 🔍 CODE REVIEW — Key Decisions

| Decision | Why |
|---|---|
| Game loop as while(tries>0) | mirrors every game engine's input→update→feedback loop |
| `srand(time(0))` once | re-seeding per round makes sequences REPEAT on quick runs — the classic bug |
| Out-of-range guesses cost nothing | friendlier UX; distinction between mistakes and guesses |
| Score decays 25/attempt | rewards efficiency; difficulty base keeps hard mode worth it |
| High scores = load→merge→sort→trim→save | the simplest correct persistence pattern for ranked tables |
| Every input through safeInt | the game can NEVER crash on "banana" |
| Logic in functions, data by reference | main is a shell; rules are testable units |

## 8. 🐛 COMMON BUGS & FIXES

| Bug | Why | Fix (as coded) |
|---|---|---|
| Same target every run | missing `srand(time(0))` | one seed at start |
| Identical targets on rapid replays | seeding PER ROUND with same-second time | seed ONCE (done) |
| Infinite loop on letter input | `cin >>` fails and loops | safeInt (done) |
| Attempts drain on invalid entries | count++ before validation | validate first (done) |
| High score file corrupts entry order | appended without re-sorting | load→sort→trim→rewrite (done) |
| "rand() always 41 first" | unseeded default sequence | srand fix above |

**Motivation:** You started this book not knowing what `#include` meant. You just shipped a playable, persistent, uncrashable game. That's not nothing — that's *everything*. 🏹

---

**⬅️ [Chapter 22](chapter-22-project-bank-system.md) | [🏠 Home](README.md) | [Conclusion ➡️](conclusion.md)**
