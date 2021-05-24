#include <iostream>
#include <ctime>

#include "SimpleTree.h"
using namespace std;


void test_simple_tree();

int main() {
//    test_simple_tree();
    return 0;
}

void test_simple_tree() {
    srand(time(NULL));
    SimpleTree<int> tree;

    int value;
    cout << "Input: ";
    for (int i = 0; i < 10; i++) {
        value = i + rand() % 100;
        tree.insert(value);
        cout << value << " ";
    }
    cout << "\nTree: " << tree << endl;
    cout << "\nIs " << value << " in tree: " << std::boolalpha << tree.seek(value) << endl;

    tree.remove(value);

    cout << "Tree after removing one element: " << tree << endl;
}
