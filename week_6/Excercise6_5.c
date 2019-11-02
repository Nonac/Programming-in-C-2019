#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int prime;
    struct node *next;
}Node;

Node *calprime(char *argv);
Node *create();
Node *createprime(int temp);
Node *insert(Node *head,int cnt);
Node *findprime(Node *headprime, int temp);
void printlink(char *argv,Node *head);

int main()
{


    Node *head=calprime("768");
    printlink("768",head);

    return 0;
}

Node *create()
{
    Node *head=(Node *)malloc(sizeof(Node));
    head->next=NULL;
    head->prime=0;
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
    if(head->next==NULL&&head->prime==0)
    {
        head->prime=cnt;
        return head;
    }
    while (p->next != NULL) {
        p = p->next;
    }
    temp->prime = cnt;
    p->next = temp;
    temp->next = NULL;

    return head;

}


Node *calprime(char *argv)
{
    int temp=atoi(argv);
    Node *headprime=createprime(temp);
    Node *p=headprime;
    Node *head=create();
    Node *restemp;
    Node *current=head;
    while(temp>1)
    {
        restemp=create();
        p=findprime(p,temp);
        restemp->prime=p->prime;
        current->next=restemp;
        current=current->next;
        temp=temp/p->prime;
    }
    return head->next;
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

    while (p!=NULL)
    {
        temp=p->prime;
        do{
            cnt++;
            p=p->next;
            if(p==NULL)
            {
                break;
            }
        }while(temp==p->prime);
        printf("%d^%d ",temp,cnt);
        if(p!=NULL)
        {
            printf("* ");
        }
        cnt=0;
    }
}