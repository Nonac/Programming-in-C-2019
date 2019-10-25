#include "neillncurses.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#define LENGTH 40
#define EMPTY ' '
#define HEAD 'H'
#define TAIL 't'
#define COPPER 'c'
#define HEADS "H"
#define TAILS "t"
#define COPPERS "c"
#define LINEBREAKLENTH 2
/*
*Available codes from question 1 if we print out correct arrays.
*By using Neill's work, we could get api from ncurse package.
*Pass all the corrent parameters to use graphic interface.
*/
char **create();
char **readin(char **array,char *argv);
char **nextarray(char **array,char **next);
char **change(char **array,char **next);
char nextelem(char **array,int arrayx,int arrayy);
char findhead(char **array,int arrayx,int arrayy);
void friendlyError();

int main(int argc,char **argv)
{
  	
 	char **array=create(),**next=create();
	char arrayregular[LENGTH][LENGTH];
	int i,j;
	NCURS_Simplewin sw;
    	if( argc==2 )
    	{
		array=readin(array,argv[1]);

		assert(array);

		Neill_NCURS_Init(&sw);
/*if set the char and the blackground the same color,we will get a square.*/
		Neill_NCURS_CharStyle(&sw, HEADS, COLOR_BLUE, COLOR_BLUE, A_NORMAL);
		Neill_NCURS_CharStyle(&sw, TAILS, COLOR_RED, COLOR_RED, A_NORMAL);
		Neill_NCURS_CharStyle(&sw, COPPERS, COLOR_YELLOW, COLOR_YELLOW, A_NORMAL);				
		
		do{
			next=nextarray(array,next);
/*I have to change my 2-D char array to char[][] to fit Neill's code.*/
			for(i=0;i<LENGTH;i++)
			{
				for(j=0;j<LENGTH;j++)
				{
					arrayregular[i][j]=next[i][j];
				}
			}
     			Neill_NCURS_PrintArray(&arrayregular[0][0], LENGTH, LENGTH, &sw);
     			Neill_NCURS_Delay(1000.0);
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

/*write a function to create 2-D array by dynamic array*/
char **create()
{
    	int i;
    	char **array=(char**)malloc(sizeof(char*)*(LENGTH));
    	for(i=0;i<LENGTH;i++)
    	{
		*(array+i)=(char*)malloc(sizeof(char)*(LENGTH));
    	}

	assert(array);

    	return array;
}

/*read in to current from seed file.*/
char **readin(char **array,char *argv)
{
    	FILE *fp;
    	int arrayx;
    	char temp[LENGTH+LINEBREAKLENTH];
    	fp=fopen(argv,"r");
/*
*function fgets get a number n,but read in n-1 chars.
*And every rows have both '\n' and '\0' at the end.
*So we have to define a 2 chars break(LINEBREAKLIENTH)in fgets. 
 */
    	for(arrayx=0;arrayx<LENGTH;arrayx++)
    	{
		if(fgets(temp,LENGTH+LINEBREAKLENTH,fp)!=NULL)
		{
			memcpy(array[arrayx],temp,LENGTH);
    		}
	}
    	fclose(fp);

	assert(array);

	return array;
}

/*generate next array by nextelem rule.*/
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

	assert(next);

    	return next;
}

/*replace current from next array*/
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

/*use given rule to generate next element*/
char nextelem(char **array,int arrayx,int arrayy)
{

	assert(arrayx>=0&&arrayx<=LENGTH);
	assert(arrayy>=0&&arrayy<=LENGTH);

    	switch (*(*(array+arrayx)+arrayy)) {
		case EMPTY:
			return EMPTY;
		case HEAD:
			return TAIL;
		case TAIL:
			return COPPER;
		case COPPER:
			return (findhead(array,arrayx,arrayy))? HEAD:COPPER;
		default:
			friendlyError();
			exit(EXIT_FAILURE);
    	}
}

/*find out how many Head arround current element.*/
char findhead(char **array,int arrayx,int arrayy)
{
    	int i,j,cnt=0;

	assert(arrayx>=0&&arrayx<=LENGTH);
	assert(arrayy>=0&&arrayy<=LENGTH);

    	for(i=arrayx-1;i<arrayx+2;i++)
    	{
		for (j =arrayy-1;j<arrayy+2; j++)
        		{
            			if (!(i<0 || j<0 || i>=LENGTH || j>=LENGTH || (i==arrayx && j==arrayy)))
            			{
                			if(*(*(array+i)+j)==HEAD) 
					{
						cnt++;
					}
            			}
		}
    	}

	assert(cnt>=0&&cnt<=8);

	return ((cnt==1)||(cnt==2))? 1:0;
}

/*Friendly Error graphic interface.*/
void friendlyError()
{
	NCURS_Simplewin sw;
	char a[LENGTH][LENGTH];
  	int i,j;
	Neill_NCURS_Init(&sw);
	/* fill the array with spaces */
  	for(j=0; j<LENGTH; j++)
	{
     		for(i=0; i<LENGTH; i++)
		{
        		a[j][i] = ' ';
     		}
  	}
	do{
		memcpy(a[LENGTH/2], "Input invalid. Please change the files.\n", LENGTH);
		Neill_NCURS_PrintArray(&a[0][0], LENGTH, LENGTH, &sw);
		Neill_NCURS_Delay(1000.0);
     		Neill_NCURS_Events(&sw);
	}while(!sw.finished);
	atexit(Neill_NCURS_Done);         
	exit(EXIT_FAILURE);
}
