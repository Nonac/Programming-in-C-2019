#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <assert.h>
#define LENTH 3

/*This code base on A* Algotithm and Dynamic Double linked list structure.
 * Through time testing, this algorithm can be nearly a thousand times
 * faster than the fixed array BFS algorithm.
 * But I fail to control the code length of a single function.
 * Function eightpuzzle and Fuction proenqueue have a poor length control.*/

typedef struct node
{
    int data[LENTH][LENTH];
    int level;
    int pro;
    /*it is used in calculating the priority
     * value of a node for comparative checking*/
    struct node *next;
    struct node *parent;
}*list;

struct c
{
    int row;
    int col;
};

void test();
void stoarray(int (*p)[LENTH],char *s);
int isValid(int i, int j);
void findzero(int temp[LENTH][LENTH],int *itemp,int *jtemp);
void swap(int *a,int *b);
void copydata(int temp[LENTH][LENTH],list t);
void copydata(int temp[LENTH][LENTH],list t);
void checknext(list t,list temp,int flag);
void assign(struct c check[LENTH*LENTH]);
void eightpuzzle(int m[LENTH][LENTH]);
int getinversion(int a[]);
int solvable(int a[LENTH][LENTH]);
void priority(list t);
void printout(int x[LENTH][LENTH]);
void result(list t);
int compare(int x[LENTH][LENTH],int y[LENTH][LENTH]);
int goaltest(list t);
list insert(list head,list parent,int plev,int temp[LENTH][LENTH]);
list movegen(list t);
list proenqueue(list head,list temp,int flag);
list dequeue(list t);
void waste(list t,list closed);

int main(int argc, char **argv)
{
    clock_t startTime,endTime;
    int m[LENTH][LENTH];
    char *s = argv[1];
    int (*p)[LENTH]=m;

    if(argc!=2)
    {
        printf("Error argv.\n");
        exit(EXIT_FAILURE);
    }
    test();
    startTime = clock();
    stoarray(p,s);

    eightpuzzle(m);
    endTime = clock();
    printf("Total time is:%fs\n",(double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}

void test()
{
    int a[LENTH][LENTH]={{1,2,3},{4,5,6},{7,8,0}};
    int b[LENTH][LENTH]={{1,2,3},{4,5,6},{8,7,0}};
    assert(isValid(0,0) == 1);
    assert(isValid(-1,0) == 0);
    assert(isValid(3,3) == 0);
    assert(solvable(a)==1);
    assert(solvable(b)==0);
    assert(getinversion(*a)==0);
    assert(getinversion(*b)==1);
    assert(compare(a,b)==0);
    assert(compare(a,a)==1);
}

/*turn string to an array*/
void stoarray(int (*p)[LENTH],char *s)
{
    int i,j,cnt=0;
    if(strlen(s)!=LENTH*LENTH)
    {
        printf("Error input.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < LENTH; i++) {
        for (j = 0; j < LENTH; j++) {
            if (s[cnt] >= '1' && s[cnt] <= '9') {
                p[i][j] = s[cnt] - '0';
                cnt++;
            } else if (s[cnt] == ' ') {
                p[i][j] = 0;
                cnt++;
            } else {
                printf("Error input.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

/*eight puzzle core function*/
void eightpuzzle(int m[LENTH][LENTH])
{
    int flag=0;
    list open,closed,t,temp,p,q;
    /* p        is for temporarily handling closed.
     * t        is for temporarily holding open.
     * temp     is for return Function movgen which generate
     *       next step.
     * q        is for temporarily holding movgen.
     * open     is for a possible shortest way to target.
     * closed   is for the node whose priority larger than
     *      the same level in open list,and we must save
     *      the waste path and never use them.*/
    closed=open=NULL;
    /*There is a solution about eight puzzle.
     * If the target array's Inverse sequence is even/odd number.
     * Then there are solutions for the giving array with a same
     * even/odd Inverse sequence. If not, it is unsolvable.
     * */
    if(!solvable(m))
    {
        printf("\nnot solvable.");
        exit(EXIT_FAILURE);
    }
    /*Put the first generation in the list*/
    open=insert(open,NULL,0,m);

    while(open!=NULL)
    {
        if(!goaltest(open))
        {
            /*Generate next step*/
            temp=movegen(open);
            t=open;
            /*Move the pointer backward*/
            open=dequeue(open);
            t->next=NULL;
            /*Put the iterated matrix into closed list*/
            waste(t,closed);

            while(temp!=NULL)
            {
                q=temp;
                temp=dequeue(temp);
                q->next=NULL;
                t=open;
                /*Function compare() is determine if the array is identical*/
                while(t!=NULL&&(!compare(t->data,q->data)))
                {
                    t=t->next;
                }
                if(t==NULL)
                {
                    p=closed;
                    while(p!=NULL&&(!compare(p->data,q->data)))
                    {
                        p=p->next;
                    }
                    if(p==NULL)
                    {
                        /*Start recursion*/
                        open=proenqueue(open,q,flag);
                    }
                }
            }
        }
        else
        {
            /*Print the results*/
            result(open);
            return;
        }
    }
}

/*Put the iterated matrix into closed list*/
void waste(list t,list closed)
{
    list p;
    if(closed==NULL)
    {
        closed=t;
    }
    else
    {
        p=closed;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        p->next=t;
    }
}

/*Move the pointer backward*/
list dequeue(list t)
{
    return t->next;
}

/*Check the next element of the current element
 * and move the pointer or recursion*/
void checknext(list t,list temp,int flag)
{
    if(t->next->pro<temp->pro)
    {
        t->next=proenqueue(t->next,temp,flag);
    }
    else if(t->next->pro==temp->pro)
    {
        if(t->next->level<=temp->level)
        {
            temp->next=t->next;
            t->next=temp;
        }
        else {
            t->next = proenqueue(t->next, temp, flag);
        }
    }
    else
    {
        temp->next=t->next;
        t->next=temp;
    }
}

/*Recursive process*/
list proenqueue(list head,list temp,int flag)
{
    list t=head;
    /*Add the first element when the list is empty*/
    if(t==NULL)
    {
        return temp;
    }
    /*flag is for the priority value is same but level
     * is bigger elements.*/
    if(flag==0)
    {
        if(t->pro>temp->pro)
        {
            temp->next=t;
            return temp;
        }
        else if(t->pro==temp->pro)
        {
            if(t->level<=temp->level)
            {
                temp->next=t;
                return temp;
            }
            else
            {
                flag=1;
            }
        }
        else
        {
            flag=1;
        }
    }
    if(t->next!=NULL)
    {
        checknext(t,temp,flag);
    }
    else
    {
        if(t->pro<temp->pro)
        {
            t->next=temp;
        }
        else if(t->pro==temp->pro)
        {
            /*Element add into the list when
             * the element priority value is small*/
            if(t->level<temp->level)
            {
                temp->next=t;
                return temp;
            }
            else
            {
                /**/
                t->next=temp;
            }
        }
        else
        {
            temp->next=t;
            return temp;
        }
    }
    return t;
}

/*Copy the parent array to the child array*/
void copydata(int temp[LENTH][LENTH],list t)
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            temp[i][j]=t->data[i][j];
        }
    }
}

/*Exchange 0 position*/
void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

/*Looking for a 0 position*/
void findzero(int temp[LENTH][LENTH],int *itemp,int *jtemp)
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            if(temp[i][j]==0)
            {
                *itemp=i;
                *jtemp=j;
            }
        }
    }
}

/*Judge whether it is out of bounds*/
int isValid(int i, int j)
{
    if (i<0||i>=LENTH||j<0||j>=LENTH)
        return 0;
    return 1;
}
/*Find the next step by looping*/
list movegen(list t)
{
    list head;
    int i=0,j=0,temp[LENTH][LENTH],x,y;
    int *itemp=&i;
    int *jtemp=&j;
    head=NULL;
    copydata(temp,t);
    findzero(temp,itemp,jtemp);

    for(x=i-1;x<i+2;x++)
    {
        for(y=j-1;y<j+2;y++)
        {
            if(abs(i-x)+abs(j-y)==1 && isValid(x,y))
            {
                swap(&temp[x][y],&temp[i][j]);
                head=insert(head,t,t->level,temp);
                swap(&temp[x][y],&temp[i][j]);
            }
        }
    }
    t=head;
    return t;
}

/*Insert node*/
list insert(list head,list parent,int plev,int temp[LENTH][LENTH])
{
    list t=head;
    list tnode;
    int i,j;
    if(t!=NULL)
    {
        t->next=insert(t->next,parent,plev,temp);
    }
    else
    {
        tnode=malloc(sizeof(struct node));
        for(i=0;i<LENTH;i++)
            for(j=0;j<LENTH;j++)
            {
                tnode->data[i][j]=temp[i][j];
            }
        tnode->level=plev+1;
        tnode->parent=parent;
        tnode->next=NULL;
        priority(tnode);
        t=tnode;
    }
    return t;
}
/*Target Detection*/
int goaltest(list t)
{
    int test[LENTH][LENTH]={{1,2,3},{4,5,6},{7,8,0}};

    if(compare(test,t->data))
        return 1;
    else
        return 0;
}

/*Determine if the array is identical*/
int compare(int x[LENTH][LENTH],int y[LENTH][LENTH])
{
    int i,j=0;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            if(x[i][j]!=y[i][j])
            {
                return 0;
            }
        }
    }
    if(i==LENTH && j==LENTH)
        return 1;
    else
        return 0;
}
/*Traversing the linked list by recursive reverse order*/
void result(list t)
{
    static int cnt=0;
    if(t!=NULL)
    {
        result(t->parent);
        printf("\nThis is No.%d step:\n",cnt);
        cnt++;
        printout(t->data);
    }
}
/*print out the array to screen*/
void printout(int x[LENTH][LENTH])
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {for(j=0;j<LENTH;j++)
        {
            if(x[i][j]==0)
                printf("  ");
            else
                printf("%d ",x[i][j]);
        }
        if(i!=2)
            printf("\n");
    }
    printf("\n\n");
}

/*use in calculating the hash value*/
void priority(list t)
{
    static struct c check[9];
    int i,j;
    assign(check);
    t->pro=t->level;
    for(i=0;i<LENTH;i++)
        for(j=0;j<LENTH;j++)
        {
            /*This is the A* Algorithm core code I think.
             * Through the sequence difference between the
             * matrix and the target matrix, a hash value
             * belonging to the current matrix is obtained.*/
            t->pro=t->pro+abs(check[t->data[i][j]].row-i)\
            +abs(check[t->data[i][j]].col-j);
        }
}
/*Determine if the starting array has a valid solution*/
int solvable(int a[LENTH][LENTH])
{
    int inv=getinversion((int *)a);
    if(inv%2==0)
        return 1;
    else
        return 0;
}
/*Inverse sequence*/
int getinversion(int a[])
{
    int i,j;
    int inv=0;
    for(i=0;i<8;i++)
        for(j=i+1;j<9;j++)
        {
            if(a[i]&&a[j]&&a[i]>a[j])
            {
                inv++;
            }
        }
    return inv;
}
/*Generating detection sequence*/
void assign(struct c check[9])
{
    int goal[LENTH][LENTH]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for(i=0;i<LENTH;i++)
        for(j=0;j<LENTH;j++)
        {
            check[goal[i][j]].row=i;
            check[goal[i][j]].col=j;
        }
}
