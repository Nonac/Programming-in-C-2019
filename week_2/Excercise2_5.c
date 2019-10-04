#include<stdio.h>

typedef struct
{
	int longest;
	int longest_num;
	int max;
	int max_num;
}Record;

int hailstone(int temp);

int main()
{
	int i,n,cnt,temp;
	Record record;
	printf("Please enter a range:");
	scanf("%d",&n);
	record.max=0;
	record.longest=0;
	record.max_num=0;
	record.longest_num=0;

	for(i=1;i<=n;i++)
	{
		temp=i;
		cnt=1;
		if(temp>record.max)
                {
	                record.max=temp;
                        record.max_num=i;
                }
		while(temp!=1)
		{
			temp=hailstone(temp);
			cnt++;
			if(temp>record.max)
			{
				record.max=temp;
				record.max_num=i;
			}		
		}
		if(cnt>record.longest)
		{
			record.longest=cnt;
			record.longest_num=i;
		}		
	}
	
	printf("\n\nThe initial number (less than %d) creating the longest hailstone sequence (%d numbers) is %d.\n",n,record.longest,record.longest_num);
	printf("\nThe initial number (less than %d) creating the largest hailstone sequence (%d) is %d.\n",n,record.max,record.max_num);
	return 0;
}

int hailstone(int temp)
{
	if(temp%2==0)
	{
		return (temp/2);
		
	}else
	{
		return (3*temp+1);
	}
}
