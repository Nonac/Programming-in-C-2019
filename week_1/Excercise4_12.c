#include<stdio.h>
#include<math.h>

int main()
{
	int n,cnt=1,temp,sqt,flag=0;
	double f;
	printf("How many primes do you want to print out?");
	scanf("%d",&n);
	for (temp=2;cnt<=n;temp++)
	{
		f=sqrt((float)temp);
		for(sqt=2;((sqt<f)&&(flag==0));sqt++)
		{
			if(temp%sqt==0) flag=1;
		}
		if((sqt>f)&&(flag==0))
		{
			printf("%d ",temp);
			cnt++;
		}
		flag =0;
	}
	printf("\n");
	return 0;	
}
