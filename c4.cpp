#include "c4.h"
#include <unistd.h>
#include <sstream>

#define DEPTH 2

using namespace std;


// Main menu of options, performs error checking and returns a valid option
int Connect4::main_menu()
{
  int num;
  string line;

  cout << "Main Menu" << endl;
  cout << "1. Play against another player" << endl;
  cout << "2. Play against a dumb ai" << endl;
  cout << "3. Play against a greedy ai" << endl;
  cout << "4. Play against a \"perfect\" ai" << endl;
  cout << "5. Watch greedy ai play against dumb ai" << endl;
  cout << "6. Watch greedy ai play against itslef" << endl;
  cout << "7. Watch greedy ai play \"perfect\" ai" << endl;
  cout << "8. Watch \"perfect\" ai play against itslef" << endl;
  cout << "Enter option: " << endl;

  while (getline(cin,line))
  {
    stringstream stream(line);
    if ( !(stream >> num) )
    {
      cout << "Not a valid option";
      cout << endl << "Enter a valid option: ";
      continue; 
    }
    char error;
    if (stream >> error)
    {
      cout << "More than a single number was input please try again";
      cout << endl << "Enter a valid option: ";
      continue;
    }
    break;
  }
  return num;
}


// Game manager switches based on main menu option
void Connect4::play()
{
  srand(time(0));

  bool option = true;

  int turn = rand()%2;
  int move = 0;
  int who_won = 0;

  Board b;

  Human player1;
  Human player2;

  Ai cpu1;
  Ai cpu2;

  player1.set_game_piece(RED);
  player2.set_game_piece(BLACK);

  cpu1.set_game_piece(RED);
  cpu2.set_game_piece(BLACK);

  switch(main_menu())
  {
    case 1:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = player1.get_move();
            who_won = 1;
          } while ( !b.make_move(move,player1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            move = player2.get_move();
            who_won = 2;
          } while ( !b.make_move(move,player2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Player 1 Won!" << endl;
      else
        cout << "Player 2 Won!" << endl;
      break;

    case 2:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = player1.get_move();
            who_won = 1;
          } while ( !b.make_move(move,player1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            move = cpu2.get_move();
            who_won = 2;
          } while ( !b.make_move(move,player2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Player Won!" << endl;
      else
        cout << "Dumb AI Won!" << endl;
      break;

    case 3:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = player1.get_move();
            who_won = 1;
          } while ( !b.make_move(move,player1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            move = cpu2.pick_best(b,cpu2.get_piece());
            who_won = 2;
            sleep(1);
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Player Won!" << endl;
      else
        cout << "Greedy AI Won!" << endl;
      break;

    case 4:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = player1.get_move();
            who_won = 1;
          } while ( !b.make_move(move,cpu1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            cpu2.minimax(b,DEPTH,true,move);
            who_won = 2;
            sleep(1);
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Player Won!" << endl;
      else
        cout << "\"Perfect\" AI Won!" << endl;
      break;

    case 5:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = cpu1.pick_best(b,cpu1.get_piece());
            who_won = 1;
            sleep(1);
          } while ( !b.make_move(move,cpu1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            move = cpu2.get_move();
            who_won = 2;
            sleep(1);
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Greedy AI Won!" << endl;
      else
        cout << "Dumb AI Won!" << endl;
      break;

    case 6:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = cpu1.pick_best(b,cpu1.get_piece());
            who_won = 1;
            sleep(1);
          } while ( !b.make_move(move,cpu1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            move = cpu2.pick_best(b,cpu2.get_piece());
            who_won = 2;
            sleep(1);
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Greedy AI 1 Won!" << endl;
      else
        cout << "Greedy AI 2 Won!" << endl;
      break;

    case 7:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            move = cpu1.pick_best(b,cpu1.get_piece());
            sleep(2);
            who_won = 1;
          } while ( !b.make_move(move,cpu1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            cpu2.minimax(b,DEPTH,true,move);
            sleep(2);
            who_won = 2;
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.winning_move(RED) && !b.winning_move(BLACK) && !b.is_draw());
      b.display();
      if ( who_won == 1)
        cout << "Greedy AI Won!" << endl;
      else
        cout << "Minimax AI Won!" << endl;
      break;

    case 8:
      do
      {
        b.display();
        if ( turn == 1 )
        {
          do{
            cpu1.minimax(b,DEPTH,true,move);
            sleep(1);
            who_won = 1;
          } while ( !b.make_move(move,cpu1.get_piece()) );
          turn = 2;
        }
        else
        {
          do
          {
            cpu2.minimax(b,DEPTH,true,move);
            sleep(1);
            who_won = 2;
          } while ( !b.make_move(move,cpu2.get_piece()) );
          turn = 1;
        } 
      }while (!b.is_winner(move));
      b.display();
      if ( who_won == 1)
        cout << "Minimax AI 1 Won!" << endl;
      else
        cout << "Minimax AI 2 Won!" << endl;
      break;

    default:
      cout << "Not a valid option";
  }
}
