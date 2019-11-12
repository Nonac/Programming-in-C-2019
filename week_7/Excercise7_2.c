#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 362880

struct node
{
    int data[3][3];
    int level;
    int pro;
};

struct c
{
    int row;
    int col;
};


void eightpuzzle(int m[3][3]);
void assign(struct c *goalcheck);
int solvable(int a[3][3]);
int getinversion(int a[]);

int main() {
    char *s = "87 216354";
    int m[3][3], i, j, cnt = 0;
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
    return 0;
}

void eightpuzzle(int m[3][3])
{
    struct node board[MAXSIZE]={0};
    struct node open[MAXSIZE]={0};
    struct node closed[MAXSIZE]={0};
    struct c check[9];
    struct c *goalcheck=check;
    int i,j;
    assign(goalcheck);

    if(solvable(m))
    {

    }
    else
    {
        printf("\nnot solvable.");
    }
}

void assign(struct c *goalcheck)
{
    int goal[3][3]={{1,2,3},{4,5,6},{7,8,0}};
    int i,j;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
        {
            goalcheck[goal[i][j]].row=i;
            goalcheck[goal[i][j]].col=j;
        }
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


