/**
 * @file test.cpp
 * @author Alex Katrompas
 * @assignment Hash Tables
 * @brief Implements the HashTable testing module.
 */


#include "test.h"

/**
 * @brief Records the result of one test condition.
 * @param condition The condition being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note This function does not print test results.
 */
void recordTest(bool condition, TestResult& result) {

    result.total++;

    if (condition) {
        result.passed++;
    }
}

/**
 * @brief Compares two floating-point values using a small tolerance.
 * @param first First value to compare.
 * @param second Second value to compare.
 * @param tolerance Maximum permitted absolute difference.
 * @exception none
 * @return true when the values differ by no more than tolerance, false otherwise.
 * @note This helper is used for load-factor tests.
 */
bool nearlyEqual(double first, double second, double tolerance) {

    return std::fabs(first - second) <= tolerance;
}

/**
 * @brief Checks whether a stored HashTable entry matches expected data.
 * @param table A reference to the HashTable being tested.
 * @param id The expected id.
 * @param information The expected information.
 * @exception none
 * @return true if the entry exists and matches the expected values, false otherwise.
 * @note none
 */
bool matchesEntry(const HashTable& table, int id, const std::string& information) {

    bool matches = false;
    Data result = {-1, "unchanged"};

    if (table.getEntry(id, result)) {
        matches = result.id == id && result.information == information;
    }

    return matches;
}

/**
 * @brief Tests default, invalid, and custom HashTable construction.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note Local HashTable objects are used so constructor behavior can be tested
 *       independently from the stateful application-level test object.
 */
void testConstruction(TestResult& result) {

    result.passed = 0;
    result.total = 0;

    HashTable defaultTable;
    recordTest(defaultTable.getCapacity() == 17, result);
    recordTest(defaultTable.getCount() == 0, result);
    recordTest(defaultTable.isEmpty(), result);
    recordTest(nearlyEqual(defaultTable.getLoadFactor(), 0.0), result);

    HashTable zeroCapacity(0);
    recordTest(zeroCapacity.getCapacity() == 17, result);
    recordTest(zeroCapacity.getCount() == 0, result);
    recordTest(zeroCapacity.isEmpty(), result);

    HashTable negativeCapacity(-5);
    recordTest(negativeCapacity.getCapacity() == 17, result);
    recordTest(negativeCapacity.getCount() == 0, result);
    recordTest(negativeCapacity.isEmpty(), result);

    HashTable customCapacity(10);
    recordTest(customCapacity.getCapacity() == 10, result);
    recordTest(customCapacity.getCount() == 0, result);
    recordTest(customCapacity.isEmpty(), result);
    recordTest(nearlyEqual(customCapacity.getLoadFactor(), 0.0), result);
}

/**
 * @brief Tests the initial state of a newly constructed HashTable.
 * @param table A reference to the HashTable being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note The incoming HashTable is expected to have capacity 10 and be empty.
 */
void testInitialState(HashTable& table, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    Data data = {-1, "unchanged"};

    recordTest(table.getCapacity() == 10, result);
    recordTest(table.getCount() == 0, result);
    recordTest(table.isEmpty(), result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.0), result);
    recordTest(!table.exists(1), result);
    recordTest(!table.getEntry(1, data), result);
    recordTest(data.id == -1 && data.information == "unchanged", result);
    recordTest(!table.deleteEntry(1), result);

    table.clearTable();

    recordTest(table.getCapacity() == 10, result);
    recordTest(table.getCount() == 0, result);
    recordTest(table.isEmpty(), result);
}

/**
 * @brief Tests insertion, collisions, retrieval, existence, count, and load factor.
 * @param table A reference to the HashTable being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note The incoming HashTable is expected to be empty. This test leaves six
 *       entries in the table, including four entries that collide in bucket 1.
 */
void testBasicInsertion(HashTable& table, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    std::string one = "one";
    std::string two = "two";
    std::string three = "three";
    std::string eleven = "eleven";
    std::string twentyOne = "twenty-one";
    std::string thirtyOne = "thirty-one";

    recordTest(table.addEntry(1, one), result);
    recordTest(table.addEntry(2, two), result);
    recordTest(table.addEntry(3, three), result);
    recordTest(table.addEntry(11, eleven), result);
    recordTest(table.addEntry(21, twentyOne), result);
    recordTest(table.addEntry(31, thirtyOne), result);

    recordTest(!table.isEmpty(), result);
    recordTest(table.getCount() == 6, result);
    recordTest(table.getCapacity() == 10, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.6), result);

    recordTest(table.exists(1), result);
    recordTest(table.exists(2), result);
    recordTest(table.exists(3), result);
    recordTest(table.exists(11), result);
    recordTest(table.exists(21), result);
    recordTest(table.exists(31), result);

    recordTest(matchesEntry(table, 1, one), result);
    recordTest(matchesEntry(table, 2, two), result);
    recordTest(matchesEntry(table, 3, three), result);
    recordTest(matchesEntry(table, 11, eleven), result);
    recordTest(matchesEntry(table, 21, twentyOne), result);
    recordTest(matchesEntry(table, 31, thirtyOne), result);
}

/**
 * @brief Tests duplicate, invalid, missing-entry, and state-preservation behavior.
 * @param table A reference to the HashTable being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception none
 * @return none
 * @note The incoming HashTable is expected to contain the six entries created
 *       by testBasicInsertion. Its state should remain unchanged.
 */
void testRejectedOperations(HashTable& table, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    std::string duplicate = "not eleven";
    std::string valid = "valid";
    std::string empty = "";
    Data unchanged = {-1, "unchanged"};

    recordTest(!table.addEntry(11, duplicate), result);
    recordTest(!table.addEntry(0, valid), result);
    recordTest(!table.addEntry(-10, valid), result);
    recordTest(!table.addEntry(40, empty), result);

    recordTest(table.getCount() == 6, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.6), result);
    recordTest(matchesEntry(table, 11, "eleven"), result);

    recordTest(!table.exists(0), result);
    recordTest(!table.exists(-1), result);
    recordTest(!table.exists(999), result);

    recordTest(!table.getEntry(999, unchanged), result);
    recordTest(unchanged.id == -1 && unchanged.information == "unchanged", result);

    recordTest(!table.deleteEntry(999), result);
    recordTest(!table.deleteEntry(0), result);
    recordTest(!table.deleteEntry(-1), result);
    recordTest(table.getCount() == 6, result);
}


/**
 * @brief Tests clearTable on populated and empty tables and reuse after clearing.
 * @param table A reference to the HashTable being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note This test establishes its own starting state, preserves capacity, and
 *       leaves four new entries in the table.
 */
void testClearAndReuse(HashTable& table, TestResult& result) {

    result.passed = 0;
    result.total = 0;

    table.clearTable();

    std::string two = "two";
    std::string three = "three";
    std::string fortyOne = "forty-one";
    std::string fiftyOne = "fifty-one";

    table.addEntry(2, two);
    table.addEntry(3, three);
    table.addEntry(41, fortyOne);
    table.addEntry(51, fiftyOne);

    recordTest(table.getCount() == 4, result);
    recordTest(table.getCapacity() == 10, result);
    recordTest(table.exists(2), result);
    recordTest(table.exists(3), result);
    recordTest(table.exists(41), result);
    recordTest(table.exists(51), result);

    table.clearTable();

    recordTest(table.isEmpty(), result);
    recordTest(table.getCount() == 0, result);
    recordTest(table.getCapacity() == 10, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.0), result);
    recordTest(!table.exists(2), result);
    recordTest(!table.exists(3), result);
    recordTest(!table.exists(41), result);
    recordTest(!table.exists(51), result);

    table.clearTable();

    recordTest(table.isEmpty(), result);
    recordTest(table.getCount() == 0, result);
    recordTest(table.getCapacity() == 10, result);

    std::string five = "five";
    std::string fifteen = "fifteen";
    std::string twentyFive = "twenty-five";
    std::string six = "six";

    recordTest(table.addEntry(5, five), result);
    recordTest(table.addEntry(15, fifteen), result);
    recordTest(table.addEntry(25, twentyFive), result);
    recordTest(table.addEntry(6, six), result);

    recordTest(table.getCount() == 4, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.4), result);
    recordTest(matchesEntry(table, 5, five), result);
    recordTest(matchesEntry(table, 15, fifteen), result);
    recordTest(matchesEntry(table, 25, twentyFive), result);
    recordTest(matchesEntry(table, 6, six), result);
}

/**
 * @brief Performs deterministic large-scale insertion, retrieval, rejection,
 *        deletion, and final-state tests.
 * @param table A reference to the HashTable being tested.
 * @param result A reference to the TestResult object being updated.
 * @exception std::bad_alloc May be thrown if allocation fails.
 * @return none
 * @note The incoming HashTable is expected to be empty and have capacity 10.
 *       The test finishes with an empty table.
 */
void testScaledStress(HashTable& table, TestResult& result) {

    result.passed = 0;
    result.total = 0;
    table.clearTable();

    const int TEST_SIZE = 300;

    recordTest(table.isEmpty(), result);
    recordTest(table.getCount() == 0, result);
    recordTest(table.getCapacity() == 10, result);

    for (int i = 0; i < TEST_SIZE; i++) {
        int id = ((i * 113) % TEST_SIZE) + 1;
        std::string information = "record-" + std::to_string(id);
        recordTest(table.addEntry(id, information), result);
    }

    recordTest(table.getCount() == TEST_SIZE, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 30.0), result);

    for (int id = 1; id <= TEST_SIZE; id++) {
        std::string information = "record-" + std::to_string(id);
        recordTest(table.exists(id), result);
        recordTest(matchesEntry(table, id, information), result);
    }

    for (int id = 30; id <= TEST_SIZE; id += 30) {
        std::string duplicate = "duplicate";
        recordTest(!table.addEntry(id, duplicate), result);
    }

    recordTest(table.getCount() == TEST_SIZE, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 30.0), result);

    std::string valid = "valid";
    std::string empty = "";

    recordTest(!table.addEntry(0, valid), result);
    recordTest(!table.addEntry(-1, valid), result);
    recordTest(!table.addEntry(TEST_SIZE + 1, empty), result);
    recordTest(table.getCount() == TEST_SIZE, result);

    for (int i = 0; i < TEST_SIZE; i++) {
        int id = ((i * 197) % TEST_SIZE) + 1;
        recordTest(table.deleteEntry(id), result);
        recordTest(!table.exists(id), result);
    }

    recordTest(table.isEmpty(), result);
    recordTest(table.getCount() == 0, result);
    recordTest(nearlyEqual(table.getLoadFactor(), 0.0), result);
    recordTest(table.getCapacity() == 10, result);
    recordTest(!table.deleteEntry(1), result);
    recordTest(!table.exists(1), result);
}



// write your comment function block here
void testCollisionDeletion(HashTable& table, TestResult& result) {
    result.passed = 0;
    result.total = 0;
    // write your own test code here to verify that deletion works correctly when
    // the target entry is at the head, middle, or tail of a collision chain.
    // erase this comment when you are done

}


// write your comment function block here
void testHighLoadFactor(HashTable& table, TestResult& result) {
    result.passed = 0;
    result.total = 0;
    // write your own test code here to verify correct behavior with a load factor
    // greater than 1.0 and a deliberately heavy collision chain.
    // erase this comment when you are done

}
