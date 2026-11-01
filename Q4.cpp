#include <iostream>
#include <string>
using namespace std;

class SavingsAccount {
private:
    string accountNumber;
    double balance;
    string transactions[10];
    int count;
    int nextIndex; // next position to write; circular buffer
public:
    SavingsAccount(const string& number, double openingBalance)
        : accountNumber(number), balance(openingBalance), count(0), nextIndex(0) {}
    void deposit(double amount);
    void withdraw(double amount);
    void miniStatement() const;
    double getBalance() const { return balance; }
};

void SavingsAccount::deposit(double amount) {
    if (amount <= 0) { cout << "Invalid deposit\n"; return; }
    balance += amount;
    transactions[nextIndex] = "Deposit: +" + to_string(amount);
    nextIndex = (nextIndex + 1) % 10;
    if (count < 10) ++count;
}
void SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) { cout << "Invalid withdrawal\n"; return; }
    balance -= amount;
    transactions[nextIndex] = "Withdrawal: -" + to_string(amount);
    nextIndex = (nextIndex + 1) % 10;
    if (count < 10) ++count;
}
void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << "\nBalance: " << balance << "\nLast transactions:\n";
    int start = (count == 10) ? nextIndex : 0;
    for (int i = 0; i < count; ++i) cout << transactions[(start + i) % 10] << '\n';
}
int main() {
    SavingsAccount account("SA1001", 5000);
    account.deposit(1000); account.withdraw(500);
    for (int i = 1; i <= 10; ++i) account.deposit(i * 10);
    account.miniStatement();
}
