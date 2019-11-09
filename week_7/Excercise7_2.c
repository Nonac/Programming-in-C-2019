#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXARRANGEMENT 362880
#define SIZE 3

char ***eightpuzzle(char ***p);

int main()
{
    char res[MAXARRANGEMENT][SIZE][SIZE]={'\0'};
    char ***p=res;
    char *s="513276 48";
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            res[0][i][j]=*(s+i+j);
        }
    }

    p=eightpuzzle(p);
    return 0;
}

char ***eightpuzzle(char ***p)
{


}
