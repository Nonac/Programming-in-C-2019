#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define LENGTH 40

char **create();
char **readin(char **array);

int main()
{
    int i,j;
    char **array=create();
    array=readin(array);
    for(i=0;i<LENGTH;i++)
    {
        for(j=0;j<LENGTH;j++)
        {
            printf("%c",array[i][j]);
        }
	printf("\n");
    }
    return 0;
}

char **create()
{
    int i,j;
    char **array=(char**)malloc(sizeof(char*)*LENGTH);
    for(i=0;i<LENGTH;i++)
    {
        *(array+i)=(char*)malloc(sizeof(char)*LENGTH);
    }
    for(i=0;i<LENGTH;i++)
    {
        for(j=0;j<LENGTH;j++)
        {
            *(*(array+i)+j)=' ';
        }
    }
    return array;
}

char **readin(char **array)
{
    FILE *fp;
    int arrayx;
    char temp[LENGTH];
    fp=fopen("wirewcircuit1.txt","r");
    for(arrayx=0;arrayx<LENGTH;arrayx++)
    {
        fgets(temp,1000,fp);
        memcpy(array[arrayx],temp,LENGTH);

    }
    fclose(fp);
    return array;
}
