#include "doctest.h"
#include "Huffman.h"
#include <sstream>
#include <iostream>


TEST_CASE("End-to-end"){
    Huffman huffman;
    (void) huffman;

    std::stringstream input_stream, output_stream, result_stream;

    SUBCASE("Random string."){
        input_stream << "Hello World! \n It's such a wonderful, wondeful place to live in! \n";

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        CHECK(input_stream.str() == result_stream.str());
    }

    SUBCASE("One symbol."){
        input_stream << "                                  ";

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        CHECK(input_stream.str() == result_stream.str());
    }

    SUBCASE("No data at all."){

        huffman.save(input_stream, output_stream);
        huffman.load(output_stream, result_stream);

        CHECK(input_stream.str() == result_stream.str());
    }
}