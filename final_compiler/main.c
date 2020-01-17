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
#define ERROR(PHRASE,FILENAME) {fprintf(stderr,"Fatal Error %s occured in file %s\n",\
PHRASE,FILENAME); exit(2); }

#define INTERPRET 1

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
    NAL_SPACE           /* SPACE */
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


mvm *lexicalAnalysis(char *argv,mvm *lexeme);
Symbol nextToken(FILE *fp,char *word,char *filename);
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
void print(mvmcell **p,char *filename,Table *table);
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
int ifGreaterIsVaild(char *value1,char *value2, char *filename);
void int2string(double slope,char *buffer);

mvm* mvm_init(void);
void mvm_free(mvm** p);
void free_linked_list(mvmcell **head);
void mvm_insert(mvm* m, Symbol key, char* data);

void initStack(Stack *s);
void push(Stack *s,Symbol e);
void pop(Stack *s,Symbol *e);
void freeStack(Stack *s);
int StackLen(Stack s);

Table *table_init(void);
void table_insert(Table * m, char* key, char* data,Symbol property);
void table_free(Table ** p);
char* table_search(Table * m, char* key,Symbol property);
void free_table_linked_list(Node **head);
void tableUpdate(Table *table, char *key, char *data,Symbol property);


int main()
{
    char *argv="escape211.nal";
    mvm *lexeme=mvm_init();
    Table *table=table_init();

    srand((unsigned)time(NULL));

    lexeme=lexicalAnalysis(argv,lexeme);
    grammarCheck(lexeme,argv,table);

    if(INTERPRET)
    {

    } else{
        printf("Parsed OK");
    }

    table_free(&table);
    mvm_free(&lexeme);
    return 0;
}

mvm *lexicalAnalysis(char *argv,mvm *lexeme)
{
    Symbol token;
    char *word;
    FILE *fp=fopen(argv,"r");

    while (!feof(fp))
    {
        word=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        token=nextToken(fp,word,argv);
        if(token!=NAL_UNDEFINE&&token!=NAL_NEWLINE&&token!=NAL_SPACE)
        {
            if(token==NAL_STRCON||token==NAL_STRVAR||token==NAL_NUMVAR||\
            token==NAL_NUMCON)
            {
                mvm_insert(lexeme,token,word);
                free(word);
            }else{
                mvm_insert(lexeme,token,"\0");
                free(word);
            }
        } else if(token!=NAL_NEWLINE&&token!=NAL_SPACE){
            ERROR("Unexpected token!",argv)
        }
    }
    fclose(fp);
    return lexeme;
}

void grammarCheck(mvm *lexeme,char *filename,Table *table)
{
    mvmcell *p=lexeme->head;
    if(!validParentheses(lexeme))
    {
        ERROR("Unexpected parentheses.",filename)
    }
    program(&p,filename,table,lexeme);
}

void movePointer(mvmcell **p,char *filename)
{
    if((*p)==NULL)
    {
        ERROR("Out of bound",filename)
    }
    if((*p)->next!=NULL)
    {
        *p=(*p)->next;
    } else{
        ERROR("Missing statement.",filename)
    }
}

void program(mvmcell **p,char *filename,Table *table,mvm *lexeme)
{
    mvmcell *head=(*p);
    Stack st;
    initStack(&st);
    if((*p)->key!=NAL_L_BRACES)
    {
        ERROR("No { statement ?",filename)
    }
    push(&st,(*p)->key);
    movePointer(p,filename);
    instrs(p,filename,table,1,head,lexeme,&st);
}

void instrs(mvmcell **p,char *filename,Table *table,int flag,mvmcell *head,mvm *lexeme,Stack *st)
{
    Symbol ch;
    if((*p)->key==NAL_R_BRACES && StackLen(*st)==1)
    {
            return;
    }
    if(flag)
    {
        instruct(p,filename,table,head,lexeme,st);
    }else if((*p)->key==NAL_L_BRACES){
        push(st,(*p)->key);
    }else if((*p)->key==NAL_R_BRACES){
        pop(st,&ch);
    }
    movePointer(p,filename);
    instrs(p,filename,table,flag,head,lexeme,st);
}

void instruct(mvmcell **p,char *filename,Table *table,mvmcell *head,mvm *lexeme,Stack *st)
{
    switch ((*p)->key){
        case NAL_PRINT:
            print(p,filename,table);
            return;
        case NAL_PRINTN:
            print(p,filename,table);
            return;
        case NAL_STRVAR:
            set(p,filename,table);
            return;
        case NAL_NUMVAR:
            set(p,filename,table);
            return;
        case NAL_IFEQUAL:
            ifCond(p,filename,NAL_IFEQUAL,table,head,lexeme,st);
            return;
        case NAL_JUMP:
            jump(p,filename,head);
            return;
        case NAL_FILE:
            file(p,filename,table);
            return;
        case NAL_RND:
            rnd(p,filename,table);
            return;
        case NAL_INC:
            inc(p,filename,table);
            return;
        case NAL_IFGREATER:
            ifCond(p,filename,NAL_IFGREATER,table,head,lexeme,st);
            return;
        case NAL_ABORT:
            table_free(&table);
            mvm_free(&lexeme);
            exit(0);
        case NAL_INNUM:
            innum(p,filename,table);
            return;
        case NAL_IN2STR:
            in2str(p,filename,table);
            return;
        case NAL_R_BRACES:
            movePointer(p,filename);
            return;
        default:
            ERROR("Unexpected head token in a statement",filename)
    }
}

void in2str(mvmcell **p,char *filename,Table *table)
{
    Symbol property1,property2;
    char *key1,*key2;
    char *data1, *data2;
    movePointer(p,filename);
    if((*p)->key!=NAL_L_PARENTHESES)
    {
        ERROR("No ( in IN2STR statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_STRVAR)
    {
        ERROR("No STRVAR in IN2STR statement ?",filename)
    }
    property1=(*p)->key;
    key1=(*p)->data;
    movePointer(p,filename);
    if((*p)->key!=NAL_COMMA)
    {
        ERROR("No , in IN2STR statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_STRVAR)
    {
        ERROR("No STRVAR in IN2STR statement ?",filename)
    }
    property2=(*p)->key;
    key2=(*p)->data;
    movePointer(p,filename);
    if((*p)->key!=NAL_R_PARENTHESES)
    {
        ERROR("No ) in IN2STR statement ?",filename)
    }
    if(INTERPRET)
    {
        data1=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        data2=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        scanf("%s",data1);
        scanf("%s",data2);
        if(table_search(table,key1,property1)==NULL)
        {
            table_insert(table,key1,data1,property1);
        } else{
            tableUpdate(table,key1,data1,property1);
        }
        if(table_search(table,key2,property2)==NULL)
        {
            table_insert(table,key2,data2,property2);
        } else{
            tableUpdate(table,key2,data2,property2);
        }
        free(data1);
        free(data2);
    }
}

void innum(mvmcell **p,char *filename,Table *table)
{
    double n;
    Symbol property;
    char *key;
    char *data;
    movePointer(p,filename);
    if((*p)->key!=NAL_L_PARENTHESES)
    {
        ERROR("No ( in INNUM statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_NUMVAR)
    {
        ERROR("No NUMVAR in INNUM statement ?",filename)
    }
    property=(*p)->key;
    key=(*p)->data;
    movePointer(p,filename);
    if((*p)->key!=NAL_R_PARENTHESES)
    {
        ERROR("No ) in INNUM statement ?",filename)
    }
    if(INTERPRET)
    {
        data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        scanf("%lf",&n);
        int2string(n,data);
        if(table_search(table,key,property)==NULL)
        {
            table_insert(table,key,data,property);
        } else{
            tableUpdate(table,key,data,property);
        }
        free(data);
    }
}

void inc(mvmcell **p,char *filename,Table *table)
{
    double n;
    Symbol property;
    char *key;
    char *data,*ori;

    movePointer(p,filename);
    if((*p)->key!=NAL_L_PARENTHESES)
    {
        ERROR("No ( in INC statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_NUMVAR)
    {
        ERROR("No NUMVAR in INC statement ?",filename)
    }
    property=(*p)->key;
    key=(*p)->data;
    movePointer(p,filename);
    if((*p)->key!=NAL_R_PARENTHESES)
    {
        ERROR("No ) in INC statement ?",filename)
    }
    if(INTERPRET)
    {
        ori=table_search(table,key,property);
        if(ori==NULL)
        {
            ERROR("Variable not declared",filename)
        }
        n=strtof(ori,NULL)+1;
        data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        int2string(n,data);
        tableUpdate(table,key,data,property);
    }
}

void rnd(mvmcell **p,char *filename,Table *table)
{
    double n=(double)(rand()%RANDOM_MAX);
    Symbol property;
    char *key;
    char *data;

    movePointer(p,filename);
    if((*p)->key!=NAL_L_PARENTHESES)
    {
        ERROR("No ( in RND statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_NUMVAR)
    {
        ERROR("No NUMVAR in RND statement ?",filename)
    }
    property=(*p)->key;
    key=(*p)->data;
    movePointer(p,filename);
    if((*p)->key!=NAL_R_PARENTHESES)
    {
        ERROR("No ) in RND statement ?",filename)
    }
    if(INTERPRET)
    {
        data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        int2string(n,data);
        table_insert(table,key,data,property);
        free(data);
    }
}

void int2string(double slope,char *buffer)
{
    int temp,i,j;
    temp = (int)slope;
    for(i=0;temp!=0;i++)
        temp /=10;
    temp =(int)slope;
    for(j=i-1;j>=0;j--)
    {
        buffer[j] = (temp%10)+'0';
        temp /=10;
    }
    buffer[i] = '.';
    slope -=(int)slope;
    for(i=i+1;i<strlen(buffer);i++)
    {
        slope*=10;
        buffer[i]=(int)slope+'0';
        slope-=(int)slope;
    }
    buffer[strlen(buffer)-1] = '\0';
}

void file(mvmcell **p,char *filename,Table *table)
{
    static char openedfile[MAX_TOKEN_SIZE];
    static int flag =0;
    mvm *lexeme_new=mvm_init();
    movePointer(p,filename);
    if (flag==0)
    {
        strcpy(openedfile,filename);
        flag++;
    }
    if((*p)->key!=NAL_STRCON)
    {
        ERROR("No STRCON in FILE statement ?",filename)
    }
    if(INTERPRET)
    {
        lexeme_new=lexicalAnalysis((*p)->data,lexeme_new);
        grammarCheck(lexeme_new,(*p)->data,table);
        mvm_free(&lexeme_new);

    } else{
        if(strstr(openedfile,(*p)->data)==NULL)
        {
            strcat(openedfile,(*p)->data);
            lexeme_new=lexicalAnalysis((*p)->data,lexeme_new);
            grammarCheck(lexeme_new,(*p)->data,table);
            mvm_free(&lexeme_new);
        }
    }

}

void jump(mvmcell **p,char *filename,mvmcell *head)
{
    int cnt,i;
    movePointer(p,filename);
    if((*p)->key==NAL_NUMCON)
    {
        if(INTERPRET)
        {
            cnt=atoi((*p)->data);
            if(cnt==0)
            {
                ERROR("Invalid JUMP parameter",filename)
            }
            *p=head;
            for(i=1;i<cnt;i++)
            {
                movePointer(p,filename);
            }
            return;
        }
        return;
    }
    ERROR("No NUMCON in JUMP statement ?",filename)
}

void ifCond(mvmcell **p,char *filename,Symbol logic,Table *table,mvmcell *head,mvm *lexeme, Stack *st)
{
    mvmcell *var1,*var2;
    char *value1, *value2;
    movePointer(p,filename);
    if((*p)->key!=NAL_L_PARENTHESES)
    {
        ERROR("No ( in IFEQUAL statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_STRCON&&(*p)->key!=NAL_NUMCON&&(*p)->key!=NAL_STRVAR&&(*p)->key!=NAL_NUMVAR)
    {
        ERROR("No VARCON in IFEQUAL statement ?",filename)
    }
    var1=(*p);
    movePointer(p,filename);
    if((*p)->key!=NAL_COMMA)
    {
        ERROR("No , in IFEQUAL statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_STRCON&&(*p)->key!=NAL_NUMCON&&(*p)->key!=NAL_STRVAR&&(*p)->key!=NAL_NUMVAR)
    {
        ERROR("No VARCON in IFEQUAL statement ?",filename)
    }
    var2=(*p);
    movePointer(p,filename);
    if((*p)->key!=NAL_R_PARENTHESES)
    {
        ERROR("No ) in IFEQUAL statement ?",filename)
    }
    movePointer(p,filename);
    if((*p)->key!=NAL_L_BRACES)
    {
        ERROR("No { in IFEQUAL statement ?",filename)
    }
    movePointer(p,filename);
    if(INTERPRET)
    {
        if(ifVarIsVaild(var1,var2,logic))
        {
            value1=getValue(var1,table,filename);
            value2=getValue(var2,table,filename);
            if(logic==NAL_IFEQUAL)
            {
                if(strcmp(value1,value2)==0)
                {
                    instrs(p,filename,table,1,head,lexeme,st);
                } else{
                    instrs(p,filename,table,0,head,lexeme,st);
                }
            } else if (logic==NAL_IFGREATER)
            {
                if(ifGreaterIsVaild(value1,value2,filename))
                {
                    instrs(p,filename,table,1,head,lexeme,st);
                } else{
                    instrs(p,filename,table,0,head,lexeme,st);
                }
            }
        } else{
            ERROR("Uncomparable variables",filename)
        }
    } else{
        instrs(p,filename,table,1,head,lexeme,st);
    }
}

int ifGreaterIsVaild(char *value1,char *value2, char *filename)
{
    double a=strtof(value1,NULL);
    double b=strtof(value2,NULL);
    /*if()
    {
        ERROR("IFCOND function parameter out of bounds",filename)
    }*/
    if(a>b)
    {
        return 1;
    } else{
        return 0;
    }
}

char *getValue(mvmcell *var,Table *table,char *filename)
{
    char *value;
    if(var->key==NAL_STRCON||var->key==NAL_NUMCON)
    {
        return var->data;
    } else{
        value=table_search(table,var->data,var->key);
        if(value==NULL)
        {
            ERROR("Variable not declared",filename)
        } else{
            return value;
        }
    }
}

int ifVarIsVaild(mvmcell *var1,mvmcell *var2,Symbol logic)
{
    if(logic==NAL_IFEQUAL)
    {
        if((var1->key==NAL_STRVAR||var1->key==NAL_STRCON)&&\
        (var2->key==NAL_NUMVAR||var2->key==NAL_NUMCON))
        {
            return 0;
        }
        else if((var2->key==NAL_STRVAR||var2->key==NAL_STRCON)&&\
        (var1->key==NAL_NUMVAR||var1->key==NAL_NUMCON))
        {
            return 0;
        }
    } else if(logic==NAL_IFGREATER)
    {
        if(var1->key==NAL_STRVAR||var1->key==NAL_STRCON||\
        var2->key==NAL_STRVAR||var2->key==NAL_STRCON)
        {
            return 0;
        }
    }
    return 1;
}

void set(mvmcell  **p,char *filename,Table *table)
{
    Symbol property=(*p)->key;
    char *key=(*p)->data;
    char *data;
    movePointer(p,filename);
    if((*p)->key==NAL_EQUAL){
        movePointer(p,filename);
        if((*p)->key==NAL_STRCON){
            if(INTERPRET)
            {
                if(property==NAL_NUMVAR)
                {
                    ERROR("Unexpected set assign property",filename)
                } else{
                    if(table_search(table,key,property)!=NULL)
                    {
                        tableUpdate(table,key,(*p)->data,property);
                    } else{
                        table_insert(table,key,(*p)->data,property);
                    }
                }
            }
            return;
        } else if((*p)->key==NAL_NUMCON){
            if(INTERPRET)
            {
                if(property==NAL_STRVAR)
                {
                    ERROR("Unexpected set assign property",filename)
                } else{
                    if(table_search(table,key,property)!=NULL)
                    {
                        tableUpdate(table,key,(*p)->data,property);
                    } else{
                        table_insert(table,key,(*p)->data,property);
                    }
                }
            }
            return;
        }
        else if((*p)->key==NAL_STRVAR){
            if(INTERPRET)
            {
                if(property==NAL_NUMVAR)
                {
                    ERROR("Unexpected set assign property",filename)
                } else{
                    data=table_search(table,(*p)->data,property);
                    if(data==NULL)
                    {
                        ERROR("Variable not declared",filename)
                    }
                    table_insert(table,key,data,property);
                }
            }
            return;
        }
        else if((*p)->key==NAL_NUMVAR){
            if(INTERPRET)
            {
                if(property==NAL_STRVAR)
                {
                    ERROR("Unexpected set assign property",filename)
                } else{
                    data=table_search(table,(*p)->data,property);
                    if(data==NULL)
                    {
                        ERROR("Variable not declared",filename)
                    }
                    table_insert(table,key,data,property);
                }
            }
            return;
        }
    }
    ERROR("Unexpected set grammar.",filename)
}

void print(mvmcell **p,char *filename,Table *table)
{
    char *data;
    movePointer(p,filename);
    if(((*p)->key==NAL_STRCON)||((*p)->key==NAL_NUMCON))
    {
        if(INTERPRET)
        {
            puts((*p)->data);

        }
        return;
    } else if(((*p)->key==NAL_STRVAR)||((*p)->key==NAL_NUMVAR))
    {
        if(INTERPRET)
        {
            data=table_search(table,(*p)->data,(*p)->key);
            if(data==NULL)
            {
                ERROR("Variable not declared",filename)
            }
            puts(data);
        }
        return;
    }
    ERROR("Unexpected print grammar.",filename)
}

int validParentheses(mvm *lexeme)
{
    Symbol ch;
    Stack st;
    initStack(&st);
    mvmcell *p=lexeme->head;
    while (p!=NULL)
    {
        if(p->key==NAL_L_PARENTHESES||p->key==NAL_L_BRACES)
        {
            push(&st,p->key);
            p=p->next;
        } else if(p->key==NAL_R_PARENTHESES||p->key==NAL_R_BRACES){
            if(st.base==st.top)
            {
                freeStack(&st);
                return 0;
            }
            else{
                pop(&st,&ch);
                if((ch==NAL_L_BRACES&&p->key!=NAL_R_BRACES)||\
                (ch==NAL_L_PARENTHESES&&p->key!=NAL_R_PARENTHESES))
                {
                    freeStack(&st);
                    return 0;
                }
                p=p->next;
            }
        } else{
            p=p->next;
        }
    }
    free(p);
    if(st.base==st.top)
    {
        freeStack(&st);
        return 1;
    }else {
        freeStack(&st);
        return 0;
    }
}

Symbol nextToken(FILE *fp,char *word,char *filename)
{
    int ch;
    int i;
    for(i=0;i<MAX_TOKEN_SIZE;i++)
    {
        word[i]='\0';
    }

    ch=fgetc(fp);

    switch (ch){
        case '{':
            return NAL_L_BRACES;
        case '"':
            word=getString(ch,fp,word,filename);
            return NAL_STRCON;
        case '#':
            word=getString(ch,fp,word,filename);
            word=rotchange(word);
            return NAL_STRCON;
        case '}':
            return NAL_R_BRACES;
        case '$':
            word=getWord(ch,fp,word);
            return NAL_STRVAR;
        case '%':
            word=getWord(ch,fp,word);
            return NAL_NUMVAR;
        case '=':
            return NAL_EQUAL;
        case '(':
            return NAL_L_PARENTHESES;
        case ')':
            return NAL_R_PARENTHESES;
        case ',':
            return NAL_COMMA;
        case '\n':
            return NAL_NEWLINE;
        case '\t':
            return NAL_NEWLINE;
        case ' ':
            return NAL_SPACE;
        case -1:
            return NAL_NEWLINE;
        default:
            if((ch>='0')&&(ch<='9'))
            {
                word=getWord(ch,fp,word);
                return NAL_NUMCON;
            }
            if((ch>='A')&&(ch<='Z'))
            {
                word=getWord(ch,fp,word);
                return symbolMatch(word);
            }
            if(ch>=' '&&ch<='~'){
                return NAL_UNDEFINE;
            }
    }
    return NAL_UNDEFINE;
}

Symbol symbolMatch(char *word)
{
    if(strcmp(word,"PRINT")==0)
    {
        return NAL_PRINT;
    }
    if(strcmp(word,"PRINTN")==0)
    {
        return NAL_PRINTN;
    }
    if(strcmp(word,"IFEQUAL")==0)
    {
        return NAL_IFEQUAL;
    }
    if(strcmp(word,"IFGREATER")==0)
    {
        return NAL_IFGREATER;
    }
    if(strcmp(word,"JUMP")==0)
    {
        return NAL_JUMP;
    }
    if(strcmp(word,"FILE")==0)
    {
        return NAL_FILE;
    }
    if(strcmp(word,"RND")==0)
    {
        return NAL_RND;
    }
    if(strcmp(word,"INC")==0)
    {
        return NAL_INC;
    }
    if(strcmp(word,"ABORT")==0)
    {
        return NAL_ABORT;
    }
    if(strcmp(word,"INNUM")==0)
    {
        return NAL_INNUM;
    }
    if(strcmp(word,"IN2STR")==0)
    {
        return NAL_IN2STR;
    }
    return NAL_UNDEFINE;
}

char *getWord(int ch, FILE *fp,char *word)
{
    int i=0;
    while(ch!=' '&&ch!='\n'&&ch!='\t')
    {
        if(ch!='$'&&ch!='%')
        {
            word[i++]=ch;
        }
        ch=fgetc(fp);
    }
    word=(char *)realloc(word,i* sizeof(char));
    return word;
}

char *getString(int ch,FILE *fp,char *word,char *filename)
{
    int i=0,len=0;
    do{
        if((ch!='"')&&(ch!='#'))
        {
            word[i++]=ch;
            len++;
        }
        if(feof(fp))
        {
            ERROR("Error! Can not find a vaild string.",filename)
        }
        if(len>=MAX_TOKEN_SIZE)
        {
            word=(char *)realloc(word,(len+MAX_TOKEN_SIZE)* sizeof(char));
            len-=MAX_TOKEN_SIZE;
        }
        ch=fgetc(fp);
    }while ((ch!='"')&&(ch!='#'));
    word=(char *)realloc(word,(i+1)* sizeof(char));
    return word;
}

char *rotchange(char *word)
{
    int i;
    for(i=0;i<strlen(word);i++)
    {
        if(((word[i]>='A')&&(word[i]<='M'))||((word[i]>='a')&&(word[i]<='m')))
        {
            word[i]+=ROT13;
        }
        else if(((word[i]>='N')&&(word[i]<='Z'))||((word[i]>='n')&&(word[i]<='z')))
        {
            word[i]-=ROT13;
        }
        else if((word[i]>='0')&&(word[i]<='4'))
        {
            word[i]+=ROT5;
        }
        else if((word[i]>='5')&&(word[i]<='9'))
        {
            word[i]-=ROT5;
        }
    }
    return word;
}


mvm* mvm_init(void)
{
    mvm *head=(mvm *)calloc(1, sizeof(mvm));
    assert(head!=NULL);
    head->head=NULL;
    return head;
}

void mvm_free(mvm** p)
{
    mvm *a;
    if( p ==NULL || *p == NULL) {
        return;
    }
    a=*p;

    free_linked_list(&(a->head));
    free(a);
    *p=NULL;
}

void free_linked_list(mvmcell **head)
{
    if(head !=NULL){
        mvmcell *current = *head;
        mvmcell *next;
        while(current != NULL){
            next = current->next;
            free(current->data);
            free(current);
            current = next;
        }
        *head = NULL;
    }
}

void mvm_insert(mvm* m, Symbol key, char* data)
{
    mvmcell *p=(mvmcell *)calloc(1, sizeof(mvmcell));
    mvmcell *cur;
    if (m == NULL || data == NULL)
    {
        free(p);
        return;
    }
    p->key=key;
    p->data=(char *)calloc(1, (strlen(data)+1)* sizeof(char));
    assert(data!=NULL);
    strcpy(p->data,data);

    cur=m->head;
    if(cur!=NULL)
    {
        while(cur->next!=NULL)
        {
            cur=cur->next;
        }
        cur->next=p;
    } else{
        m->head=p;
    }
    p->next=NULL;
    m->numkeys++;
}

void initStack(Stack *s)
{
    s->base=(Symbol *)malloc(STACK_INIT_SIZE *sizeof(Symbol));
    if(!s->base) exit(0);
    s->top=s->base;
    s->stacklen=STACK_INIT_SIZE;
}

void push(Stack *s,Symbol e)
{
    if(s->top-s->base>=s->stacklen)
    {
        s->base=(Symbol *)realloc(s->base,(STACK_INIT_SIZE+STACRINCREMENT) *sizeof(Symbol));
        if(!s->base) exit(0);
    }
    *(s->top)=e;
    s->top++;
}

void pop(Stack *s,Symbol *e)
{
    if(s->base==s->top) return;
    *e=*--(s->top);
}

int StackLen(Stack s)
{
    return (s.top-s.base);
}

void freeStack(Stack *s)
{
    free(s->base);
    s=NULL;
}

Table *table_init(void)
{
    Table *head=(Table *)calloc(1, sizeof(mvm));
    assert(head!=NULL);
    head->head=NULL;
    return head;
}

void table_insert(Table * m, char* key, char* data,Symbol property)
{
    Node *p=(Node *)calloc(1, sizeof(Node));
    if (m == NULL || key == NULL || data == NULL) {
        free(p);
        return;
    }
    p->key=(char *)calloc(1, (strlen(key)+1)* sizeof(char));
    p->data=(char *)calloc(1, (strlen(data)+1)* sizeof(char));
    assert(key!=NULL);
    assert(data!=NULL);
    strcpy(p->key,key);
    strcpy(p->data,data);
    p->property=property;
    p->next=m->head;
    m->head=p;
    m->numkeys++;
}

char* table_search(Table * m, char* key,Symbol property)
{
    Node *p;
    p = m->head;
    int n;
    while (p != NULL){
        if ((strcmp(p->key, key) == 0)&&(property==p->property))
        {
            n=strcmp(p->key, key);
            return p->data;
        }
        p = p->next;
    }
    return NULL;
}

void free_table_linked_list(Node **head)
{
    if(head !=NULL){
        Node *current = *head;
        Node *next;
        while(current != NULL){
            next = current->next;
            free(current->data);
            free(current->key);
            free(current);
            current = next;
        }
        *head = NULL;
    }
}

/* Free & set p to NULL from head*/
void table_free(Table ** p)
{
    Table *a;
    if( p ==NULL || *p == NULL) {
        return;
    }
    a=*p;

    free_table_linked_list(&(a->head));
    free(a);
    *p=NULL;
}

void tableUpdate(Table *table, char *key, char *data, Symbol property)
{
    Node *p;
    p = table->head;

    assert(key!=NULL);
    assert(data!=NULL);
    while (p != NULL){
        if ((strcmp(p->key, key) == 0)&&(property==p->property))
        {
            free(p->data);
            p->data=(char *)calloc(1, (strlen(data)+1)* sizeof(char));
            strcpy(p->data,data);
        }
        p = p->next;
    }
}
