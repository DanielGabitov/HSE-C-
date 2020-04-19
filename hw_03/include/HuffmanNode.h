#pragma once
#include <cstdio>


class HuffmanNode{
public:
    HuffmanNode(size_t weight, char data);
    HuffmanNode(size_t weight, HuffmanNode *left, HuffmanNode *right);
    size_t get_weight() const {return weight;};
    bool has_data() const {return left_node == nullptr and right_node == nullptr;};
    char get_data() const {return data;};
    HuffmanNode* get_left_node(){return left_node;};
    HuffmanNode* get_right_node(){return right_node;};
private:
    size_t weight;
    HuffmanNode *left_node;
    HuffmanNode *right_node;
    char data;
};