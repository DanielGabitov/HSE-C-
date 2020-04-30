#pragma once

#include <string>

class Parser {
public:
    Parser(int argc, char **argv);
    std::string get_action() const;
    char* get_input_file_name() const;
    char* get_output_file_name() const;
private:
    std::string action;
    char *first_file_flag;
    char *input_file_name;
    char *second_file_flag;
    char *output_file_name;
};

