# Assignment 6 — Hash Tables

## Overview

In the previous Linked List assignment, you built a reusable `LinkedList` ADT.

In this assignment, you will **reuse that ADT as a component inside a larger ADT**: a fixed-capacity hash table that uses **separate chaining** for collision resolution.

This is an important software engineering step.

You are no longer building an isolated data structure. You are composing one ADT from another and relying on a previously established public interface instead of reaching into another class's implementation.

Your `HashTable` must use `LinkedList` only through its **public interface**.

You must not access or expose `LinkedList::Node`, `head`, `next`, `prev`, or any other private implementation detail.

---

## Backgound
 - Notes in the Notes folder, Part I and II
 - Lectures in the lectures folder, Hash Tables, Part I and part II

---

## Files You Will Use

The starter repository provides:

- `main.cpp`
- `main.h`
- `test.cpp`
- `test.h`
- `ANALYSIS.md`
- `ASSIGNMENT.md`

You must add your own files from the previous Linked List assignment:

- `data.h`
- `linkedlist.h`
- `linkedlist.cpp`

You must create:

- `hashtable.h`
- `hashtable.cpp`
- `README.md`
- `.gitignore`

Your previous `LinkedList` implementation will **not be regraded** in this assignment. It only needs to work correctly enough to support the `HashTable`.

You may repair defects in your previous `LinkedList` implementation if necessary.

Do **not** change the existing public interface of `LinkedList`, and do not add public methods merely to make this assignment easier. **Your public linked list contract must remain as specified in that assignment**.

If your previous Linked List assignment is not usable, an instructor-supplied reference version will be available so that problems in the previous assignment do not prevent you from completing this one. If you need that solution, send an email and request it.

---

## Important: This Project Will Not Compile at First

The starter repository is intentionally incomplete.

That is not an error.

Before implementing the hash table algorithms, your first milestone should be:

1. inspect the supplied files;
2. copy your previous `data.h`, `linkedlist.h`, and `linkedlist.cpp` into the repository;
3. create `hashtable.h` and `hashtable.cpp`;
4. create the required class declaration and method stubs;
5. compile the entire project successfully;
6. **only then begin implementing and testing the actual behavior**.

Continue using the interface-first development process practiced in previous assignments. This will be part of your grade and your commits will be inspected to ensure you proceeded interface first.

---

# HashTable Design

## Required Public Interface

Your `HashTable` class must provide **exactly** the following public interface:

```cpp
HashTable(int = 17);
~HashTable();

bool getEntry(int, Data&) const;
bool exists(int) const;
int getCount() const;
int getCapacity() const;
double getLoadFactor() const;
bool isEmpty() const;

bool addEntry(int, std::string&);
bool deleteEntry(int);
void clearTable();

void printTable() const;
```

### No Other Public Methods

Do not add additional public methods.

Private helper methods are allowed if they improve your design, but they must not expose the internal representation of either `HashTable` or `LinkedList`.

---

## Required Internal Representation

Your `HashTable` must use a dynamically allocated array of `LinkedList` objects.

Conceptually:

```text
HashTable
    |
    +-- table[0] -> LinkedList
    +-- table[1] -> LinkedList
    +-- table[2] -> LinkedList
    ...
    +-- table[capacity - 1] -> LinkedList
```

The class must contain these three persistent attributes:

```cpp
LinkedList* table;
int capacity;
int count;
```

Do not add:

- arrays of `Data`;
- STL containers;
- direct access to `LinkedList::Node`;
- pointers to individual LinkedList Nodes;
- additional persistent state.

The required private hash method is:

```cpp
int hash(int) const;
```

---

# Construction and Ownership

## Constructor

The constructor accepts the desired number of buckets:

```cpp
HashTable(int = 17);
```

The default capacity is `17`.

If the requested capacity is less than `1`, use the default capacity of `17`.

The constructor must dynamically allocate the bucket array:

```cpp
table = new LinkedList[capacity];
```

and initialize the table count to zero.

---

## Destructor

The `HashTable` owns the dynamically allocated array of `LinkedList` objects.

The destructor must release that array correctly.

Remember that each `LinkedList` owns its own dynamically allocated Nodes. The `HashTable` must not manually delete those Nodes.

The ownership relationship is:

```text
HashTable
    owns the LinkedList array

LinkedList
    owns its Nodes

Node
    contains its Data
```

---

# Hashing

This assignment uses a deliberately simple hash/index calculation:

```cpp
id % capacity
```

For example, with capacity `10`:

```text
1  -> bucket 1
11 -> bucket 1
21 -> bucket 1
31 -> bucket 1
```

These entries collide and must coexist in the same bucket through separate chaining.

The `hash()` method assumes it receives a valid positive ID.

---

# Required Behavior

## Data Rules

The same basic record rules from the previous Linked List assignment still apply:

- IDs must be positive.
- IDs must be unique.
- information must not be empty.
- failed operations must not corrupt or unnecessarily change the table.
- `getEntry()` must modify the caller-owned `Data` object only when the requested entry is found.

Because the same ID always hashes to the same bucket, duplicate detection does **not** require searching every bucket.

---

## `addEntry()`

```cpp
bool addEntry(int, std::string&);
```

A successful insertion must:

1. determine the correct bucket using `hash()`;
2. delegate storage to that bucket's `LinkedList`;
3. increment the table-level `count`.

Return `false` when:

- the ID is invalid;
- information is empty;
- the ID already exists.

Do not increment `count` when insertion fails.

---

## `deleteEntry()`

```cpp
bool deleteEntry(int);
```

Determine the correct bucket using the hash function and delegate deletion to that bucket's `LinkedList`.

Return `true` only when an entry is actually deleted.

Decrement `count` only when deletion succeeds.

---

## `getEntry()`

```cpp
bool getEntry(int, Data&) const;
```

Hash to the correct bucket and use the public `LinkedList` interface to retrieve the record.

The caller's `Data` object must remain unchanged when the requested ID is not found.

---

## `exists()`

```cpp
bool exists(int) const;
```

Hash to the correct bucket and search only that bucket.

Do not search every bucket in the table.

---

## `getCount()`

```cpp
int getCount() const;
```

Return the stored number of entries in the hash table.

Do not calculate the table count by traversing all buckets.

---

## `getCapacity()`

```cpp
int getCapacity() const;
```

Return the number of buckets in the table.

The capacity does not change during the lifetime of the object in this assignment.

---

## `getLoadFactor()`

```cpp
double getLoadFactor() const;
```

The load factor is:

\[
\alpha = \frac{n}{m}
\]

where:

- `n` is the number of stored entries;
- `m` is the table capacity.

Use floating-point division.

Because this assignment uses separate chaining, a load factor greater than `1.0` is valid.

---

## `isEmpty()`

```cpp
bool isEmpty() const;
```

Determine whether the table is empty using the stored table-level count.

Do not scan all buckets.

---

## `clearTable()`

```cpp
void clearTable();
```

Clear every bucket using the public `LinkedList` interface.

After clearing:

- `count` must be `0`;
- `capacity` must remain unchanged;
- the same `HashTable` object must be reusable.

---

## `printTable()`

```cpp
void printTable() const;
```

Print each bucket number and delegate the contents of that bucket to the `LinkedList` printing method.

`HashTable` must not traverse LinkedList Nodes directly.

This method is for visual inspection and does not replace automated testing.

---

# What You Are Not Implementing

This assignment uses a deliberately limited hash-table design.

You are **not** implementing:

- automatic resizing;
- rehashing;
- open addressing;
- linear probing;
- quadratic probing;
- double hashing;
- tombstones;
- custom hash-function design;
- STL containers.

These topics are still important and are addressed in the lectures and `ANALYSIS.md`, but they are not required implementation features in this assignment.

---

# Testing

Note there are **no autograding tests** since testing is part of the assignment.

The starter repository includes a supplied testing architecture and a substantial set of completed tests.

You are not being asked to redesign the testing system.

The supplied test module already tests:

- construction;
- initial state;
- normal insertion and retrieval;
- deliberate collisions;
- invalid and duplicate operations;
- clear and reuse;
- deterministic scaled stress behavior.

## Student-Written Tests

You must complete these two test functions in `test.cpp`:

```cpp
void testCollisionDeletion(HashTable&, TestResult&);
void testHighLoadFactor(HashTable&, TestResult&);
```

The declarations are already provided in `test.h`.

### `testCollisionDeletion()`

Write meaningful tests that demonstrate correct deletion when multiple entries collide into the same bucket.

Your tests must demonstrate that deleting entries from a collision chain does not corrupt or incorrectly remove the other entries in that chain.

### `testHighLoadFactor()`

Write meaningful tests that demonstrate correct hash-table behavior when the load factor is greater than `1.0`.

Use deliberate collisions so that your tests demonstrate the behavior of separate chaining under a heavy bucket load.

### Testing Rules

For both student-written test functions:

- Each student-written test must establish the table state it needs and must not depend on state left by a previous test.
- initialize the supplied `TestResult&`;
- use the provided `recordTest()` helper;
- do not print results from the test module;
- write an appropriate function comment block;
- remove the starter comments when your implementation is complete.

The supplied `main.cpp` will report a required student test as:

```text
INCOMPLETE
```

when that test records zero conditions, and the program will return failure.

---

# Analysis

This assignment includes `ANALYSIS.md`.

Complete all ten questions.

---

# Memory Verification

After the program is working normally, build and run it with AddressSanitizer.

Example:

```bash
g++ -Wall -Wextra -pedantic -g -fsanitize=address \
    main.cpp test.cpp hashtable.cpp linkedlist.cpp -o hashtable
```

Then run:

```bash
./hashtable
```

The completed program must not produce:

- memory leaks;
- use-after-free errors;
- invalid reads or writes;
- double deletes.

Passing the functional tests does not prove that dynamic memory ownership is correct.

---

# Git Requirements

Use Git throughout the assignment.

Your history should show meaningful development rather than one final bulk commit.

Commit as you reach real milestones: small, smart, often.

Do not manufacture meaningless commits merely to increase the count.

Your history should make it possible to see the development of the `HashTable`, the completion of your two required tests, debugging work, and completion of the analysis.

---

# Final Verification

Before submitting, verify all of the following:

- your own `data.h`, `linkedlist.h`, and `linkedlist.cpp` are present, or you are using the instructor-supplied fallback version;
- the `LinkedList` public interface has not been changed;
- `hashtable.h` and `hashtable.cpp` exist;
- the project builds with the required compiler warnings enabled;
- all supplied and student-written tests pass;
- `testCollisionDeletion()` is complete and records meaningful tests;
- `testHighLoadFactor()` is complete and records meaningful tests;
- `HashTable` uses a dynamically allocated array of `LinkedList` objects;
- `HashTable` interacts with `LinkedList` only through its public interface;
- the class stores `table`, `capacity`, and `count`;
- hashing uses `id % capacity`;
- collisions are resolved through separate chaining;
- failed insertions and deletions do not corrupt the table count;
- load factor is calculated correctly;
- `clearTable()` preserves capacity and leaves the object reusable;
- AddressSanitizer reports no memory errors;
- `ANALYSIS.md` is complete;
- your Git history shows meaningful development.

---

# Submission

Submit the URL of your completed GitHub repository in Blackboard.

Do not submit individual source files separately unless instructed to do so.
