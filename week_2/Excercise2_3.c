#include<stdio.h>
#define UPPERCASE_SUM ('A'+'Z')
#define LOWERCASE_SUM ('a'+'z')

int scode(int a);

int main()
{
	printf("Please enter the source code:\n");
	char c;
	while((c=getchar())!= EOF)
	{
		putchar(scode(c));	
	}
	return 0;
}

int scode(int a)
{
	if(a<='z' && a>='a')
	{
		return (LOWERCASE_SUM-a);
	}
	if(a<='Z' && a>='A')
	{
		return(UPPERCASE_SUM-a);
	}
}
