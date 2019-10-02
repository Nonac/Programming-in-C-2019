#include<stdio.h>

void Range_array(int m,int *array);

int main()
{
	int array[2],m;
	while(1)
	{
		printf("How much mone would you like?");
		scanf("%d",&m);
		if (m<=0) printf("R U kidding me?\n");
		if (m%20==0 && m!=0)
		{
			printf("OK, dispensing ...\n");
			return 0;
		}else
		{
			Range_array(m,array);
			printf("I can give you %d or %d, try again.\n",array[0],array[1]);
		}
	}
}

void Range_array(int m, int *array)
{
	array[0]=m/20*20;
	array[1]=array[0]+20;
}
