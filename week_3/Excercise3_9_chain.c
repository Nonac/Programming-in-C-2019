#include <stdio.h>
#include <stdlib.h>
#define _tolower(c) ((c)+'a'-'A')
#define _toupper(c) ((c)+'A'-'a')

typedef struct node
{
    char c;
    char num;
    struct node *next;
}Node;

Node *create(char *s);
char replace(char c);
int search(char c,char *target);
void checkrepeat(Node *p);
Node *cheakWandH(Node *p);
void checkskippedchar(Node *p);
Node *fillwithzero(Node *p);
void printsundex(Node *p);

int main()
{
    Node *p;
    char *s;
    int i;
    printf("Enter the name:\n");
    if(scanf("%s",s)!=1) printf("%d",1);

    p=create(s);
    p=cheakWandH(p);
    checkrepeat(p);
    checkskippedchar(p);
    p=fillwithzero(p);
    printsundex(p);
    return 0;
}

Node *create(char *s)
{
    Node*p=NULL,*head,*temp;
    int i=1;
    head=(Node *)malloc(sizeof(Node));
    p=head;
    p->c=(((s[0]<='z')&&(s[0]>='a'))||(s[0]=='0'))?s[0]:_tolower(s[0]);
    p->num=replace(head->c);

    while(s[i]!='\0')
    {
        temp=(Node *)malloc(sizeof(Node));
        temp->c=(((s[i]<='z')&&(s[i]>='a'))||(s[i]=='0'))?s[i]:_tolower(s[i]);
        temp->num=replace(temp->c);
        p->next=temp;
        p=temp;
        i++;
    }
    p->next=NULL;
    return head;
}

char replace(char c)
{
    char _LABIAL[]={'b','f','v','p','\0'};
    char _GUTTERALS_SIBILANTS[]={'c','g','j','k','q','s','x','z','\0'};
    char _DENTAL[]={'d','t','\0'};
    char _LONG_LIQUID[]={'l','\0'};
    char _NASAL[]={'m','n','\0'};
    char _SHORT_LIQUID[]={'r','\0'};
    char _SKIPPED[]={'a','e','i','o','u','y','\0'};
    char _SKIPPED_SPECIAL[]={'h','w','\0'};
    char _ZERO[]={'0','\0'};
    char cha;

    if (search(c,_LABIAL)) return '1';
    if (search(c,_GUTTERALS_SIBILANTS)) return '2';
    if (search(c,_DENTAL)) return '3';
    if (search(c,_LONG_LIQUID)) return '4';
    if (search(c,_NASAL)) return '5';
    if (search(c,_SHORT_LIQUID)) return '6';
    if (search(c,_SKIPPED)) return '7';
    if (search(c,_SKIPPED_SPECIAL)) return '8';
    if (search(c,_ZERO)) return '0';

    return cha;
}

int search(char c,char *target)
{
    int i=0;
    while(target[i]!='\0')
    {
        if (c == target[i]) return 1;
        i++;
    }
    return 0;
}

Node *cheakWandH(Node *head)
{
    Node *temp,*cur=head;
    temp=cur->next;
    while (temp!=NULL)
    {
        if(temp->num!='8')
        {
            cur=temp;
            temp=temp->next;
        }else{
            cur->next=temp->next;
            temp=temp->next;
        }
    }
    return head;
}

void checkrepeat(Node *p)
{
    Node *temp,*cur=p;
    temp=cur->next;
    while (temp!=NULL)
    {
        if(cur->num!=temp->num)
        {
            cur=temp;
            temp=temp->next;
        }else{
            cur->next=temp->next;
            temp=temp->next;
        }
    }
}

void checkskippedchar(Node *p)
{
    Node *temp,*cur=p;
    temp=cur->next;
    while (temp!=NULL)
    {
        if(temp->num!='7')
        {
            cur=temp;
            temp=temp->next;
        }else{
            cur->next=temp->next;
            temp=temp->next;
        }
    }
}

Node *fillwithzero(Node *p)
{
    Node *temp,*cur=p,*zero;
    int i=1;
    temp=cur->next;
    while (temp!=NULL)
    {
        cur=temp;
        temp=temp->next;
        i++;
    }
    switch (i){
        case 1:
            zero=create("000");
            cur->next=zero;
            break;
        case 2:
            zero=create("00");
            cur->next=zero;
            break;
        case 3:
            zero=create("0");
            cur->next=zero;
            break;
    }
    return p ;
}

void printsundex(Node *p)
{
    int i;
    Node *temp=p->next;
    printf("%c",_toupper(p->c));
    for(i=0;i<3;i++)
    {
        printf("%c",temp->num);
        temp=temp->next;
    }
    printf("\n");
}
