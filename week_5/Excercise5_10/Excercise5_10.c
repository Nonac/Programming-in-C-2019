#include <stdio.h>
#include <stdlib.h>
#define SIZELIMIT 20

typedef struct coordinate{
    int x;
    int y;
}coordinate;

char **readin(char **maze,FILE *fp,int width, int height);
char **calmaze(char **maze,int x,int y,int width, int height);
int isValue(char **maze,int x,int y,int width,int height);

int main(int argc, char **argv)
{
    FILE *fp;
    int i,j,width,height;
    char **maze;
    coordinate man;
    if(argc==2)
    {
        fp=fopen(argv[1],"r");
        fscanf(fp,"%d",&width);
        fscanf(fp,"%d",&height);
        if(width>SIZELIMIT||height>SIZELIMIT)
        {
            printf("Error.");
            return 0;
        } else{
            maze=(char**)malloc(sizeof(char*)*height);
            for(i=0;i<height;i++)
            {
                *(maze+i)=(char*)malloc(sizeof(char)*width);
            }
            maze=readin(maze,fp,width,height);
            man.x=0;
            man.y=1;
            maze=calmaze(maze,man.x,man.y,width,height);

            for(i=0;i<width;i++)
            {
                for (j = 0;  j<height ; j++) {
                    printf("%c",*(*(maze+i)+j));
                }
                printf("\n");
            }
        }
    } else{
        printf("Error.\n");
    }
}

char **readin(char **maze,FILE *fp,int width, int height)
{
    char temp[width];
    int arrayx,arrayy;
    for(arrayx=0;arrayx<height;arrayx++)
    {
        if(fgets(temp,width+1,fp)!=NULL)
        {
            for(arrayy=0;arrayy<width;arrayy++)
            {
                *(*(maze+arrayx)+arrayy)=temp[arrayy];
            }
        }
    }
    fclose(fp);
    return maze;
}

char **calmaze(char **maze,int x,int y,int width, int height)
{
    int i,j;
    if(x==width||y==height)
    {
        return maze;
    } else{
        for(i=x-1;i<x+2;i++)
        {
            for(j=y-1;j<y+2;j++)
            {
                if((i==x||j==y)&&((i!=x)&&(j!=y)))
                {
                    if (isValue(maze,i,j,width,height))
                    {
                        *(*(maze+x)+y)='.';
                        maze=calmaze(maze,i,j,width,height);
                        *(*(maze+x)+y)=' ';
                    }
                }
            }
        }
    }
    return maze;
}

int isValue(char **maze,int x,int y,int width,int height)
{
    if(x==width||y==height)
    {
        return 1;
    }
    if(*(*(maze+x)+y)==' ')
    {
        return 1;
    }
    return 0;
}
