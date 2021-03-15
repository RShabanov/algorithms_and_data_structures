#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <set>
using namespace std;

using ull = unsigned long long;


int get_collision_amount(char*, function<ull(const string&, size_t)>, size_t);
ull poly_hash(const string&, size_t);
ull ASCII_hash(const string&, size_t);
ull midsquare_hash(const string&, size_t);
ull hash_shift(const string&, size_t);
ull quick_pow(int, unsigned int);


int main(int argc, char* argv[]) {    
    if (argc > 1) {
        size_t n_bits = 0;
        cout << "Enter hash size: ";
        while (!(cin >> n_bits)) {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad input - enter hash size again: ";
        }
        
        for (int i = 1; i < argc; i++) {
            cout << "File: " << argv[i] << endl;
            cout << "Collision amount (" << argv[i] << ") using poly_hash:\t\t" 
                << get_collision_amount(argv[i], poly_hash, n_bits) << endl;
                
            cout << "Collision amount (" << argv[i] << ") using ASCII_hash:\t\t" 
                << get_collision_amount(argv[i], ASCII_hash, n_bits) << endl;
                
            cout << "Collision amount (" << argv[i] << ") using midsquare_hash:\t" 
                << get_collision_amount(argv[i], midsquare_hash, n_bits) << endl;
                
            cout << "Collision amount (" << argv[i] << ") using hash_shift:\t\t" 
                << get_collision_amount(argv[i], hash_shift, n_bits) << endl << endl;
        }
    }
    
    else cerr << "Error! There must be a file path" << endl;
    
    return 0;
}


int get_collision_amount(char* filepath, 
                         function<ull(const string&, size_t)> fun_hash, 
                         size_t hash_size) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "File cannot be opened\n";
        throw;
    }

    int collisions = 0;
    set<ull> keys_set;
    string key;
    while (file >> key)
        collisions += !keys_set.emplace(fun_hash(key, hash_size)).second;
    
    return collisions;
}


ull ASCII_hash(const string& key, size_t hash_bit) {
    ull sum = 0;
    for (auto ch : key) sum += ch;
    return sum % (1 << hash_bit);
}


ull poly_hash(const string& key, size_t hash_bit) {
    ull sum = 0;
    for (unsigned int i = 0; i < key.size();) 
        sum += quick_pow(key[i], ++i);
    return sum % (1 << hash_bit);
}

ull midsquare_hash(const string& key, size_t hash_bit) {
    auto hash_sum = ASCII_hash(key, hash_bit);
    hash_sum *= hash_sum;
    
    size_t sum_bits = sizeof(hash_sum) << 3;
    if (sum_bits > (1 << hash_bit)) 
        return hash_sum;
    
    hash_bit >>= 1;
    sum_bits >>= 1;
    
    ull sum = 0;
//     from midsquare_hash / 2 - hash_bit / 2 to midsquare_hash / 2 + hash_bit / 2
    for (size_t idx_bit = sum_bits - hash_bit; idx_bit <= sum_bits + hash_bit; idx_bit++)
        sum += hash_sum & ull(1 << idx_bit);    

    return sum % (1 << hash_bit); // in case sum > hash_size
}

ull hash_shift(const string& key, size_t hash_bit) {
    ull addr = 0;
    size_t i = 0;
    for (auto ch : key)
        addr ^= (ch >> i++);
    return addr % hash_bit;
}


ull quick_pow(int number, unsigned int power) {
    ull res = 1;
	while (power) {
		if (power & 1)
			res *= number;
		number *= number;
		power >>= 1;
	}
	return res;
}
