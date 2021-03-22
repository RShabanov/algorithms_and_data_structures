#include <iostream>
#include <bitset>

using namespace std;


class CAGenerator {
public:
    using CA_code = bitset<1023>;
    
    CAGenerator(size_t);
    ~CAGenerator() = default;
    
    CA_code operator()();

    void set_satellite(size_t);
    
private:
    CA_code code;
    size_t PRN_id;
    static const size_t PRN_id_size = 32;
    
    void G1_generator(CA_code&);
    void G2_generator(CA_code&);
    
    pair<size_t, size_t> PRN_ids[PRN_id_size];
};




int main() {
    size_t PRN_id;
    cout << "Enter PRN id: ";
    while (!(cin >> PRN_id)) {
        cout << "Bad input!\nEnter PRN id, again: ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    CAGenerator CA_generator(PRN_id - 1);
    cout << "CA code for satellite with PRN id (" << PRN_id << "): " << CA_generator() << endl;
    return 0;
}



CAGenerator::CAGenerator(size_t _PRN_id) : PRN_ids {
    {2, 6}, {3, 7}, {4, 8}, {5, 9}, {1, 9}, {2, 10}, {1, 8}, {2, 9}, 
    {3, 10}, {2, 3}, {3, 4}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 10}, 
    {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 9}, {1, 3}, {4, 6}, 
    {5, 7}, {6, 8}, {7, 9}, {8, 10}, {1, 6}, {2, 7}, {3, 8}, {4, 9}
}, PRN_id(_PRN_id) {
    if (PRN_id > PRN_id_size) {
        cerr << "There are only 32 PRN ids!" << endl;
        throw;
    }
}

CAGenerator::CA_code CAGenerator::operator()() { 
    G1_generator(code);
    G2_generator(code);
    return code;
}

void CAGenerator::G1_generator(CAGenerator::CA_code& code) {
    // G1 = 1 ^ x_3 ^ x_10
    
    bitset<10> G1 { 0b1111111111 };
    bitset<1> G1_res { 0 };
    
    size_t i = 1023;
    do {
        code[--i] = G1[0];
        G1_res[0] = G1[7] ^ G1[0];
        G1 >>= 1;
        G1[9] = G1_res[0];
    } while (G1 != 0b1111111111);
}

void CAGenerator::G2_generator(CAGenerator::CA_code& code) {
    // G2 = 1 ^ x_2 ^ x_3 ^ x_6 ^ x_8 ^ x_9 ^  x_10

    bitset<10> G2 { 0b1111111111 };
    bitset<1> G2_res { 0 };
    
    size_t i = 1023;
    do {
        i--;
        code[i] = code[i] ^ G2[10 - PRN_ids[PRN_id].first] ^ G2[10 - PRN_ids[PRN_id].second];
        G2_res[0] = G2[8] ^ G2[7] ^ G2[4] ^ G2[2] ^ G2[1] ^ G2[0];
        G2 >>= 1;
        G2[9] = G2_res[0];
    } while (G2 != 0b1111111111);
}

void CAGenerator::set_satellite(size_t _PRN_id) {
    if (PRN_id == _PRN_id) return;
    if (_PRN_id > PRN_id_size) {
        cerr << "There are only 32 PRN ids!" << endl;
        throw;
    }
    else {
        code.set();
        PRN_id = _PRN_id;
    }
}
