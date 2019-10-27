#include <stdio.h>
#include <stdlib.h>
#define SIZELIMIT 20

typedef struct coordinate{
    int x;
    int y;
}coordinate;

char **readin(char **maze,FILE *fp,int width, int height);
char **calmaze(char **maze,int x,int y,int width, int height);
int isValue(char **maze,int x,int y);

int main(int argc, char **argv)
{
    FILE *fp;
    int i,width,height;
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
    if(x==width||y==height)
    {
        return maze;
    } else{
        switch (isValue(maze,x,y))
        {
            case 1:
                *(*(maze+x)+y)='.';
                maze=calmaze(maze,x-1,y,width,height);
                break;
            case 2:
                *(*(maze+x)+y)='.';
                maze=calmaze(maze,x+1,y,width,height);
                break;
            case 3:
                *(*(maze+x)+y)='.';
                maze=calmaze(maze,x,y-1,width,height);
                break;
            case 4:
                *(*(maze+x)+y)='.';
                maze=calmaze(maze,x,y+1,width,height);
                break;
            default:
                *(*(maze+x)+y)='X';
                maze=calmaze(maze,x,y,width,height);
                break;
        }
    }
}

int isValue(char **maze,int x,int y)
{
    if(*(*(maze+x-1)+y)==' ')
    {
        return 1;
    }
    if(*(*(maze+x+1)+y)==' ')
    {
        return 2;
    }
    if(*(*(maze+x)+y-1)==' ')
    {
        return 3;
    }
    if(*(*(maze+x-1)+y+1)==' ')
    {
        return 4;
    }
    return 0;
}
