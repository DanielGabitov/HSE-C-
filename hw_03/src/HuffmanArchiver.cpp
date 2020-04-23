#include "../include/HuffmanArchiver.h"

// match symbol to new string.
void HuffmanArchiver::dfs_to_compress(std::unordered_map<char, std::string> &new_bytes, HuffmanNode *node, std::string &code){

    if (node == nullptr){
        return;
    }

    if (node->has_data()){
        new_bytes[node->get_data()] = code;
        return;
    }

    code.push_back('0');
    dfs_to_compress(new_bytes, node->get_left_node(), code);
    code.pop_back();
    
    code.push_back('1');
    dfs_to_compress(new_bytes, node->get_right_node(), code);
    code.pop_back();
}

void HuffmanArchiver::dfs_to_extract(
        std::unordered_map<std::string, char> &bytes, HuffmanNode *node, std::string &code){
    
    if (node == nullptr){
        return;
    }

    if (node->has_data()){
        bytes[code] = node->get_data();
        return;
    }

    code.push_back('0');
    dfs_to_extract(bytes, node->get_left_node(), code);
    code.pop_back();
    
    code.push_back('1');
    dfs_to_extract(bytes, node->get_right_node(), code);
    code.pop_back();
}

// returns new bytes table.
std::unordered_map<char, std::string> HuffmanArchiver::compress(HuffmanTree &tree){

    std::unordered_map<char, std::string> encoded_bytes;

    // in case there has been only 1 symbol, we need root to have a code.
    std::string code = (tree.is_one_symbol_case()) ? "0" : std::string();

    dfs_to_compress(encoded_bytes, tree.get_root(), code);
    return encoded_bytes;
}

// return extracted table.
std::unordered_map<std::string, char> HuffmanArchiver::extract(HuffmanTree &tree){

    std::unordered_map<std::string, char> extracted_bytes;

    // in case there has been only 1 symbol, we need root to have a code.
    std::string code = (tree.is_one_symbol_case()) ? "0" : std::string();

    dfs_to_extract(extracted_bytes, tree.get_root(), code);
    return extracted_bytes;
}