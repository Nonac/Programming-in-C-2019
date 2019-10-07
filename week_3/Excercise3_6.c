#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define DIF 'a'-'A'

int read(char *sp);

int main()
{
	char *sp=(char *)malloc(sizeof(char));
	int len,i,flag=0;
	printf("Please enter a test string:\n");
		
	len=read(sp);
	for(i=0;i<((len/2)+1);i++)
	{
		if(sp[i]!=sp[len-i-1]) flag=1;
	}
	if (flag==0) printf("It is Palindromes!\n");
	else printf("It is not Palindromes\n");
	return 0;
}


int read(char *sp)
{
	char str;
	int len=0;

        while((str=getchar())!='\n')
        {
                if(islower(str)) 
		{
			sp[len]=str;
			sp=(char *)realloc(sp,((++len)+1)*sizeof(char));
		}
		else if(isupper(str)) 
		{
			sp[len]=str+DIF;
                	sp=(char *)realloc(sp,((++len)+1)*sizeof(char));
                }
        }       
	return len;
}
