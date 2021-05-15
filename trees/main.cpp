#include <iostream>
#include <ctime>

#include "SimpleTree.h"
using namespace std;

int main() {
    srand(time(NULL));
    SimpleTree<int> tree;

    int value;
    for (int i = 0; i < 10; i++) {
        value = i + rand() % 100;
        tree.insert(value);
        cout << value << " ";
    }

    cout << "\nIs " << value << " in tree: " << std::boolalpha << tree.seek(value) << endl;

    tree.remove(value);
    return 0;
}
