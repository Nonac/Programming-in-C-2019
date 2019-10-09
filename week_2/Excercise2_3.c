#include<stdio.h>
#define UPPERCASE_SUM ('A'+'Z')
#define LOWERCASE_SUM ('a'+'z')

int scode(int a);

int main()
{
	char c;
	printf("Please enter the source code:\n");
	while((c=getchar())!= EOF)
	{
		putchar(scode(c));	
	}
	return 0;
}

int scode(int a)
{
	if(a<='z' && a>='a') return (LOWERCASE_SUM-a);
	else if(a<='Z' && a>='A') return(UPPERCASE_SUM-a);
	else return a;
	return 0;
}
