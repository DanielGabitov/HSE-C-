#pragma once
#include "Test.h"

class BoardTest : public Test {
private:
    void can_move_to_free_cell();
    void can_move_to_filled_cell();
    void can_move_outside_of_a_field();
    void make_a_move();
    void no_move();
    void state_O_wins_row();
    void state_O_wins_diag();
    void state_X_wins_row();
    void state_X_wins_diag();
    void state_Draw();
    void state_Continue();
public:
    void runAllTests() override;
};
