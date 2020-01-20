/************************************************************************************
 * Code by ff19085, Yinan Yang.
 *
 * This is parse and interpret for nal's language.
 * I define INTERPRET switch (via makefile to pass in) so that only the extra code for
 * the interpreter is inside #ifdef INTERPRET #endif
 *
 * There are several steps to complete this C language interpreter:
 * ***************************parse precess******************************************
 *  1.  read in from .nal file and change words flow to token flow
 *  2.  grammar check from token flow
 * ***************************parse precess******************************************
 * ***********************interpret precess******************************************
 *  3.  identify token to run every command and create various table
 *  4.  recursive every command to the end of token flow
 * ***********************interpret precess******************************************
 *
 * I create enumerated type to keep token-name, and attribute-value in char type to
 * describe value in various table. So in this way, I create two types of link
 * structure to keep both token flow and various table: MVM and Table
 *
 * To correspond to the above behavior, I also create two type of stack to grammar
 * checker and calculator.
 *
 * EXTENSION:
 * What I do in extension part is I create sample math calculator by using math
 * expression. The grammar like this:
 * <MATH SET>:= <NUMVAR> = <MATH EXPRESSION> ";"
 * <MATH EXPRESSION>:= <NUMVAR>|<NUMCON>|"+"|"-"|"*"|"/"|"("|")"
 * Emp:     %A = %B + %C * ( %D - 1 ) / 2 ;
 * More details in extension.txt
 *
 * ********************************************************************************/
#ifdef INTERPRET
    #define INTERPRET 0
#else
    #define INTERPRET 1
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define MAX_TOKEN_SIZE 255
#define ROT13 13
#define ROT5 5
#define STACK_INIT_SIZE 100000
#define STACRINCREMENT 10
#define RANDOM_MAX 100
#define DIGITS 16
#define ERROR(PHRASE,FILENAME) {fprintf(stderr,"Fatal Error %s occured in file %s\n",\
PHRASE,FILENAME); exit(2); }

/*enumerated type to keep token-name*/
typedef enum{
    NAL_UNDEFINE,
    NAL_EQUAL,			/* = */
    NAL_L_BRACES,		/* { */
    NAL_R_BRACES,		/* } */
    NAL_L_PARENTHESES,	/* ( */
    NAL_R_PARENTHESES,	/* ) */
    NAL_COMMA,			/* , */
    NAL_FILE,			/* FILE */
    NAL_PRINT,			/* PRINT */
    NAL_PRINTN,			/* PRINTN */
    NAL_STRCON,			/* "string" */
    NAL_STRVAR,			/* $A */
    NAL_NUMCON,			/* 123 */
    NAL_NUMVAR,			/* %A */
    NAL_RND,			/* RND */
    NAL_INC,			/* INC */
    NAL_INNUM,			/* INNUM */
    NAL_IN2STR,         /* IN2STR */
    NAL_IFGREATER,		/* IFGREATER */
    NAL_IFEQUAL,		/* IFEQUAL */
    NAL_JUMP,			/* JUMP */
    NAL_ABORT,			/* ABORT */
    NAL_NEWLINE,        /* NEW LINE */
    NAL_SPACE,          /* SPACE */
    NAL_PLUS,           /* + */
    NAL_MINUS,          /* - */
    NAL_MULTIPY,        /* * */
    NAL_DIVISION,       /* / */
    NAL_SEMICOLON       /* ; */
} Symbol;

/*Structure of token flow*/
typedef struct mvmcell {
    Symbol key;
    char* data;
    struct mvmcell* next;
}mvmcell;

typedef struct mvm {
    mvmcell* head;
    int numkeys;
}mvm;

/*Structure of various table with three property:
 * key is for name of various
 * data is for value of varous
 * property if for various type like NUMVAR or STRVAR
 * */
typedef struct node {
    char* key;
    char* data;
    Symbol property;
    struct node *next;
}Node;

typedef struct table {
    Node* head;
    int numkeys;
}Table;

/*This is a token stack to complete parentheses check*/
typedef struct Stack
{
    Symbol *base;
    Symbol *top;
    int stacklen;
}Stack;

/*This is a various and calculator symbol stack for
 * calculator*/
typedef struct StackMvm
{
    mvmcell *base;
    mvmcell *top;
    int stacklen;
}StackMvm;

/*basic structure of parse and interpreter*/

/*generate lexeme flow by token*/
mvm *lexicalAnalysis(char *argv,mvm *lexeme);
/*get next token*/
Symbol nextToken(FILE *fp,char **word,char *filename);
/*match token to symbol in grammar*/
Symbol symbolMatch(char *word);
/*get word and string in words flow*/
char *getWord(int ch, FILE *fp,char *word);
char *getString(int ch,FILE *fp,char *word,char *filename);
/*change ROT18 code to normal order letter*/
char *rotchange(char *word);
/*main structure to parse and grammar checker*/
void grammarCheck(mvm *lexeme,char *filename,Table *table);
/*Using stack to check parentheses and brace*/
int validParentheses(mvm *lexeme);
/*move to next token in link*/
void movePointer(mvmcell **p,char *filename);
/*start of program*/
void program(mvmcell **p,char *filename,Table *table,mvm *lexeme);
/*main structure of recursive*/
void instrs(mvmcell **p,char *filename,Table *table,int flag,mvmcell *head,mvm *lexeme,Stack *st);
/*token match to every command in grammar*/
void instruct(mvmcell **p,char *filename,Table *table,mvmcell *head,mvm *lexeme,Stack *st);
void print(mvmcell **p,char *filename,Table *table,Symbol flag);
void set(mvmcell **p,char *filename,Table *table);
void ifCond(mvmcell **p,char *filename,Symbol logic,Table *table,mvmcell *head,mvm *lexeme, Stack *st);
void jump(mvmcell **p,char *filename,mvmcell *head,int n);
void file(mvmcell **p,char *filename,Table *table);
void rnd(mvmcell **p,char *filename,Table *table);
void inc(mvmcell **p,char *filename,Table *table);
void innum(mvmcell **p,char *filename,Table *table);
void in2str(mvmcell **p,char *filename,Table *table);

/*function using in interpret process*/

/*to check various in IF command*/
int ifVarIsVaild(mvmcell *var1,mvmcell *var2,Symbol logic,char *filename);
/*get value in various table*/
char *getValue(mvmcell *var,Table *table,char *filename);
/*if IFGREATER should work*/
int ifGreaterIsVaild(char *value1,char *value2);
/*change int to string to keep in table*/
void int2string(double slope,char *buffer);
/*to check decimal part in double type,
 * if the various value is 3.00000000,
 * only print 3*/
int decimalTest(char *data);
/*print the main part for double type*/
void putsWithoutDecimal(char *data);

/*the main function in calculator*/

/*check if it is a math expression by find a ";"*/
int mathExpression(mvmcell **endTest,char *filename);
/*main part in calculator, to calculate from Reverse Polish notation*/
char *calculator(mvmcell *start,mvmcell *end,char *filename,Table *table);
/*change math expression to Reverse Polish notation*/
void toRPN(mvm **RPN, mvmcell *start,mvmcell *end);
/*get various data from table*/
double getData(mvmcell a, Table *table, char *filename);

/*Structure operate function*/

/*create token flow*/
mvm* mvm_init(void);
void mvm_free(mvm** p);
void free_linked_list(mvmcell **head);
void mvm_insert(mvm* m, Symbol key, char* data);

/*token flow stack to check Parentheses*/
void initStack(Stack *s);
void push(Stack *s,Symbol e);
void pop(Stack *s,Symbol *e);
void freeStack(Stack *s);
int StackLen(Stack s);

/*various stack to calculator*/
void freeStackMvmcell(StackMvm *s);
int StackLenMvmcell(StackMvm s);
void popMvmcell(StackMvm *s,mvmcell *e);
void pushMvmcell(StackMvm *s_mvm,mvmcell e);
void initMvmcellStack(StackMvm *s_mvm);

/*various table to keep various, search various and update new value*/
Table *table_init(void);
void table_insert(Table * m, char* key, char* data,Symbol property);
void table_free(Table ** p);
char* table_search(Table * m, char* key,Symbol property);
void free_table_linked_list(Node **head);
void tableUpdate(Table *table, char *key, char *data,Symbol property);

void test(void);
