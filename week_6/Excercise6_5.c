#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int prime;
    struct Node *next;
}Node;

Node *calprime(char *argv);
Node * create();
Node *createprime(int temp);
Node *insert(Node *head,int cnt);
Node *findprime(Node *headprime, int temp);
void printlink(char *argv,Node *head);

int main(int argc, char **argv)
{
    if(argc==2)
    {
        Node *head=calprime(argv[1]);
        printlink(argv[1],head);
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
    int i,cnt=2,flag=0;
    Node *head=create();
    while(cnt<=temp)
    {
        for (i = 2;  i<cnt ; i++)
        {
            if(cnt%i==0)
            {
                flag=1;
            }
        }
        if (flag==0&&i==cnt)
        {
            head=insert(head,cnt);
        }
        cnt++;
        flag=0;
    }
    return head;
}

Node *insert(Node *head,int cnt)
{
    Node *p=head,*temp=create();
    while (p->next!=NULL)
    {
        p=p->next;
    }
    temp->prime=cnt;
    p->next=temp;
    temp->next=NULL;
    return head;
}


Node *calprime(char *argv)
{
    int temp=atoi(argv);
    Node *headprime=createprime(temp);
    Node *p=headprime;
    Node *head=create();
    Node *restemp=create();
    Node *current=head;
    while(temp>1)
    {
        p=findprime(p,temp);
        restemp->prime=p->prime;
        current->next=restemp;
        current=current->next;
        temp/=p->prime;
    }
    return head;
}

Node *findprime(Node *p, int temp)
{
    while (temp%p->prime!=0)
    {
        p=p->next;
    }
    return p;
}

void printlink(char *argv,Node *head)
{
    int cnt=0,temp=0;
    Node *p=head;
    printf("%d = ",atoi(argv));
    temp=head->prime;
    while (p->next!=NULL)
    {
        while(temp==p->prime)
        {
           p=p->next;
           cnt++;
        }
        printf("%d^%d ",temp,cnt);
        temp=p->prime;
        cnt=0;
    }
}