#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXSIZE 46

typedef struct Node
{
	char *word;
	struct Node *next;
}Node;

Node *insert(Node *head,char *temp, int lenth);
Node *addarray(Node *head,char *argv);
int compare(char *a, char*b);
int countminsize(char *a, char *b);
void printlink(Node *head);
Node *create();

int main(int argc, char **argv)
{
	if (argc==2)
	{
		Node *head=create();
		head=addarray(head,argv[1]);
		printlink(head);
	}
	else{
		printf("Error.\n");
	}

	return 0;
}

Node *create()
{
    Node *p=(Node *)malloc(sizeof(Node));
    p->word=(char *)malloc(sizeof(char)*MAXSIZE);
    return p;
}

void printlink(Node *head)
{
    int i;
    Node *p=head;
    do
    {
        for(i=0;i<strlen(p->word);i++)
        {
            printf("%c",p->word[i]);
        }
        if(p->next!=NULL)
        {
            printf(" -> ");
        }
        p=p->next;
    }while (p!=NULL);
    printf("\n");
}


Node *addarray(Node *head,char *argv)
{
	FILE *fp=fopen(argv,"r");
	char *temp=(char *)malloc(sizeof(char)*MAXSIZE);
	int lenth=0;

	fscanf(fp,"%s",temp);
	while(!feof(fp))
	{
		head=insert(head,temp,lenth);
		fscanf(fp,"%s",temp);
	}
}

Node *insert(Node *head, char *temp, int lenth)
{
    Node *p=head,*current=create();
    while (compare(p->word,temp))
    {
        p=p->next;
    }
    current->word=temp;
    current->next=p->next;
    p->next=current;
	lenth++;
    return head;
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
