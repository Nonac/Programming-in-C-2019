#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 46

typedef struct Node
{
	char *word;
	struct Node *next;
}Node;

int main(int argc, char **argv)
{
	if (argc==2)
	{
		Node *head=(Node *)malloc(sizeof(Node));
		head=addarray(head,argv[1]);	
	}
	else{
		printf("Error.\n");
	}

	return 0;
}

Node *addarray(Node *head,char *argv)
{
	FILE *fp=fopen(argv,"r");
	char *temp=(char *)malloc(sizeof(char)*MAXSIZE);

	fscanf(fp,"%s",temp);
	while(!feof(fp))
	{

	}	
}


int countminsize(char *a, char *b)
{
	return (strlen(a)>=strlen(b))?strlen(b):strlen(a);	
}

int compare(char *a, char*b)
{
	int i;
	for(i=0;i<countminsize(a,b);i++)
	{
		if((*(a+i))<(*(b+i)))
		{
			return 0;
		}else if((*(a+i))>(*(b+1)))
		{
			return 1;
		}		
	}
	return (strlen(a)>strlen(b)?1:0;	
}
