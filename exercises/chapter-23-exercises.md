# Extra Practice — Chapter 23: Project 3 Extensions (Number Hunter Game)

> 🎯 **Bonus task list.** The full project + code lives in [chapter-23-project-game.md](../chapter-23-project-game.md).
> ⚠️ **No solutions here by design** — these extend YOUR build of Project 3. Working behavior IS your verification.
>
> 📌 This is the last file of bonus tasks in the book. Finish even one and you've out-built the syllabus. 🏆

```
Task X23.1 ⭐
Personal Hall of Fame: ask the player's name once at startup;
every high-score entry records name + attempts + difficulty
(then Mahadi can finally beat "Player" fair and square).

Task X23.2 ⭐
Round timer: time(0) at round start and win; print seconds taken
with the victory message.

Task X23.3 ⭐⭐
Difficulty filter in Hall of Fame: menu asks which difficulty to
show (or ALL), and only lists entries from saved rows matching
it (needs Task X23.1's extra column or your own scheme — design
the CSV row yourself and keep old rows loading!).

Task X23.4 ⭐⭐
Two-player mode: Player 1 secretly types the secret number
(cin, then print 30 blank lines as a poor-man's screen clear 😄),
Player 2 hunts it. Attempts still counted; bragging rights logged.

Task X23.5 ⭐⭐
Hot/Cold hints: alongside higher/lower, print "🔥 very close"
when |guess − secret| ≤ 5 and "🧊 freezing" when ≥ 40% of the
range away. Tune thresholds so they feel fair on every difficulty.

Task X23.6 ⭐⭐⭐
Hunter-hard mode (the famous one): the COMPUTER guesses YOUR
number with binary search. You answer h/l/c; it halves the range
each turn (Ch. 20's exact loop). Print its guess count... then
compare with the human average in the Hall of Fame. Who wins?

Task X23.7 ⭐⭐⭐
Lives campaign: a session is 5 rounds; losing a round (out of
attempts) costs a life; 3 lives total. Campaign score = rounds
won × 100 − total attempts × 10. Save campaign bests to a new
file campaign.csv — without breaking highscores.csv.

Task X23.8 ⭐⭐⭐
Treasure grid (graduation task): 10×10 hidden grid; player enters
row/col guesses; hint = Manhattan distance ("warmer/colder" vs.
previous guess). Reuse: nested loops (Ch. 6), functions (Ch. 7),
rand (this chapter), save best moves to file (Ch. 17). You now
hold every tool needed — go build it.
```

⬅️ [Back to Chapter 23](../chapter-23-project-game.md)
