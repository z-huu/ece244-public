//
//  GameState.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "GameState.h"
#include "globals.h"

// ECE244 Student: add you code below

/* functions to implement

  // The constructor. It initializes:
  //     selectedRow to 0
  //     selectedColum to 0
  //     moveValid to true
  //     gameOver to false
  //     turn to true
  //     winner to Empty
  //     gameBoard locations to Empty (see globals.h)
  GameState();

  // Return the selected row (in the range 0..boardSize - 1)
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

// implementing the constructor

GameState::GameState()
{ 
    selectedRow = 0;
    selectedColumn = 0;
    moveValid = true;
    gameOver = false;
    turn = true;
    winner = Empty; // empty is a global equal to 0
    //loop through gameBoard array, setting each element equal to Empty
    for (int row = 0; row < boardSize; row++) {
      for (int col = 0; col < boardSize; col++) {
        gameBoard[row][col] = Empty;
      }
    }

}

int GameState::get_selectedRow() { 
  return selectedRow;
}

int GameState::get_selectedColumn() {
  return selectedColumn;
}

// Set the selected row to value in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
void GameState::set_selectedRow(int value) { 

  if (value < 0||value > boardSize - 1) {
    return;
  } else {
    selectedRow = value;
    return;
  }

}

// Set the selected column in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
void GameState::set_selectedColumn(int value) {

  if (value < 0||value > boardSize - 1) {
    return;
  } else {
    selectedColumn = value;
    return;
  }

}

bool GameState::get_moveValid() {
  return moveValid;
}

// Get the gameOver value
bool GameState::get_gameOver() {
  return gameOver;
}

// Set the gameOver variable to value
void GameState::set_gameOver(bool value) {
  gameOver = value; return;
}

// Get the value of turn
bool GameState::get_turn() {
  return turn;
}

// Set the value of turn
void GameState::set_turn(bool value) {
  turn = value;
}

// Get the value of winner
int GameState::get_winner() {
  return winner;
}

// Set the value of winner;
void GameState::set_winner(int value) {
  winner = value;
}

// Get the game board value at the board location at row and col
// This method checks that row, col and value are in range/valid
// and if not it returns Empty
int GameState::get_gameBoard(int row, int col) {
  if (row<0||row>boardSize-1||col<0||col>boardSize-1) { //if row or col values are invalid
    return Empty;
  } else {
    return gameBoard[row][col];
  }
}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are in range/valid and if not it
// just returns
void GameState::set_gameBoard(int row, int col, int value) { //no need to check value
  if (row<0||row>boardSize-1||col<0||col>boardSize-1) { //if row or col values are invalid
    return;
  } else {
    gameBoard[row][col] = value;
  }
}