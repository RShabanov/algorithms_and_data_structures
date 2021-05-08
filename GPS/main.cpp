#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <cmath>
#include <iomanip>

#include "CA_generator.h"

using namespace std;

struct Point {
    float x, y, r;
};


void task_1();

// Коррелятор
void task_2();
bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code&);

// Нахождение PRN по входным данным
void task_3();

// Вычисление положения спутника по параметрам орбиты
void task_4();

// Триангуляция,  нахождение координат приемника по расстояниям до спутников
void task_5();

// just for generating codes
void generate_received_codes();

int main() {
//    generate_received_codes();
    void (*tasks[])() {
        task_1, task_2, task_3, task_4, task_5
    };
    for (const auto& task : tasks)
        task();
    return 0;
}


void task_1() {
    cout << "Task 1\n";

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
    cout << "Task 2\n";

    srand(time(NULL));
    auto PRN_id = rand() % 32 + 1;

    CAGenerator CA_generator(PRN_id);

    ifstream in("./received_codes/" + to_string(PRN_id) + "_received.txt");
    in.ignore(numeric_limits<streamsize>::max(),'\n');

    bitset<rcode_bit_length << 1> temp;
    in >> temp;

    auto generated_ca = CA_generator();
    for (size_t i = 0, j = 0; i < rcode_bit_length + nav_bit_length; i++, j = 0) {
        for (; j < CA_bit_length; j++)
            if (temp[i + j] != generated_ca[j]) break;

        if (j == CA_bit_length) {
            in.close();
            cout << "Shift for " << PRN_id << " PRN: " << i + 1 << endl;
            return;
        }
    }
}

void task_3() {
    cout << "Task 3\n";

    srand(time(NULL));
    auto PRN_id = rand() % 32 + 1;

    CAGenerator CA_generator(1);

    string path = "./received_codes/" + to_string(PRN_id) + "_received.txt";
    ifstream in(path);
    in.ignore(numeric_limits<streamsize>::max(),'\n');

    bitset<rcode_bit_length << 1> temp;
    in >> temp;

    for (size_t prn = 1; prn < 33; prn++) {
        CA_generator.set_satellite(prn);
        auto generated_ca = CA_generator();
        for (size_t i = 0, j = 0; i < rcode_bit_length + nav_bit_length; i++, j = 0) {
            for (; j < CA_bit_length; j++)
                if (temp[i + j] != generated_ca[j]) break;

            if (j == CA_bit_length) {
                in.close();
                cout << "For " << path << " PRN: " << prn << endl;
                return;
            }
        }
    }
    in.close();
}

void task_4() {
    cout << "Task 4\n";
    srand(time(NULL));
    Point orbit_centre { float(rand() % 100), float(rand() % 100), float(rand() % 100) },
            satellite_pos;
    auto angular_v = rand() % 100, t = rand() % 100;

    cout << "Input:\n" << left
        << setw(25) << "orbit centre:" << "(" << orbit_centre.x << "; " << orbit_centre.y << ")\n"
        << setw(25) << "radius:" << orbit_centre.r << endl
        << setw(25) << "angular_velocity:" << angular_v << endl
        << setw(25) << "time:" << t << endl << endl;

    satellite_pos.x = orbit_centre.x + orbit_centre.r * sin(angular_v * t);
    satellite_pos.y = orbit_centre.y + orbit_centre.r * cos(angular_v * t);

    cout << "Output:\n"
        << setw(25) << "satellite position:" << "(" << satellite_pos.x << "; " << satellite_pos.y << ")\n";
}

void task_5() {
    cout << "Task 5\n";

    Point fst_set { 
        float(rand() % 100), 
        float(rand() % 100), 
        float(rand() % 100)
        }, snd_set { 
        float(rand() % 100), 
        float(rand() % 100), 
        float(rand() % 100) 
        }, trd_set { 
        float(rand() % 100), 
        float(rand() % 100), 
        float(rand() % 100) 
    };
    
    double x, y;
    
    x = ((snd_set.y - fst_set.y) * (snd_set.r * snd_set.r - trd_set.r * trd_set.r - snd_set.y * snd_set.y + trd_set.y * trd_set.y - snd_set.x * snd_set.x + trd_set.x * trd_set.x)
            - (trd_set.y - snd_set.y) * (fst_set.r * fst_set.r - snd_set.r * snd_set.r - fst_set.y * fst_set.y + snd_set.y * snd_set.y - fst_set.x * fst_set.x + snd_set.x * snd_set.x))
                    / (2 * ((trd_set.y - snd_set.y) * (fst_set.x - snd_set.x) - (snd_set.y - fst_set.y) * (snd_set.x - trd_set.x)));
    y = ((snd_set.x - fst_set.x) * (snd_set.r * snd_set.r - trd_set.r * trd_set.r - snd_set.x * snd_set.x + trd_set.x * trd_set.x - snd_set.y * snd_set.y + trd_set.y * trd_set.y)
            - (trd_set.x - snd_set.x) * (fst_set.r * fst_set.r - snd_set.r * snd_set.r - fst_set.x * fst_set.x + snd_set.x * snd_set.x - fst_set.y * fst_set.y + snd_set.y * snd_set.y))
                    / (2 * ((trd_set.x - snd_set.x) * (fst_set.y - snd_set.y) - (snd_set.x - fst_set.x) * (snd_set.y - trd_set.y)));

    cout << "Receiver position: "
        << "(" << x << "; " << y << ")\n";
}


bitset<rcode_bit_length> receive_ca_code(const typename CAGenerator::CA_code& ca_code) {
    bitset<rcode_bit_length> received_ca;

    for (size_t i = 0; i < CA_bit_length; i++)
        received_ca[i + nav_bit_length] = ca_code[i];

    auto nav = generate_nav();
    for (size_t i = 0; i < nav_bit_length; i++)
        received_ca[i] = nav[i];
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
    size_t offset;
    ofstream out;
    for (int i = 1; i < 33; i++) {
        CA_generator.set_satellite(i);
        auto received = receive_ca_code(CA_generator());

        out.open("./received_codes/" + to_string(i) + "_received.txt");
        out << N << endl;

        offset = i + (rcode_bit_length % (nav_bit_length + i));
        for (auto j = offset; j < received.size(); j++)
            out << received[j];
        for (int j = 0; j < N - 1; j++)
            out << received;
        for (size_t i = 0; i < offset; i++)
            out << received[i];

        out.close();
    }
}