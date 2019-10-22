#include<stdio.h>
#include<stdlib.h>
#define LENGTH 40
#define EMPTY ' '
#define HEAD 'H'
#define TAIL 't'
#define COPPER 'c'
#define GENERATION 1000
#define LINEBREAKLENTH 2

/*
*We could solve the problem by  following steps:
*1.create two 2-D array:current and next.
*2.read in from wireworld seed file.
*3.generate a next array from current array.
*4.print next array to a out file.
*5.replace current from next
*6.loop from 3 to 5 steps 1000 times.
*/

int **create();
int **readin(int **array,char *argv);
int **nextarray(int **array,int **next);
int **change(int **array,int **next);
int nextelem(int **array,int arrayx,int arrayy);
int findhead(int **array,int arrayx,int arrayy);
void printout(int **next,FILE *ofp);

int main(int argc,char **argv)
{
    	int **array=create(),**next=create();
    	int i;
    	FILE *ofp;
    	if( argc==2 )
    	{
        		ofp=fopen("wireworld_out.txt","wt");
        		array=readin(array,argv[1]);
        		for (i = 0; i < GENERATION; ++i) 
		{
            			next=nextarray(array,next);
            			printout(next,ofp);
            			array=change(array,next);
        		}
        		fclose(ofp);
    	}
    	else
    	{
        		printf("ERROR: Incorrect usage.\n");
    	}
    	return 0;
}

/*write a function to create 2-D array by dynamic array*/
int **create()
{
    	int i;
    	int **array=(int**)malloc(sizeof(int*)*LENGTH);
    	for(i=0;i<LENGTH;i++)
    	{
        		*(array+i)=(int*)malloc(sizeof(int)*LENGTH);
    	}
    	return array;
}

/*read in to current from seed file.*/
int **readin(int **array,char *argv)
{
    	FILE *fp;
    	int arrayx,arrayy;
    	char temp[LENGTH+LINEBREAKLENTH];
    	fp=fopen(argv,"r");
    	for(arrayx=0;arrayx<LENGTH;arrayx++)
    	{
/*function fgets get a number n,but read in n-1 chars.
And every rows have both '\n' and '\0' at the end.
So we have to define a 2 chars break(LINEBREAKLIENTH)in fgets. 
 */
        		fgets(temp,LENGTH+LINEBREAKLENTH,fp);
        		for(arrayy=0;arrayy<LENGTH;arrayy++)
        		{
            			*(*(array+arrayx)+arrayy)=temp[arrayy];
        		}
    	}
    	fclose(fp);
    	return array;
}

/*print out to file*/
void printout(int **next,FILE *ofp)
{
    	int nextx,/*find out how many Head arround current element.*/nexty;
    	char elem;
    	for(nextx=0;nextx<LENGTH;nextx++)
    	{
        		for(nexty=0;nexty<LENGTH;nexty++) 
			{
            			elem=*(*(next+nextx)+nexty);
            			fprintf(ofp,"%c",elem);
        		}
        		fprintf(ofp,"\n");
    	}
}

/*generate next array by nextelem rule.*/
int **nextarray(int **array,int **next)
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

/*replace current from next array*/
int **change(int **array,int **next)
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
int nextelem(int **array,int arrayx,int arrayy)
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
            			printf("Input invalid. Please change the files.\n");
				exit(EXIT_FAILURE);
    	}
}

/*find out how many Head arround current element.*/
int findhead(int **array,int arrayx,int arrayy)
{
    	int i,j,cnt=0;
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
    	if((cnt==1)||(cnt==2)) 
	{
		return 1;
    	}else{
		return 0;
	}
}
