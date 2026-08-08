# APPENDIX B — OPERATOR PRECEDENCE TABLE

> Higher in the table = evaluated FIRST. When in doubt: **use parentheses** — clarity is free.

**⬅️ [Appendix A](appendix-a-keywords.md) | [🏠 Home](../README.md) | [Appendix C ➡️](appendix-c-common-errors.md)**

| Level | Category | Operators | Associates |
|---|---|---|---|
| 1 | Scope, postfix primary | `::` `a++` `a--` `()` (call) `[]` `.` `->` `type()` | left→right |
| 2 | Prefix unary | `++a` `--a` `-a` `+a` `!` `~` `*` (deref) `&` (addr) `sizeof` `new` `delete` | right→left |
| 3 | Pointer-to-member | `.*` `->*` | left |
| 4 | Multiplicative | `*` `/` `%` | left |
| 5 | Additive | `+` `-` | left |
| 6 | Shifts | `<<` `>>` | left |
| 7 | Relational | `<` `<=` `>` `>=` | left |
| 8 | Equality | `==` `!=` | left |
| 9 | Bitwise AND | `&` | left |
| 10 | Bitwise XOR | `^` | left |
| 11 | Bitwise OR | `\|` | left |
| 12 | Logical AND | `&&` | left |
| 13 | Logical OR | `\|\|` | left |
| 14 | Ternary | `?:` | right |
| 15 | Assignment | `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `\|=` `^=` | right |
| 16 | Comma | `,` | left |

### The 5 gotchas that bite beginners:

```cpp
2 + 3 * 4          // 14, not 20        (* beats +)              → Chapter 4
a > b || c < d && e // && eats before || → (a>b) || ((c<d) && e)
x = y == 5        // y==5 first! x gets a BOOL                   → Chapter 4
*ptr++            // means *(ptr++) — move the pointer, then deref the OLD spot
5 > 3 == true     // (5>3) first = true, then true == true ✓    (compares left→right BUT as a chain)
```

**The golden rule:** `()` always wins. `makeIntent(obvious)`.

**[🏠 Home](../README.md) | [Appendix C ➡️](appendix-c-common-errors.md)**
