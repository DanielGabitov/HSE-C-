#include "../include/Huffman.h"
#include <iostream>
#include <cassert>
#include "../include/Parser.h"
#include <fstream>

int main(int argc, char *argv[]){
    Parser pareser(argc, argv);

    pareser.do_command();
}