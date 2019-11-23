#include<stdio.h>
#include<string.h>

typedef struct node
{
	char c[5];
	int code[10];
	struct node *left;
	struct node *right;
}Node;

Node *readin(char *s);

int main()
{
	char *s="20(10(5(*)(*))(17(*)(*)))(30(21(*)(*))(*))";
	Node *treehead=readin(s);	

}

Node *readin(char *s)
{
	Node *head
}

Node *maketreenode(char *num)
{
	Node *head=(Node *)calloc(1,sizeof(Node));
		
}
