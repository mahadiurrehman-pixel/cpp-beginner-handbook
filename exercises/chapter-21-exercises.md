# Extra Practice — Chapter 21: Project 1 Extensions (Student Management System)

> 🎯 **Bonus task list.** The full project + code lives in [chapter-21-project-student-system.md](../chapter-21-project-student-system.md).
> ⚠️ **No solutions here by design** — these extend YOUR build of Project 1. Working behavior IS your verification.
>
> 📌 Pick any tasks you like — each one is independent unless it says otherwise. Star ratings assume the base project is done.

```
Task X21.1 ⭐
Add menu option "Search by name substring": read a query string,
print every student whose name contains it (name.find(q) != npos).
Case-sensitive is fine for one star.

Task X21.2 ⭐ → ⭐⭐
Honors report: menu option writing "honors.txt" listing only
students with marks ≥ 85. ⭐⭐ version: sort the report by marks
descending before writing.

Task X21.3 ⭐⭐
Multiple subjects: change marks to vector<int> of size 3
(Urdu, Math, CS — or your pick). avg() drives grade(); add/edit/
list/stats must ALL still work, and the CSV gains 2 columns.

Task X21.4 ⭐⭐
Undo delete: push the deleted Student onto a stack<Student>
before erasing; menu option "Undo last delete" pops it back.
Confirm it survives a save/load cycle correctly.

Task X21.5 ⭐⭐
Attendance field: percent double, validated 0–100, added to the
CSV row (load must tolerate OLD 3-column files — hint: default
to 100 when a row parses short).

Task X21.6 ⭐⭐⭐
Login screen: before the menu appears, prompt for a 4-digit PIN
stored on the FIRST line of students.csv (shift it out of the
student rows). 3 wrong attempts → program exits politely.

Task X21.7 ⭐⭐⭐
Class ranking: assign each student a rank (1 = highest marks)
computed fresh after every load/add/edit, shown in listAll as a
properly aligned new column. Ties share a rank.

Task X21.8 ⭐⭐⭐
Full validation audit: hunt EVERY cin in the project; make each
one survive letter input, blank input, and out-of-range numbers
without crashing or looping forever (Ch. 18 techniques).
```

⬅️ [Back to Chapter 21](../chapter-21-project-student-system.md)
