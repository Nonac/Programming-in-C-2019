#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 362880

typedef struct node
{
    int data[3][3];
    int parent;
}Node;

typedef struct coordinate
{
    int x;
    int y;
}Zero;

void eightpuzzle(int m[3][3]);
void readin(Node array[MAXSIZE],int m[3][3]);
int solvable(int a[3][3]);
int getinversion(int a[]);
Zero *findzero(Node array[MAXSIZE], int num, Zero *zero);
int goaltest(Node array[MAXSIZE], int num);
int next(Node array[MAXSIZE],int times,int cnt,Zero *zero);
int isValid(int i, int j);
void change(int *a,int *b);
void copynext(Node array[MAXSIZE],int times,int cnt);
int checkdata(Node array[MAXSIZE],int i,int cnt);
int checklist(Node array[MAXSIZE],int cnt);
int isValid(int i, int j);
void printlist(Node array[MAXSIZE],int cnt);
void printout(int x[3][3]);

int main(int argc, char **argv)
{
    clock_t startTime,endTime;
    char *s = argv[1];
    int m[3][3], i, j, cnt = 0;

    if(argc!=2)
    {
        printf("Error argv.\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (s[cnt] >= '1' && s[cnt] <= '9') {
                m[i][j] = s[cnt] - '0';
                cnt++;
            } else if (s[cnt] == ' ') {
                m[i][j] = 0;
                cnt++;
            } else {
                printf("Error input.\n");
            }
        }
    }
    eightpuzzle(m);
    endTime = clock();
    printf("Total time is:%fs\n",(double)abs((endTime - startTime)) / CLOCKS_PER_SEC);
    return 0;
}

void eightpuzzle(int m[3][3])
{
    static Node array[MAXSIZE] = {0};
    Zero *zero=(Zero *)malloc(sizeof(Zero));
    int i,j,times,cnt=0;
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
    printf("\nThe begining is:\n");
    printout(array[0].data);
    printlist(array,times);
}

void printlist(Node array[MAXSIZE],int cnt)
{
    static int total=1;
    if(array[cnt].parent==0) {
        printf("\nThis is No.%d step:\n", total);
        total++;
        printout(array[cnt].data);
    } else
    {
        printlist(array,array[cnt].parent);
        printf("\nThis is No.%d step:\n",total);
        total++;
        printout(array[cnt].data);
    }
}

void printout(int x[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {for(j=0;j<3;j++)
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

int isValid(int i, int j)
{
    if (i < 0 || i >= 3 || j < 0 || j >= 3)
        return 0;
    return 1;
}

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
                change(&array[cnt+new].data[i][j],&array[cnt+new].data[zero->x][zero->y]);
                if(checklist(array,cnt+new))
                {
                    new--;
                }
            }
        }
    }
    return new;
}

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

int checkdata(Node array[MAXSIZE],int n,int cnt)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(array[n].data[i][j]!=array[cnt].data[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

void copynext(Node array[MAXSIZE],int times,int cnt)
{
    int i, j;
    int a[3][3];
    for (i=0;i<3; i++)
    {
        for(j=0;j<3;j++)
        {
            array[cnt].data[i][j]=array[times].data[i][j];
            a[i][j]=array[times].data[i][j];
        }
    }

    array[cnt].parent=times;
}

void change(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

int goaltest(Node array[MAXSIZE], int num)
{
    int goal[3][3]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if(array[num].data[i][j]!=goal[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}


Zero *findzero(Node array[MAXSIZE], int num, Zero *zero)
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
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

void readin(Node array[MAXSIZE],int m[3][3])
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            array[0].data[i][j]=m[i][j];
        }
    }
    array[0].parent=0;
}

int solvable(int a[3][3])
{
    int inv=getinversion((int *)a);
    if(inv%2==0)
        return 1;
    else
        return 0;
}

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