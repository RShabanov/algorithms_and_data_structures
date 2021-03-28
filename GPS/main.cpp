#include <iostream>
#include "CA_generator.h"

using namespace std;


void task_1();

void task_2();
bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code&, size_t);

int main() {
    task_2();
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

    auto received_code { receive_ca_code(generated_ca, PRN_id) };

    double time = 0;
    for (size_t i = 0; i < CA_bit_length; i++)
        time += generated_ca[i] == received_code[i + nav_bit_length] ? 1 : -1;
    time /= CA_bit_length;

    cout << "Generated CA code: " << generated_ca << endl;
    cout << "Received code:     " << received_code << endl;
    cout << "Time shift: " << time << endl;
}


bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code& ca_code, size_t PRN_id) {
    srand(time(NULL));

    bitset<rcode_bit_length> received_ca;

    for (size_t i = 0; i < CA_bit_length; i++)
        received_ca[i + nav_bit_length] = ca_code[i];

    auto nav = generate_nav();
    for (size_t i = 0; i < nav_bit_length; i++)
        received_ca[i] = nav[i];

    bitset<rcode_bit_length << 1> buffer;
    for (size_t i = 0; i < buffer.size(); i++)
        buffer[i] = received_ca[i % rcode_bit_length];

    size_t pos = rand() % rcode_bit_length;
    for (size_t i = 0; i < rcode_bit_length; i++)
        received_ca[i] = buffer[pos + i];

    return received_ca;
}