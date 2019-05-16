#ifndef C4_H
#define C4_H

#include "board.h"
#include "player.h"


class Connect4 {
  public:
    Connect4() { };     // Default Constructor 
    int main_menu();    // Menu of options for game
    void play();        // Driver method manages game

  private:
    Board game_board;   // Game board for connect 4
    Human player1;      // Human player
    Human player2;      // Human player
    Ai computer1;       // AI object
    Ai computer2;       // AI object
};
#endif
