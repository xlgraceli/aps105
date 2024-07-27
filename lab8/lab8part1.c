//
// Author: Grace Li
//

#include "lab8part1.h"
#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
void printBeginBoard(int n, char board[][26]);
bool positionInBounds(int n, int row, int col);
bool availableMovesLeft(char board[][26], int n, char colour);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
void printMoves(char board[][26], int n, char colour, char row, char col, bool *end);
bool checkLegalInMove(char board[][26], int n, int row, int col, char colour);
void flipTiles(char board[][26], int n, int row, int col, char colour);
bool isFull(char board[][26], int n);
int computeScore(char board[][26], int n, int row, int col, char colour);
void computerMove(char board[][26], int n, char colour);

int main(void) {
  int dim;
  char board[26][26];
  char compColour, userColour, uRow, uCol;
  bool end = false, noMoreUser = false, noMoreComp = false;

  printf("Enter the board dimension: ");
  scanf("%d", &dim);

  printf("Computer plays (B/W): ");
  scanf(" %c", &compColour);
  printBeginBoard(dim, board); //initialize board

  if (compColour == 'B'){
    userColour = 'W';
    while (!isFull(board, dim) && !end){
      //computer moves
      if (availableMovesLeft(board, dim, compColour)){
        computerMove(board, dim, compColour);
        if (isFull(board, dim)) {
          break;
        }
        noMoreComp = false;
      }else{
        printf("%c player has no valid move.\n", compColour);
        noMoreComp = true;
      }
      if (noMoreUser && noMoreComp){
        break;
      }

      //user moves
      if(availableMovesLeft(board, dim, userColour)){
        printf("Enter move for colour W (RowCol): ");
        scanf(" %c%c", &uRow, &uCol);
        printMoves(board, dim, userColour, uRow, uCol, &end);
        if (isFull(board, dim) || end) {
          break;
        }
        noMoreUser = false;
      }else{
        printf("%c player has no valid move.\n", userColour);
        noMoreUser = true;
      }
      if (noMoreUser && noMoreComp){
        break;
      }
      
    }
  }else{
    userColour = 'B';
    while (!isFull(board, dim) && !end){
      //user moves
      if (availableMovesLeft(board, dim, userColour)){
        printf("Enter move for colour B (RowCol): ");
        scanf(" %c%c", &uRow, &uCol);
        printMoves(board, dim, userColour, uRow, uCol, &end);
        if (isFull(board, dim) || end) {
          break;
        }
        noMoreUser = false;
      }else{
        printf("%c player has no valid move.\n", userColour);
        noMoreUser = true;
      }
      if (noMoreUser && noMoreComp){
        break;
      }

      //computer moves
      if (availableMovesLeft(board, dim, compColour)){
        computerMove(board, dim, compColour);
        if (isFull(board, dim)) {
          break;
        }
        noMoreComp = false;
      }else{
        printf("%c player has no valid move.\n", compColour);
        noMoreComp = true;
      }
      if (noMoreUser && noMoreComp){
        break;
      }
      
    }
  }

  //determining which player wins
  int black = 0, white = 0;
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (board[i][j] == 'B') {
        black++;
      } else if (board[i][j] == 'W') {
        white++;
      }
    }
  }

  if (black > white){
    printf("B player wins.\n");
  }else{
    printf("W player wins.\n");
  }
  return 0;
}

//checks if board is full or not
bool isFull(char board[][26], int n){
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U'){
        return false;
      }
    }
  }
  return true;
}

// prints the game board after moves
void printBoard(char board[][26], int n) {
  printf("  ");
  for (int i = 0; i < n; i++) {
    printf("%c", (char)('a' + i));
  }
  printf("\n");

  for (int row = 0; row < n; row++) {
    printf("%c ", (char)('a' + row));
    for (int col = 0; col < n; col++) {
      printf("%c", board[row][col]);
    }
    printf("\n");
  }
}

//outputs the best move for the computer
void computerMove(char board[][26], int n, char colour) {
  int maxScore = -1;
  int bestRow = -1, bestCol = -1, score;

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == 'U' && checkLegalInMove(board, n, row, col, colour)) {
        score = computeScore(board, n, row, col, colour);
        if (score > maxScore || (score == maxScore && row < bestRow) || (score == maxScore && row == bestRow && col < bestCol)) {
          maxScore = score;
          bestRow = row;
          bestCol = col;
        }
      }
    }
  }
  // Place computer's tile at the best position
  if (bestRow == -1 && bestCol == -1){
    printf("%c player has no valid move.\n", colour);
  }else{
    board[bestRow][bestCol] = colour;
    printf("Computer places %c at %c%c.\n", colour, (char)('a' + bestRow), (char)('a' + bestCol));
    flipTiles(board, n, bestRow, bestCol, colour);
    printBoard(board, n);
  }
}

//computes the score after flipping a certain tile
int computeScore(char board[][26], int n, int row, int col, char colour) {
  char oppColour;
  if (colour == 'W') {
      oppColour = 'B';
  }else {
      oppColour = 'W';
  }

  int score = 0, newRow, newCol;

  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      //Skip the current position (row, col)
      if (deltaRow == 0 && deltaCol == 0) {
        continue;
      }
      newRow = row + deltaRow;
      newCol = col + deltaCol;

      bool validSequence = false;

      //number of opponent's tiles that can be flipped
      int tilesToFlip = 0;

      while (positionInBounds(n, newRow, newCol) && board[newRow][newCol] == oppColour) {
        tilesToFlip++;
        newRow += deltaRow;
        newCol += deltaCol;
        validSequence = true;
      }

      if (validSequence && positionInBounds(n, newRow, newCol) && board[newRow][newCol] == colour) {
        score += tilesToFlip;
      }
    }
  }

  // Return the computed score
  return score;
}

// prints out the initial game board
void printBeginBoard(int n, char board[][26]) {
  int border = 'a';
  for (int row = 0; row < n + 1; row++) {
    for (int col = -1; col < n + 1; col++) {
      if (row == 0 && col < 1 || col == 0) {
        printf(" ");
      } else if (row == 0) {
        printf("%c", (char)(border + col - 1));
      } else if (col == -1) {
        printf("%c", (char)(border + row - 1));
      } else {
        if ((row == n / 2 || row == n / 2 + 1) && row == col) {
          printf("W");
          board[row - 1][col - 1] = 'W';
        } else if ((row == n / 2 && row == col - 1) ||
                   (row == n / 2 + 1 && row == col + 1)) {
          printf("B");
          board[row - 1][col - 1] = 'B';
        } else {
          printf("U");
          board[row - 1][col - 1] = 'U';
        }
      }
    }
    printf("\n");
  }
}

// checks whether (row , col) lies in the board
bool positionInBounds(int n, int row, int col) {
  if ((row >= 0 && row < n) && (col >= 0 && col < n)) {
    return true;
  } else {
    return false;
  }
}

// checks whether it is a legal move
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  int newRow = row + deltaRow;
  int newCol = col + deltaCol;
  
  char oppositeColour;
  if (colour == 'W'){
    oppositeColour = 'B';
  }else{
    oppositeColour = 'W';
  }

  if (!positionInBounds(n, newRow, newCol) || board[newRow][newCol] != oppositeColour){
    return false;
  }

  while (positionInBounds(n, newRow, newCol)) {
    if (board[newRow][newCol] == 'U') {
        return false;  
    }

    if (board[newRow][newCol] == colour) {
        return true;
    }
    
    newRow += deltaRow;
    newCol += deltaCol;
  }
  return false;
}

bool availableMovesLeft(char board[][26], int n, char colour){
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == 'U') {
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
            if (!(deltaRow == 0 && deltaCol == 0)){ 
              if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
                return true;
              }
            }
          }
        }
      }
    }
  } 
  return false;
}

//Will output the board after move if legal
void printMoves(char board[][26], int n, char colour, char row, char col, bool *end) {
  if (checkLegalInMove(board, n, row-'a', col-'a', colour)){
    board[row - 'a'][col - 'a'] = colour;
    flipTiles(board, n, row-'a', col-'a', colour);
    printBoard(board, n);
  }else{
    printf("Invalid move.\n");
    *end = true; //terminates game
  }
}

//checks whether the move made by user is valid or not
bool checkLegalInMove(char board[][26], int n, int row, int col, char colour) {
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (!(deltaRow == 0 && deltaCol == 0) && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
        return true;
      }
    }
  }
  return false;
}

//flips the colour of the tile that the selected tile passes
void flipTiles(char board[][26], int n, int row, int col, char colour){
  for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
    for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
      if (!(deltaRow == 0 && deltaCol == 0) && checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)) {
        int newRow = row + deltaRow;
        int newCol = col + deltaCol;
        while(board[newRow][newCol] != colour){
          board[newRow][newCol] = colour;
          newRow += deltaRow;
          newCol += deltaCol;
        }
      }
    }
  }
}