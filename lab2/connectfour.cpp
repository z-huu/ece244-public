//
//  connectfour.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// The main function
int main()
{
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds]; // constructor is called three times for each game_state in the array

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col, row;
  int redScore = 0;
  int yellowScore = 0;
  int round = 0;

  cout << "Game 1" << endl;

  while (!game_state[round].get_gameOver())
  {
    cout << "Enter column to place piece: ";
    cin >> col;

    if (cin.eof())
    {

      cerr << endl
           << "Game ended by user." << endl;
      exit(0);
    }
    if (cin.fail())
    {
      cin.clear();
      cin.ignore(1000, '\n');
      col = -1; // giving col invalid value so it will be handled as invalid input below
    }

    // Check validity of input and if not valid, handle accordingly
    // check that col value is between 0 and 6 and column is not full

    if ((col < 0) || (col > 6) || (game_state[round].get_gameBoard(boardSize - 1, col) != Empty))
    {
      cout << "Invalid column!" << endl;
    }
    else
    { // if the input column is valid, print column chosen

      cout << "column chosen: " << col;

      // find corresponding row value

      for (int i = 0; i <= boardSize - 1; i++)
      { // works!
        if (game_state[round].get_gameBoard(i, col) == Empty)
        {
          row = i;
          // cout << endl << col << " " << i; debug statement
          break;
        }
      }

      // set selectedRow & selectedColumn (works)
      game_state[round].set_selectedColumn(col);
      game_state[round].set_selectedRow(row);

      // update gameboard (works)
      if (game_state[round].get_turn())
      { // true = Red
        game_state[round].set_gameBoard(row, col, R);
      }
      else
      { // false = Yellow
        game_state[round].set_gameBoard(row, col, Y);
      }

      // call playMove to update game_state values
      playMove(game_state[round]);
      // print board (
      cout << endl;
      for (int i = boardSize - 1; i >= 0; i--)
      { // row >=0 maybe?
        for (int k = 0; k <= boardSize - 1; k++)
        {
          // printing content of each board coordinate
          if (game_state[round].get_gameBoard(i, k) == Empty)
          {
            cout << "_";
          }
          else if (game_state[round].get_gameBoard(i, k) == R)
          {
            cout << "R";
          }
          else if (game_state[round].get_gameBoard(i, k) == Y)
          {
            cout << "Y";
          }
        }
        cout << endl;
      }
      // check for game over
      if (game_state[round].get_winner() != Empty)
      { // game is over
        // outputting game winner
        if (game_state[round].get_winner() == R)
        {
          cout << "R won this round!" << endl;
          redScore++;
        }
        else
        {
          cout << "Y won this round!" << endl;
          yellowScore++;
        }

        // checking if match is over TO DO:::::::::::::::::::::::::
        
        if ((redScore <2)&&(yellowScore < 2)) { //nobody has a score of 2. we should increment the round
          round++;
          cout << "Game " << round+1 << endl;
        } else { // this runs if somebody does have a score of 2. let's print the winner
          
          if (redScore > yellowScore) {
            cout << "R won the match!";
          } else {
            cout << "Y won the match!";
          }
        }

      } // if game is not over, nothing happens
    }
  }
}

/*
Once the game boards are initialized, for each GameState you should:

    Prompt the player for an integer representing the column of the game board that the player wishes to place their piece in.
    Check that the player enters an integer that is in the range of 0–6 and  that the column is not full.
    Print the selected column if it is valid. Otherwise, print "Invalid column", and give the player another chance till they enter a valid column.
    Find the lowest available row that the piece will fall to, and then set the selectedColumn and selectedRow of the GameState object to the entered values.
    Update the game board at the appropriate location by either R or Y.
    Call the playMove().
    Print the gameBoard of the GameState.
    Announce the winner if there is one, and repeat for another game, untill a player wins best-of-3 games.


*/