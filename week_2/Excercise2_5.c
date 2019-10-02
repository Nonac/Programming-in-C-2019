#include<stdio.h>

typedef struct node
{
	int data;
	struct Qnode *next;
}Node

void hailstone(int n);
node *create(int n);

int main()
{
	int i,n,*array,lenth;
	printf("Please enter an number:");
	scanf("%d",&n);

	return 0;
}

node *create(int n)
{
	
}


int hailstone(int n)
{
	if(n%2==0)
	{
		return (n/2);
		
	}else
	{
		retunr (3*n+1);
	}
}
