# Extra Practice — Chapter 10: Pointers & Memory

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-10-pointers.md](../chapter-10-pointers.md).

```
Problem X10.1 ⭐
Print the addresses of 3 locals; then of 3 array elements —
explain (comment) the GAP pattern between the array ones.

Problem X10.2 ⭐
Using only pointer write (*p = ...), fill a 5-array with evens
2,4,6,8,10 then print backward via index.

Problem X10.3 ⭐
Function void neg(int* p): flips the sign of caller's int.
Also write the reference version; call both on the same variable.

Problem X10.4 ⭐⭐
Write countEvens(int* a, int n) that scans via p++ ONLY (no [i])
and returns the count. Test with 3 arrays.

Problem X10.5 ⭐⭐
Read N scores to a dynamic array; remove ALL below-40 scores
by compacting IN PLACE (write index w), print remaining list
with the new count. Free memory properly.

Problem X10.6 ⭐⭐
Write findMinMax(int* a, int n, int& mn, int& mx) walking a
pointer; set BOTH outputs in one pass.

Problem X10.7 ⭐⭐
Two ways to swap values via TWO pointers: void ps(int* x, int* y)
that swaps the VALUES, and one that swaps the POINTERS' targets
(comment why the latter can't persist to caller — scope!).

Problem X10.8 ⭐⭐⭐
Implement your own strcat: void mycat(char* dest, const char* src)
walking to the '\0' of dest then copying src incl. its '\0'.
Test on "hello"+"world".

Problem X10.9 ⭐⭐⭐
Dynamic 2-D array R×C: allocate int*[R] rows of new int[C],
fill with R*C counting order (1..), print as a grid, then
delete each row then the row-pointer array. VERIFY order of
deletes in a comment.

Problem X10.10 ⭐⭐⭐
Build grow-on-demand vector-like behavior MANUALLY: start with
capacity 2; each time full, allocate double-sized new array,
copy, delete old, keep going. Push 10 values proving growth logs:
"cap 2→4→8→16". Then free.
```

⬅️ [Back to Chapter 10](../chapter-10-pointers.md)
