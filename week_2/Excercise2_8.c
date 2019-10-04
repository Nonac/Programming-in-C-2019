#include<stdio.h>

int TriangleNum(int n);

int main()
{
	int n,i;
	printf("Please enter an iteration times:\n");		
	scanf("%d",&n);
	printf("The triangle numbers is:\n");	
	for(i=1;i<=n;i++)
	{
		printf("%d ",TriangleNum(i));		
		if(i%10==0) printf("\n"); 	
	}
	return 0;
}

int TriangleNum(int n)
{
	if (n==1||n==2||n==3) return(n*(n+1)/2);
	else return(TriangleNum(n-1)+n);	
	return 0;	
}
