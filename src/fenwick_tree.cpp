#include "fenwick_tree.hpp"
#include <stdexcept>
#include <algorithm>
using namespace std;

FenwickTree::FenwickTree(size_t n) : size(n) {
    if (n == 0) {
        throw invalid_argument("Fenwick Tree size must be greater than 0");
    }
    // Initialize tree with size + 1 because Fenwick Trees use 1-based indexing
    tree.resize(n + 1, 0);
}

int64_t FenwickTree::lsb(int64_t x) {
    return x & (-x);
}

void FenwickTree::update(size_t i, int64_t delta) {
    if (i == 0 || i > size) {
        throw std::out_of_range("Index out of range for Fenwick Tree update");
    }
    
    // Update all affected nodes in the tree
    while (i <= size) {
        tree[i] += delta;
        i += lsb(i);
    }
}

// prefix sum: sum[1..i]=arr[1]+arr[2]+⋯+arr[i]

int64_t FenwickTree::query(size_t i) const {
    if (i == 0) return 0;
    if (i > size) {
        throw std::out_of_range("Index out of range for Fenwick Tree query");
    }
    
    int64_t sum = 0;
    // Sum all values from index 1 to i
    while (i > 0) {
        sum += tree[i];
        i -= lsb(i);
    }
    return sum;
}

int64_t FenwickTree::rangeQuery(size_t left, size_t right) const {
    if (left > right) {
        throw std::invalid_argument("Left boundary must be <= right boundary");
    }
    if (left == 0 || right > size) {
        throw std::out_of_range("Range boundaries out of range for Fenwick Tree");
    }
    
    // Range sum = prefix[sum to right] - prefix[sum to (left-1)]
    return query(right) - query(left - 1);
}

void FenwickTree::reset() {
    std::fill(tree.begin(), tree.end(), 0);
}

int64_t FenwickTree::getValue(size_t i) const {
    if (i == 0 || i > size) {
        throw std::out_of_range("Index out of range for Fenwick Tree getValue");
    }
    
    // Get the value at index i by querying the range [i, i]
    return rangeQuery(i, i);
}
