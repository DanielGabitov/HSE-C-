#include "../include/Huffman.h"
#include <iostream>
#include <cassert>
#include <string>
#include "../include/Parser.h"
#include <fstream>
#include "../include/ParserExceptions.h"

int main(int argc, char *argv[]){

    char *input_file_name;
    char *output_file_name;
    std::string action;

    try {
        Parser parser(argc, argv);
        input_file_name = parser.get_input_file_name();
        output_file_name = parser.get_output_file_name();
        action = parser.get_action(); 
    } catch (const ParserExceptions &exception){
        std::cout << exception.what() << '\n';
        return EXIT_FAILURE;
    }

    std::ofstream output_stream;
    std::ifstream input_stream;

    output_stream.open(output_file_name);
    input_stream.open(input_file_name);

    if (!input_stream.is_open() or !output_stream.is_open()){
        std::cout << "Error.\n Couldn't open file/files.\n";
        return EXIT_FAILURE;
    }

    Huffman huffman;

    if (action == "save"){
        huffman.save(input_stream, output_stream);
    } else if (action == "load"){
        huffman.load(input_stream, output_stream);
    }
}