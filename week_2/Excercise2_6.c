#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int randxy();

int main() {
	int i, ha, hc = 0;
	srand((unsigned)time(NULL));

    	printf("Please enter a loop time:");
    	scanf("%d",&ha);

    	for(i=0;i<ha;i++)
        {
                if (randxy()) hc++;
        }
    	printf("\nPi is %f\n",4*((float)hc)/((float)ha));
    	return 0;
}

int randxy()
{
    	double x= rand()/(RAND_MAX+1.);
    	double y= rand()/(RAND_MAX+1.);

    	return (x*x+y*y)>1?0:1;
}
