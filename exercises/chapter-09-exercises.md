# Extra Practice — Chapter 9: Strings

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-09-strings.md](../chapter-09-strings.md).

```
Problem X9.1 ⭐
Read a word; print the MIDDLE character(s): odd length → 1 char,
even → 2 chars.  "apple" → p,   "code" → od.

Problem X9.2 ⭐
Swap case of every letter in a sentence: "HeLLo" → "hEllO".

Problem X9.3 ⭐
Remove ALL digits from a string: "a1b2c3" → "abc" (build result).

Problem X9.4 ⭐⭐
Run-length compression: "aaabcccc" → "a3b1c4". Read one word.
(Tip: count repeats of the current char, flush on change.)

Problem X9.5 ⭐⭐
Check if two words are anagrams (same letters, any order):
"listen"/"silent" → true. (Hint: sort COPIES of both, compare.)

Problem X9.6 ⭐⭐
Rotate word by k: "abcdef" k=2 → "cdefab" (use substr twice).

Problem X9.7 ⭐⭐
Check palindrome IGNORING spaces & case: "Never Odd Or Even" → true
(build a cleaned copy first).

Problem X9.8 ⭐⭐⭐
Longest word in a sentence (getline): print the word and its length.
"The quick brown fox" → quick, 5.

Problem X9.9 ⭐⭐⭐
Simple Caesar cipher: shift each letter by +3 within alphabet
('x'→'a'), leaving other chars as-is. Then decode it back.
(Hint: (c - 'a' + 3) % 26 + 'a')

Problem X9.10 ⭐⭐⭐
Expression splitter: read "12+34-5" and print the three parts on
separate lines WITHOUT stoi: tokens cut at + and -.
(Tip: split via find ops; then bonus—compute the full value with
cascading ifs, challenges X19.* later welcome.)
```

⬅️ [Back to Chapter 9](../chapter-09-strings.md)
