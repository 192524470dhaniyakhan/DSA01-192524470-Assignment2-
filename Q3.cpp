#include <iostream>
#include <string>
using namespace std;
struct Parcel { double weightKg; bool express; bool insured; };

// One unambiguous default-argument overload for kg.
double charge(double weightKg, bool express = false, bool insured = false) {
    double total = weightKg * 40.0;
    if (express) total += 50.0;
    if (insured) total += 20.0;
    cout << "Kilogram overload: "; return total;
}
// Grams are deliberately a distinct integer overload with no default bool parameters.
double charge(int weightGrams) {
    cout << "Gram overload: "; return (weightGrams / 1000.0) * 40.0;
}
double charge(const Parcel& p) {
    cout << "Parcel overload: "; return charge(p.weightKg, p.express, p.insured);
}

int main() {
    cout << charge(2) << '\n';       // int exact match
    cout << charge(2.0) << '\n';     // double exact match
    cout << charge(2.0f) << '\n';    // float promotes to double
    cout << charge(2000) << '\n';    // int exact match (grams)
    cout << charge(2.5, true) << '\n';
    Parcel p{3.0, true, true};
    cout << charge(p) << '\n';
}
