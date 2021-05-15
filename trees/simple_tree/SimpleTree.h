#ifndef TREES_SIMPLETREE_H
#define TREES_SIMPLETREE_H

#include "Node.h"


template<typename data_type>
class SimpleTree {
    Node<data_type>* root;

    Node<data_type>* remove_node(Node<data_type>*, data_type);
    data_type find_min(Node<data_type>*) const;
    data_type find_max(Node<data_type>*) const;
public:
    SimpleTree();
    explicit SimpleTree(data_type);
    explicit SimpleTree(Node<data_type>*);

    void insert(data_type);
    void insert(Node<data_type>*);

    bool seek(data_type) const;

    void remove(data_type);

    data_type min() const;
    data_type max() const;
};

template<typename data_type>
SimpleTree<data_type>::SimpleTree()
        : root() {}

template<typename data_type>
SimpleTree<data_type>::SimpleTree(data_type data) {
    root = new Node<data_type>(data);
}

template<typename data_type>
SimpleTree<data_type>::SimpleTree(Node<data_type>* node)
        : root(node){}

template<typename data_type>
void SimpleTree<data_type>::insert(data_type data) {
    auto new_node = new Node<data_type>(data);
    insert(new_node);
}

template<typename data_type>
void SimpleTree<data_type>::insert(Node<data_type>* new_node) {
    if (root == nullptr) {
        root = new_node;
        return;
    }

    Node<data_type>* current = root;
    while (true) {
        if (new_node->data < current->data) {
            if (current->left == nullptr) {
                current->left = new_node;
                break;
            }
            current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = new_node;
                break;
            }
            current = current->right;
        }
    }
}

template<typename data_type>
bool SimpleTree<data_type>::seek(data_type data) const {
    Node<data_type>* current = root;
    while (current != nullptr) {
        if (current->data == data)
            return true;

        if (data < current->data)
            current = current->left;
        else current = current->right;
    }
    return false;
}

template<typename data_type>
void SimpleTree<data_type>::remove(data_type data) {
    remove_node(root, data);
}

template<typename data_type>
Node<data_type>* SimpleTree<data_type>::remove_node(Node<data_type>* node, data_type data) {
    if (node == nullptr) return node;

    if (data < node->data)
        node->left = remove_node(node->left, data);
    else if (data > node->data)
        node->right = remove_node(node->right, data);
    else if (node->left != nullptr && node->right != nullptr) {
        node->data = find_min(node->right);
        node->right = remove_node(node->right, node->data);
    }
    else {
        Node<data_type>* temp_ptr;
        if (node->left != nullptr)
            temp_ptr = node->left;
        else temp_ptr = node->right;

        delete node;
        return temp_ptr;
    }
    return node;
}

template<typename data_type>
data_type SimpleTree<data_type>::find_min(Node<data_type>* node) const {
    auto current = node;
    while (current->left != nullptr)
        current = current->left;
    return current->data;
}

template<typename data_type>
data_type SimpleTree<data_type>::find_max(Node<data_type>* node) const {
    auto current = node;
    while (current->right != nullptr)
        current = current->right;
    return current->data;
}

template<typename data_type>
data_type SimpleTree<data_type>::min() const {
    return find_min(root);
}

template<typename data_type>
data_type SimpleTree<data_type>::max() const {
    return find_max(root);
}


#endif //TREES_SIMPLETREE_H
