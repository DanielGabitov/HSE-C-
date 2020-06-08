#include "Board.h"
#include <iostream>
#include "StdioBoardView.h"
#include "assert.h"
#include "string.h"

int main(int argc, char *argv[]){
    if (argc > 2){
        std::cout << "Undefined behaviour.\n";
        return 0;
    }
    bool is_silent = (argc == 2 and strcmp(argv[1], "silent") == 0);
    Board board;
    StdioBoardView view(board, is_silent);
    view.run_game();
}
