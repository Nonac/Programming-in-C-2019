#include<stdio.h>
#define DIF '0'

void int2string(int i,char *s);

int main()
{
	int i;
	char s[256];
	scanf("%d",&i);
	int2string(i,s);
	printf("%s\n",s);
	return 0 ;
}

void int2string(int i,char *s)
{
	int pos=0,j;
	while(i!=0)
	{
		if(pos==0)
		{
			s[pos]=i%10+DIF;
			i/=10;
			pos++;
		}else
		{
			for(j=pos;j>0;j--)
			{
				s[j]=s[j-1];
			}
			s[0]=i%10+DIF;
			i/=10;
			pos++;
		}	
	}
}
