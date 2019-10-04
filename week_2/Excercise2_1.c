#include<stdio.h>

void Createunvowel(char *unvowel,char *vowel);

int main()
{
	char unvowel[21],vowel[5]={'a','e','i','o','u'};
	int i,j,k,cnt=1;
	Createunvowel(unvowel,vowel);	
	for(i=0;i<21;i++)
	{
		for(j=0;j<5;j++)
		{
			for(k=0;k<21;k++)
			{
				printf("%d %c%c%c\n",cnt,unvowel[i],vowel[j],unvowel[k]);
				cnt++;
			}
		}
	}
	return 0;		
		
}

void Createunvowel(char *unvowel,char *vowel)
{
	int i,j=0,k=0;
	char temp;
	for(i=0;i<26;i++)
	{
		temp='a'+i;
		if(temp!=vowel[j])
		{
			unvowel[k]=temp;
			k++;
		}
		else
		{
			j++;
		}
	}
}	
