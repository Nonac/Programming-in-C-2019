/*the solution of wireworld:
1. create two 2D arrays: wire[][] and new_wire[][];
2. read the data from the source file(ifp) into wire[][] and then close ifp;
3. generate the next genration and store it in the new_wire[][];
4. write the data in the new_wire[][] to the target file(ofp);
5. repeat step 3 and step 4 1000 times.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ROW 40
#define COLUMN 40
#define GENERATION 1000

void executeWireworld(char *input_file_name);
void outputFileName(char *input_file_name, char output_file_name[]);
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
  test();
  if(argc == 2){
    executeWireworld(argv[1]);
  } else {
    printf("ERROR: Incorrect usage. try e.g %s file.txt\n", argv[0]);
  }
  return 0;
}
/* if the input is right, execute program*/
void executeWireworld(char *input_file_name)
{
  char wire[ROW][COLUMN], new_wire[ROW][COLUMN], output_file_name[50];
  FILE *ifp, *ofp;

  outputFileName(input_file_name, output_file_name);
  ifp = fopen(input_file_name, "r");
  ofp = fopen(output_file_name, "w");
  if (ifp == NULL || ofp == NULL) {
    printf("Failed to open two filenames.\n");
    exit(1);
  }
    readFromFile(ifp, wire);
    fclose(ifp);
    nGenerationsToFile(ofp, wire, new_wire);
    printf("1000 generations have also been written into %s\n",output_file_name);
    fclose(ofp);
}
/*get output filename according to input filename*/
void outputFileName(char *input_file_name, char output_file_name[])
{
  int i = 0;

  strcpy(output_file_name, input_file_name);
  while (output_file_name[++i] != '.');
  output_file_name[i] = '\0';
  strcat(output_file_name,"_output.txt");
}
/*generate 1000 generations array and write to ofp*/
void nGenerationsToFile(FILE *ofp, char wire[ROW][COLUMN],char new_wire[ROW][COLUMN])
{
  int i, j, cnt;

  for (cnt = 0; cnt < GENERATION; cnt++) {
    nextGeneration(wire, new_wire);
    writeToFile(ofp, new_wire);
    for (i = 0; i < ROW; i++) {
      for (j = 0; j < COLUMN; j++) {
        wire[i][j] = new_wire[i][j];
      }
    }
  }
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

/*write the data in the new_wire[][] to fp*/
void writeToFile(FILE *fp, char new_wire[ROW][COLUMN])
{
  int i, j;

  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COLUMN; j++) {
      putc(new_wire[i][j],fp);
      printf("%c",new_wire[i][j]);
    }
    putc('\n',fp);
    printf("\n");
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
