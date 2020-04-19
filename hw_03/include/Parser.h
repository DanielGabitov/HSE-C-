#pragma once

class Parser {
public:
    Parser(int argc, char **argv);
    void do_command();
private:
    char action;
    char first_file_flag;
    char *first_file_name;
    char second_file_flag;
    char *second_file_name;
};

