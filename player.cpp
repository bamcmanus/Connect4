#include "player.h"
#include "board.h"
#include <unistd.h>
#include <string>
#include <sstream>
#include <limits>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define DEPTH 2

using namespace std;


// Returns the player's piece character
char Human::get_piece()
{
  return game_piece;
}


// Prompts the user for a move and returns that move. Continues to prompt until
// a valid move is input.
int Human::get_move()
{
  int num;
  string line;
  cout << "Enter the column number for your move: ";
  while (getline(cin,line))
  {
    stringstream stream(line);
    if ( !(stream >> num) )
    {
      cout << "Not a valid number";
      cout << endl << "Enter the column number for your move: ";
      continue; 
    }
    char error;
    if (stream >> error)
    {
      cout << "More than a single number was input please try again";
      cout << endl << "Enter the column number for your move: ";
      continue;
    }
    break;
  }
  return num;
}


// Returns the AI character's piece character
char Ai::get_piece()
{
  return game_piece;
}


// needs implementation
int Ai::get_move()
{
  return rand()%7;
}


// Checks if the game is over
bool Ai::is_terminal( Board& b )
{
  return b.winning_move(RED) || b.winning_move(BLACK) || b.is_draw();
}


// Minimax algorithm for deciding best move, returns column of best move
int Ai::minimax(Board& b, int depth, bool is_ai, int& best_move)
{
  if ( b.is_draw() )
    return 0;
  else if ( b.winning_move(BLACK) )
    return numeric_limits<int>::max();
  else if ( b.winning_move(RED) )
    return numeric_limits<int>::min();;

  if ( depth == 0 )
    return ( (is_ai) ? b.score(BLACK) : b.score(RED) );

  if ( is_ai )
  {
    int best_value = numeric_limits<int>::min(); 
    for ( int col = 0; col < COLS; ++col )
    {
      if ( b.is_legal(col) )
      {
        b.make_move(col,BLACK);
        int value = minimax(b,depth-1,!is_ai,best_move);
        if ( value > best_value )
        {
          best_value = value;
          best_move = col;
        }
        b.undo(col);
      }
    }
    return best_value;
  }
  else
  {
    int best_value = numeric_limits<int>::max();
    for ( int col = 0; col < COLS; ++col )
    {
      if ( b.is_legal(col) )
      {
        b.make_move(col,RED);
        int value = minimax(b,depth-1,!is_ai,best_move);
        if ( value < best_value )
        {
          best_value = value;
        }
        b.undo(col);
      }
    }
    return best_value;
  }
}


// Greedy algorithm uses single move look ahead to determine the best move, returns colum of best move
int Ai::pick_best(Board& b, const char piece)
{
  int best_score = numeric_limits<int>::min();
  int score = 0;
  int best_col = rand()%7;
  for ( int col = 0; col < COLS; ++col )
  {
    if ( b.is_legal(col) )
      b.make_move(col,piece);
    else
      continue;
    score = b.score(piece);
    if ( score > best_score )
    {
      best_score = score;
      best_col = col;
    }
    b.undo(col);
  }
  return best_col;
}


// Negamax algorithm for deciding best move, returns column of best move
int Ai::negamax(Board& b, int depth, char mark, int alpha, int beta, int& best_move)  
{
  char opponent;
  if ( mark == BLACK )
    opponent = RED;
  else
    opponent = BLACK;

  if ( b.is_draw() )
    return 0;
  else if ( b.winning_move(mark) )
    return numeric_limits<int>::max();
  else if ( b.winning_move(opponent) )
    return numeric_limits<int>::min();

  if ( depth == 0 )
    return b.score(mark);;

  int best_value = numeric_limits<int>::min(); 
  for ( int col = 0; col < COLS; ++col )
  {
    if ( b.is_legal(col) )
    {
      b.make_move(col,mark);
      int value = -negamax(b,depth-1,opponent,-beta,-alpha,best_move);
      if ( value > best_value )
      {
        best_value = value;
        best_move = col;
      }
      alpha = max(alpha,best_value);
      b.undo(col);
      if ( beta <= alpha )
        break;
    }
  }
  return best_value;
}
