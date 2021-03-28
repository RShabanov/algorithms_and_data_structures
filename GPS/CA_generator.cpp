#include "CA_generator.h"

#include <iostream>
#include <bitset>
#include <ctime>

using namespace std;

CAGenerator::CAGenerator(size_t _PRN_id) : PRN_id(_PRN_id), was_generated(false) {
    if (PRN_id > PRN_id_size) {
        cerr << "There are only 32 PRN ids!" << endl;
        throw;
    }
}

CAGenerator::CA_code CAGenerator::operator()() { 
    // to avoid generating the same code all the time we call this function
    if (was_generated) return code;
    else {
        G1_generator(code);
        G2_generator(code);
        was_generated = true;
        return code;
    }
}

void CAGenerator::G1_generator(CAGenerator::CA_code& _code) {
    // G1 = 1 ^ x_3 ^ x_10
    
    bitset<10> G1 { 0b1111111111 };
    bitset<1> G1_res { 0 };
    
    size_t i = CA_bit_length;
    do {
        _code[--i] = G1[0];
        G1_res[0] = G1[7] ^ G1[0];
        G1 >>= 1;
        G1[9] = G1_res[0];
    } while (G1 != 0b1111111111);
}

void CAGenerator::G2_generator(CAGenerator::CA_code& _code) {
    // G2 = 1 ^ x_2 ^ x_3 ^ x_6 ^ x_8 ^ x_9 ^  x_10

    bitset<10> G2 { 0b1111111111 };
    bitset<1> G2_res { 0 };
    
    size_t i = CA_bit_length;
    do {
        i--;
        _code[i] = _code[i] ^ G2[10 - PRN_ids[PRN_id].first] ^ G2[10 - PRN_ids[PRN_id].second];
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
        code.reset();
        PRN_id = _PRN_id;
        was_generated = false;
    }
}


bitset<nav_bit_length> generate_nav() {
    return bitset<nav_bit_length>();
}