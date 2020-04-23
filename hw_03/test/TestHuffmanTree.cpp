#include "doctest.h"
#include "HuffmanTree.h"
#include <unordered_map>

namespace {
    void do_simple_test(HuffmanNode *node){

        // now we have to check all 7 nodes.
        CHECK (node->get_weight() == 10);
        CHECK (node->has_data() == false);

        //               ---------               //
        HuffmanNode *left_child = node->get_left_node();
        HuffmanNode *right_child = node->get_right_node();

        CHECK(left_child->has_data() == true);
        CHECK(left_child->get_data() == 'd');
        CHECK(left_child->get_weight() == 4);

        CHECK(right_child->has_data() == false);
        CHECK(right_child->get_weight() == 6);

        CHECK(left_child->get_left_node() == nullptr);
        CHECK(left_child->get_right_node() == nullptr);

        //               ---------               //
        left_child = right_child->get_left_node();
        right_child = right_child->get_right_node();


        CHECK(right_child->has_data() == true);
        CHECK(right_child->get_data() == 'c');
        CHECK(right_child->get_weight() == 3);

        CHECK(left_child->has_data() == false);
        CHECK(left_child->get_weight() == 3);

        CHECK(right_child->get_left_node() == nullptr);
        CHECK(right_child->get_right_node() == nullptr);

        //               ---------               //
        right_child = left_child->get_right_node();
        left_child = left_child->get_left_node();

        CHECK(left_child->has_data() == true);
        CHECK(left_child->get_data() == 'a');
        CHECK(left_child->get_weight() == 1);

        CHECK(right_child->has_data() == true);
        CHECK(right_child->get_data() == 'b');
        CHECK(right_child->get_weight() == 2);

        CHECK(right_child->get_left_node() == nullptr);
        CHECK(right_child->get_right_node() == nullptr);

        CHECK(left_child->get_left_node() == nullptr);
        CHECK(left_child->get_right_node() == nullptr);
    }
} // Anonymous namespace ends.

TEST_CASE("Testing huffman Tree"){
    std::vector<char> unique_bytes;
    std::unordered_map<char, int32_t> frequency_table;

    SUBCASE("One symbol"){
        unique_bytes.push_back('a');
        frequency_table['a'] = 1;

        HuffmanTree tree(unique_bytes, frequency_table);

        CHECK(tree.get_root()->get_data() == 'a');
    }

    SUBCASE("Simple example"){

        for (size_t i = 0; i < 4; i++){
            unique_bytes.push_back('a' + i);
            frequency_table['a' + i] = i + 1;
        }

        HuffmanTree tree(unique_bytes, frequency_table);

        do_simple_test(tree.get_root());

    }

    SUBCASE("Simple example but bytes are not sorted"){
        unique_bytes.push_back('d');
        unique_bytes.push_back('a');
        unique_bytes.push_back('c');
        unique_bytes.push_back('b');

        frequency_table['a'] = 1;
        frequency_table['b'] = 2;
        frequency_table['c'] = 3;
        frequency_table['d'] = 4;

        HuffmanTree tree(unique_bytes, frequency_table);

        do_simple_test(tree.get_root());
    }
}