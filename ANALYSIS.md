# Assignment 6 — Hash Table Analysis

## Instructions

Complete all ten questions.

Each question is worth **1 point** for a total of **10 points**.

Partial credit may be awarded for answers that are incomplete but demonstrate correct understanding.

Your answers must be based on the **actual HashTable and LinkedList designs used in this assignment**, not generic definitions copied from another source.

Use your code, the supplied tests, and the Hash Table and Complexity lectures as references.

Answer directly below each question.

---

## 1. ADT Reuse and Loose Coupling — 1 point

In this assignment, your `HashTable` reuses the `LinkedList` ADT you built previously.

Explain why this demonstrates **code reuse** and **loose coupling**.

Your answer should explain why `HashTable` can use `LinkedList` without knowing anything about `Node`, `next`, `prev`, or the internal representation of the list.

### Answer



---

## 2. Does the HashTable Care How LinkedList Is Implemented? — 1 point

Your current `LinkedList` is an **ordered doubly linked list**.

Suppose it were replaced by a **singly linked list** that preserved the same public interface and behavior required by `HashTable`.

Would the `HashTable` implementation need to change?

Explain why or why not, and connect your answer to the distinction between **interface** and **implementation**.

### Answer



---

## 3. Expected and Worst-Case Complexity — 1 point

For this assignment, the table uses separate chaining.

Analyze the expected and worst-case time complexity of:

- `addEntry()`
- `getEntry()`
- `exists()`
- `deleteEntry()`

Explain what must be true about both the distribution of keys and the load factor for the expected performance to remain close to constant time, and explain what causes the worst case.

### Answer



---

## 4. Load Factor — 1 point

The load factor is:

\[
\alpha = \frac{n}{m}
\]

where `n` is the number of stored entries and `m` is the table capacity.

Explain what load factor tells us about a hash table.

Then explain why a load factor greater than `1.0` is legal in this assignment.

### Answer



---

## 5. Poor Hash Distribution — 1 point

Assume a table has capacity `10` and uses:

```cpp
id % capacity
```

as its hash/index calculation.

Suppose most inserted IDs end in the same digit.

Explain what happens to the distribution of entries, the collision chains, and the performance of lookup and deletion.

### Answer



---

## 6. Why Resizing Requires Rehashing — 1 point

Suppose a table with capacity `10` is resized to capacity `20`.

Explain why the existing bucket contents cannot simply be copied from the old table into the same bucket numbers in the new table.

Use the hash/index calculation in your explanation.

### Answer



---

## 7. Why This LinkedList Interface Makes Resizing Difficult — 1 point

The current `HashTable` interacts with `LinkedList` only through its public interface.

Explain why that makes automatic resizing and rehashing difficult with the current design.

What additional capability would the architecture need in order for `HashTable` to visit every stored `Data` record and insert it into a new table without exposing private `Node` objects?

### Answer



---

## 8. Is a Doubly Linked Ordered Bucket Necessary? — 1 point

Each collision chain in this assignment uses the ordered doubly linked list from the previous assignment.

Explain whether a hash-table bucket actually requires:

- ordered storage; and
- a `prev` pointer.

Discuss at least one cost and one possible benefit of reusing the existing `LinkedList` anyway.

### Answer



---

## 9. Complexity Analysis vs. Performance Analysis — 1 point

Two hash-table implementations may both have expected lookup complexity of `O(1)` but still perform differently in real programs.

Explain the difference between **complexity analysis** and **performance analysis / benchmarking** in this context.

Give at least two implementation or hardware factors that Big-O notation does not capture.

### Answer



---

## 10. What Your Two Student-Written Tests Demonstrate — 1 point

You were required to complete:

```cpp
testCollisionDeletion()
testHighLoadFactor()
```

Explain what each test is intended to demonstrate about hash-table behavior.

Your answer should explain why these are specifically **hash-table tests**, rather than merely generic ADT tests.

### Answer
