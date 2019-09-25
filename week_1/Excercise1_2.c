#include<stdio.h>
int main()
{
	int a,b,c;
	printf("Input three integers: ");
	scanf("%d%d%d",&a,&b,&c);
	printf("Twice the sum of integers plus 7 is %d\n",(a+b+c)*2+7);
	return 0;
}