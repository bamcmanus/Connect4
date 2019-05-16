#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>


static const char RED = 'R';
static const char BLACK = 'B';
static const char EMPTY = ' ';
static const int ROWS = 6;
static const int COLS = 7;

class Board
{
  private:
    std::vector<std::vector<char>> game_board;

  public:
    Board();
    bool winning_move( const char piece );
    int score( const char piece );
    int horiz_score( const std::vector<char>, char );
    int vert_score( const std::vector<char>, char );
    int rdiag_score( const char piece );
    int ldiag_score( const char piece );
    int evaluate_window( const std::vector<char> window, const char piece );
    void new_board();
    bool is_legal(const int col) const;
    bool make_move(const int col, const char piece);
    void undo(const int col);
    char get_value(const int row, const int col);
    bool is_draw();
    bool is_winner(const int col);
    bool is_winner_horiz(const int col);
    bool is_winner_vert(const int col);
    bool is_winner_ldiag(const int col);
    bool is_winner_rdiag(const int col);
    void display();
};

class NoValueException { };
#endif
