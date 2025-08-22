#pragma once
#include <vector>
#include <cstdint>

/**
 * @brief Fenwick Tree (Binary Indexed Tree) implementation for efficient range sum queries
 * 
 * Provides O(log n) time complexity for:
 * - Point updates (adding/subtracting values)
 * - Range sum queries (prefix sums)
 * 
 * This is the core data structure that enables fast vote counting and aggregation.
 */
class FenwickTree {
private:
    std::vector<int64_t> tree;
    size_t size;

    /**
     * @brief Get the least significant bit of a number
     * @param x The number
     * @return The least significant bit
     */
    static int64_t lsb(int64_t x);

public:
    /**
     * @brief Construct a Fenwick Tree with given size
     * @param n The size of the tree
     */
    explicit FenwickTree(size_t n);

    /**
     * @brief Update the value at index i by adding delta
     * @param i The index to update (1-based indexing)
     * @param delta The value to add
     * 
     * Time complexity: O(log n)
     */
    void update(size_t i, int64_t delta);

    /**
     * @brief Get the prefix sum from index 1 to i
     * @param i The end index (1-based indexing)
     * @return The sum of values from index 1 to i
     * 
     * Time complexity: O(log n)
     */
    int64_t query(size_t i) const;

    /**
     * @brief Get the sum of values in range [left, right]
     * @param left The left boundary (1-based indexing)
     * @param right The right boundary (1-based indexing)
     * @return The sum of values in the range
     * 
     * Time complexity: O(log n)
     */
    int64_t rangeQuery(size_t left, size_t right) const;

    /**
     * @brief Get the current size of the tree
     * @return The size of the tree
     */
    size_t getSize() const { return size; }

    /**
     * @brief Reset all values in the tree to zero
     */
    void reset();

    /**
     * @brief Get the value at a specific index
     * @param i The index (1-based indexing)
     * @return The value at index i
     */
    int64_t getValue(size_t i) const;
};
