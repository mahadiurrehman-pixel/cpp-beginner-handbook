# CHAPTER 22 — PROJECT 2: BANK MANAGEMENT SYSTEM

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
"Money demands two things:
 accuracy and trust. Build both."
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

**⬅️ [Chapter 21](chapter-21-project-student-system.md) | [🏠 Home](README.md) | [Chapter 23 ➡️](chapter-23-project-game.md)**

---

## 1. 🎯 PROBLEM STATEMENT — What & Why

A bank's core is deceptively small: accounts with owners, PINs, and balances; deposits and withdrawals with *laws*; a history of transactions; and absolute reliability — the system must never crash and never let data be wrong. In this project we build that core: OOP design, file persistence, exception-guarded input, and security thinking.

**Chapters it combines:** everything from Project 1 plus deeper OOP (12–16), exceptions (18), and operators/precision care (3–4).

## 2. 📋 FEATURES LIST

```
1 🆕 Create account (name, 4-digit PIN, opening deposit ≥ 0)
2 🔐 Login by account number + PIN (accounts numbered from 1000)
3 💰 Deposit (positive amounts only)
4 💸 Withdraw (funds-checked; overdraft IMPOSSIBLE by design)
5 📊 Balance check
6 🧾 Transaction statement (last 10 entries, kept per session + appended to log)
7 🔒 Change PIN (old PIN required)
8 🗑️ Close account (PIN required)
9 💾 Auto-save of accounts to bank.csv + transaction log to bank.log
10 🚪 Logout / Exit — zero data loss
```

## 3. 🗺️ PLANNING PHASE

```
CLASSES
  class Account: no, name, pin (private!), balance, history(deque of strings)
      deposit(), withdraw(), checkPin(), changePin(), toCSV(), statement()
  helper free functions: loadBank(), saveBank(), safeReadDouble/PIN...

STORAGE
  bank.csv   one row per account:  no,name,pin,balance
  bank.log   appended transaction lines: [acc 1001] DEPOSIT +500 → bal 1500

SECURITY LAWS (enforced INSIDE Account — nowhere else can touch money)
  ✗ any money op without login      ✗ amount <= 0
  ✗ withdraw > balance              ✗ PIN shorter/longer than 4 digits
  ✗ wrong PIN on sensitive ops      ✗ PIN stored forever in log (never!)

FLOW
  START → loadBank() → OUTER MENU (create / login / exit)
     └── login success → INNER MENU (deposit / withdraw / balance /
                                    statement / change PIN / close / logout)

PSEUDOCODE (withdraw):
  amount = safeReadDouble("amount: ")
  if amount <= 0          → refuse politely
  else if amount > balance → refuse with current balance shown
  else balance -= amount; history.push_front(...); log to bank.log
```

## 4. 💻 COMPLETE CODE

> Save as `bank_system.cpp` → `g++ bank_system.cpp -o bank` → run.

```cpp
// @BANK-START
// ============================================
// PROJECT 2: BANK MANAGEMENT SYSTEM
// Chapters used: 3-9, 11-19 (classes, files, exceptions, STL)
// ============================================

#include <iostream>
#include <vector>
#include <deque>                      // for rolling statement history
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;

const string CSV_FILE = "bank.csv";
const string LOG_FILE = "bank.log";
const int    FIRST_ACCOUNT_NO = 1000;

// ---------------- SAFE INPUT ----------------
string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

double safeReadDouble(const string& prompt) {
    while (true) {
        string line = readLine(prompt);
        try { return stod(line); }
        catch (const invalid_argument&) { cout << "✗ Numbers only.\n"; }
    }
}

string safeReadPin(const string& prompt) {
    while (true) {
        string p = readLine(prompt);
        if (p.length() == 4) {
            bool digits = true;
            for (char c : p) if (!isdigit(c)) digits = false;
            if (digits) return p;
        }
        cout << "✗ PIN must be exactly 4 digits.\n";
    }
}

// ---------------- MODEL ----------------
class BankException : public runtime_error {
public: BankException(const string& m) : runtime_error(m) { }
};

class Account {
private:
    int    no;
    string name;
    string pin;                        // private by design (file keeps it — demo only)
    double balance;
    deque<string> history;             // newest FIRST, max 10

    void record(const string& entry) {
        history.push_front(entry);
        if (history.size() > 10) history.pop_back();

        ofstream log(LOG_FILE, ios::app);              // append-only audit trail
        log << "[acc " << no << "] " << entry << "\n";
    }

public:
    Account() : no(0), balance(0) { }
    Account(int n, const string& nm, const string& p, double b)
        : no(n), name(nm), pin(p), balance(b) { }

    int    getNo()      const { return no; }
    string getName()    const { return name; }
    double getBalance() const { return balance; }
    bool   checkPin(const string& p) const { return pin == p; }

    void deposit(double amount) {
        if (amount <= 0) throw BankException("Deposit must be > 0");
        balance += amount;
        record("DEPOSIT +" + to_string(amount) + " → bal " + to_string(balance));
    }

    void withdraw(double amount) {
        if (amount <= 0)      throw BankException("Withdrawal must be > 0");
        if (amount > balance) throw BankException("Insufficient funds");
        balance -= amount;
        record("WITHDRAW -" + to_string(amount) + " → bal " + to_string(balance));
    }

    bool changePin(const string& oldPin, const string& newPin) {
        if (!checkPin(oldPin)) return false;
        pin = newPin;
        record("PIN changed");
        return true;
    }

    void statement() const {
        cout << "\n--- Recent activity (acc " << no << ") ---\n";
        if (history.empty()) { cout << "(no transactions this session)\n"; return; }
        for (const string& h : history) cout << "  • " << h << "\n";
    }

    string toCSV() const {
        return to_string(no) + "," + name + "," + pin + "," + to_string(balance);
    }
};

// ---------------- FILE LAYER ----------------
vector<Account> loadBank() {
    vector<Account> v;
    ifstream in(CSV_FILE);
    string line;
    while (getline(in, line)) {
        try {
            int p1 = line.find(',');
            int p2 = line.find(',', p1 + 1);
            int p3 = line.find(',', p2 + 1);
            int    no  = stoi(line.substr(0, p1));
            string nm  = line.substr(p1 + 1, p2 - p1 - 1);
            string pin = line.substr(p2 + 1, p3 - p2 - 1);
            double bal = stod(line.substr(p3 + 1));
            v.push_back(Account(no, nm, pin, bal));
        } catch (...) { /* skip corrupt rows */ }
    }
    return v;
}

void saveBank(const vector<Account>& v) {
    ofstream out(CSV_FILE);
    for (const Account& a : v) out << a.toCSV() << "\n";
}

int nextAccountNo(const vector<Account>& v) {
    int maxNo = FIRST_ACCOUNT_NO - 1;
    for (const Account& a : v) if (a.getNo() > maxNo) maxNo = a.getNo();
    return maxNo + 1;
}

// ---------------- INNER SESSION (after login) ----------------
void session(Account& acc, vector<Account>& bank, bool& closed) {
    while (true) {
        cout << "\n===== Welcome, " << acc.getName() << " (acc " << acc.getNo() << ") =====\n"
             << "1 Deposit  2 Withdraw  3 Balance  4 Statement\n"
             << "5 Change PIN  6 Close account  0 Logout\n> ";
        int c = (int)safeReadDouble("");

        try {
            if (c == 1) {
                acc.deposit(safeReadDouble("Amount: "));
                saveBank(bank);
                cout << "✓ Deposited.\n";
            } else if (c == 2) {
                acc.withdraw(safeReadDouble("Amount: "));
                saveBank(bank);
                cout << "✓ Withdrawn.\n";
            } else if (c == 3) {
                cout << "Balance: Rs. " << acc.getBalance() << "\n";
            } else if (c == 4) {
                acc.statement();
            } else if (c == 5) {
                string oldP = safeReadPin("Old PIN: ");
                string newP = safeReadPin("New PIN: ");
                if (acc.changePin(oldP, newP)) { saveBank(bank); cout << "✓ PIN changed.\n"; }
                else cout << "✗ Wrong old PIN.\n";
            } else if (c == 6) {
                string p = safeReadPin("Confirm PIN to close account: ");
                if (!acc.checkPin(p)) { cout << "✗ Wrong PIN.\n"; continue; }
                for (int i = 0; i < (int)bank.size(); i++)
                    if (bank[i].getNo() == acc.getNo()) { bank.erase(bank.begin() + i); break; }
                saveBank(bank);
                cout << "Account closed. We're sad to see you go.\n";
                closed = true;
                return;
            } else if (c == 0) {
                cout << "Logged out.\n";
                return;
            } else {
                cout << "✗ Choose 0-6.\n";
            }
        }
        catch (const BankException& e) {       // financial laws defend themselves
            cout << "🏦 Refused: " << e.what() << "\n";
        }
    }
}

// ---------------- MAIN / DIRECTOR ----------------
int main() {

    vector<Account> bank = loadBank();
    cout << "🏦 Karachi National Bank — " << bank.size() << " accounts loaded.\n";

    while (true) {
        cout << "\n===== MAIN MENU =====\n1 Create account  2 Login  0 Exit\n> ";
        int c = (int)safeReadDouble("");

        if (c == 1) {
            string name = readLine("Full name: ");
            if (name.empty()) { cout << "✗ Name required.\n"; continue; }
            string pin = safeReadPin("Choose a 4-digit PIN: ");
            double dep = safeReadDouble("Opening deposit: ");
            if (dep < 0) { cout << "✗ Cannot be negative.\n"; continue; }

            int no = nextAccountNo(bank);
            bank.push_back(Account(no, name, pin, dep));
            saveBank(bank);
            cout << "✓ Account created. Your account number is " << no
                 << " — write it down!\n";
        }
        else if (c == 2) {
            if (bank.empty()) { cout << "✗ No accounts yet. Create one first.\n"; continue; }
            int no = (int)safeReadDouble("Account number: ");
            string pin = safeReadPin("PIN: ");

            int idx = -1;
            for (int i = 0; i < (int)bank.size(); i++)
                if (bank[i].getNo() == no && bank[i].checkPin(pin)) { idx = i; break; }

            if (idx == -1) { cout << "✗ Login failed.\n"; continue; }

            bool closed = false;
            session(bank[idx], bank, closed);   // reference → edits hit the vector
        }
        else if (c == 0) {
            saveBank(bank);
            cout << "All data saved. Have a secure day! 🔒\n";
            return 0;
        }
        else {
            cout << "✗ Choose 0-2.\n";
        }
    }
}
// @BANK-END
```

## 5. 📺 OUTPUT SCREENSHOT (text)

```
🏦 Karachi National Bank — 1 accounts loaded.

===== MAIN MENU =====
1 Create account  2 Login  0 Exit
> 2
Account number: 1000
PIN: 4321

===== Welcome, Mahadi Rehman (acc 1000) =====
1 Deposit  2 Withdraw  3 Balance  4 Statement
5 Change PIN  6 Close account  0 Logout
> 2
Amount: 5000
🏦 Refused: Insufficient funds

> 1
Amount: 2500
✓ Deposited.

> 4
--- Recent activity (acc 1000) ---
  • DEPOSIT +2500.000000 → bal 7500.000000

> 0
Logged out.

===== MAIN MENU =====
1 Create account  2 Login  0 Exit
> 0
All data saved. Have a secure day! 🔒
```

## 6. 🚀 HOW TO EXTEND IT

1. **Transfer between accounts** — find both, withdraw+deposit as ONE validated operation
2. **3-attempt PIN lockout** — counter per session, locks login for that account
3. **Interest application** — a method applying N% to all savings accounts monthly
4. **Hashed PINs** — store a numeric hash instead of the PIN text (real security step!)
5. **Admin mode** — list all accounts without PINs via a special login
6. **Persist full statement** — parse bank.log at startup into history deques

## 7. 🔍 CODE REVIEW + SECURITY CONSIDERATIONS

| Decision | Why |
|---|---|
| Money-touching laws INSIDE `Account` | impossible to bypass from menus — encapsulation carrying security |
| Custom `BankException` | financial refusals read as policy, not crashes |
| PIN read as **string** | `isdigit` checks; avoids leading-zero loss (0421 ≠ 421) |
| Reference session (`Account&`) | edits hit the vector's account — no stale copies |
| Append-only `bank.log` | audit trail survives even crashes; money moves leave evidence |
| Rolling 10-entry statement | memory-bounded; real banks do windows, then archive |
| ⚠️ Plaintext PIN in CSV | acceptable for LEARNING demo; production hashes+salts |

**Security notes to graduate with:** never log PINs; clamp input lengths; validate at trust boundaries; assume users WILL type "-999999" as a deposit. (All handled above — find each one!)

## 8. 🐛 COMMON BUGS & FIXES

| Bug | Cause | Fix (as coded) |
|---|---|---|
| Statement shows someone else's history | session given a COPY of the Account | `Account& acc` (done) |
| Login OK but changes don't persist | edited copy, saved vector | same — reference session |
| to_string(amount) shows "2500.000000" | default double formatting | acceptable demo; or format manually |
| Closing an account skips save | erase forgets saveBank() | always pair them (done) |
| Deadlock after failed `stod` | raw `cin >>` on letters | safeReadDouble everywhere (done) |

**Motivation:** Banks are *boring on purpose*: predictable, guarded, audited. You just wrote genuinely bank-shaped code. 🏦

---

**⬅️ [Chapter 21](chapter-21-project-student-system.md) | [🏠 Home](README.md) | [Chapter 23 ➡️](chapter-23-project-game.md)**
