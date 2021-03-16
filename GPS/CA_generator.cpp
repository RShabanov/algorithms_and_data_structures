#include <iostream>
#include <bitset>

using namespace std;


class CAGenerator {
public:
    using CA_code = bitset<1023>;
    
    CAGenerator(size_t);
    ~CAGenerator() = default;
    
    CA_code operator()();
    
private:
    size_t PRN_id;
    
    CA_code G1_generator();
    CA_code G2_generator();
    
    pair<size_t, size_t> PRN_ids[32];
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
}, PRN_id(_PRN_id) {}

CAGenerator::CA_code CAGenerator::operator()() { return G1_generator() ^ G2_generator(); }

CAGenerator::CA_code CAGenerator::G1_generator() {
    // G1 = 1 ^ x_3 ^ x_10
    
    CA_code code;
    bitset<10> G1 { 0b1111111111 };
    
    size_t i = 0;
    do {
        bool G1_res = G1[7] ^ G1[0];
        G1 >>= 1;
        G1[9] = G1_res;
        code[i++] = G1[0];
    } while (G1 != 0b1111111111);
    
    return code;
}

CAGenerator::CA_code CAGenerator::G2_generator() {
    // G2 = 1 ^ x_2 ^ x_3 ^ x_6 ^ x_8 ^ x_9 ^  x_10
    // Номер спутника пока что забит программно
    // В bitset нумерация индексов идет <-:
    //  9 8 7 6 5 4 3 2 1
    //  0 0 1 0 1 1 0 1 1

    CA_code code;
    bitset<10> G2 { 0b1111111111 };
    
    size_t i = 0;
    do {
        bool G2_res = G2[8] ^ G2[7] ^ G2[4] ^ G2[2] ^ G2[1] ^ G2[0];
        G2 >>= 1;
        G2[9] = G2_res;
        code[i++] = G2[PRN_ids[PRN_id].first - 1] ^ G2[PRN_ids[PRN_id].second - 1];
    } while (G2 != 0b1111111111);
    
    return code;
}
