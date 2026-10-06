/**
 * @file test.h
 * @author Alex Katrompas
 * @assignment Hash Tables
 * @brief Declares the HashTable testing module.
 */

#ifndef TEST_H
#define TEST_H

#include <string>
#include <cmath>
#include "hashtable.h"

struct TestResult {
    int passed;
    int total;
};

// instructor test functions
void recordTest(bool, TestResult&);
bool nearlyEqual(double, double, double = 0.000000001);
bool matchesEntry(const HashTable&, int, const std::string&);

void testConstruction(TestResult&);
void testInitialState(HashTable&, TestResult&);
void testBasicInsertion(HashTable&, TestResult&);
void testRejectedOperations(HashTable&, TestResult&);
void testClearAndReuse(HashTable&, TestResult&);
void testScaledStress(HashTable&, TestResult&);

// student test functions
// COMPLETE THE FOLLOWING TEST FUNCTIONS IN test.cpp
void testCollisionDeletion(HashTable&, TestResult&);
void testHighLoadFactor(HashTable&, TestResult&);

#endif // TEST_H
