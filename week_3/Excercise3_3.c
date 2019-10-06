#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void RandomNum(int *array,int num);

int main()
{
	int *array;
	int i,num;

	srand((unsigned)time(NULL));	
	printf("How many songs required ?\n");
	scanf("%d",&num);

	array = (int *)malloc(num*sizeof(int));
	if(!array)
	{
		printf("Failed to create array.\n");
		exit(1);
		return 0;
	}

	for(i=0;i<num;i++)
	{
		array[i]=(i+1);
	}
	
	RandomNum(array,num);

	for(i=0;i<num;i++)
	{
		printf("%d ",array[i]);
		if(i%10==0&&i!=0) printf("\n");
	}
	printf("\n");
	return 0;	
}

void RandomNum(int *array,int num)
{
	int i,RandomAdd,temp;
	for(i=num;i>1;i--)
	{
		RandomAdd=rand()%i;
		temp=array[i-1];
		array[i-1]=array[RandomAdd];
		array[RandomAdd]=temp;	
	}
}
