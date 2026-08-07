# Extra Practice — Chapter 22: Project 2 Extensions (Bank Management System)

> 🎯 **Bonus task list.** The full project + code lives in [chapter-22-project-bank-system.md](../chapter-22-project-bank-system.md).
> ⚠️ **No solutions here by design** — these extend YOUR build of Project 2. Working behavior IS your verification.
>
> 📌 Keep the Karachi National Bank vibe: receipts in Rs., polite refusals, full audit log for every money movement.

```
Task X22.1 ⭐
PIN lockout: 3 wrong PIN attempts at login → that account is
locked FOR THE SESSION; print a "visit your branch" message.
(Per-session only — no new file needed.)

Task X22.2 ⭐⭐
Transfer: one menu option asking for a target account number +
amount. Withdraw from one and deposit into the other as ONE
validated operation (target must exist, funds must suffice —
refuse BEFORE touching either balance). Both histories + log
must record it.

Task X22.3 ⭐⭐
Interest day: an option applying a fixed % (e.g. 5) to every
account balance, logged per account. Guard the precision —
print balances with 2 decimals afterwards (fixed/setprecision).

Task X22.4 ⭐⭐
Account numbers sorted in listAll: keep storage order as-is but
DISPLAY sorted. Use a vector of indices or pointers — do NOT
reorder the main vector.

Task X22.5 ⭐⭐⭐
Hashed PINs: store PIN % 99991 * 7 + 13 (or any tiny numeric
scramble you invent) in bank.csv instead of the raw PIN; login
hashes the typed PIN and compares. Old plaintext file row →
refuse it with a clear error. Explain in a comment why real
banks use one-way hashes you can't un-scramble.

Task X22.6 ⭐⭐⭐
Admin mode: account number 0 + master PIN opens a staff menu —
list ALL accounts with balances (no PINs shown!), plus a grand-
total "money held by the bank" line.

Task X22.7 ⭐⭐⭐
Persistent statements: on startup, parse bank.log back into each
account's history deque (cap 5). Statements must survive restart:
deposit, save, exit, relaunch, login → statement still shows it.

Task X22.8 ⭐⭐⭐
"The auditor": menu option replaying bank.log and verifying that
starting balance + all deposits − all withdrawals equals each
saved balance. Print ✅ or ❌ per account. (Corrupt the CSV by
hand once to see an ❌ — then fix it. That's a real audit!)
```

⬅️ [Back to Chapter 22](../chapter-22-project-bank-system.md)
