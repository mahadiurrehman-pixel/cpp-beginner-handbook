# Extra Practice — Chapter 15: Polymorphism

> 🎯 **Bonus problem set.** Chapter problems + solutions live in [chapter-15-polymorphism.md](../chapter-15-polymorphism.md).

```
Problem X15.1 ⭐
Overload demo(): int → prints value², double → √ via <cmath>,
string → its reverse. Call with one of each.

Problem X15.2 ⭐
class CelsiusTemp with operator+ adding two temps AND operator>
comparing; demo results with prints.

Problem X15.3 ⭐
Abstract Base64-ish Codec: pure virtual encode()/decode() =
build Rot13 (shift 13, self-inverse) fulfilling the contract for
strings; show both directions.

Problem X15.4 ⭐⭐
Abstract Alert pure virtual trigger()=0; children EmailAlert,
SMSAlert, SirenAlert with distinctive messages; panic(Alert&) calls
trigger through the interface for all 3 via one function.

Problem X15.5 ⭐⭐
Abstract Vehicle with virtual fuelCostPer100km() = 0 and virtual
tank() = 0; Car and Motorcycle implement; print cost for entered
km for any vehicle via base pointer. (fuel price as a parameter.)

Problem X15.6 ⭐⭐
class Vision2D revisited: add operator- and operator* (scalar
double each coordinate); verify with prints: v1+v2, v1-v2, v1*2.5.

Problem X15.7 ⭐⭐
Abstract Printer pure virtual print(doc)=0; PDFPrinter and
USBPrinter implement; Queue program: loop reading doc names, send
through a Printer* chosen by user option, both interleaved.

Problem X15.8 ⭐⭐⭐
Deliberate slicing experiment: assign a Kid object to a Base VALUE
then call virtual(); then bind Base& and call again. Both outputs +
commented explanation of slicing.

Problem X15.9 ⭐⭐⭐
Abstract Task with pure virtuals estimateHours(), execute(); three
children (EmailTask, BuildTask, TestTask); a day planner function
accepting Task& printing both; then a hybrid multifunction print.

Problem X15.10 ⭐⭐⭐
Mini-plugin hall: abstract Character (attack, defend) + 4 heroes
with distinct numbers; a Boss HP 400; polymorphic loop turns each
hero to hit until boss falls; log every hit (name+damage+HP-left).
(Extension of Problem 15.10 with defend used to negate 20%.
Bonus: virtual dtor proven via log.)
```

⬅️ [Back to Chapter 15](../chapter-15-polymorphism.md)
