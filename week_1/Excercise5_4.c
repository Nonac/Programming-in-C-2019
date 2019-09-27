#include<stdio.h>
#define FAR 'a'-'A'


char isvowel(char c);

int main()
{
	
	char c;
	printf("input a charracter\n");
	while ((c = getchar()) != EOF) {
		c=isvowel(c);
		putchar(c);
	}
	return 0;
}


char isvowel(char c)
{
	char vowel[] = "aeiou";
	char nonvowels[] ="BCDFGHJKLMNPQRSTVWXYZ";
	int i;
	for(i=0;vowel[i]!='\0';i++)
	{
		if(c==vowel[i]) c-=FAR;
	}
	for(i=0;nonvowels[i]!='\0';i++)
	{
		if(c==nonvowels[i]) c+=FAR;
	}
	return c;
}
