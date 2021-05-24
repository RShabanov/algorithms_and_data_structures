#ifndef TREES_NODE_H
#define TREES_NODE_H


template<typename data_type>
struct Node {
    data_type data;
    int height;
    Node<data_type>* left = nullptr, *right = nullptr;

    Node() = default;
    explicit Node(data_type _data) : data(_data), height(1) {}
};


#endif //TREES_NODE_H
