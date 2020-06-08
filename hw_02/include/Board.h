#pragma once


enum class Player{
    X,O
};

enum class GameStatus{
    Continues, Draw, OWins, XWins
};

class Board {
private:
    char **_field;
    GameStatus status;
    int cell_filled;
    void check(int x, int y, Player);
    void set_a_winner(Player);
public:             
    Board();
    Board(const Board &) = delete;
    Board& operator=(const Board &) = delete;
    ~Board(); 
    char get_cell(int x, int y) const;
    bool can_move(int x, int y) const;
    void move(int x, int y, Player);
    GameStatus get_state() const;
};
