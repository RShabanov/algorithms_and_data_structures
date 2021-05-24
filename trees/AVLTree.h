#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include "Node.h"
#include "SimpleTree.h"


template<typename data_type>
class AVLTree : public SimpleTree<data_type> {
    Node<data_type>* left_rotation(Node<data_type>* root_node,
                       Node<data_type>* parent) const;
    Node<data_type>* right_rotation(Node<data_type>* root_node,
                        Node<data_type>* parent) const;

    Node<data_type>* big_right_rotation(Node<data_type>* root_node,
                            Node<data_type>* parent) const;
    Node<data_type>* big_left_rotation(Node<data_type>* root_node,
                           Node<data_type>* parent) const;

    virtual void insert_node(Node<data_type>* root_node,
                             Node<data_type>* parent,
                             Node<data_type>* new_node);

    virtual void remove_node(Node<data_type>* root_node,
                             Node<data_type>* parent,
                             Node<data_type>* new_node);

    int get_child_height(Node<data_type>*) const;
    int get_node_height(Node<data_type>*) const;

    void balance(Node<data_type>* root_node,
                 Node<data_type>* parent);
public:
    AVLTree();
    explicit AVLTree(data_type);
    explicit AVLTree(Node<data_type>*);
    virtual ~AVLTree();

    void insert(data_type) override;
    void insert(Node<data_type>*) override;
    void remove(data_type) override;
};


template<typename data_type>
AVLTree<data_type>::AVLTree()
        : SimpleTree<data_type>() {}

template<typename data_type>
AVLTree<data_type>::AVLTree(data_type data)
    : SimpleTree<data_type>(data) {}

template<typename data_type>
AVLTree<data_type>::AVLTree(Node<data_type>* node)
        : SimpleTree<data_type>(node) {}

template<typename data_type>
AVLTree<data_type>::~AVLTree() {}

template<typename data_type>
Node<data_type>* AVLTree<data_type>::left_rotation(Node<data_type>* root_node,
                                                   Node<data_type>* parent) const {
    auto pivot_node = root_node->right;
    root_node->right = pivot_node->left;
    pivot_node->left = root_node;

    root_node->height = get_node_height(root_node);
    pivot_node->height = get_node_height(pivot_node);

    if (parent != nullptr) {
        if (parent->left == root_node) parent->left = pivot_node;
        else parent->right = pivot_node;

        parent->height = get_node_height(parent);
    }

    return pivot_node;
}

template<typename data_type>
Node<data_type>* AVLTree<data_type>::right_rotation(Node<data_type>* root_node,
                                                    Node<data_type>* parent) const {
    auto pivot_node = root_node->left;
    root_node->left = pivot_node->right;
    pivot_node->right = root_node;

    root_node->height = get_node_height(root_node);
    pivot_node->height = get_node_height(pivot_node);

    if (parent != nullptr) {
        if (parent->left == root_node) parent->left = pivot_node;
        else parent->right = pivot_node;

        parent->height = get_node_height(parent);
    }

    return pivot_node;
}

template<typename data_type>
Node<data_type>* AVLTree<data_type>::big_right_rotation(Node<data_type>* root_node,
                                                        Node<data_type>* parent) const {
    left_rotation(root_node->left, root_node);
    return right_rotation(root_node, parent);
}

template<typename data_type>
Node<data_type>* AVLTree<data_type>::big_left_rotation(Node<data_type>* root_node,
                                                       Node<data_type>* parent) const {
    right_rotation(root_node->right, root_node);
    return left_rotation(root_node, parent);
}

template<typename data_type>
void AVLTree<data_type>::insert(data_type data) {
    auto new_node = new Node<data_type>(data);
    insert(new_node);
}

template<typename data_type>
void AVLTree<data_type>::insert(Node<data_type>* new_node) {
    if (new_node == nullptr) return;

    if (SimpleTree<data_type>::root == nullptr)
        SimpleTree<data_type>::root = new_node;
    else
        insert_node(SimpleTree<data_type>::root, nullptr, new_node);
}

template<typename data_type>
void AVLTree<data_type>::insert_node(Node<data_type>* root_node,
                                     Node<data_type>* parent,
                                     Node<data_type>* new_node) {
    if (new_node->data < root_node->data) {
        if (root_node->left == nullptr)
            root_node->left = new_node;
        else insert_node(root_node->left, root_node, new_node);
    }
    else {
        if (root_node->right == nullptr)
            root_node->right = new_node;
        else insert_node(root_node->right, root_node, new_node);
    }

    balance(root_node, parent);
}

template<typename data_type>
int AVLTree<data_type>::get_child_height(Node<data_type>* node) const {
    return node != nullptr ? node->height : 0;
}

template<typename data_type>
int AVLTree<data_type>::get_node_height(Node<data_type>* node) const {
    return 1 + (get_child_height(node->left) > get_child_height(node->right) ?
                get_child_height(node->left) : get_child_height(node->right));
}

template<typename data_type>
void AVLTree<data_type>::balance(Node<data_type>* root_node,
                                 Node<data_type>* parent) {
    auto l_height = get_child_height(root_node->left);
    auto r_height = get_child_height(root_node->right);

    root_node->height = 1 + (l_height < r_height ? r_height : l_height);
    Node<data_type>* temp_node_ptr = nullptr;

    if (l_height - r_height > 1) {
        // left subtree is bigger
        l_height = get_child_height(root_node->left->left);
        r_height = get_child_height(root_node->left->right);

        if (r_height <= l_height)
            temp_node_ptr = right_rotation(root_node, parent);
        else
            temp_node_ptr = big_right_rotation(root_node, parent);

        if (parent == nullptr) SimpleTree<data_type>::root = temp_node_ptr;

    }
    else if (r_height - l_height > 1) {
        // right subtree is bigger
        l_height = get_child_height(root_node->right->left);
        r_height = get_child_height(root_node->right->right);

        if (l_height <= r_height)
            temp_node_ptr = left_rotation(root_node, parent);
        else temp_node_ptr = big_left_rotation(root_node, parent);

        if (parent == nullptr) SimpleTree<data_type>::root = temp_node_ptr;
    }
}

template<typename data_type>
void AVLTree<data_type>::remove(data_type data) {
    remove_node(SimpleTree<data_type>::root, nullptr, data);
}

template<typename data_type>
void AVLTree<data_type>::remove_node(Node<data_type> *root_node,
                                     Node<data_type> *parent,
                                     Node<data_type> *new_node) {
    // will finish later
    // I have a headache :)
}


#endif //TREES_AVLTREE_H
