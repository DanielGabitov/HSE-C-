#include "../include/Parser.h"
#include <cassert>
#include <algorithm>
#include "../include/Huffman.h"
#include "../include/ParserExceptions.h"

namespace{

    char read_flag(const char * line){
        size_t i = 0;
        while (line[i] == '-'){
            i++;
        }
        return line[i];
    } 

} // anonymous namespace ends.


// Парсит консольные данные.
Parser::Parser(int argc, char **argv) {

    if (argc < 5){
        throw ParserExceptions("Not enough arguments.");
    }

    char terminal_action  = read_flag( *(argv + 1) );
    first_file_flag = read_flag ( *(argv + 2) );
    input_file_name = *(argv + 3);
    second_file_flag = read_flag ( *( argv + 4) );
    output_file_name = *(argv + 5);

    switch (terminal_action){

        case 'c':
            action = "save";
            break;

        case 'u':
            action = "load";
            break;

        default:
            throw ParserExceptions("Not known command.");
            break;
    }


    if (first_file_flag != 'f'){
        std::swap(first_file_flag, second_file_flag);
        std::swap(input_file_name, output_file_name);
    }

    if (first_file_flag != 'f' or second_file_flag != 'o'){
        throw ParserExceptions("Not known flags.");
    }

}

char* Parser::get_input_file_name() const{
    return input_file_name;
}

char* Parser::get_output_file_name() const{
    return output_file_name;
}

std::string Parser::get_action() const {
    return action;
}