#include <iostream>
using namespace std;

void changeByValue(int a) { a += 10; }
void changeByReference(int& b) { b += 10; }
void changeByPointer(int* c) { if (c != nullptr) *c += 10; }

int& bigger(int& p, int& q) { return (p > q) ? p : q; }
void show(int x, int y = 5, int z = 10) { cout << x + y + z << ' '; }

void applyByValue(long long fee, int percent) {
    fee -= fee * percent / 100;
}
void applyConcession(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void applyConcessionByPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= (*fee) * percent / 100;
}

int main() {
    int a = 1, b = 2, c = 3;
    changeByValue(a); changeByReference(b); changeByPointer(&c);
    cout << "Value/reference/pointer: " << a << ' ' << b << ' ' << c << '\n';
    bigger(a, c) = 100;
    cout << "After bigger assignment: " << a << ' ' << c << '\n';
    cout << "Default arguments: ";
    show(1); show(1, 2); show(1, 2, 3); cout << '\n';
    long long hostelFee = 45000;
    applyByValue(hostelFee, 10);
    cout << "after call by value   : " << hostelFee << '\n';
    applyConcession(hostelFee, 10);
    cout << "after call by reference: " << hostelFee << '\n';
    applyConcessionByPointer(&hostelFee, 10);
    cout << "after call by pointer  : " << hostelFee << '\n';
}
