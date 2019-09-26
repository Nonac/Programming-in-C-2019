#include<stdio.h>
#include<math.h>

int main()
{
	int n,cnt=1,temp=2,sqt;
	printf("How many primes do you want to print out?");
	scanf("%d",&n);
	for (temp;cnt<=n;temp++)
	{
		for(sqt=2;sqt<temp;sqt++)
		{
			if(temp%sqt==0) break;
		}
		if(temp==sqt)
		{
			printf("%d ",temp);
			cnt++;
		}
	}
	printf("\n");
	return 0;	
}
