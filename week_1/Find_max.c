#include<stdio.h>
int main()
{
	int i,n;
	double max,temp;
	printf("How many numbers do you wish to enter ?");
	scanf("%d",&n);
	printf("Enter %d real numbers: ",n);
	scanf("%lf",&max);
	for(i=0;i<n-1;i++)
	{
		scanf("%lf",&temp);
		if(max<temp) max=temp;
	}
	printf("Maximum value: %5f\n",max);
	return 0;
}
