#include<stdio.h>
#include<stdlib.h>

int **readin(int **array);
int **create();
int nextarray(int **array,int **next);
int nextelem(int **array,int arrayx,int arrayy);
int main()
{
	int **array,**next;
	array=create();
	next=create();

	array=readin(array);
}

int **create(int **arrat)
{
	int i;
	array=(int**)malloc(sizeof(int*)*40);
	for(i=0;i<40;i++)
	{
		*(array+i)=(int*)malloc(sizeof(int)*40);
	}		
	return array;
}

int readin(**array)
{
	FILE *fp;
	fp=fopen();

	fclose(fp);
	return array;
}

int nextarray(int **array,int **next)
{
	int arrayx,arrayy,nextx,nexty;
	for(arrayx=0;arrayx<40;arrayx++)
	{
		for(arrayy=0;arrayy<40;arrayy++)
		{
			for(nextx=0;nextx<40;nextx)
			{
				for(nexty=0;nexty<40;nexty++)
				{
					*(*(next+nextx)+nexty)=nextelem(array,arrayx,arrayy);	
				}
			}
		}
	}	
}

int nextelem(int **arrayy,int arrayx,int arrayy)
{
	switch (*(*(array+arrayx)+arrayy)):
		case 0:return 0;
		case 1:return 2;
		case 2:return 3;
		case 3:
				
}
