/**
 * @file main.cpp
 * @author Alex Katrompas
 * @assignment Hash Tables
 * @brief Application driver for the HashTable test suite.
 */

#include "main.h"

int main() {

    int status = 0;
    TestResult result = {0, 0};
    TestResult overall = {0, 0};
    HashTable table(10);

    std::cout << "HashTable Tests" << std::endl;
    std::cout << "===============" << std::endl;

    testConstruction(result);
    std::cout << "Construction: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testInitialState(table, result);
    std::cout << "Initial state: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testBasicInsertion(table, result);
    std::cout << "Insertion, collision, and retrieval: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testRejectedOperations(table, result);
    std::cout << "Rejected operations: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    std::cout << std::endl;
    std::cout << "Visual table verification" << std::endl;
    std::cout << "Capacity: 10, count: 6, load factor: 0.6" << std::endl;
    std::cout << "Bucket 1 should contain ids 1, 11, 21, 31." << std::endl;
    std::cout << "Bucket 2 should contain id 2." << std::endl;
    std::cout << "Bucket 3 should contain id 3." << std::endl;
    std::cout << "All other buckets should be empty." << std::endl;
    std::cout << std::endl;
    table.printTable();
    std::cout << std::endl;

    testCollisionDeletion(table, result);

    if (result.total == 0) {
        std::cout << "Collision-chain deletion: INCOMPLETE" << std::endl;
        status = 1;
    } else {
        std::cout << "Collision-chain deletion: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testClearAndReuse(table, result);
    std::cout << "Clear and reuse: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    testHighLoadFactor(table, result);

    if (result.total == 0) {
        std::cout << "High load factor and heavy collision: INCOMPLETE" << std::endl;
        status = 1;
    } else {
        std::cout << "High load factor and heavy collision: "
                  << result.passed << "/" << result.total
                  << " passed" << std::endl;
        overall.passed += result.passed;
        overall.total += result.total;
    }

    testScaledStress(table, result);
    std::cout << "Scaled stress: "
              << result.passed << "/" << result.total
              << " passed" << std::endl;
    overall.passed += result.passed;
    overall.total += result.total;

    std::cout << std::endl;
    std::cout << "Overall: "
              << overall.passed << "/" << overall.total
              << " passed" << std::endl;

    if (overall.passed != overall.total) {
        status = 1;
    }

    return status;
}
