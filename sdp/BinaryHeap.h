#pragma once

#include <functional>
#include <utility>
#include <vector>

using std::swap;
using std::vector;

template <typename T, typename cmp = std::less<T>>
class BinaryHeap {
   public:
    BinaryHeap(cmp predicate) : largerThan(predicate) {}

    BinaryHeap() = default;
    BinaryHeap(const BinaryHeap& binaryHeap) = default;
    BinaryHeap& operator=(const BinaryHeap& binaryHeap) = default;

    const T& getRoot() const { return data[0]; }

    size_t getSize() const { return data.size(); }

    bool isEmpty() const { return data.empty(); }

    void insert(const T& element) {
        data.push_back(element);

        for (size_t i = data.size(); i > 0; i = parent(i)) {
            size_t parentNodeIndex = parent(i);
            if (largerThan(data[i], data[parentNodeIndex])) {
                swap(data[i], data[parentNodeIndex]);
            } else {
                return;
            }
        }
    }

    bool removeRoot() {
        if (data.empty()) {
            return false;
        }

        data[0] = data.back();
        data.pop_back();

        size_t current = 0, next = leftNode(current), right = rightNode(current);

        while (next < data.size()) {
            if (right < data.size() && largerThan(data[right], data[next])) {
                next = right;
            }

            if (!largerThan(data[next], data[current])) {
                return true;
            }

            swap(data[current], data[next]);
            current = next;
            next = leftNode(current);
            right = rightNode(current);
        }

        return true;
    }

   private:
    vector<T> data;
    cmp largerThan;

    static size_t parent(size_t index) { return (index - 1) / 2; }
    static size_t leftNode(size_t index) { return index * 2 + 1; }
    static size_t rightNode(size_t index) { return (index + 1) * 2; }
};
