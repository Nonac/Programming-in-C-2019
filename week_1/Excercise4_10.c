#include<stdio.h>
int main()
{
	int i,n;
	printf("Please enter an number:");
	scanf("%d",&n);
	printf("The hailstone sequence is:\n%d\n",n);
	for(i=0:i<9;i++)
	{
		if(n%2==0)
		{
			n=n/2;
			printf("%d\n",n);
		}else
		{
			n=3*n+1;
			printf("%d\n",n);
		}
	}
}
