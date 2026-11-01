#include <iostream>
#include <string>
using namespace std;

class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat;
    string name;
public:
    explicit BusTicket(const string& n) : seat(0), name(n) {
        if (issued < CAPACITY) seat = ++issued;
    }
    static int count() { return issued; }
    void print() const {
        cout << name << ": " << (seat ? "Seat " + to_string(seat) : string("Waiting")) << '\n';
    }
};
int BusTicket::issued = 0;

void createMoreTickets() {
    BusTicket a("Esha"), b("Farhan");
    a.print(); b.print();
    cout << "Cumulative issued: " << BusTicket::count() << '\n';
}
int main() {
    BusTicket trip[4] = {BusTicket("Asha"), BusTicket("Bala"), BusTicket("Chitra"), BusTicket("Dev")};
    for (const BusTicket& t : trip) t.print();
    cout << "Issued: " << BusTicket::count() << '\n';
    createMoreTickets();
    createMoreTickets();
}
