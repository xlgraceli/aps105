//
// Author: Grace Li
//

#include "reversi.h"
#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[][26], int n);
void printConfigBoard(char board[][26], int n);
void printBeginBoard(int n, char board[][26]);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
void printLegalMoves(char board[][26], int n, char colour);
void printMoves(char board[][26], int n);
bool checkLegalInMove(char board[][26], int n, int row, int col, char colour);
void flipTiles(char board[][26], int n, int row, int col, char colour);

int main(void) {
  int dim;
  char board[26][26];

  printf("Enter the board dimension: ");
  scanf("%d", &dim);

  printBeginBoard(dim, board); //initialize board
  printConfigBoard(board, dim); //configures board
  printLegalMoves(board, dim, 'W'); //outputs available moves for W
  printLegalMoves(board, dim, 'B'); //output available moves for B
  printMoves(board, dim); //outputs the board after a move is made
  return 0;
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

// prints out the configured board
void printConfigBoard(char board[][26], int n) {
  char colour = 0, row = 0, col = 0, garbage;
  printf("Enter board configuration:\n");
  for (int i = 0; colour != '!' && row != '!' && col != '!'; i++) {
    scanf(" %c%c%c", &colour, &row, &col);
    board[row - 'a'][col - 'a'] = colour;
  }

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

// checks whether (row , col) [labelled as letters] lies in the board
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
    
    //continue searching in this direction
    newRow += deltaRow;
    newCol += deltaCol;
  }
  return false;
}

// prints out the legal moves after configuration
void printLegalMoves(char board[][26], int n, char colour){
  printf("Available moves for %c:\n", colour);
  for (int row = 0; row < n; row++){
    for (int col = 0; col < n; col++){
      if (board[row][col] == 'U') {
        bool validMove = false; //ensures no dups
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++){
            if (!(deltaRow == 0 && deltaCol == 0)){ 
              if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)){
                printf("%c%c\n", (char)('a' + row), (char)('a' + col));
                validMove = true;
                break;
              }
            }
          }
          if (validMove) {
            break;
          }
        }
      }
    }
  } 
}

//prompts user for move and will output the board after move if legal
void printMoves(char board[][26], int n) {
  char colour, row, col, tempBoardVal;
  printf("Enter a move:\n");
  scanf(" %c%c%c", &colour, &row, &col);
  tempBoardVal = board[row - 'a'][col - 'a'];
  board[row - 'a'][col - 'a'] = colour;
  if (checkLegalInMove(board, n, row-'a', col-'a', colour)){
    printf("Valid move.\n");
    flipTiles(board, n, row-'a', col-'a', colour);
    printBoard(board, n);
  }else{
    printf("Invalid move.\n");
    board[row - 'a'][col - 'a'] = tempBoardVal;
    printBoard(board, n);
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