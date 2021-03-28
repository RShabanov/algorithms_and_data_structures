#include <iostream>
#include "CA_generator.h"

using namespace std;


void task_1();
void task_2();

int main() {
    task_1();
    return 0;
}


void task_1() {
    size_t PRN_id;
    cout << "Enter PRN id: ";
    while (!(cin >> PRN_id)) {
        cout << "Bad input!\nEnter PRN id, again: ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    CAGenerator CA_generator(PRN_id - 1);
    cout << "CA code for satellite with PRN id (" << PRN_id << "): " << CA_generator() << endl;
}


void task_2() {
    size_t PRN_id;
    cout << "Enter PRN id: ";
    while (!(cin >> PRN_id)) {
        cout << "Bad input!\nEnter PRN id, again: ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    CAGenerator CA_generator(PRN_id - 1);
    auto generated_ca { CA_generator() };
    bitset<CA_bit_length + nav_bit_length> received_cagenerated_ca;
    cout << "CA code for satellite with PRN id # " << PRN_id << " (generated): " << generated_ca << endl;
}
