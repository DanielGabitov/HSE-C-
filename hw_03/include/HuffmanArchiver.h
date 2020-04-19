
#pragma once

#include <fstream>
#include "HuffmanTree.h"
#include <string>

class HuffmanArchiver{ 
public:
    std::unordered_map<char, std::string> compress(HuffmanTree &tree);

    std::unordered_map<std::string, char> extract(HuffmanTree &tree);

private:
    void dfs_to_compress(
        std::unordered_map<char, std::string> &new_bytes, HuffmanNode &node, std::string &code);

    void dfs_to_extract(
        std::unordered_map<std::string, char> &new_bytes, HuffmanNode &node, std::string &code);

};