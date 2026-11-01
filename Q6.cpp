#include <iostream>
#include <cstdlib>
#include <chrono>
using namespace std;

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend int minutesBetweenNoInline(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return abs(first - second);
}
inline bool earlier(const Time& a, const Time& b) {
    return (a.h * 60 + a.m) < (b.h * 60 + b.m);
}

// Non-inline comparison for the requested timing comparison (GCC/Clang).
#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
int minutesBetweenNoInline(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;
    return abs(first - second);
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' ' << boolalpha
         << earlier(arrival, departure) << '\n';
    Time noonBefore(11, 55), noonAfter(12, 5), same(12, 5);
    cout << minutesBetween(noonBefore, noonAfter) << ' '
         << earlier(noonBefore, noonAfter) << '\n';
    cout << minutesBetween(same, noonAfter) << ' ' << earlier(same, noonAfter) << '\n';

    constexpr int ITERATIONS = 10000000;
    volatile int minuteInput = 10; // volatile read prevents the loop being folded away
    volatile int result = 0;
    auto startInline = chrono::steady_clock::now();
    int inlineTotal = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        Time changingArrival(13, minuteInput);
        inlineTotal += minutesBetween(departure, changingArrival);
    }
    result = inlineTotal;
    auto endInline = chrono::steady_clock::now();
    auto startNoInline = chrono::steady_clock::now();
    int noInlineTotal = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        Time changingArrival(13, minuteInput);
        noInlineTotal += minutesBetweenNoInline(departure, changingArrival);
    }
    result = noInlineTotal;
    auto endNoInline = chrono::steady_clock::now();
    cout << "10,000,000 inline calls (microseconds): "
         << chrono::duration_cast<chrono::microseconds>(endInline - startInline).count() << '\n';
    cout << "10,000,000 non-inline calls (microseconds): "
         << chrono::duration_cast<chrono::microseconds>(endNoInline - startNoInline).count() << '\n';
    (void)result;
}
