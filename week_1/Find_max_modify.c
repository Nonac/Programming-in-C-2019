#include<stdio.h>
int main()
{
	int i,n,max,temp;
	printf("How many odd numbers do you wish to enter ?");
	scanf("%d",&n);
	printf("Enter %d odd numbers: ",n);
	scanf("%d",&max);
	if (max%2==0) do
	{
		printf("Please enter an odd numbers:");
		scanf("%d",&max);
	}while(max%2==0);
	for(i=0;i<n-1;i++)
	{	
		scanf("%d",&temp);
		if (temp%2==0) do
		{
			printf("Please enter an odd numbers:");
			scanf("%d",&temp);
		}while(temp%2==0);
		if(max<temp) max=temp;
	}
	printf("Maximum value: %d\n",max);
}
