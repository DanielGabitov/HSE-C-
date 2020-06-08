#include "Test.h"
#include "BoardTest.h"
#include "Board.h"

#define DO_CHECK(EXPR) check(EXPR, __func__, __FILE__, __LINE__);

void BoardTest::can_move_to_free_cell(){
    Board b;
    DO_CHECK(b.can_move(0,0));
}

void BoardTest::can_move_to_filled_cell(){
    Board b;
    b.move(0, 0, Player::O);
    DO_CHECK(b.can_move(0, 0) == 0);
}

void BoardTest::can_move_outside_of_a_field(){
    Board b;
    DO_CHECK(b.can_move(10, 10) == 0);
    DO_CHECK(b.can_move(-1, -1) == 0);
}

void BoardTest::make_a_move(){
    Board b;
    b.move(1, 1, Player::O);
    DO_CHECK(b.get_cell(1, 1) == 'O');

    b.move(2,2, Player::X);
    DO_CHECK(b.get_cell(2, 2) == 'X');
}

void BoardTest::no_move(){
    Board b;
    DO_CHECK(b.get_cell(0, 0) == '.');
}

void BoardTest::state_O_wins_row(){
    Board b;
    b.move(0, 0, Player::O);
    b.move(0, 1, Player::O);
    b.move(0, 2, Player::O);
    b.move(0, 3, Player::O);
    b.move(0, 4, Player::O);
    DO_CHECK(b.get_state() == GameStatus::OWins);
}

void BoardTest::state_O_wins_diag(){
    Board b;
    b.move(9, 9, Player::O);
    b.move(8, 8, Player::O);
    b.move(7, 7, Player::O);
    b.move(6, 6, Player::O);
    b.move(5, 5, Player::O);
    DO_CHECK(b.get_state() == GameStatus::OWins);

    Board c;
    c.move(9, 9, Player::O);
    c.move(8, 8, Player::O);
    c.move(7, 7, Player::O);
    c.move(6, 6, Player::O);
    c.move(5, 5, Player::O);
    DO_CHECK(c.get_state() == GameStatus::OWins);

    Board d;
    d.move(5, 4, Player::O);
    d.move(4, 3, Player::O);
    d.move(3, 2, Player::O);
    d.move(2, 1, Player::O);
    d.move(1, 0, Player::O);
    DO_CHECK(d.get_state() == GameStatus::OWins);

    Board f;
    f.move(5, 5, Player::O);
    f.move(6, 6, Player::O);
    f.move(7, 7, Player::O);
    f.move(8, 8, Player::O);
    f.move(9, 9, Player::O);
    DO_CHECK(d.get_state() == GameStatus::OWins);
}

void BoardTest::state_X_wins_row(){
    Board b;
    b.move(6, 5, Player::X);
    b.move(6, 4, Player::X);
    b.move(6, 3, Player::X);
    b.move(6, 2, Player::X);
    b.move(6, 1, Player::X);
    DO_CHECK(b.get_state() == GameStatus::XWins);

    Board c;
    c.move(3, 3, Player::X);
    c.move(4, 3, Player::X);
    c.move(2, 3, Player::X);
    c.move(1, 3, Player::X);
    c.move(5, 3, Player::X);
    DO_CHECK(c.get_state() == GameStatus::XWins);
}

void BoardTest::state_X_wins_diag(){
    Board b;
    b.move(3, 2, Player::X);
    b.move(4, 3, Player::X);
    b.move(5, 4, Player::X);
    b.move(6, 5, Player::X);
    b.move(7, 6, Player::X);
    DO_CHECK(b.get_state() == GameStatus::XWins);

    Board c;
    c.move(9, 9, Player::X);
    c.move(8, 8, Player::X);
    c.move(7, 7, Player::X);
    c.move(6, 6, Player::X);
    c.move(5, 5, Player::X);
    DO_CHECK(c.get_state() == GameStatus::XWins);

    Board d;
    d.move(0, 9, Player::X);
    d.move(1, 8, Player::X);
    d.move(2, 7, Player::X);
    d.move(3, 6, Player::X);
    d.move(4, 5, Player::X);
    DO_CHECK(d.get_state() == GameStatus::XWins);

    Board f;
    f.move(5, 4, Player::X);
    f.move(6, 3, Player::X);
    f.move(7, 2, Player::X);
    f.move(8, 1, Player::X);
    f.move(9, 0, Player::X);
    DO_CHECK(f.get_state() == GameStatus::XWins);

    Board h;
    h.move(5, 5, Player::X);
    h.move(6, 4, Player::X);
    h.move(7, 3, Player::X);
    h.move(8, 2, Player::X);
    h.move(9, 1, Player::X);
    DO_CHECK(h.get_state() == GameStatus::XWins);
}

void BoardTest::state_Draw(){
    Board b;
    for (size_t i = 0; i < 10; i++){
        for (size_t j = 0; j < 10; j += 2){
            b.move(i, j, Player::O);
            b.move(i, j + 1, Player::X);
        }
    }
    DO_CHECK(b.get_state() == GameStatus::Draw);
}

void BoardTest::state_Continue(){
    Board b;
    DO_CHECK(b.get_state() == GameStatus::Continues);
    b.move(5, 5, Player::X);
    b.move(5, 4, Player::X);
    b.move(5, 3, Player::X);
    b.move(5, 2, Player::X);
    b.move(5, 0, Player::X);
    DO_CHECK(b.get_state() == GameStatus::Continues);

    b.move(8, 8, Player::X);
    b.move(8, 7, Player::X);
    b.move(8, 6, Player::X);
    b.move(8, 5, Player::X);
    b.move(8, 3, Player::X);
    b.move(7, 4, Player::X);
    DO_CHECK(b.get_state() == GameStatus::Continues);
}

void BoardTest::runAllTests(){
    can_move_to_free_cell();
    can_move_to_filled_cell();
    can_move_outside_of_a_field();
    make_a_move();
    no_move();
    state_O_wins_row();
    state_O_wins_diag();
    state_X_wins_row();
    state_X_wins_diag();
    state_Draw();
    state_Continue();
}
