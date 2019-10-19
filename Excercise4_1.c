#include<stdio.h>
#include<stdlib.h>

int **readin(int **array);
int **nextelem(int **array,int **next);

int main()
{
	int **array,**next; 

	array=(int**)malloc(sizeof(int*)*40);
	for(i=0;i<40;i++)
	{
		*array=(int*)malloc(sizeof(int)*40);
	}
	array=readin(array);
	return 0;		
}

int **readin(int **array)
{
	FILE *fp;
	fp=fopeb();
	
	fclose(fp);
	return array;	
}

int **nextelem(int **array,**next)
{
	
}
