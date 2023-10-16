//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)

// function is called only if the move is valid

/* contents of GameState class

int selectedRow;     // Game board row coordinate selected (in the range
                       // 0..boardSize-1)
  int selectedColumn;  // Game board column coordinate selected (in the range
                       // 0..boardSize-1)
  bool moveValid;  // Is the grid location selected by the above coordinates a
                   // valid move?
  bool
      gameOver;  // Is the game over as a result of the selected row and column?
  bool turn;     // Whose turn is it?
  int winner;    // who won the game? (Empty if a tie or game still in progress)
  int gameBoard[boardSize][boardSize];  // The game board

*/

/* Return the selected row (in the range 0..boardSize - 1)
  int get_selectedRow();

  // Return the selected column (in the range 0..boardSize - 1)
  int get_selectedColumn();

  // Set the selected row to value in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
  void set_selectedRow(int value);

  // Set the selected column in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
  void set_selectedColumn(int value);

  // Get the moveValid value
  bool get_moveValid();

  // Set the moveValid variable to value
  void set_moveValid(bool value);

  // Get the gameOver value
  bool get_gameOver();

  // Set the gameOver variable to value
  void set_gameOver(bool value);

  // Get the value of turn
  bool get_turn();

  // Set the value of turn
  void set_turn(bool value);

  // Get the value of winner
  int get_winner();

  // Set the value of winner;
  void set_winner(int value);

  // Get the game board value at the board location at row and col
  // This method checks that row, col and value are in range/valid
  // and if not it returns Empty
  int get_gameBoard(int row, int col);

  // Set the game board value at the board location at row and col to value
  // This method checks that row, col and value are in range/valid and if not it
  // just returns
  void set_gameBoard(int row, int col, int value);
*/

//game_state passed by reference
void playMove(GameState &game_state)
{
  //(turn = true means red turn to play)
  //function is only called if the move is valid. assume the move is valid

  //CHANGE TURN

    if (game_state.get_turn()) { //if the turn is true

      game_state.set_turn(false);
    } else {
      game_state.set_turn(true);

    } //end turn modification

   

  // Change gameOver (check if the game is over)
    /*
      check for full board. if there are no empty spots, the game is over
      check for winner. cycle through each spot and if there is a color there, check in all directions
      for four of the same color.
    */

//check for winner first because if there's a winner, the game is over
  for (int row = 0; (row < boardSize)&&(game_state.get_winner() == Empty); row++) {
    for (int col = 0; (col < boardSize)&&(game_state.get_winner() == Empty); col++) {
      if (game_state.get_gameBoard(row, col) != Empty) { //if we encounter a color
        
        //check for color
        int color = game_state.get_gameBoard(row, col);
        
          //check to the left
            if (col - 3 >= 0) {
              int left1 = game_state.get_gameBoard(row, col-1);
              int left2 = game_state.get_gameBoard(row, col-2);
              int left3 = game_state.get_gameBoard(row, col-3);
              if ((left1==left2)&&(left2==left3)&&(left3==color)) { //if 3 tiles to the left are same color
                game_state.set_winner(color);
              }
            }
          //check downwards
            if (row - 3 >= 0) {
              int down1 = game_state.get_gameBoard(row-1, col);
              int down2 = game_state.get_gameBoard(row-2, col);
              int down3 = game_state.get_gameBoard(row-3, col);
              if ((down1==down2)&&(down2==down3)&&(down3==color)) {
                game_state.set_winner(color);
              }
            }
          //check to the right
            if (col + 3 <= boardSize-1) {
              int right1 = game_state.get_gameBoard(row, col+1);
              int right2 = game_state.get_gameBoard(row, col+2);
              int right3 = game_state.get_gameBoard(row, col+3);
              if ((right1==right2)&&(right2==right3)&&(right3==color)) {
                game_state.set_winner(color);
              }
            }
          //check upwards
            if (row + 3 <= boardSize-1) {
              int up1 = game_state.get_gameBoard(row+1, col);
              int up2 = game_state.get_gameBoard(row+2, col);
              int up3 = game_state.get_gameBoard(row+3, col);
              if ((up1==up2)&&(up2==up3)&&(up3==color)) {
                game_state.set_winner(color);
              }
            }
          //check top left
            if ((row + 3 <= boardSize-1)&&(col - 3 >= 0)) {
              int topleft1 = game_state.get_gameBoard(row+1, col-1);
              int topleft2 = game_state.get_gameBoard(row+2, col-2);
              int topleft3 = game_state.get_gameBoard(row+3, col-3);
              if ((topleft1==topleft2)&&(topleft2==topleft3)&&(topleft3==color)) {
                game_state.set_winner(color);
              }
            }
          //check top right
            if ((row+3<=boardSize-1)&&(col+3<=boardSize-1)) {
              int topright1 = game_state.get_gameBoard(row+1, col+1);
              int topright2 = game_state.get_gameBoard(row+2, col+2);
              int topright3 = game_state.get_gameBoard(row+3, col+3);
              if ((topright1==topright2)&&(topright2==topright3)&&(topright3==color)) {
                game_state.set_winner(color);
              }
            }
          //check bottom left
          if ((col - 3 >= 0)&&(row - 3>=0)) {
              int bottomLeft1 = game_state.get_gameBoard(row-1, col-1);
              int bottomLeft2 = game_state.get_gameBoard(row-2, col-2);
              int bottomLeft3 = game_state.get_gameBoard(row-3, col-3);
                if ((bottomLeft1==bottomLeft2)&&(bottomLeft2==bottomLeft3)&&(bottomLeft3==color)) {
                  game_state.set_winner(color);
                }
          }
          //check bottom right
          if ((col + 3 <= boardSize-1)&&(row-3 >= 0)) {
              int bottomright1 = game_state.get_gameBoard(row-1, col+1);
              int bottomright2 = game_state.get_gameBoard(row-2, col+2);
              int bottomright3 = game_state.get_gameBoard(row-3, col+3);
              if ((bottomright1==bottomright2)&&(bottomright2==bottomright3)&&(bottomright3==color)) {
                game_state.set_winner(color);
              }
          }

        
      }
    }
  }

  if (game_state.get_winner() == Empty) { //there is no winner. check for possible moves
    for (int row = 0; (row < boardSize-1); row++) {
      for (int col = 0; (col < boardSize-1); col++) {
        if (game_state.get_gameBoard(row, col) == Empty) { //there is a possible move. game is not over
          game_state.set_gameOver(false);
          return;
        }
      }
    } //end of iterating through board
    //at this point there is no winner but also no moves.
    game_state.set_gameOver(true);
  } else { //if there is a winner
    game_state.set_gameOver(true);
  }

  return;
  
}