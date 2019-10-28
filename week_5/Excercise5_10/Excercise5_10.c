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

int main()
{
    	FILE *fp;
    	int i,j,width,height;
    	char **maze,c;
    	coordinate man;
    	fp=fopen("/home/ff19085/CLionProjects/clion/maze.txt","r");
    	fscanf(fp,"%d",&width);
    	fscanf(fp,"%d",&height);
		c=fgetc(fp);
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
}

char **readin(char **maze,FILE *fp,int width, int height)
{
    	char temp[width];
    	int arrayx,arrayy;
    	for(arrayx=0;arrayx<height;arrayx++)
    	{
        	if(fgets(temp,width+2,fp)!=NULL)
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
    	int i,j,k=1;
    	if(x==width||y==height)
    	{
        	return maze;
    	} else{
        	for(i=x-1;i<x+2;i++)
        	{
            		for(j=y-1;j<y+2;j++)
            		{
                		if((!(i<0 || j<0 || i>=width|| j>=height || (i==x&& j==y)))\
                            &&((i==x)||(j==y)))
                		{
                    			if (isValue(maze,i,j,width,height))
                    			{
						
                        			*(*(maze+i)+j)='.';
                        			maze=calmaze(maze,i,j,width,height);
                    			}
                		}
            		}
        	}
    	}
    return maze;
}

int isValue(char **maze,int x,int y,int width,int height)
{
	int i,j,cnt=0;	
	if(y==width||x==height)
    	{
        	return 1;
    	}
    	if(*(*(maze+x)+y)==' ')
    	{
        	return 1;
    	}
        return 0;
}
