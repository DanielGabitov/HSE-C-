#include "doctest.h"
#include "Huffman.h"
#include <sstream>
#include <iostream>

namespace{
    void compare_string_streams(std::stringstream &a, std::stringstream &b){
        char init_byte, res_byte;
        while (a.read(&init_byte, sizeof(char))){
            b.read(&res_byte, sizeof(char));
            CHECK(res_byte == init_byte);
        }

        b >> res_byte;
        CHECK(b.eof());
    }
} // anonymous namepspace ends.


TEST_CASE("End-to-end"){
    Huffman huffman;
    (void) huffman;

    std::stringstream input_stream, output_stream, result_stream;

    SUBCASE("Random string."){
        input_stream << "Hello World! \n It's such a wonderful, wondeful place to live in! \n";

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        compare_string_streams(input_stream, result_stream);
    }

    SUBCASE("One symbol."){
        input_stream << "                                  ";

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        compare_string_streams(input_stream, result_stream);
    }

    SUBCASE("No data at all."){

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        compare_string_streams(input_stream, result_stream);
    }
}