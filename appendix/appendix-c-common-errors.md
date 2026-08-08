# APPENDIX C — COMMON ERROR MESSAGES & FIXES

> Method: read the FIRST error → find file:line → match it here → fix → recompile. (Chapter 0's rule never stops applying.)

**⬅️ [Appendix B](appendix-b-precedence.md) | [🏠 Home](../README.md) | [Appendix D ➡️](appendix-d-cheat-sheet.md)**

---

## Syntax & structure errors

| Compiler says | Real cause | Fix |
|---|---|---|
| `expected ';' before 'X'` | missing semicolon on the line ABOVE | find the `;`-less statement just before the reported line |
| `expected '}' at end of input` | unbalanced braces | count `{` vs `}`; VS Code match-highlighting |
| `expected primary-expression before '}'` | dangling/extra token before `}` (often `;` after `if(cond);`) | remove stray `;` or fix the block |
| `'cout' was not declared in this scope` | missing `#include <iostream>` or typo'd name | add include / fix spelling (case-sensitive!) |
| `'string' was not declared...` | missing `#include <string>` | add it |
| `stray '\226' in program` | smart quotes copied from Word/web | retype quotes with plain `"` |
| `invalid conversion from 'const char*' to 'char'` | `"A"` where `'A'` meant | single vs double quotes (Ch. 3) |
| `error: expected unqualified-id before ...` | rogue character/broken line above | inspect the line above for typos |

## Type & variable errors

| Compiler says | Cause | Fix |
|---|---|---|
| `assignment of read-only variable` | modifying a `const` | remove the modification, or un-const (Ch. 3) |
| `redeclaration of 'x'` | declared the same variable twice | drop the second type keyword (Ch. 3 mistake #6) |
| `conflicting declaration` | variable and function/name clash | rename one |
| `invalid operands of types 'double' and 'int' to binary 'operator%'` | `%` with floating types | `%` is integers-only (Ch. 4) |
| `narrowing conversion of 'double' to 'int'` | braces init `{ }` catches precision loss | use `=` instead or cast explicitly |
| `'x' is used uninitialized` | read before assign | give a default at birth (always!) |

## Function & class errors

| Compiler says | Cause | Fix |
|---|---|---|
| `'f' was not declared in this scope` | prototype missing; call before definition | add prototype above main (Ch. 7) |
| `too few arguments to function` | wrong argument count at call | match parameter list |
| `control reaches end of non-void function` | a path forgets `return` | ensure every path returns (Ch. 7 m#1) |
| `expected ';' after class definition` | the classic `class X {... }` | add `;` after the class's closing `}` |
| `'x' is private within this context` | accessing private member from outside | use the public getter/setter (Ch. 12) |
| `no default constructor` | you wrote a custom ctor; `X x;` has nowhere to go | re-add `X() {}` or provide args (Ch. 13) |
| `cannot declare variable to be of abstract type` | instantiating a class with `= 0` pure virtuals | instantiate a concrete child instead (Ch. 15) |
| `no matching function for call... (candidate expects...)` | overload resolution mismatch | check arg TYPES (int vs double vs string) |

## Linker errors (post-compile stage)

| Linker says | Cause | Fix |
|---|---|---|
| `undefined reference to 'main'` | no `main()`, typo'd `Main()`/`mian()` | exactly one lowercase `int main()` (Ch. 2) |
| `undefined reference to 'Class::staticMember'` | static member declared but never DEFINED | add `Type Class::member = value;` in a .cpp (Ch. 16) |
| `undefined reference to 'void X::f()'` | declared `f()` but never defined | write the definition or delete the declaration |
| `multiple definition of 'X'` | same body defined in two .cpp files | keep definition once; declarations in headers |

## Runtime disasters (program compiles but misbehaves)

| Symptom | Cause | Fix |
|---|---|---|
| Garbage values | uninitialized variables / array OOB | initialize; check index bounds (Ch. 8) |
| `Segmentation fault` | wild/dangling pointer deref | `nullptr` at birth; guard before use (Ch. 10) |
| Infinite loop | loop CHANGE missing / wrong condition | verify `i++`; inspect `<` vs `<=` (Ch. 6) |
| Program "skips" a getline | leftover `'\n'` from previous `cin >>` | `cin.ignore(10000, '\n');` (Ch. 9) |
| Math results wrong but no error | int division / precedence traps | make one side `double`; add `()` (Ch. 3/4) |
| `terminate called after throwing...` | thrown exception with NO catch | add matching catch (Ch. 18) |
| Stack overflow | recursion with no/incorrect base case | base case + progress (Ch. 7) |

---

💡 **PRO TIP:** New error? Copy its first line into a search engine in quotes — you're almost certainly not its first victim today. Reading error threads is a real developer skill; welcome to it.

**[🏠 Home](../README.md) | [Appendix D ➡️](appendix-d-cheat-sheet.md)**
