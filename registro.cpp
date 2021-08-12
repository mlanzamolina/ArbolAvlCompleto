#include "registro.h"

using namespace std;

void registro::printRegister() {
    cout << "id: " << id << endl;
    cout << "name: " << name << endl;
    cout << "lastname: " << lastname << endl;
    cout << "credit card: " << credit_card << endl;
    cout << "date: " << date << endl;
    cout << "day: " << day << endl;
    cout << "month: " << month << endl;
    cout << "year: " << year << endl;
    cout << "payment type: " << payment_type << endl;
    cout << "total: " << total << endl;
    cout << "business type: " << business_type << endl;
    cout << "business name: " << business_name << endl;
}