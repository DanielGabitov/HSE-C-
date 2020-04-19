#include "../include/HuffmanNode.h"

HuffmanNode::HuffmanNode(size_t weight , char data)
  : weight(weight)
  , left_node()
  , right_node()
  , data(data)
{}

HuffmanNode::HuffmanNode(size_t weight, HuffmanNode *left, HuffmanNode *right)
  : weight(weight)
  , left_node(left)
  , right_node(right)
  , data()
{}
