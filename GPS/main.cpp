#include <iostream>
#include <fstream>
#include <filesystem>
#include "CA_generator.h"

using namespace std;


void task_1();

void task_2();
bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code&);

// just for generating codes
void generate_received_codes();

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
    
    CAGenerator CA_generator(PRN_id);
    cout << "CA code for satellite with PRN id (" << PRN_id << "): " << CA_generator() << endl;
}


void task_2() {
    auto PRN_id = rand() % 32 + 1;

    CAGenerator CA_generator(1);

    ifstream in("./received_codes/" + to_string(PRN_id) + "_received.txt");
    in.ignore(numeric_limits<streamsize>::max(),'\n');

    bitset<rcode_bit_length << 1> temp;
    in >> temp;

    for (size_t prn = 1; prn < 33; prn++) {
        CA_generator.set_satellite(prn);
        auto generated_ca = CA_generator();
        for (size_t i = 0, j = 0; i < rcode_bit_length; i++, j = 0) {
            for (; j < rcode_bit_length; j++)
                if (temp[i + j] != generated_ca[j]) break;

            if (j == CA_bit_length) {
                in.close();
                cout << "PRN: " << prn << endl;
                return;
            }
        }
    }
    in.close();
}


bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code& ca_code) {
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

void generate_received_codes() {
    namespace fs = std::filesystem;

    constexpr int N = 10;
    CAGenerator CA_generator(1);

    try {
        if (!fs::create_directory("./received_codes")) {
            cerr << "Cannot create directory for received codes" << endl;
            return;
        }
    }
    catch (filesystem::filesystem_error& e) {
        cerr << e.what() << endl;
        return;
    }
    catch (...) {
        cerr << "Something went wrong" << endl;
        return;
    }

    ofstream out;
    for (int i = 1; i < 33; i++) {
        CA_generator.set_satellite(i);
        auto received = receive_ca_code(CA_generator());

        out.open("./received_codes/" + to_string(i) + "_received.txt");
        out << N << endl;
        for (int j = 0; j < N; j++)
            out << received;

        out.close();
    }
}