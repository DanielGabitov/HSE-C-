#pragma once
#pragma once
#include "Board.h"

class StdioBoardView {
private:
    Board &board;
    bool is_silent;
    void print_board() const;
    void print_game_status() const;
public:
    static char get_char(Player);
    StdioBoardView(Board &board, bool is_silent = 0);
    void run_game();
};
