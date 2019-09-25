#include <stdio.h>
#define HEIGHT 4
int main(void) {
	int i = 0,n=1;
	printf("\n\n"); 
	while(n<9)
	{
		if (n==1||n==8)
		{
			printf("  ccccc\n"); 
			n++;
		}
		else if(n==2||n==7)
		{
			printf("cc     cc\n"); 
			n++;
		}
		else while(i < HEIGHT)
		{ 
			printf("cc\n"); 
			i ++;
			n++;
		} 
	}
	return 0;
}
