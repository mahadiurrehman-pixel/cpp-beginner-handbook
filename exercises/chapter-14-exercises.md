# Extra Practice — Chapter 14: Inheritance

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-14-inheritance.md](../chapter-14-inheritance.md).

```
Problem X14.1 ⭐
Base UIElement (label member via protected ctor); child Button
adds click(); child Panel adds open(). Both print acting labels.

Problem X14.2 ⭐
Base Person(int age) → Teenager(overrides canDrive() false→
unless age>=18 w/ license flag). Show ctor chain order in prints.

Problem X14.3 ⭐
Chain: Entity → Enemy → BossEnemy, each ctor prints its birth;
add bossRage() only in child. One object; 3 messages; explain.

Problem X14.4 ⭐⭐
Base Account (balance, deposit()); child HighYield adds
depositWithBonus() = parent logic ×1.02 — calling parent's deposit
inside (bonus: explain why protected matters here).

Problem X14.5 ⭐⭐
Base Shape2D (name); children Square(side) and Circle(r) each
override describe() printing name + area. Make a tiny array of
BASE objects? (comment why values won't polymorph — Ch. 15 awaits!)

Problem X14.6 ⭐⭐
Base Media (title); Song(title,artist) and Podcast(title,host),
both with play() printing formatted labels + Media's title via
protected access. Demo 2 of each.

Problem X14.7 ⭐⭐
Override-hunt file: Base.show() not virtual; Child.show() hides;
call via Child obj AND via Base REFERENCE binding & compare —
document the difference in a comment (bridge to Ch. 15!).

Problem X14.8 ⭐⭐⭐
Multiple inheritance: Phone (call()) + WebBrowser (browse()) →
SmartDevice (assistant()); plus status() composing both parents'
info() explicitly. Name-clash demonstrated & resolved.

Problem X14.9 ⭐⭐⭐
Payroll suite: Employee(virtual-less pay) → HourlyEmp(rate×hrs)
and SalariedEmp(fixed + 25% bonus via override using base getter);
print both pays through non-virtual BASE references and explain
the “wrong” result vs what Ch. 15 fixed.

Problem X14.10 ⭐⭐⭐
Build GuardBuilder: base Guard protected domain member + ctor;
child TerrainGuard(domain) overrides inspect() printing
"scanning <domain>" + Guard::inspect() inside; deep chain with a
CastleGuard level-3 override and full ctor message trace.
```

⬅️ [Back to Chapter 14](../chapter-14-inheritance.md)
