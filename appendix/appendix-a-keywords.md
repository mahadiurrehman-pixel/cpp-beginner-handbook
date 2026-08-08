# APPENDIX A — ALL KEYWORDS IN C++

> Keywords are words C++ **owns** — you can never use them as variable/class names. This table groups them by job. Ones with a chapter number are covered in this book.

**⬅️ [Conclusion](../conclusion.md) | [🏠 Home](../README.md)**

---

## Data types & declarations

| Keyword | What it does | Chapter |
|---|---|---|
| `int`, `double`, `float`, `char`, `bool` | basic types | 3 |
| `void` | "no value" return type | 7 |
| `const` | locked values / read-only | 3 |
| `static` | class-shared / file-local storage | 16 |
| `auto` | compiler-deduced type | 3 |
| `unsigned`, `signed`, `short`, `long` | integer variants | — |
| `wchar_t`, `char8_t`, `char16_t`, `char32_t` | wide/unicode characters | — |
| `enum` | named constant lists | — |
| `typedef` | type alias (legacy) | — |
| `using` | namespace alias / type alias | 2 |
| `namespace` | named scopes | 2 |

## Flow control

| Keyword | What it does | Chapter |
|---|---|---|
| `if`, `else` | decisions | 5 |
| `switch`, `case`, `default` | multi-way branch | 5 |
| `for`, `while`, `do` | loops | 6 |
| `break`, `continue` | loop exits/skips | 6 |
| `goto` | jump to label (avoid!) | — |
| `return` | hand back result | 7 |

## Functions & memory

| Keyword | What it does | Chapter |
|---|---|---|
| `new`, `delete` | heap allocate / free | 10 |
| `this` | self-pointer inside methods | 12 |
| `sizeof` | byte size of type/expr | 3 |
| `inline` | hint: expand function at call sites | — |
| `template` | generic code (STL's engine) | 19 |
| `typename` | names a type inside templates | 19 |

## OOP

| Keyword | What it does | Chapter |
|---|---|---|
| `class` | define a class | 12 |
| `struct` | class with public default | 19 |
| `union` | overlapping storage fields | — |
| `public`, `private`, `protected` | access specifiers | 12, 14 |
| `virtual` | runtime polymorphic dispatch | 15 |
| `friend` | trusted-access grant | 16 |
| `operator` | operator overloading | 15 |
| `explicit` | blocks implicit conversions | — |
| `mutable` | field edible even on const objects | — |
| `constexpr` | compile-time constant expressions | — |
| `consteval`, `constinit` | stricter compile-time forms (C++20) | — |

## Exceptions

| Keyword | What it does | Chapter |
|---|---|---|
| `try`, `throw`, `catch` | exception machinery | 18 |
| `noexcept` | "this never throws" promise | — |

## Type inspection & casting

| Keyword | What it does | Chapter |
|---|---|---|
| `typeid` | runtime type info | — |
| `static_cast` | checked, normal cast | 3 (as `(double)x`) |
| `dynamic_cast` | safe downcast with RTTI | — |
| `const_cast` | strips const (rarely wise) | — |
| `reinterpret_cast` | raw bit reinterpretation (dangerous) | — |
| `decltype` | deduces declared type of expr | — |

## Threading & concurrency (advanced)

| Keyword | What it does |
|---|---|
| `thread_local` | per-thread fresh copies |
| `atomic_*` family | (in `<atomic>`) lock-free ops |

## Miscellaneous

| Keyword | What it does | Chapter |
|---|---|---|
| `true`, `false`, `nullptr` | boolean & null literals | 3, 10 |
| `export` | module export (C++20) | — |
| `extern` | "defined elsewhere" linkage | — |
| `register` | (removed in C++17 — museum piece) | — |
| `volatile` | memory-can-change-anytime marker | — |
| `asm` | embed assembly | — |
| `concept`, `requires` | constrained templates (C++20) | — |
| `co_await`, `co_yield`, `co_return` | coroutines (C++20) | — |

---

📌 **NOTE:** Total count varies by standard (C++11/14/17/20 add some). You only *needed* about 30 for this entire book — the rest wait in your future.

**[🏠 Home](../README.md) | [Appendix B ➡️](appendix-b-precedence.md)**
