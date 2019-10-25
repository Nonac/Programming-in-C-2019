#include<stdio.h>

typedef struct Node{
	char c;
	struct Node *next;
}Node;



int main()
{
	char **dict=(char **)malloc((char *));

	dict=readindictionary(dict);		
}


char **readindictionary(char **dict)
{
	FILE *fp;

	fp=fopen("eng_370K_shuffle.txt","r");

	
}

