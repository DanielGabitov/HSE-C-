#include "../include/HuffmanTree.h"
#include "algorithm"
#include <deque>

namespace{

template <typename T>
T get_and_pop_front_in_deque(std::deque<T> &deque){
    T front_value = deque.front();
    deque.pop_front();
    return front_value;
}
} // anonymous namespace ends.

// return true if 1st node's weight is min out of two
bool HuffmanTree::compare_two_nodes_by_weight(int index_of_first_node, int index_of_second_node) const{
    return nodes[index_of_first_node]->get_weight() < nodes[index_of_second_node]->get_weight();
}

void HuffmanTree::merge_two_nodes(int index_of_first_node, int index_of_second_node){

    HuffmanNode *new_node = new HuffmanNode(nodes[index_of_first_node]->get_weight() + nodes[index_of_second_node]->get_weight(),
        nodes[index_of_first_node], nodes[index_of_second_node]);
    
    nodes.push_back(new_node);
}


HuffmanTree::HuffmanTree(std::vector<char> &unique_bytes, const std::unordered_map<char, int32_t> &frequency_table)
    : root()
    , nodes(){

  // sort by frequency
    std::sort(unique_bytes.begin(), unique_bytes.end(), 
        [&frequency_table](const char &a, const char &b){return (frequency_table.find(a)->second < frequency_table.find(b)->second);});

    // add data to nodes
    for (char byte : unique_bytes){
        nodes.push_back(new HuffmanNode(frequency_table.find(byte)->second, byte));
    }

    // Special case
    if (nodes.size() == 1){
        root = nodes[nodes.size() - 1];
        one_symbol_case = true;
        return;
    }

    // Реализация Хаффмана через две очереди за линию
    std::deque<int> first_queue(nodes.size()); // в очередях хранятся индексы вектора nodes
    std::deque<int> second_queue;

    for (size_t i = 0; i < nodes.size(); i++){
        first_queue[i] = i;
    }
  
    while (!first_queue.empty()){
        // pick 2 nodes with min weight and merge them
        int first_node_index;
        int second_node_index;

        // take fist node index
        if (second_queue.empty()){

            first_node_index = get_and_pop_front_in_deque<int>(first_queue);

        } else {

            first_node_index = (compare_two_nodes_by_weight(first_queue.front(), second_queue.front())) ? 
                get_and_pop_front_in_deque<int>(first_queue) : get_and_pop_front_in_deque<int>(second_queue);
        }

    // take second node index
    if (second_queue.empty()){

        second_node_index = get_and_pop_front_in_deque<int>(first_queue);

    } else if (first_queue.empty()){

        second_node_index = get_and_pop_front_in_deque<int>(second_queue);

    } else {

        second_node_index = (compare_two_nodes_by_weight(first_queue.front(), second_queue.front())) ? 
            get_and_pop_front_in_deque<int>(first_queue) : get_and_pop_front_in_deque<int>(second_queue); 
  
    }
        // Merge
        merge_two_nodes(first_node_index, second_node_index);
        second_queue.push_back(nodes.size() - 1);
    }

    // free second queue untill theres only root left or none

    while (second_queue.size() > 1){
        int first_node_index = get_and_pop_front_in_deque(second_queue);
        int second_node_index = get_and_pop_front_in_deque(second_queue);

        merge_two_nodes(first_node_index, second_node_index);
        second_queue.push_back(nodes.size() - 1);
    }
    // pick a root.
    root = nodes[nodes.size() - 1];
}

HuffmanTree::~HuffmanTree() {
    for (HuffmanNode *elem : nodes){
        delete elem;
    }
}
