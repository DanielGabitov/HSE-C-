#include "Board.h"
#include "cstdio"
#include <string.h>
#include "assert.h"
#include <algorithm>
#include "StdioBoardView.h"

extern const int COL_SIZE = 10;
extern const int ROW_SIZE = 10;

Board::Board()
    : _field(new char* [ROW_SIZE])
    , status(GameStatus::Continues)
    , cell_filled(0)
{
    for (size_t i = 0; i < COL_SIZE; i++){
        _field[i] = new char [COL_SIZE];
        memset(_field[i], '.', COL_SIZE);
    }
}

Board::~Board(){
    for (size_t i = 0; i < COL_SIZE; i++){
        delete [] _field[i];
    }
    delete [] _field;
}


char Board::get_cell(int x, int y) const {
    if (0 <= x and x < 10 and 0 <= y and y < 10){
        return _field[x][y];
    }
    fprintf(stderr, "Incorrect data is given to a method get_cell!\n");
    assert(0);
}

GameStatus Board::get_state() const {
    return status;
}

bool Board::can_move(int x, int y) const{
    if (COL_SIZE <= x || x < 0 || ROW_SIZE <= y || y < 0){
        return false;
    }
    if (_field[x][y] != '.'){
        return false;
    }
    return true;
}

void Board::set_a_winner(Player player){
    status = (player == Player::X) ? GameStatus::XWins : GameStatus::OWins;
}

void Board::check(int x, int y, Player player){
    size_t counter_for_row = 0;
    size_t counter_for_col = 0;
    for (size_t i = 0; i < 10; i++){
        //
        counter_for_row = (_field[x][i] == StdioBoardView::get_char(player)) ? (counter_for_row + 1) : 0;
        counter_for_col = (_field[i][y] == StdioBoardView::get_char(player)) ? (counter_for_col + 1) : 0;
        //
        if (counter_for_row >= 5 or counter_for_col >= 5){
            set_a_winner(player);
        }
    }
    //
    size_t counter_for_diagonal = 0;
    int distance_to_edge = std::min(x, y);
    int board_edge_x = x - distance_to_edge;
    int board_edge_y = y - distance_to_edge;
    for (; board_edge_x < COL_SIZE and board_edge_y < ROW_SIZE; board_edge_x++, board_edge_y++){
        if (_field[board_edge_x][board_edge_y] == StdioBoardView::get_char(player)){
            counter_for_diagonal++;
        } else {
            counter_for_diagonal = 0;
        }
        if (counter_for_diagonal >= 5){
            set_a_winner(player);
            return;
        }
    }
    // from right to left
    counter_for_diagonal = 0;
    board_edge_x = x;
    board_edge_y = y;
    //
    while (board_edge_x > 0 and board_edge_y < COL_SIZE - 1){
        board_edge_x--;
        board_edge_y++;
    }
    for (; board_edge_x < ROW_SIZE  and board_edge_y >= 0; board_edge_x++, board_edge_y--){
        if (_field[board_edge_x][board_edge_y] == StdioBoardView::get_char(player)){
            counter_for_diagonal++;
        } else {
            counter_for_diagonal = 0;
        }
        if (counter_for_diagonal >= 5){
            set_a_winner(player);
            return;
        }
    }
    if (cell_filled == ROW_SIZE * COL_SIZE){
        status = GameStatus::Draw;
        return;
    }
}

void Board::move(int x, int y, Player player){
    _field[x][y] = StdioBoardView::get_char(player);
    cell_filled++;
    check(x, y, player);
}
