#include <iostream>
#include <vector>
using namespace std;

int& highestMark(int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) if (marks[i] > marks[index]) index = i;
    return marks[index];
}

// Deliberately unsafe demonstration: returning a reference to a local variable is invalid.
// Do not call this function; compile with warnings to observe the diagnostic.
int& danglingReference() {
    int local = 50;
    return local; // Undefined behaviour if the returned reference is used.
}

int highestMarkIndex(const int marks[], int size) {
    int index = 0;
    for (int i = 1; i < size; ++i) if (marks[i] > marks[index]) index = i;
    return index;
}

int main() {
    int marks[] = {78, 92, 85, 88};
    int size = sizeof(marks) / sizeof(marks[0]);
    cout << "Highest mark: " << highestMark(marks, size) << '\n';
    highestMark(marks, size) += 2;
    cout << "After moderation: " << highestMark(marks, size) << '\n';
    int index = highestMarkIndex(marks, size);
    cout << "Index-based access: marks[" << index << "] = " << marks[index] << '\n';

    vector<int> dynamicMarks = {78, 92, 85};
    int& saved = dynamicMarks[1];
    cout << "Before vector growth: " << saved << '\n';
    // A vector reallocation can invalidate saved. Do not use saved after growth.
    dynamicMarks.reserve(dynamicMarks.capacity() + 100);
    cout << "Vector size after reserve: " << dynamicMarks.size() << '\n';
}
