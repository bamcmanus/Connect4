#include "board.h"
#include <iostream>
#include <algorithm>
#include <limits>

#define TOP_INDEX 0
#define CENTER 3

using namespace std;

// Default constructor calls helper function
Board::Board()
{
  new_board();
}


// Initialized a game board to all empty spaces;
void Board::new_board()
{
  vector<char> row(COLS,EMPTY);
  game_board = vector<vector<char>>(ROWS,row);
}


// Scores a board for a given player, returns score
int Board::score(const char piece)
{
  int score = 0;
  int center_count = 0;

  for ( int row = 0; row < ROWS; ++row)
  {
    if (game_board[row][CENTER] == piece)
      ++center_count;
  }
  score += center_count * 3;


  for ( int row = 0; row < ROWS; ++row)
  {
    vector<char> temp_row = game_board[row]; // get row
    score += horiz_score(temp_row, piece);
  }

  for ( int col = 0; col < COLS; ++col )
  {
    vector<char> temp_col(ROWS);
    for ( int row = 0; row < ROWS; ++row)
    {
      temp_col.at(row) = game_board[row][col];
    }
    score += vert_score(temp_col,piece);
  }

  score += rdiag_score(piece);

  score += ldiag_score(piece);

  return score;
}


// Scores all the horizontal win possibilities in a row and returns score
int Board::horiz_score(const vector<char> temp_row, const char piece)
{
  int window_length = 4;
  int score = 0;
  vector<char> window(4);
  for ( int col = 0; col < COLS; ++col)
  {
    if (col+3 == COLS)
      break;
    window.at(0) = temp_row[col];
    window.at(1) = temp_row[col+1];
    window.at(2) = temp_row[col+2];
    window.at(3) = temp_row[col+3];

    score += evaluate_window( window, piece );
  }
  return score;
}


// Scores all the possible vertical win possibilities in a column and returns the score
int Board::vert_score(const vector<char> temp_col, const char piece)
{
  int window_length = 4;
  int score = 0;
  vector<char> window(4);
  for ( int row = 0; row < ROWS; ++row)
  {
    if (row+3 == ROWS)
      break;
    window.at(0) = temp_col[row];
    window.at(1) = temp_col[row+1];
    window.at(2) = temp_col[row+2];
    window.at(3) = temp_col[row+3];

    score += evaluate_window( window, piece );
  }
  return score;
}


// Scores all the left diagonal win possibilites on a board and returns score
int Board::ldiag_score(const char piece)
{
  int score = 0;
  for ( int row = 3; row < ROWS; ++row)
  {
    for ( int col = 0; col < COLS-3; ++col)
    {
      if ( col+3 == COLS )
        continue;

      vector<char> window(4);
      window.at(0) = game_board[row][col];
      window.at(1) = game_board[row-1][col+1];
      window.at(2) = game_board[row-2][col+2];
      window.at(3) = game_board[row-3][col+3];

      score += evaluate_window( window, piece );
    }
  }
  return score;
}


// Scores all the right diagonal win possibilites on a board and returns score
int Board::rdiag_score(const char piece)
{
  int score = 0;
  for ( int row = 0; row < ROWS-3; ++row)
  {
    for ( int col = 0; col < COLS-3; ++col)
    {
      vector<char> window(4);
      window.at(0) = game_board[row][col];
      window.at(1) = game_board[row+1][col+1];
      window.at(2) = game_board[row+2][col+2];
      window.at(3) = game_board[row+3][col+3];

      score += evaluate_window( window, piece );
    }
  }
  return score;
}


// Checks if the board is full, should be used after is_winner
bool Board::is_draw()
{
  for (int i = 0; i < COLS; ++i)
  {
    if ( game_board[0][i] == EMPTY )
      return false;
  }
  return true;
}


int Board::evaluate_window(const vector<char> window, const char piece)
{
  int score = 0;
  char opponent;
  if (piece == BLACK)
    opponent = RED;
  else
    opponent = BLACK;

  if ( count(window.begin(),window.end(),piece) == 4 )
    score += 1000;
  if ( count(window.begin(),window.end(), piece) == 3 &&
      count(window.begin(),window.end(), EMPTY) == 1 )
    score += 10;
  if ( count(window.begin(),window.end(), piece) == 2 &&
      count(window.begin(),window.end(), EMPTY) == 2 )
    score += 2;

  if ( count(window.begin(),window.end(), opponent) == 3 &&
      count(window.begin(),window.end(), EMPTY) == 1 )
    score -= 900;
  if ( count(window.begin(),window.end(), opponent) == 2 &&
      count(window.begin(),window.end(), EMPTY) == 2 )
    score -= 50;

  return score;
}


// Checks if the column is valid for the game and if the top slot is available,
// returns true if both cases are true, false otherwise
bool Board::is_legal(const int col) const
{
  if ( col >= 0 && col < COLS )
  {
    if ( game_board[TOP_INDEX][col] == EMPTY )
    {
      return true;
    }
  }
  return false;
}


// If a move is valid, makes the move on the board with the piece arguement,
// Returns true if move was made, false otherwise
bool Board::make_move(const int col, const char piece)
{
  if (is_legal(col))
  {
    for (int i = ROWS-1; i >= 0; --i)
    {
      if ( game_board[i][col] == EMPTY )
      {
        game_board[i][col] = piece;
        break;
      }
    }
    return true;
  }
  return false;
}


void Board::undo(const int col)
{
  for (int i = ROWS-1; i >= 0; --i)
  {
    if ( game_board[i][col] == EMPTY )
    {
      if (i+1 < ROWS)
        game_board[i+1][col] = EMPTY;
      break;
    }
  }
}


// Returns the value of the board at the given row and col
char Board::get_value(const int row, const int col) 
{
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
    return game_board[row][col];
  throw new NoValueException();
}


// Displays the current board to stdout
void Board::display()
{
  cout<<endl << "    0   " << "    1   " << "    2   " << "    3   " << "    4   " << "    5   " << "    6   " << endl;
  for ( int row = 0; row < ROWS; ++row)
  {
    cout << string(57,'-') << endl;
    for (int col = 0; col < COLS; ++col)
    {
      cout << "|" << string(7,' ');
    }
    cout << "|" << endl;
    for (int col = 0; col < COLS; ++col)
    {
      cout << "|" << "   " << game_board[row][col] << "   ";
    }
    cout << "|" << endl;
    for (int col = 0; col < COLS; ++col)
    {
      cout << "|" << string(7,' ');
    }
    cout << "|" << endl;
  }
  cout << string(57,'-') << endl << endl;
}


bool Board::winning_move(const char piece)
{
  //vertical win
  for ( int col = 0; col < COLS; ++col )
  {
    for ( int row = 0; row < ROWS-3; ++row)
    {
      if ( game_board[row][col] == piece && game_board[row+1][col] == piece && game_board[row+2][col] == piece && game_board[row+3][col] == piece)
      {
        return true;
      }
    }
  }

  //horizontal win
  for ( int col = 0; col < COLS-3; ++col )
  {
    for ( int row = 0; row < ROWS; ++row)
    {
      if ( game_board[row][col] == piece && game_board[row][col+1] == piece
          && game_board[row][col+2] == piece && game_board[row][col+3] == piece)
      {
        return true;
      }
    }
  }
  //rdiag win
  for ( int col = 0; col < COLS-3; ++col )
  {
    for ( int row = 0; row < ROWS-3; ++row)
    {
      if ( game_board[row][col] == piece && game_board[row+1][col+1] == piece
          && game_board[row+2][col+2] == piece && game_board[row+3][col+3] == piece)
      {
        return true;
      }
    }
  }
  //ldiag win
  for ( int col = 0; col < COLS-3; ++col )
  {
    for ( int row = 3; row < ROWS; ++row)
    {
      if ( game_board[row][col] == piece && game_board[row-1][col+1] == piece
          && game_board[row-2][col+2] == piece && game_board[row-3][col+3] == piece)
      {
        return true;
      }
    }
  }
}


// Checks the board to see if there is a winner
bool Board::is_winner( const int col )
{
  if ( is_winner_horiz(col) || is_winner_vert(col) || is_winner_ldiag(col) || is_winner_rdiag(col) )
  {
    return true;
  }
  return false;
}


// Given the column of the last move, checks if there is a horizontal win
bool Board::is_winner_horiz( const int col )
{
  int count = 1;
  for ( int i = 0; i < ROWS; ++i)
  {
    if ( game_board[i][col] != EMPTY )
    {
      for (int j = col+1; j < COLS; ++j)
      {
        if (game_board[i][j] == game_board[i][col] )
          ++count;
        else
          break;
      }
      for (int j = col-1; j >= 0; --j)
      {
        if (game_board[i][j] == game_board[i][col] )
          ++count;
        else
          break;
      }
      break;
    }
  }
  if (count >= 4)
    return true;
  return false; 
}


// Given the column of the last move, checks if there is a vertical win
bool Board::is_winner_vert( const int col )
{
  int count = 1;
  for ( int i = 0; i < ROWS; ++i)
  {
    if ( game_board[i][col] == RED || game_board[i][col] == BLACK )
    {
      for (int j = i+1; j < ROWS; ++j)
      {
        if (game_board[j][col] == game_board[i][col] )
        {
          ++count;
        }
        else
          break;
      }
      break;
    }
  }
  if (count >= 4)
    return true;
  return false; 
}


// Given the column of the last move, checks if there is a left diagonal win
bool Board::is_winner_ldiag( const int col )
{
  int count = 1;
  char piece;
  for ( int i = ROWS-1; i >= 0; --i )
  {
    if ( game_board[i][col] == EMPTY )
    {
      int row = i+1;
      int cols = col;
      piece = game_board[i+1][col];

      do
      {
        ++row;
        --cols;
        if (row < ROWS && cols >= 0)
        {
          if (game_board[row][cols] == piece )
            ++count;
          else break;
        }
        else break;
      } while (game_board[row][cols] == piece);

      row = i+1;
      cols = col;

      do
      {
        --row;
        ++cols;
        if (row >= 0 && cols < COLS)
        {
          if (game_board[row][cols] == piece )
            ++count;
          else break;
        }
        else break;
      } while (game_board[row][cols] == piece);

      if (count >= 4)
        return true;
      else
        return false;
    }
  }
  return false;
}


// Given the column of the last move, checks if there is a right diagonal win
bool Board::is_winner_rdiag( const int col )
{
  int count = 1;
  char piece;
  for ( int i = ROWS-1; i >= 0; --i )
  {
    if ( game_board[i][col] == EMPTY )
    {
      int row = i+1;
      int cols = col;
      piece = game_board[i+1][col];

      do
      {
        ++row;
        ++cols;
        if (row < ROWS && cols < COLS)
        {
          if (game_board[row][cols] == piece )
            ++count;
          else break;
        }
        else break;
      } while (game_board[row][cols] == piece);

      row = i+1;
      cols = col;

      do
      {
        --row;
        --cols;
        if (row > -1 && cols > -1)
        {
          if (game_board[row][cols] == piece )
            ++count;
          else break;
        }
        else break;
      } while (game_board[row][cols] == piece);

      if (count >= 4)
        return true;
      else
        return false;
    }
  }
  return false;
}
