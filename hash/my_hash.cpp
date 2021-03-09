#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;


int get_collision_amount(char*, unsigned long long(*)(const string&));
unsigned long long poly_hash(const string&);
unsigned long long ASCII_hash(const string&);
unsigned long long quick_pow(int, unsigned int);


int main(int argc, char* argv[]) {
    if (argc > 1)      
        for (int i = 1; i < argc; i++) {
            cout << "File: " << argv[i] << endl;
            cout << "Collision amount (" << argv[i] << ") using poly_hash:\t" 
                << get_collision_amount(argv[i], poly_hash) << endl;
                
            cout << "Collision amount (" << argv[i] << ") using ASCII_hash:\t" 
                << get_collision_amount(argv[i], ASCII_hash) << endl << endl;
        }
    
    else cerr << "Error! There mush be a file path" << endl;
    
    return 0;
}


int get_collision_amount(char* filepath, unsigned long long(*fun_hash)(const string&)) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "File cannot be opened\n";
        throw;
    }

    int collisions = 0;
    set<unsigned long long> keys_set;
    string key;
    while (file >> key)
        collisions += keys_set.emplace(fun_hash(key)).second;
    
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
