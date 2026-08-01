# Extra Practice — Chapter 16: Friend Functions & Static Members

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-16-friend-static.md](../chapter-16-friend-static.md).

```
Problem X16.1 ⭐
class Vault2 (private code). friend unlock(Vault2) prints code;
main attempts direct access in a comment showing the error.

Problem X16.2 ⭐
class Circle2D with friend operator<< printing "Circle(r=3.0)";
chain-print three circles with arrows between them.

Problem X16.3 ⭐
class Ticket: static int issued; ctor increments. 5 tickets,
print getIssued at every step — including BEFORE any object exists.

Problem X16.4 ⭐⭐
class Lab (samples private) + friend class Inspector with
log(Lab&) and sanitize(Lab&) — show clean audit printout.

Problem X16.5 ⭐⭐
class Basket: static double taxRate shared across instances with
static setRate and per-object totalWithTax(items sum); rate change
once — show all baskets update.

Problem X16.6 ⭐⭐
Date utilities: static-only class DateTools with isLeap(y),
daysInMonth(m,y), isValid(d,m,y) combos. Print a validation table.

Problem X16.7 ⭐⭐
friend compare on two DIFFERENT classes: CircleArea vs SquareArea
(largerOf(C,S) prints the bigger shape's name). Explain in comment
why friend, not member.

Problem X16.8 ⭐⭐⭐
class Config singleton: theme, volume, getInstance(); show two
"modules" (functions) seeing one shared config, with copy blocking
demonstrated via commented line.

Problem X16.9 ⭐⭐⭐
class QueueCaps: static sharedLimits with static totalIn+
totalOut across MULTIPLE queue objects; show net flows consistent
after several enq/deq calls from two queue instances.

Problem X16.10 ⭐⭐⭐
class Parcel: static nextTracking id + alive current count;
friend operator<< shows "PK-0007"; die-by-scope tests; final
stats call with zero living parcels.
```

⬅️ [Back to Chapter 16](../chapter-16-friend-static.md)
