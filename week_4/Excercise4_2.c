#include<stdio.h>
#include "neillncurses.h"
#include<stdio.h>
#include<stdlib.h>
#define LENGTH 40
#define EMPTY ' '
#define HEAD 'H'
#define TAIL 't'
#define COPPER 'c'
#define HEADS "H"
#define TAILS "t"
#define COPPERS "c"
#define GENERATION 1000
#define LINEBREAKLENTH 8

char **create();
char **readin(char **array,char *argv);
char **nextarray(char **array,char **next);
char **change(char **array,char **next);
char nextelem(char **array,int arrayx,int arrayy);
char findhead(char **array,int arrayx,int arrayy);

int main(int argc,char **argv)
{
  	/* Array we'll display */
 	char **array=create(),**next=create();
	NCURS_Simplewin sw;
    	if( argc==2 )
    	{
        		array=readin(array,argv[1]);
        		Neill_NCURS_Init(&sw);
		Neill_NCURS_CharStyle(&sw, HEADS, COLOR_BLUE, COLOR_BLUE, A_NORMAL);
		Neill_NCURS_CharStyle(&sw, TAILS, COLOR_RED, COLOR_RED, A_NORMAL);
		Neill_NCURS_CharStyle(&sw, COPPERS, COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);				
		
		do{
			next=nextarray(array,next);
     			Neill_NCURS_PrintArray(&next[0][0], LENGTH+LINEBREAKLENTH, LENGTH, &sw);
     			/*  Delay in 1/1000s of a second */
     			Neill_NCURS_Delay(1000.0);
     			/* Test for mouse click, or ESC key */
     			Neill_NCURS_Events(&sw);
			array=change(array,next);
  		}while(!sw.finished);
    	
		atexit(Neill_NCURS_Done);
  		exit(EXIT_SUCCESS);
	}
    	else
    	{
        	printf("ERROR: Incorrect usage.\n");
    	}
    	return 0;
}

char **create()
{
    	int i;
    	char **array=(char**)malloc(sizeof(char*)*LENGTH);
    	for(i=0;i<LENGTH;i++)
    	{
        		*(array+i)=(char*)malloc(sizeof(char)*LENGTH);
    	}
    	return array;
}

char **readin(char **array,char *argv)
{
    	FILE *fp;
    	int arrayx;
    	char temp[LENGTH+2];
    	fp=fopen(argv,"r");
    	for(arrayx=0;arrayx<LENGTH;arrayx++)
    	{
        		fgets(temp,LENGTH+2,fp);
		memcpy(array[arrayx],temp,LENGTH);
        		/*for(arrayy=0;arrayy<LENGTH;arrayy++)
        		{
            			*(*(array+arrayx)+arrayy)=temp[arrayy];
        		}*/
    	}
    	fclose(fp);
    	return array;
}

char **nextarray(char **array,char **next)
{
    	int arrayx,arrayy;
    	for(arrayx=0;arrayx<LENGTH;arrayx++)
    	{
        		for(arrayy=0;arrayy<LENGTH;arrayy++)
        		{
            			*(*(next+arrayx)+arrayy)=nextelem(array,arrayx,arrayy);
        		}
    	}
    	return next;
}

char **change(char **array,char **next)
{
    	int arrayx,arrayy;
    	for(arrayx=0;arrayx<LENGTH;arrayx++)
    	{
        		for(arrayy=0;arrayy<LENGTH;arrayy++)
        		{
            			*(*(array+arrayx)+arrayy)=*(*(next+arrayx)+arrayy);
        		}
    	}
    	return array;
}

char nextelem(char **array,int arrayx,int arrayy)
{
    	switch (*(*(array+arrayx)+arrayy)) {
        		case EMPTY:
            			return EMPTY;
        		case HEAD:
            			return TAIL;
        		case TAIL:
            			return COPPER;
        		case COPPER:
            			if (findhead(array,arrayx,arrayy))
            			{
                			return HEAD;
            			}else
            			{
                			return COPPER;
            			}
        			default:
            				return -1;
    	}
}

char findhead(char **array,int arrayx,int arrayy)
{
    	int i,j,cnt=0;
    	for(i=arrayx-1;i<arrayx+2;i++)
    	{
        		for (j =arrayy-1;j<arrayy+2; j++)
        		{
            			if (!(i<0 || j<0 || i>=LENGTH || j>=LENGTH || (i==arrayx && j==arrayy)))
            			{
                			if(*(*(array+i)+j)==HEAD) cnt++;
            			}
        		}
    	}
    	if((cnt==1)||(cnt==2)) return 1;
    	else return 0;
}
