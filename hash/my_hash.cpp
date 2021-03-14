#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <set>
using namespace std;


int get_collision_amount(char*, function<unsigned long long(const string&)>, size_t);
unsigned long long poly_hash(const string&);
unsigned long long ASCII_hash(const string&);
unsigned long long quick_pow(int, unsigned int);


int main(int argc, char* argv[]) {
    if (argc > 1) {
        size_t hash_size = 0;
        cout << "Enter hash size: ";
        while (!(cin >> hash_size)) {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Bad input - enter hash size again: ";
        }
        
        for (int i = 1; i < argc; i++) {
            cout << "File: " << argv[i] << endl;
            cout << "Collision amount (" << argv[i] << ") using poly_hash:\t" 
                << get_collision_amount(argv[i], poly_hash, hash_size) << endl;
                
            cout << "Collision amount (" << argv[i] << ") using ASCII_hash:\t" 
                << get_collision_amount(argv[i], ASCII_hash, hash_size) << endl << endl;
        }
    }
    
    else cerr << "Error! There must be a file path" << endl;
    
    return 0;
}


int get_collision_amount(char* filepath, 
                         function<unsigned long long(const string&)> fun_hash, 
                         size_t hash_size) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "File cannot be opened\n";
        throw;
    }

    int collisions = 0;
    set<unsigned long long> keys_set;
    string key;
    while (file >> key)
        collisions += !keys_set.emplace(fun_hash(key) % hash_size).second;
    
    return collisions;
}


unsigned long long ASCII_hash(const string& key) {
    unsigned long long sum = 0;
    for (auto ch : key) sum += ch;
    return sum;
}


unsigned long long poly_hash(const string& key) {
    unsigned long long sum = 0;
    for (unsigned int i = 0; i < key.size();) 
        sum += quick_pow(key[i], ++i);
    return sum;
}


unsigned long long quick_pow(int number, unsigned int power) {
    unsigned long long res = 1;
	while (power) {
		if (power & 1)
			res *= number;
		number *= number;
		power >>= 1;
	}
	return res;
}
