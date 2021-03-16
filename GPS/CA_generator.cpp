#include <iostream>
#include <bitset>

using namespace std;


class CAGenerator {
public:
    using CA_code = bitset<1023>;
    
    CAGenerator() = default;
    ~CAGenerator() = default;
    
    CA_code operator()();
    
private:
    CA_code G1_generator();
    CA_code G2_generator();
};




int main() {
    CAGenerator CA_generator;
    cout << CA_generator() << endl;
    return 0;
}


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

    CA_code code;
    bitset<10> G2 { 0b1111111111 };
    
    size_t i = 0;
    do {
        bool G2_res = G2[8] ^ G2[7] ^ G2[4] ^ G2[2] ^ G2[1] ^ G2[0];
        G2 >>= 1;
        G2[9] = G2_res;
        code[i++] = G2[8] ^ G2[4];
    } while (G2 != 0b1111111111);
    
    return code;
}
