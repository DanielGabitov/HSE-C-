#pragma once

#include "../include/HuffmanNode.h"
#include <fstream>
#include <unordered_map>
#include <vector>

class HuffmanTree{
public:
    HuffmanTree(std::vector<char> &unique_bytes, std::unordered_map<char, int32_t> &frequency_table);
    HuffmanNode* get_root() const {return root;};
private:
  bool compare_two_nodes_by_weight(int index_of_first_node, int index_of_second_node) const;
  void merge_two_nodes(int index_of_first_node, int index_of_second_node);
private:
  HuffmanNode *root;
  std::vector<HuffmanNode> nodes;
};
