#include "StdioBoardView.h"
#include "Board.h"
#include <stdio.h>
#include "ctype.h"
#include "stdlib.h"
#include "cstring"
#include "string"

char StdioBoardView::get_char(Player player){
    return (player == Player::X) ? 'X' : 'O';
}

void StdioBoardView::print_game_status() const{
    switch(board.get_state())
    {
    case GameStatus::Continues:
        printf("Game continues");
        break;
    case GameStatus::Draw:
        printf("Draw.\n");
        break;
    case GameStatus::XWins:
        printf("X wins!\n");
        break;
    case GameStatus::OWins:
        printf("O wins!\n");
        break;
    }
}

bool check_if_digit(std::string s){
    if (!isdigit(s[0]) and s[0] !=  '-'){
        return false;
    }
    for (size_t i = 1; i < s.size(); i++){
        if (!isdigit(s[i])){
            return false;
        }
    }
    return true;
}

void set_next_player(Player &player){
    player = (player == Player::X) ? Player::O : Player::X;
}

StdioBoardView::StdioBoardView(Board &board, bool is_silent)
    : board(board)
    , is_silent(is_silent)
    {}

void StdioBoardView::print_board() const{
    if (is_silent and board.get_state() == GameStatus::Continues){
        return;
    }
    printf("\n");
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j++){
            printf("%c", board.get_cell(i, j));
        }
        printf("\n");
    }
}

void StdioBoardView::run_game(){
    Player player = Player::O;
    char *input_number_one;
    char *input_number_two;
    std::string buff_1, buff_2;
    int x, y;
    print_board();
    while (board.get_state() == GameStatus::Continues){
        printf("%c move: ", get_char(player));    
        scanf("%ms%ms", &input_number_one, &input_number_two);

        buff_1 = input_number_one;
        buff_2 = input_number_two;
        
        if (!check_if_digit(buff_1) or !check_if_digit(buff_2)){
            printf("Bad move!\n");
            continue;
        }

        x = atoi(input_number_one);
        y = atoi(input_number_two);
        free(input_number_one);
        free(input_number_two);

        if (x == -1 and y == -1){
            return;
        }

        if (!board.can_move(x, y)){
            printf("Bad move!\n");
            continue;
        }
        board.move(x, y, player);
        set_next_player(player);
        print_board();
    }
    is_silent = 0;
    print_game_status();
}
