#include<stdio.h>

int overcooked(int n);
void count(int n,int *times);

int main()
{
	int i,n,cnt,times[3];
	cnt=0;
	for(i=0;i<3;i++)
	{
		times[i]=0;
	}
	printf("Type the time required:\n");
	scanf("%d",&n);

	n=overcooked(n);
	count(n,times);

	for(i=0;i<3;i++)
	{
		cnt+=times[i];	
	}
	
	printf("The number of button presses = %d\n",cnt);
	return 0;
	
}

int overcooked(int n)
{
	while(n%10!=0)
	{
		n++;
	}
	return n;
}

void count(int n,int *times)
{
	while(n/600!=0)
	{
		n-=600;
		times[0]++;
	}
	while(n/60!=0)
	{
		n-=60;
		times[1]++;
	}
	while(n/10!=0)
	{
		n-=10;
		times[2]++;
	}			
}
