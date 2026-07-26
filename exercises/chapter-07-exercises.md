# Extra Practice — Chapter 7: Functions

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-07-functions.md](../chapter-07-functions.md).
> ⚠️ **No solutions here by design** — but unit-test every function in main like the chapter does.

```
Problem X7.1 ⭐
Write void printHeader(string title) that prints the title
wrapped in ===== lines. Use it 3 times with different titles.

Problem X7.2 ⭐
Write double rectangleArea(double l, double w) and use it to
compare two rooms: print which room number is bigger (1 or 2).

Problem X7.3 ⭐
Write bool isLeap(int year) (Ch.5 logic as a function). Print
leap years from 2020 to 2040 by calling it in a loop.

Problem X7.4 ⭐⭐
Write int absolute(int n) WITHOUT if (use a ternary) — then
version 2 using multiply-by-sign logic. Compare.

Problem X7.5 ⭐⭐
Write double average(int a, int b, int c) — be careful the
result is NOT integer-chopped. Then an OVERLOADED
double average(double a, double b). Call both.

Problem X7.6 ⭐⭐
Write int countDigits(int n) recursively. (Hint: n<10 → 1;
else 1 + countDigits(n/10).) Also make the loop version and
verify answers match for 8 test values.

Problem X7.7 ⭐⭐
Write bool isArmstrong(int n) reusing a helper
long long power(int,int) — 3-digit numbers only. Print all
Armstrong numbers from 100 to 999.

Problem X7.8 ⭐⭐⭐
Write int fib(int n) — the nth Fibonacci number RECURSIVELY.
Then run it for n=35 and time it (feel the slowness!). Add a
comment explaining why pure recursion is slow here, and write
the loop version to see the difference.

Problem X7.9 ⭐⭐⭐
Overloaded min(): 2 ints, 3 ints, and 2 doubles. Plus a
default-parameter function clamp(int v, int lo=0, int hi=100)
that forces v into [lo,hi] using your mins/maxes.

Problem X7.10 ⭐⭐⭐
"Bank v2 with functions": deposit(balance, amount),
withdraw(balance, amount), showMenu(), validatePin(attempt).
Design decision (comment it!): should these return the NEW
balance or modify via reference? Try the return version now.
```

💡 **Stuck?** X7.10 is a preview of the Chapter 22 Bank Project — solve it well and the project is 60% done.

⬅️ [Back to Chapter 7](../chapter-07-functions.md)
