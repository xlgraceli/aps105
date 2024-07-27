#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//all 8 directions: SE, S, SW, W, NW, N, NE, E
const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1}; //rows
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1}; //columns

void readWordPuzzle(const int Size, char puzzle[][Size]);
char* readWord(int* wordSize);
void printWordPuzzle(const int Size, char puzzle[][Size]);
void printWord(char* word, const int wordSize);

void search(const int Size,
            char puzzle[][Size],
            const int wordSize,
            char* word);

bool inBounds(int row, int col, const int Size);

int main(void) {
  const int Size = 20;
  char puzzle[Size][Size];
  readWordPuzzle(Size, puzzle);
  int wordSize = 0;
  char* word = readWord(&wordSize);
  printWordPuzzle(Size, puzzle);
  printf("The word you are looking for is\n");
  printWord(word, wordSize);
  printf("\n");
  printf("Do you want to search? (Y or N)\n");
  char isSearch;
  scanf(" %c", &isSearch);
  if (isSearch == 'Y' || isSearch == 'y') {
    search(Size, puzzle, wordSize, word);
  }
  free(word);
  return 0;
}

void search(const int Size, char puzzle[][Size], const int wordSize, char* word) {
    int drow, dcol, curRow, curCol;
    for (int row = 0; row < Size; row++){
        for (int col = 0; col < Size; col++){
            for (int dir = 0; dir < 8; dir++){ //search for word starting from (row, col)
                drow = dr[dir];
                dcol = dc[dir];

                curRow = row;
                curCol = col;

                int i;
                for (i = 0; i < wordSize; i++){
                    if (!inBounds(curRow, curCol, Size) || puzzle[curRow][curCol] != word[i]){
                        break;
                    }
                    curRow += drow;
                    curCol += dcol;
                }

                if (i == wordSize){
                    printWord(word, wordSize);
                    printf(" can be found at row , col = (%d, %d) in the ", row+1, col+1);
                    switch (dir) {
                        case 0: printf("north-west direction.\n"); break;
                        case 1: printf("north direction.\n"); break;
                        case 2: printf("north-east direction.\n"); break;
                        case 3: printf("west direction.\n"); break;
                        case 4: printf("east direction.\n"); break;
                        case 5: printf("south-west direction.\n"); break;
                        case 6: printf("south direction.\n"); break;
                        case 7: printf("south-east direction.\n"); break;
                    }
                    return;
                }
            }
        }
    }
    printWord(word, wordSize);
    printf(" cannot be found!\n");

}

char* readWord(int* wordSize) {
  printf("\nHow many characters are there in the word?\n");
  scanf("%d", wordSize);

  char* word = (char*)malloc((*wordSize + 1) * sizeof(char));

  printf("What is the word that you are looking for?\n");
  for (int i = 0; i < *wordSize; i++){
    scanf(" %c", &word[i]);
  }
  word[*wordSize] = '\0';

  return word;
}

void readWordPuzzle(const int Size, char puzzle[][Size]) {
  char ch;
  printf("Please enter the word puzzle: ");
  for (int i = 0; i < Size; i++){
    for (int j = 0; j < Size; j++){
      scanf(" %c", &ch);
      puzzle[i][j] = ch;
    }
  }
}

bool inBounds(int row, int col, const int Size) {
    return row >= 0 && row < Size && col >= 0 && col < Size;
}

void printWordPuzzle(const int Size, char puzzle[][Size]) {
  printf("The word puzzle entered is\n");
  for (int i = 0; i < Size; i++){
    for (int j = 0; j < Size; j++){
      printf("%c", puzzle[i][j]);
    }
  }
  printf("\n");
}

void printWord(char* word, const int wordSize) {
  for (int i = 0; i < wordSize; i++){
    printf("%c", word[i]);
  }
}