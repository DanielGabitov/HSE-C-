#include "../include/Parser.h"
#include <cassert>
#include <algorithm>
#include "../include/Huffman.h"


// Парсит консольные данные.
Parser::Parser(int argc, char **argv) {

    assert(argc > 5);

    action  = *(*(argv + 1) + 1);
    first_file_flag = *(*(argv + 2) + 1);
    first_file_name = *(argv + 3);
    second_file_flag = *(*(argv + 4) + 1);
    second_file_name = *(argv + 5);

//    action  = 'c';
//    first_file_flag = 'f';
//    first_file_name = "test.txt";
//    second_file_flag = 'o';
//    second_file_name = "test_out.bin" ;


    if (first_file_flag != 'f'){
        std::swap(first_file_flag, second_file_flag);
        std::swap(first_file_name, second_file_name);
    }

    // assert(first_file_flag == 'f');
    // assert(second_file_flag == 'o');
    // assert(action == 'c' or action == 'u');
}

void Parser::do_command() {

    std::ofstream output_stream;
    std::ifstream input_stream;
    output_stream.open(second_file_name, std::ios::binary);
    input_stream.open(first_file_name, std::ios::binary);

    assert(output_stream.is_open());
    assert(input_stream.is_open());

    Huffman huffman;

    switch (action){

        case 'c':
            huffman.save(input_stream, output_stream);
            break;

        case 'u':
            huffman.load(input_stream, output_stream);

        default:
            break;
    }
}