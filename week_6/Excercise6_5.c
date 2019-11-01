#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int prime;
    struct Node *next;
}Node;

void calprime(Node *head,char *argv);
Node * create();
Node *createprime(int temp);

int main(int argc, char **argv)
{
    if(argc==2)
    {
        Node *head=create();
        calprime(head,argv[1]);
    } else{
        printf("Error.\n");
    }
    return 0;
}

Node *create()
{
    Node *head=(Node *)malloc(sizeof(Node));
    return head;
}

Node *createprime(int temp)
{
    int i,;
    for(i=2;)
    {
        
    }
    return head;
}


void calprime(Node *head,char *argv)
{
    int temp=atoi(argv);
    Node *headprime=createprime(temp);
    while(temp%)
    {

    }
}
