#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Original design: shifting all stored entries when the fixed array is full.
class ShiftHistory {
    static const int K = 10;
    int data[K]{};
    int count = 0;
public:
    void add(int value) {
        if (count < K) data[count++] = value;
        else {
            for (int i = 1; i < K; ++i) data[i - 1] = data[i];
            data[K - 1] = value;
        }
    }
    int last() const { return count ? data[count - 1] : -1; }
};

// Redesigned circular history: overwrite the oldest item in O(1).
class CircularHistory {
    static const int K = 10;
    int data[K]{};
    int count = 0;
    int next = 0;
public:
    void add(int value) {
        data[next] = value;
        next = (next + 1) % K;
        if (count < K) ++count;
    }
    int last() const { return count ? data[(next + K - 1) % K] : -1; }
};

int main() {
    const int N = 1000000;
    ShiftHistory original;
    CircularHistory redesigned;
    auto start1 = steady_clock::now();
    for (int i = 0; i < N; ++i) original.add(i);
    auto end1 = steady_clock::now();
    auto start2 = steady_clock::now();
    for (int i = 0; i < N; ++i) redesigned.add(i);
    auto end2 = steady_clock::now();
    cout << "Original last value: " << original.last() << '\n';
    cout << "Redesigned last value: " << redesigned.last() << '\n';
    cout << "Original insertion time (microseconds): "
         << duration_cast<microseconds>(end1 - start1).count() << '\n';
    cout << "Circular insertion time (microseconds): "
         << duration_cast<microseconds>(end2 - start2).count() << '\n';
}
