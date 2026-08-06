# Extra Practice — Chapter 20: Basic Data Structures

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-20-data-structures.md](../chapter-20-data-structures.md).
> ⚠️ **No solutions here by design** — correct output on every sample input IS your verification.

```
Problem X20.1 ⭐
Bubble sort DESCENDING with a printed pass-count. Verify the
"already sorted" early-exit flag stops it at pass 1.

Problem X20.2 ⭐
Linear search that returns ALL positions of a target (not just
the first). Print "not found" for an absent value.

Problem X20.3 ⭐
Singly linked list: pushFront, pushBack, display. Build
5 → 2 → 9 and print it as "5 -> 2 -> 9 -> NULL".

Problem X20.4 ⭐⭐
Binary search on a sorted array of 10 ints; also print how many
COMPARISONS it took. Compare that number against linear search.

Problem X20.5 ⭐⭐
Stack (array-based, from scratch — no STL): push, pop, top, isEmpty.
Handle pop-on-empty gracefully with a message, not a crash.

Problem X20.6 ⭐⭐
Queue as a railway ticketing line: enqueue 6 named passengers,
serve (dequeue) 2, show front + remaining line, refuse a 7th
when capacity is 6.

Problem X20.7 ⭐⭐
Selection sort WITH tracing: print the array after every swap.
Feed it {64, 25, 12, 22, 11} and count total swaps (should be 4).

Problem X20.8 ⭐⭐⭐
Linked list deleteByValue + findMiddle (slow/fast pointer trick).
Test: delete head, delete tail, delete missing value, list of 1.

Problem X20.9 ⭐⭐⭐
Circular queue (array, fixed size 5): the wrap-around kind with
front/rear indices. Enqueue-dequeue interleaved 12 times; prove
slots get reused without overflow.

Problem X20.10 ⭐⭐⭐
Big-O detective: time bubble sort vs. binary search prep +
binary search on N = 1,000 / 10,000 / 100,000 random ints using
time(0) or <chrono>. Print a small table and state each Big-O
in one comment line. Watch bubble fall apart live. 😅
```

⬅️ [Back to Chapter 20](../chapter-20-data-structures.md)
