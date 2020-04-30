#include "../include/Parser.h"
#include <cassert>
#include <algorithm>
#include <cstring>
#include "../include/Huffman.h"
#include "../include/ParserExceptions.h"

// Парсит консольные данные.
Parser::Parser(int argc, char **argv) {

    if (argc < 5){
        throw ParserExceptions("Not enough arguments.");
    }

    for (int i = 1; i < 6; i++){
        std::string command = argv[i];

        if (command == "-f" or command == "--file"){
            first_file_flag = argv[i++];
            input_file_name = argv[i];
        } else if (command == "-o" or command == "--output"){
            second_file_flag = argv[i++];
            output_file_name = argv[i];
        } else if (command == "-c"){
            action = "save";
        } else if (command == "-u"){
            action = "load";
        } else {
            throw ParserExceptions("Params are not correct.");
        }


    }

    if (action != "load" and action != "save"){
        throw ParserExceptions("Not correct param.");
    }

    if (strcmp(first_file_flag, "-f") != 0 and strcmp(first_file_flag, "--file") != 0){
        throw ParserExceptions("Params are not correct.");
    }

    if (strcmp(second_file_flag,"-o") != 0 and strcmp(second_file_flag, "--output") != 0){
        throw ParserExceptions("Params are not correct.");
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