#ifndef TREES_SIMPLETREE_H
#define TREES_SIMPLETREE_H

#include "Node.h"

#include<iostream>


template<typename data_type>
class SimpleTree {
    data_type find_min(Node<data_type>*) const;
    data_type find_max(Node<data_type>*) const;

    void delete_children(Node<data_type>*);

    void print_tree(const Node<data_type>*, std::ostream&) const;

protected:
    Node<data_type>* root;
    virtual Node<data_type>* remove_node(Node<data_type>*, data_type);
    virtual void insert_node(Node<data_type>* parent, Node<data_type>* new_node);

public:
    SimpleTree();
    explicit SimpleTree(data_type);
    explicit SimpleTree(Node<data_type>*);
    virtual ~SimpleTree();

    virtual void insert(data_type);
    virtual void insert(Node<data_type>*);

    bool seek(data_type) const;

    virtual void remove(data_type);

    data_type min() const;
    data_type max() const;

    int height() const;

    template<typename output_type> friend std::ostream& operator<<(std::ostream&, const SimpleTree<output_type>&);
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
        : root(node) {}

template<typename data_type>
SimpleTree<data_type>::~SimpleTree() {
    delete_children(root);
}

template<typename data_type>
void SimpleTree<data_type>::insert(data_type data) {
    auto new_node = new Node<data_type>(data);
    insert(new_node);
}

template<typename data_type>
void SimpleTree<data_type>::insert(Node<data_type>* new_node) {
    if (new_node == nullptr) return;

    if (root == nullptr) root = new_node;
    else insert_node(root, new_node);
}

template<typename data_type>
void SimpleTree<data_type>::insert_node(Node<data_type>* parent,
                                        Node<data_type>* new_node) {
    if (new_node->data < parent->data) {
        if (parent->left == nullptr)
            parent->left = new_node;
        else insert_node(parent->left, new_node);
    }
    else {
        if (parent->right == nullptr)
            parent->right = new_node;
        else insert_node(parent->right, new_node);
    }

    auto l_height = parent->left != nullptr ? parent->left->height : 0;
    auto r_height = parent->right != nullptr ? parent->right->height : 0;

    parent->height = 1 + (l_height < r_height ? r_height : l_height);
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

template<typename data_type>
void SimpleTree<data_type>::delete_children(Node<data_type>* node) {
    if (node == nullptr) return;

    if (node->left != nullptr) delete_children(node->left);
    if (node->right != nullptr) delete_children(node->right);
    delete node;
}

template<typename output_type>
std::ostream& operator<<(std::ostream& out, const SimpleTree<output_type>& tree) {
    tree.print_tree(tree.root, out);
    return out;
}

template<typename data_type>
void SimpleTree<data_type>::print_tree(const Node<data_type>* node, std::ostream& out) const {
    if (node == nullptr) return;

    if (node->left != nullptr) print_tree(node->left, out);
    out << node->data << " ";
    if (node->right != nullptr) print_tree(node->right, out);
}

template<typename data_type>
int SimpleTree<data_type>::height() const {
    return root->height;
}


#endif //TREES_SIMPLETREE_H
