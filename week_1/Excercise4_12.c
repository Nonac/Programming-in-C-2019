#include<stdio.h>
#include<math.h>

int main()
{
	int n,cnt=1,temp,sqt,flag=0;
	printf("How many primes do you want to print out?");
	scanf("%d",&n);
	for (temp=2;cnt<=n;temp++)
	{
		for(sqt=2;sqt<temp;sqt++)
		{
			if(temp%sqt==0) flag=1;
		}
		if((temp==sqt)&&(flag==0))
		{
			printf("%d ",temp);
			cnt++;
		}
		flag =0;
	}
	printf("\n");
	return 0;	
}
