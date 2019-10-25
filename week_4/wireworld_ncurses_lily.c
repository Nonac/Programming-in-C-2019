#include "neillncurses.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ROW 40
#define COLUMN 40
#define GENS 1000


void nGenerationsToFile(FILE *ofp, char wire[ROW][COLUMN],char new_wire[ROW][COLUMN]);
void nextGeneration(char wire[ROW][COLUMN],char new_wire[ROW][COLUMN]);
char nextGenerationOfChar(char ch, int row, int column, char wire[ROW][COLUMN]);
int countNeighbours(int row, int column, char wire[ROW][COLUMN]);
int notOverflow(int x, int y);
void readFromFile(FILE *fp, char wire[ROW][COLUMN]);
void writeToFile(FILE *fp, char new_wire[ROW][COLUMN]);
void test(void);

int main(int argc, char *argv[])
{
  /* Array we'll display */
  char wire[ROW][COLUMN], new_wire[ROW][COLUMN];
  FILE *ifp;

  /* Here's where we hold all the information we need to display
     the array in the correct colours, and also event information */
  NCURS_Simplewin sw;

  test();
  if(argc == 2){
    ifp = fopen(argv[1], "r");
    if (ifp == NULL) {
      printf("Failed to open the file.\n");
      return 1;
    }
      readFromFile(ifp, wire);
      fclose(ifp);
  } else {
    printf("ERROR: Incorrect usage. try e.g %s file.txt\n", argv[0]);
    return 1;
  }

  Neill_NCURS_Init(&sw);
  /* For the character 'H', use blue foreground colour, blue background,
     and the alternative character set */
  Neill_NCURS_CharStyle(&sw, "H", COLOR_BLUE, COLOR_BLUE, A_NORMAL);
  /* For the characters 't', use red foreground colour, red background,
     and the alternative character set */
  Neill_NCURS_CharStyle(&sw, "t", COLOR_RED, COLOR_RED, A_NORMAL);
  /* For the characters 'c', use yellow foreground colour, yellow background,
     and the alternative character set */
  Neill_NCURS_CharStyle(&sw, "c", COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);
  /* For the characters ' ', use black foreground colour, black background,
     and the alternative character set */
  Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);

  do{
     Neill_NCURS_PrintArray(&wire[0][0], ROW, COLUMN, &sw);
     nextGeneration(wire, new_wire);
     /*  Delay in 1/1000s of a second */
     Neill_NCURS_Delay(1000.0);
     /* Test for mouse click, or ESC key */
     Neill_NCURS_Events(&sw);
  }while(!sw.finished);
  /* Call this function if we exit() anywhere in the code */
  atexit(Neill_NCURS_Done);

  exit(EXIT_SUCCESS);

}

/*generate the next generation array*/
void nextGeneration(char wire[ROW][COLUMN],char new_wire[ROW][COLUMN])
{
  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COLUMN; j++) {
      new_wire[i][j] = nextGenerationOfChar(wire[i][j], i, j, wire);
    }
  }
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COLUMN; j++) {
      wire[i][j] = new_wire[i][j];
    }
  }
}
/*generate and return the next generation of a character*/
char nextGenerationOfChar(char ch, int row, int column, char wire[ROW][COLUMN])
{
  int number;

  switch(ch) {
    case '\0': /*This line is added so that the test can execute correctly*/
    case ' ': return ' ';
    case 'H': return 't';
    case 't': return 'c';
    case 'c':
      number = countNeighbours(row, column, wire);
      if ( number == 1 || number == 2)
        return 'H';
      else
        return 'c';
    default :   /*if the input is incorrect, exit */
      printf("error input!\n");
      exit(1);
      return 0;
  }
}
/* count and return the number of heads around a character */
int countNeighbours(int row, int column, char wire[ROW][COLUMN])
{
  int count = 0, i ,j;

  for (i = -1; i <= 1; i++) {
    for (j = -1; j <= 1; j++) {
      /*When out of array range, don't do judgment */
      if (notOverflow(row+i, column+j)) {
        if (wire[row+i][column+j] == 'H')
          count++;
      }
    }
  }
  return count;
}
/*Determines whether a array is overflowing, When out of array range, return 0*/
int notOverflow(int x, int y)
{
  if ( x < 0 ) return 0;
  if ( x >= ROW ) return 0;
  if ( y < 0 ) return 0;
  if ( y >= COLUMN ) return 0;
  return 1;
}
/*read data from fp and write to wire[][]*/
void readFromFile(FILE *fp, char wire[ROW][COLUMN])
{
  int i = 0, j = 0;
  char ch;

  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COLUMN; j++) {
      wire[i][j] = getc(fp);
    }
    ch = getc(fp); /*get '\n' at the end of every line*/
/*if the input file is invaild, exit*/
    if (ch != '\n' && ch != EOF) {
      printf("the input file is invaild!\n ");
      exit(1);
    }
  }
}

void test(void)
{
  char newarr[ROW][COLUMN];
  char testarr[ROW][COLUMN] = {{' ','c','t','H','H'},
                               {'c',' ',' ','c','H'},
                               {' ','c','c','c','c'},
                               {'t','c','H',' ','c'},
                               {'c','c',' ','c','c'}};
                             
/* test notOverflow fuction */
  assert(notOverflow(0, 3) == 1);
  assert(notOverflow(20, 20) == 1);
  assert(notOverflow(-1, 0) == 0);
  assert(notOverflow(41, 1) == 0);
  assert(notOverflow(1, -1) == 0);
  assert(notOverflow(1, 41) == 0);
/* test countNeighbours fuction */
  assert(countNeighbours(0, 1, testarr) == 0);
  assert(countNeighbours(2, 2, testarr) == 1);
  assert(countNeighbours(2, 3, testarr) == 2);
  assert(countNeighbours(1, 3, testarr) == 3);
/* test nextGenerationOfChar fuction */
  assert(nextGenerationOfChar(testarr[4][2], 4, 2, testarr) == ' ');/*\0->\0*/
  assert(nextGenerationOfChar(testarr[0][4], 0, 4, testarr) == 't'); /*H->t*/
  assert(nextGenerationOfChar(testarr[3][0], 3, 0, testarr) == 'c'); /*t->c*/
  assert(nextGenerationOfChar(testarr[2][2], 2, 2, testarr) == 'H'); /*c->H*/
  assert(nextGenerationOfChar(testarr[1][3], 1, 3, testarr) == 'c'); /*c->c*/
/* test nextGeneration fuction */
  nextGeneration(testarr, newarr);
  assert(newarr[4][2] == ' ');
  assert(newarr[0][4] == 't');
  assert(newarr[3][0] == 'c');
  assert(newarr[2][2] == 'H');
  assert(newarr[1][3] == 'c');
}
