# Extra Practice — Chapter 5: Conditional Statements

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-05-conditions.md](../chapter-05-conditions.md).
> ⚠️ **No solutions here by design** — test every branch with different inputs.

```
Problem X5.1 ⭐
Read a temperature (°C). Print "Freezing" (<=0), "Cold" (1-15),
"Pleasant" (16-30), or "Hot" (>30).

Problem X5.2 ⭐
Read 1-12 and print the month name (switch). Test Jan, Jun, Dec,
and 13.

Problem X5.3 ⭐
Read a character; classify as "Uppercase", "Lowercase", "Digit",
or "Other symbol" using ASCII ranges ('A'..'Z' etc.).

Problem X5.4 ⭐⭐
Read 3 angles; print whether they form a valid triangle
(sum == 180 AND each > 0), and if valid, whether it's acute,
right, or obtuse (any angle == 90, any > 90, or all < 90).

Problem X5.5 ⭐⭐
Login v1: username "admin" & password 1234 → "Welcome, admin"
Correct user wrong pass → "Wrong password"
Else → "Unknown user"    (string + int; mind the order of checks)

Problem X5.6 ⭐⭐
Parking fee: first 2 hours Rs.50, hours 3-5 add Rs.20/hr,
beyond 5 add Rs.10/hr for THOSE hours. Read hours, print fee.
(hours=7 → 50 + 3*20 + 2*10 = 130)

Problem X5.7 ⭐⭐
Read a 4-digit number; print "Lucky" if digit1+digit4 equals
digit2+digit3 (e.g. 1221: 1+1 == 2+2). Pure digit math + if.

Problem X5.8 ⭐⭐⭐
Chess color: read a square like column(1-8) row(1-8). Print
"Black" or "White". Rule: (col+row) even → Black, odd → White.
Then ALSO solve it with a ternary.

Problem X5.9 ⭐⭐⭐
Evaluate a mini expression menu: read a, b, and op like the
chapter's calculator BUT support '%' too, reject it when any
operand is 0, and use a nested default message distinguishing
"unknown operator" from "invalid operands".

Problem X5.10 ⭐⭐⭐
Zodiac-lite: read birth day & month; if month==3 && day>=21 ||
month==4 && day<=19 print "Aries". Add Taurus (Apr 20–May 20)
and Gemini (May 21–Jun 20) at minimum; "Unknown" otherwise.
```

💡 **Stuck?** Date-range logic = (month boundary checks) joined with `&&` inside `||` chains. Example X5.10 is the mother of that skill.

⬅️ [Back to Chapter 5](../chapter-05-conditions.md)
