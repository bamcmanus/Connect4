#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"


class Human
{
  private:
    char game_piece;                                                        // Marker for connect 4 game

  public:
    Human() { game_piece = ' '; };                                          // Constructor
    char get_piece();                                                       // Getter for game piece
    virtual int get_move();                                                 // Prompts user for move
    void set_game_piece(const char gamepiece) { game_piece = gamepiece; };  // Setter for game piece
};


class Ai
{
  private:
    char game_piece;                                                        // Marker for connect 4 game

  public:
    Ai() { game_piece = ' '; };                                             // Constructor
    bool is_terminal( Board& b );                                           // Checks if game is over
    char get_piece();                                                       // Getter for game piece
    int get_move();                                                         // Generates a random move
    int pick_best(Board& b, const char piece);                              // Greedy Ai looks ahead for best move
    int minimax(Board& b, int depth, bool is_ai, int& best_move);           // Minimax algorithm to generate move
    int negamax(Board& b, int depth, char mark, int alpha, int beta, int& best_move);   // Negamax algorithm generator
    void set_game_piece(const char gamepiece) { game_piece = gamepiece; };  // Setter for game piece
};

#endif
