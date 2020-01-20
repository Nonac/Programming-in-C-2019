#include "nal.h"

int main(int argc, char *argv[])
{
    mvm *lexeme=mvm_init();
    Table *table=table_init();

    if(argc!=2)
    {
        printf("Incorrect number of parameters\n");
        exit(1);
    }
    srand((unsigned)time(NULL));
    test();

    lexeme=lexicalAnalysis(argv[1],lexeme);
    grammarCheck(lexeme,argv[1],table);

    if(INTERPRET)
    {
        printf("Interpreted OK\n");
    } else{
        printf("Parsed OK\n");
    }

    table_free(&table);
    mvm_free(&lexeme);
    return 0;
}

void test(void)
{
    assert(symbolMatch("IFEQUAL")==NAL_IFEQUAL);
    assert(symbolMatch("FILE")==NAL_FILE);
    assert(symbolMatch("PRINT")==NAL_PRINT);
    assert(symbolMatch("PRINTN")==NAL_PRINTN);
    assert(symbolMatch("RND")==NAL_RND);
    assert(symbolMatch("INC")==NAL_INC);
    assert(symbolMatch("INNUM")==NAL_INNUM);
    assert(symbolMatch("IN2STR")==NAL_IN2STR);
    assert(symbolMatch("IFGREATER")==NAL_IFGREATER);
    assert(symbolMatch("JUMP")==NAL_JUMP);
    assert(symbolMatch("ABORT")==NAL_ABORT);
    assert(symbolMatch("INNUM")==NAL_INNUM);
    assert(symbolMatch("IN2STR")==NAL_IN2STR);
    assert(ifGreaterIsVaild("1","2")==0);
    assert(ifGreaterIsVaild("2","1")==1);
    assert(decimalTest("3.0000001")==1);
    assert(decimalTest("3.0000000")==0);
}

mvm *lexicalAnalysis(char *argv,mvm *lexeme)
{
    Symbol token;
    char *word;
    FILE *fp=fopen(argv,"r");

    while (!feof(fp))
    {
        word=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        token=nextToken(fp,&word,argv);
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
    freeStack(&st);
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
            print(p,filename,table,NAL_PRINT);
            return;
        case NAL_PRINTN:
            print(p,filename,table,NAL_PRINTN);
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
            jump(p,filename,head,lexeme->numkeys);
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
            if(INTERPRET)
            {
                freeStack(st);
                table_free(&table);
                mvm_free(&lexeme);
                printf("Interpreted OK\n");
                exit(0);
            } else{
                return;
            }
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
        n=atof(ori)+1;
        data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
        int2string(n,data);
        tableUpdate(table,key,data,property);
        free(data);
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
    int temp,i,j,len;
    if(slope<0)
    {
        buffer[0] = '-';
        slope = -slope;
        temp = (int)slope;
        for(i=0;temp!=0;i++)
            temp /=10;
        temp =(int)slope;
        for(j=i;j>0;j--)
        {
            buffer[j] = temp%10+'0';
            temp /=10;
        }
        buffer[i+1] = '.';
        slope -=(int)slope;
        len=DIGITS;
        for(i=i+2;i<len-1;i++)
        {
            slope*=10;
            buffer[i]=(int)slope+'0';
            slope-=(int)slope;
        }
        buffer[strlen(buffer)-1] = '\0';
    }
    temp = (int)slope;
    for(i=0;temp!=0;i++)
    {
        temp /=10;
    }
    if(slope<1)
    {
        i=1;
    }
    temp =(int)slope;
    for(j=i-1;j>=0;j--)
    {
        buffer[j] = (temp%10)+'0';
        temp /=10;
    }
    buffer[i] = '.';
    slope -=(int)slope;
    len=DIGITS;
    for(i=i+1;i<len;i++)
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

void jump(mvmcell **p,char *filename,mvmcell *head,int n)
{
    int cnt,i;
    movePointer(p,filename);
    if((*p)->key==NAL_NUMCON)
    {
        if(INTERPRET)
        {
            cnt=atoi((*p)->data);
            if(cnt>=n)
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
        if(ifVarIsVaild(var1,var2,logic,filename))
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
                if(ifGreaterIsVaild(value1,value2))
                {
                    instrs(p,filename,table,1,head,lexeme,st);
                } else{
                    instrs(p,filename,table,0,head,lexeme,st);
                }
            }
        } else{
            ERROR("Uncomparable various in IFGREATER",filename)
        }
    } else{
        instrs(p,filename,table,1,head,lexeme,st);
    }
}

int ifGreaterIsVaild(char *value1,char *value2)
{
    double a=atof(value1);
    double b=atof(value2);
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

int ifVarIsVaild(mvmcell *var1,mvmcell *var2,Symbol logic,char *filename)
{
    if(logic==NAL_IFEQUAL)
    {
        if((var1->key==NAL_STRVAR||var1->key==NAL_STRCON)&&\
        (var2->key==NAL_NUMVAR||var2->key==NAL_NUMCON))
        {
            ERROR("Uncomparable various in IFEQUAL",filename)
        }
        else if((var2->key==NAL_STRVAR||var2->key==NAL_STRCON)&&\
        (var1->key==NAL_NUMVAR||var1->key==NAL_NUMCON))
        {
            ERROR("Uncomparable various in IFEQUAL",filename)
        }
    } else if(logic==NAL_IFGREATER)
    {
        if(var1->key==NAL_STRVAR||var1->key==NAL_STRCON||\
        var2->key==NAL_STRVAR||var2->key==NAL_STRCON)
        {
            ERROR("Uncomparable various in IFGREATER",filename)
        }
    }
    return 1;
}

void set(mvmcell  **p,char *filename,Table *table)
{
    mvmcell *endTest;
    Symbol property=(*p)->key;
    char *key=(*p)->data;
    char *data;
    movePointer(p,filename);
    if((*p)->key==NAL_EQUAL){
        movePointer(p,filename);
        endTest=(*p);
        if((*p)->key==NAL_STRVAR||(*p)->key==NAL_STRCON){
            if(INTERPRET)
            {
                if(property==NAL_NUMVAR)
                {
                    ERROR("Unexpected various in set grammar",filename)
                } else{
                    data=((*p)->key==NAL_STRVAR)?table_search(table,(*p)->data,property):\
                    (*p)->data;
                    if(data==NULL)
                    {
                        ERROR("Variable not declared",filename)
                    }
                    if(table_search(table,key,property)!=NULL){
                        tableUpdate(table,key,data,property);
                    }else{
                        table_insert(table,key,data,property);
                    }

                }
            }
            return;
        }else if((*p)->key==NAL_NUMCON||(*p)->key==NAL_NUMVAR){
            if(mathExpression(&endTest,filename))
            {
                if(INTERPRET)
                {
                    data=calculator((*p),endTest,filename,table);
                    if(data==NULL)
                    {
                        ERROR("Variable not declared",filename)
                    }
                    if(table_search(table,key,property)!=NULL){
                        tableUpdate(table,key,data,property);
                    }else{
                        table_insert(table,key,data,property);
                    }
                }
                (*p)=endTest;
            } else if(INTERPRET)
            {
                if(property==NAL_STRVAR)
                {
                    ERROR("Unexpected various in set grammar",filename)
                } else{
                    data=((*p)->key==NAL_NUMVAR)?table_search(table,(*p)->data,property):\
                    (*p)->data;
                    if(data==NULL)
                    {
                        ERROR("Variable not declared",filename)
                    }
                    if(table_search(table,key,property)!=NULL){
                        tableUpdate(table,key,data,property);
                    }else{
                        table_insert(table,key,data,property);
                    }
                }
            }
            return;
        }
    }
    ERROR("Unexpected set grammar.",filename)
}

char *calculator(mvmcell *start,mvmcell *end,char *filename,Table *table)
{
    mvm *RPN=mvm_init();
    double x,y;
    mvmcell *p;
    mvmcell a,b,c,result;
    StackMvm s;
    initMvmcellStack(&s);
    toRPN(&RPN,start,end);
    p=RPN->head;

    while (p!=NULL)
    {
        switch (p->key){
            case NAL_NUMCON:
                pushMvmcell(&s,(*p));
                break;
            case NAL_NUMVAR:
                pushMvmcell(&s,(*p));
                break;
            case NAL_PLUS:
                popMvmcell(&s,&b);
                popMvmcell(&s,&a);
                x=getData(a,table,filename);
                y=getData(b,table,filename);
                c.key=NAL_NUMCON;
                c.data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
                int2string(x+y,c.data);
                pushMvmcell(&s,c);
                break;
            case NAL_MINUS:
                popMvmcell(&s,&b);
                popMvmcell(&s,&a);
                x=getData(a,table,filename);
                y=getData(b,table,filename);
                c.key=NAL_NUMCON;
                c.data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
                int2string(x-y,c.data);
                pushMvmcell(&s,c);
                break;
            case NAL_MULTIPY:
                popMvmcell(&s,&b);
                popMvmcell(&s,&a);
                x=getData(a,table,filename);
                y=getData(b,table,filename);
                c.key=NAL_NUMCON;
                c.data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
                int2string(x*y,c.data);
                pushMvmcell(&s,c);
                break;
            case NAL_DIVISION:
                popMvmcell(&s,&b);
                popMvmcell(&s,&a);
                x=getData(a,table,filename);
                y=getData(b,table,filename);
                c.key=NAL_NUMCON;
                c.data=(char *)calloc(1,MAX_TOKEN_SIZE* sizeof(char));
                int2string(x/y,c.data);
                pushMvmcell(&s,c);
                break;
            default:
            ERROR("Unexpected set grammar.",filename)
        }
        p=p->next;
    }
    popMvmcell(&s,&result);
    mvm_free(&RPN);
    freeStackMvmcell(&s);
    return result.data;
}

double getData(mvmcell a, Table *table, char *filename)
{
    char *res;
    if(a.key==NAL_NUMCON)
    {
        return atof(a.data);
    } else if (a.key==NAL_NUMVAR)
    {
        res=table_search(table,a.data,a.key);
        if(res==NULL)
        {
            ERROR("Variable not declared",filename)
        }
        return atof(res);
    } else{
        ERROR("Unexpected set grammar.",filename)
    }
}

void toRPN(mvm **RPN, mvmcell *start,mvmcell *end)
{
    StackMvm s;
    mvmcell *p=start;
    mvmcell e;
    initMvmcellStack(&s);

    while (p!=end)
    {
        if(p->key==NAL_NUMCON||p->key==NAL_NUMVAR)
        {
            mvm_insert(*RPN,p->key,p->data);
        } else if (p->key==NAL_R_PARENTHESES)
        {
            popMvmcell(&s,&e);
            while (e.key!=NAL_L_PARENTHESES)
            {
                mvm_insert(*RPN,e.key,e.data);
                popMvmcell(&s,&e);
            }
        } else if (p->key==NAL_PLUS||p->key==NAL_MINUS)
        {
            if(!StackLenMvmcell(s))
            {
                pushMvmcell(&s,(*p));
            } else
            {
                do{
                        popMvmcell(&s,&e);
                        if(e.key==NAL_L_PARENTHESES)
                        {
                            pushMvmcell(&s,e);

                        } else{
                            mvm_insert(*RPN,e.key,e.data);

                        }
                }while (StackLenMvmcell(s)&&e.key!=NAL_L_PARENTHESES);
                pushMvmcell(&s,(*p));
            }
        } else if (p->key==NAL_MULTIPY||p->key==NAL_DIVISION||p->key==NAL_L_PARENTHESES)
        {
            pushMvmcell(&s,(*p));
        } else{
            ERROR("Unexpected grammar","MathExpression")
        }
        p=p->next;
    }
    while (StackLenMvmcell(s))
    {
        popMvmcell(&s,&e);
        mvm_insert(*RPN,e.key,e.data);
    }

    freeStackMvmcell(&s);
}

int mathExpression(mvmcell **endTest,char *filename)
{
    int num_var=0;
    int num_operand=0;
    int flag=0;
    while ((*endTest)->key!=NAL_SEMICOLON)
    {
        if(((*endTest)->key==NAL_NUMCON||(*endTest)->key==NAL_NUMVAR)&&(flag==0))
        {
            num_var++;
            flag++;
            movePointer(endTest,filename);
        } else if(((*endTest)->key==NAL_PLUS||(*endTest)->key==NAL_MINUS||\
        (*endTest)->key==NAL_MULTIPY||(*endTest)->key==NAL_DIVISION)&&(flag==1))
        {
            num_operand++;
            flag--;
            movePointer(endTest,filename);
        } else if((*endTest)->key==NAL_L_PARENTHESES||(*endTest)->key==NAL_R_PARENTHESES)
        {
            movePointer(endTest,filename);
        }
        else{
            return 0;
        }
    }
    return num_var==num_operand+1?1:0;
}

void print(mvmcell **p,char *filename,Table *table,Symbol flag)
{
    char *data;
    movePointer(p,filename);
    if(((*p)->key==NAL_STRCON)||((*p)->key==NAL_NUMCON))
    {
        if(INTERPRET)
        {
            puts((*p)->data);
            if(flag==NAL_PRINT)
            {
                printf("\n");
            }

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
            if(((*p)->key==NAL_STRVAR)||((*p)->key==NAL_NUMVAR&&decimalTest(data)))
            {
                puts(data);
            } else{
                putsWithoutDecimal(data);
            }

            if(flag==NAL_PRINT)
            {
                printf("\n");
            }
        }
        return;
    }
    ERROR("Unexpected print grammar.",filename)
}

void putsWithoutDecimal(char *data)
{
    int i,len=strlen(data);
    for(i=0;(i<len && data[i]!='.');i++)
    {
        printf("%c",data[i]);
    }
}

int decimalTest(char *data)
{
    int i,len=strlen(data);
    int flag=0,digit=0;
    for(i=0;i<len;i++)
    {
        if(data[i]=='.')
        {
            flag=1;
        }
        if(flag==1&&data[i]!='0'&data[i]!='.')
        {
            digit=1;
        }
    }
    return digit;
}

int validParentheses(mvm *lexeme)
{
    Symbol ch;
    Stack st;
    mvmcell *p=lexeme->head;
    initStack(&st);
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

Symbol nextToken(FILE *fp,char **word,char *filename)
{
    int ch;
    int i;
    for(i=0;i<MAX_TOKEN_SIZE;i++)
    {
        (*word)[i]='\0';
    }

    ch=fgetc(fp);

    switch (ch){
        case '{':
            return NAL_L_BRACES;
        case '"':
            (*word)=getString(ch,fp,*word,filename);
            return NAL_STRCON;
        case '#':
            (*word)=getString(ch,fp,*word,filename);
            (*word)=rotchange(*word);
            return NAL_STRCON;
        case '}':
            return NAL_R_BRACES;
        case '$':
            (*word)=getWord(ch,fp,*word);
            return NAL_STRVAR;
        case '%':
            (*word)=getWord(ch,fp,*word);
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
        case '\0':
            return NAL_NEWLINE;
        case 13:
            return NAL_NEWLINE;
        case ' ':
            return NAL_SPACE;
        case -1:
            return NAL_NEWLINE;
        case ';':
            return NAL_SEMICOLON;
        case '+':
            return NAL_PLUS;
        case '-':
            return NAL_MINUS;
        case '*':
            return NAL_MULTIPY;
        case '/':
            return NAL_DIVISION;
        default:
            if((ch>='0')&&(ch<='9'))
            {
                (*word)=getWord(ch,fp,*word);
                return NAL_NUMCON;
            }
            if((ch>='A')&&(ch<='Z'))
            {
                (*word)=getWord(ch,fp,*word);
                return symbolMatch(*word);
            }
            if(ch>=' '&&ch<='~'){
                return NAL_UNDEFINE;
            }
    }
    return NAL_UNDEFINE;
}

Symbol symbolMatch(char *word)
{

    if(strncmp(word,"PRINT",strlen(word))==0)
    {
        return NAL_PRINT;
    }
    if(strncmp(word,"PRINTN",strlen(word))==0)
    {
        return NAL_PRINTN;
    }
    if(strncmp(word,"IFEQUAL",strlen(word))==0)
    {
        return NAL_IFEQUAL;
    }
    if(strncmp(word,"IFGREATER",strlen(word))==0)
    {
        return NAL_IFGREATER;
    }
    if(strncmp(word,"JUMP",strlen(word))==0)
    {
        return NAL_JUMP;
    }
    if(strncmp(word,"FILE",strlen(word))==0)
    {
        return NAL_FILE;
    }
    if(strncmp(word,"RND",strlen(word))==0)
    {
        return NAL_RND;
    }
    if(strncmp(word,"INC",strlen(word))==0)
    {
        return NAL_INC;
    }
    if(strncmp(word,"ABORT",strlen(word))==0)
    {
        return NAL_ABORT;
    }
    if(strncmp(word,"INNUM",strlen(word))==0)
    {
        return NAL_INNUM;
    }
    if(strncmp(word,"IN2STR",strlen(word))==0)
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
    word=(char *)realloc(word,(i+1)* sizeof(char));
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
    int i,len=strlen(word);
    for(i=0;i<len;i++)
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

void initMvmcellStack(StackMvm *s_mvm)
{
    s_mvm->base=(mvmcell *)malloc(STACK_INIT_SIZE *sizeof(mvmcell));
    if(!s_mvm->base) exit(0);
    s_mvm->top=s_mvm->base;
    s_mvm->stacklen=STACK_INIT_SIZE;
}

void pushMvmcell(StackMvm *s_mvm,mvmcell e)
{
    if(s_mvm->top-s_mvm->base>=s_mvm->stacklen)
    {
        s_mvm->base=(mvmcell *)realloc(s_mvm->base,(STACK_INIT_SIZE+STACRINCREMENT) *sizeof(mvmcell));
        if(!s_mvm->base) exit(0);
    }
    *(s_mvm->top)=e;
    s_mvm->top++;
}

void popMvmcell(StackMvm *s,mvmcell *e)
{
    if(s->base==s->top) return;
    *e=*--(s->top);
}

int StackLenMvmcell(StackMvm s)
{
    return (s.top-s.base);
}

void freeStackMvmcell(StackMvm *s)
{
    free(s->base);
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
    while (p != NULL){
        if ((strcmp(p->key, key) == 0)&&(property==p->property))
        {
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
