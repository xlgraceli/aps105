//
// Author: Grace Li
//

#include "liblab8part2.h"
#include "lab8part2.h"
#include <stdio.h>
#include <stdbool.h>

//part 1
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

//part 2
int makeMove(const char board[][26], int n, char turn, int *row, int *col);
int alphabeta(char board[][26], int n, int depth, int alpha, int beta, char colour);
int evaluate(char board[][26], int n, char colour);

int main(void) {
  int dim;
  bool isFirstGame = true;
  char board[26][26];
  char compColour, userColour, uRow, uCol;
  int temp; //temporary placeholder for makeMove
  bool end = false, noMoreUser = false, noMoreComp = false;
  int row, col; //computer row col

  printf("Enter the board dimension: ");
  scanf("%d", &dim);

  printf("Computer plays (B/W): ");
  scanf(" %c", &compColour);
  printBeginBoard(dim, board); //initializes board

  if (compColour == 'B'){
    userColour = 'W';
    while (!isFull(board, dim) && !end){
      //computer moves
      if (availableMovesLeft(board, dim, compColour)){
        findSmarterMove(board, dim, compColour, &row, &col);
        printf("Computer places %c at %c%c.\n", compColour, row + 'a', col + 'a');
        board[row][col] = compColour;
        flipTiles(board, dim, row, col, compColour);
        printBoard(board, dim);
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
        // printf("Enter move for colour W (RowCol): ");
        // scanf(" %c%c", &row, &col);
        // printMoves(board, dim, userColour, row, col, &end);

        temp = makeMove(board, dim, userColour, &row, &col);
        printf("Enter move for colour W (RowCol): %c%c\n", row+'a', col+'a');
        printMoves(board, dim, userColour, row+'a', col+'a', &end);
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
        // printf("Enter move for colour B (RowCol): ");
        // scanf(" %c%c", &row, &col);
        // printMoves(board, dim, userColour, row, col, &end);
        
        temp = makeMove(board, dim, userColour, &row, &col);
        printf("Enter move for colour W (RowCol): %c%c\n", row + 'a', col + 'a');
        printMoves(board, dim, userColour, row+'a', col+'a', &end);
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
        findSmarterMove(board, dim, compColour, &row, &col);
        printf("Computer places %c at %c%c.\n", compColour, row + 'a', col + 'a');
        board[row][col] = compColour;
        flipTiles(board, dim, row, col, compColour);
        printBoard(board, dim);
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

//computes the best move for the AI player
int makeMove(const char board[][26], int n, char turn, int *row, int *col){
    char temp[26][26];
    for (int r = 0; r < n; r++){
      for (int c = 0; c < n; c++){
        temp[r][c] = board[r][c];
      }
    }

    int maxScore = -99, score = 0;

    for (int i = 0; i < n; i++) { //row
      for (int j = 0; j < n; j++) { //col
        if (board[i][j] == 'U' && checkLegalInMove(temp, n, i, j, turn)) {
          temp[i][j] = turn;
          flipTiles(temp, n, i, j, turn);
          score = alphabeta(temp, n, 3, maxScore, 100, (turn == 'W') ? 'B' : 'W');
          for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    temp[r][c] = board[r][c];
                }
            }
          if (score > maxScore) {
            maxScore = score;
            *row = i;
            *col = j;
          }
        } 
      }
    }

    // for (int i = 0; i < n; i++) { //row
    //     for (int j = 0; j < n; j++) { //col
    //         if (board[i][j] == 'U' && checkLegalInMove(temp, n, i, j, turn)) {
    //             score = computeScore(temp, n, i, j, turn);
    //             if ((i == 0 || i == n-1) && (j == 0 || j == n-1 )){
    //                 score *= 4;
    //             }else if (((i == 0 || i == n-1) && (j == 0 || j == 1 || j == n-1 || j == n-2)) || ((i == 0 || i == n-1) && (j == 1 || j == n-1))){
    //                 score *= 0.25;
    //             }else if (i == 1 || i == n-2 || j == 1 || j == n-2){
    //                 score *= 0.8;
    //             }else if (i == 0 || i == n-1 || j == 0 || j == n-1){
    //                 score *= 2;
    //             }
    //             if (score > maxScore) { 
    //                 maxScore = score;
    //                 *row = i;
    //                 *col = j;
    //             }
    //         }
    //     }
    // }

    return 0; 
}

int alphabeta(char board[][26], int n, int depth, int alpha, int beta, char colour){
  int bestScore, score;
  if (depth == 0 || isFull(board, n) || !availableMovesLeft(board, n, colour)) {
    return evaluate(board, n, colour);
  }

  if (colour == 'W'){
    bestScore = -1;
    for (int r = 0; r < n; r++){
      for (int c = 0; c < n; c++){
        if (board[r][c] == 'U' && checkLegalInMove(board, n, r, c, colour)){
          char temp[26][26];
          for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
              temp[i][j] = board[i][j];
            }
          }
          //make temp move
          temp[r][c] = 'W';
          flipTiles(temp, n, r, c, 'W');

          //minimax for the next player
          score = alphabeta(temp, n, depth - 1, alpha, beta, 'B');
          if (score > bestScore) {
              bestScore = score;
          }
          if (alpha < score) {
              alpha = score;
          }

          // Perform alpha-beta pruning
          if (beta <= alpha) {
              return beta;
          }
        }
      }
    }
    return bestScore;
  }else{
    int minScore = 100;
    for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++) {
        if (board[row][col] == 'U' && checkLegalInMove(board, n, row, col, 'B')) {
          char temp[26][26];
          for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
              temp[i][j] = board[i][j];
            }
          }
          // Make a temporary move
          temp[row][col] = 'B';
          flipTiles(board, n, row, col, 'B');
          
          //minimax for the next player
          int score = alphabeta(board, n, depth - 1, alpha, beta, 'W');
          
          //Update beta and best score
          if (score < minScore) {
              minScore = score;
          }
          if (beta > score) {
              beta = score;
          }

          // Perform alpha-beta pruning
          if (beta <= alpha) {
              return alpha;
          }
        }
      }
    }
    return minScore;
  }
}

//evaluates the board position for given colour
int evaluate(char board[][26], int n, char colour){
  int score = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == colour) {
          score++; //add point to current colour
      }else if (board[row][col] != 'U') {
          score--; //subtract point for each opp's colour
      }
    }
  }
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

//determines if there are any available moves left for either player
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