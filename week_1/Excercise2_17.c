#include<stdio.h>
#include<stdlib.h>

int main()
{
	double n;
	int i,minus_cnt=0,plus_cnt=0;
	double median=RAND_MAX / 2;
	for(i=0;i<500;i++)
	{
		n=rand();
		if(n<median) minus_cnt++;
		else plus_cnt++;
		printf("%d\n",(plus_cnt-minus_cnt));
	}
}
