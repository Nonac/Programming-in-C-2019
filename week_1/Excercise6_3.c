#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
	double x;
	/*printf("Enter a real number:");
	scanf("%lf",&x);*/
	for(int i=0;i<500;i++)
	{
		x=pow((-1),i)*rand();
		printf("%d %lf %lf\n",i,x,(pow(sin(x),2)+pow(cos(x),2)));
	}
	
}