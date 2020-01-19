#ifdef INTERPRET
    #define INTERPRET 1
#else
    #define INTERPRET 0
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

typedef struct mvmcell {
    Symbol key;
    char* data;
    struct mvmcell* next;
}mvmcell;

typedef struct mvm {
    mvmcell* head;
    int numkeys;
}mvm;

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

typedef struct Stack
{
    Symbol *base;
    Symbol *top;
    int stacklen;
}Stack;

typedef struct StackMvm
{
    mvmcell *base;
    mvmcell *top;
    int stacklen;
}StackMvm;


mvm *lexicalAnalysis(char *argv,mvm *lexeme);
Symbol nextToken(FILE *fp,char **word,char *filename);
Symbol symbolMatch(char *word);
char *getWord(int ch, FILE *fp,char *word);
char *getString(int ch,FILE *fp,char *word,char *filename);
char *rotchange(char *word);
void grammarCheck(mvm *lexeme,char *filename,Table *table);
int validParentheses(mvm *lexeme);
void movePointer(mvmcell **p,char *filename);
void program(mvmcell **p,char *filename,Table *table,mvm *lexeme);
void instrs(mvmcell **p,char *filename,Table *table,int flag,mvmcell *head,mvm *lexeme,Stack *st);
void instruct(mvmcell **p,char *filename,Table *table,mvmcell *head,mvm *lexeme,Stack *st);
void print(mvmcell **p,char *filename,Table *table,Symbol flag);
void set(mvmcell **p,char *filename,Table *table);
void ifCond(mvmcell **p,char *filename,Symbol logic,Table *table,mvmcell *head,mvm *lexeme, Stack *st);
void jump(mvmcell **p,char *filename,mvmcell *head);
void file(mvmcell **p,char *filename,Table *table);
void rnd(mvmcell **p,char *filename,Table *table);
void inc(mvmcell **p,char *filename,Table *table);
void innum(mvmcell **p,char *filename,Table *table);
void in2str(mvmcell **p,char *filename,Table *table);

int ifVarIsVaild(mvmcell *var1,mvmcell *var2,Symbol logic);
char *getValue(mvmcell *var,Table *table,char *filename);
int ifGreaterIsVaild(char *value1,char *value2);
void int2string(double slope,char *buffer);
int decimalTest(char *data);
void putsWithoutDecimal(char *data);

int mathExpression(mvmcell **endTest,char *filename);
char *calculator(mvmcell *start,mvmcell *end,char *filename,Table *table);
void toRPN(mvm **RPN, mvmcell *start,mvmcell *end);
double getData(mvmcell a, Table *table, char *filename);

mvm* mvm_init(void);
void mvm_free(mvm** p);
void free_linked_list(mvmcell **head);
void mvm_insert(mvm* m, Symbol key, char* data);

void initStack(Stack *s);
void push(Stack *s,Symbol e);
void pop(Stack *s,Symbol *e);
void freeStack(Stack *s);
int StackLen(Stack s);

void freeStackMvmcell(StackMvm *s);
int StackLenMvmcell(StackMvm s);
void popMvmcell(StackMvm *s,mvmcell *e);
void pushMvmcell(StackMvm *s_mvm,mvmcell e);
void initMvmcellStack(StackMvm *s_mvm);

Table *table_init(void);
void table_insert(Table * m, char* key, char* data,Symbol property);
void table_free(Table ** p);
char* table_search(Table * m, char* key,Symbol property);
void free_table_linked_list(Node **head);
void tableUpdate(Table *table, char *key, char *data,Symbol property);
