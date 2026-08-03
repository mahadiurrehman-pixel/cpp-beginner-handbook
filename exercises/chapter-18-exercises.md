# Extra Practice — Chapter 18: Exception Handling

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-18-exception-handling.md](../chapter-18-exception-handling.md).

```
Problem X18.1 ⭐
safePosSqrt guarded loop: keep asking until a valid non-negative
number is entered; print the root. (invalid_argument catch)

Problem X18.2 ⭐
Read an index and vector<int>.at(i) — NOT raw [] — catch the
out_of_range and print which valid range applies.

Problem X18.3 ⭐
stoi-with-retry pattern until user enters a 2-digit number
(10-99) — catch parse errors AND range errors separately.

Problem X18.4 ⭐⭐
divideArray(a[i]/b[i]) two parallel arrays with per-index try
blocks; print "row i: result" or "row i: skipped (reason)".

Problem X18.5 ⭐⭐
WithdrawFlow: custom trio of exceptions (BadAmount, Overdraft,
DailyLimitReached) all : runtime_error; run 5 scenarios in one
loop with distinct catch for each plus family fallback.

Problem X18.6 ⭐⭐
File reading chain: open settings via a func that throws
missing/corrupt/format variants of ONE custom exception type
(different .what() text) — main differentiates by message prefix.

Problem X18.7 ⭐⭐
Call-chain lab: f1→f2→f3→f4 where f4 throws 42 (int). Catch in
f2 with int-handler, then re-route: comment how it never reaches
main; then REMOVE f2's handler and confirm main's catch works.

Problem X18.8 ⭐⭐⭐
"Never-crash calculator" revisited: add full incident LOG output
(to exceptions.log, Ch. 17!) per catch, plus session summary with
counts of each incident type.

Problem X18.9 ⭐⭐⭐
Rethrow practice: inner function catches runtime_error, LOGS it,
then throw; (rethrow) — OUTER catches and presents user message.
Show both layers' messages in correct order.

Problem X18.10 ⭐⭐⭐
Robust config loader system: 3 files (display.txt, sound.txt,
controls.txt) each "key=value" rows; missing/corrupt files each
fallback to defaults with named warnings; final printout of the
merged effective settings with SRC markers (file vs default).
```

⬅️ [Back to Chapter 18](../chapter-18-exception-handling.md)
