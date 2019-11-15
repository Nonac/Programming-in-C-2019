/********************************
*				*
*Code by ff19085 Yinan Yang	*
*				*
*********************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define MAXSIZE 362880
#define LENTH 3

/*use structure to store data and parent.*/
typedef struct node
{
    int data[LENTH][LENTH];
    int parent;
}Node;

/*use structure to store zero coordinate in data*/
typedef struct coordinate
{
    int x;
    int y;
}Zero;

void test();
void stoarray(int (*p)[LENTH],char *s);
void eightpuzzle(int m[LENTH][LENTH]);
void readin(Node array[MAXSIZE],int m[LENTH][LENTH]);
int solvable(int a[LENTH][LENTH]);
int getinversion(int a[]);
Zero *findzero(Node array[MAXSIZE], int num, Zero *zero);
int goaltest(Node array[MAXSIZE], int num);
int next(Node array[MAXSIZE],int times,int cnt,Zero *zero);
int isValid(int i, int j);
void change(int *a,int *b);
void copynext(Node array[MAXSIZE],int times,int cnt);
int checkdata(Node array[MAXSIZE],int i,int cnt);
int checklist(Node array[MAXSIZE],int cnt);
void printlist(Node array[MAXSIZE],int cnt);
void printout(int x[LENTH][LENTH]);

int main(int argc, char **argv)
{
    clock_t startTime=clock(),endTime;
    char *s = argv[1];
    int m[LENTH][LENTH];
    int (*p)[LENTH]=m;
    if(argc!=2)
    {
        printf("Error argv.\n");
        exit(EXIT_FAILURE);
    }

    test();
    stoarray(p,s);
    eightpuzzle(m);
    endTime = clock();
    printf("Total time is:%fs\n",(double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}

void test()
{
    int i,j;
    int a[LENTH][LENTH]={{1,2,3},{4,5,6},{7,8,0}};
    int b[LENTH][LENTH]={{1,2,3},{4,5,6},{8,7,0}};
    Node array[3];
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            array[0].data[i][j]=a[i][j];
            array[1].data[i][j]=b[i][j];
            array[2].data[i][j]=a[i][j];
        }
    }
    assert(isValid(0,0) == 1);
    assert(isValid(-1,0) == 0);
    assert(isValid(3,3) == 0);
    assert(solvable(a)==1);
    assert(solvable(b)==0);
    assert(getinversion(*a)==0);
    assert(getinversion(*b)==1);
    assert(goaltest(array,0)==1);
    assert(goaltest(array,1)==0);
    assert(checkdata(array,0,2)==1);
    assert(checkdata(array,0,1)==0);
    assert(checklist(array,1)==0);
    assert(checklist(array,2)==1);
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
    for (i = 0; i < LENTH; i++)
    {
        for (j = 0; j < LENTH; j++)
        {
            if (s[cnt] >= '1' && s[cnt] <= '9')
            {
                p[i][j] = s[cnt] - '0';
                cnt++;
            } else if (s[cnt] == ' ')
            {
                p[i][j] = 0;
                cnt++;
            } else
            {
                printf("Error input.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
/*eight puzzle core function*/
void eightpuzzle(int m[LENTH][LENTH])
{
    static Node array[MAXSIZE];
    Zero *zero=(Zero *)malloc(sizeof(Zero));
    int times,cnt=0;
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

    readin(array,m);
    zero=findzero(array,0,zero);

    for(times=0;!(goaltest(array,times));times++)
    {
        cnt+=next(array,times,cnt,zero);
        zero=findzero(array,times+1,zero);
    }
    printlist(array,times);
}
/*use recursive to find parents*/
void printlist(Node array[MAXSIZE],int cnt)
{
    static int total=0;
    if(cnt!=0)
    {
        printlist(array, array[cnt].parent);
    }
    printf("\nThis is No.%d step:\n",total);
    total++;
    printout(array[cnt].data);
}
/*print out the array to screen*/
void printout(int x[LENTH][LENTH])
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            if(x[i][j]==0)
            {
                printf("  ");
            }
            else
            {
                printf("%d ",x[i][j]);
            }
        }
        if(i!=2)
        {
            printf("\n");
        }
    }
    printf("\n\n");
}
/*Judge whether it is out of bounds*/
int isValid(int i, int j)
{
    if (i < 0 || i >= LENTH || j < 0 || j >= LENTH)
    {
        return 0;
    }
    return 1;
}
/*Use the loop to judge the four directions and find the next array.*/
int next(Node array[MAXSIZE],int times,int cnt,Zero *zero)
{
    int i,j,new=0;
    for(i=zero->x-1;i<zero->x+2;i++)
    {
        for (j =zero->y-1;j<zero->y+2 ; j++)
        {
            if((abs(i-zero->x)+abs(j-zero->y)==1)&&(isValid(i,j)))
            {
                new++;
                copynext(array,times,cnt+new);
                change(&array[cnt+new].data[i][j],\
                &array[cnt+new].data[zero->x][zero->y]);
                if(checklist(array,cnt+new))
                {
                    new--;
                }
            }
        }
    }
    return new;
}
/*Determine if the list has the same elements*/
int checklist(Node array[MAXSIZE],int cnt)
{
    int i;
    for(i=0;i<cnt;i++)
    {
        if(checkdata(array,i,cnt))
        {
            return 1;
        }
    }
    return 0;
}

/*Determine if the array is identical*/
int checkdata(Node array[MAXSIZE],int n,int cnt)
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            if(array[n].data[i][j]!=array[cnt].data[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}
/*Copy the parent array to the child array*/
void copynext(Node array[MAXSIZE],int times,int cnt)
{
    int i, j;
    int a[LENTH][LENTH];
    for (i=0;i<LENTH; i++)
    {
        for(j=0;j<LENTH;j++)
        {
            array[cnt].data[i][j]=array[times].data[i][j];
            a[i][j]=array[times].data[i][j];
        }
    }

    array[cnt].parent=times;
}
/*Exchange 0 position*/
void change(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

/*Detect whether the iteration of the target array is completed*/
int goaltest(Node array[MAXSIZE], int num)
{
    int goal[LENTH][LENTH]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for (i = 0; i < LENTH; i++)
    {
        for (j = 0; j < LENTH; j++)
        {
            if(array[num].data[i][j]!=goal[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

/*Looking for a 0 position*/
Zero *findzero(Node array[MAXSIZE], int num, Zero *zero)
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            if(array[num].data[i][j]==0)
            {
                zero->x=i;
                zero->y=j;
            }
        }
    }
    return zero;
}

/*Assign the starting array to the first structure*/
void readin(Node array[MAXSIZE],int m[LENTH][LENTH])
{
    int i,j;
    for(i=0;i<LENTH;i++)
    {
        for(j=0;j<LENTH;j++)
        {
            array[0].data[i][j]=m[i][j];
        }
    }
    array[0].parent=0;
}

/*Determine if the starting array has a valid solution*/
int solvable(int a[LENTH][LENTH])
{
    int inv=getinversion((int *)a);
    if(inv%2==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*Inverse sequence*/
int getinversion(int a[])
{
    int i,j;
    int inv=0;
    for(i=0;i<LENTH*LENTH-1;i++)
        for(j=i+1;j<LENTH*LENTH;j++)
        {
            if(a[i]&&a[j]&&a[i]>a[j])
            {
                inv++;
            }
        }
    return inv;
}
