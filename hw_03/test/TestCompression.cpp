#include "doctest.h"
#include "HuffmanArchiver.h"

TEST_CASE("Compression test"){
    std::vector<char> unique_bytes;
    std::unordered_map<char, int32_t> frequency_table;

    SUBCASE("One symbol scenario"){
        unique_bytes.push_back('a');
        frequency_table['a'] = 100;

        HuffmanTree tree(unique_bytes, frequency_table);
        HuffmanArchiver archiver;

        std::unordered_map<char, std::string> compressed_data = archiver.compress(tree);

        CHECK(compressed_data['a'] == "0");
    }


    // Using data from tree testing.

    SUBCASE("Simple example"){

        for (size_t i = 0; i < 4; i++){
            unique_bytes.push_back('a' + i);
            frequency_table['a' + i] = i + 1;
        }

        HuffmanTree tree(unique_bytes, frequency_table);
        HuffmanArchiver archiver;

        std::unordered_map<char, std::string> compressed_data = archiver.compress(tree);

        CHECK(compressed_data['d'] == "0");
        CHECK(compressed_data['c'] == "11");
        CHECK(compressed_data['b'] == "101");
        CHECK(compressed_data['a'] == "100");

    }
}