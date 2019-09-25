#include<stdio.h>

char isvowel(char c)
{
	char vowel[] = "aeiou";
	char nonvowels[] ="BCDFGHJKLMNPQRSTVWXYZ";
	for(int i=0;vowel[i]!='\0';i++)
	{
		if(c==vowel[i]) c-=32;
	}
	for(int i=0;nonvowels[i]!='\0';i++)
	{
		if(c==nonvowels[i]) c+=32;
	}
	return c;
}


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