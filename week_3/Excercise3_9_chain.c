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
void soundex(Node *p);
char replace(char c);
int search(char c,char *target);
void checkrepeat(Node *p);
void cheakWandH(Node *p);
void checkskippedchar(Node *p);
void fillwithzero(Node *p);

int main()
{
    Node *p;
    char *s;
    printf("Enter the name:\n");
    if(scanf("%s",s)!=1) exit(0);

    p=create(s);

    soundex(p);

    return 0;
}

Node *create(char *s)
{
    Node*p=NULL,*head,*temp;
    int i=1;
    head=(Node *)malloc(sizeof(Node));
    p=head;
    head->c=((s[0]<='z')&&(s[0]>='a'))?s[0]:_tolower(s[0]);
    head->num=replace(head->c);

    while(s[i]!='\0')
    {
        temp=(Node *)malloc(sizeof(Node));
        temp->c=((s[i]<='z')&&(s[i]>='a'))?s[i]:_tolower(s[i]);
        temp->num=replace(temp->c);
        p->next=temp;
        p=temp;
        temp=temp->next;
        i++;
    }
    free(temp);
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
    char cha;

    if (search(c,_LABIAL)) return '1';
    if (search(c,_GUTTERALS_SIBILANTS)) return '2';
    if (search(c,_DENTAL)) return '3';
    if (search(c,_LONG_LIQUID)) return '4';
    if (search(c,_NASAL)) return '5';
    if (search(c,_SHORT_LIQUID)) return '6';
    if (search(c,_SKIPPED)) return '7';
    if (search(c,_SKIPPED_SPECIAL)) return '8';

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

void soundex(Node *p)
{
    cheakWandH(p);
    checkrepeat(p);
    checkskippedchar(p);
    fillwithzero(p);
}

void cheakWandH(Node *p)
{
    Node *temp,*cur=p;
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
        if(temp->num!=7)
        {
            cur=temp;
            temp=temp->next;
        }else{
            cur->next=temp->next;
            temp=temp->next;
        }
    }
}

void fillwithzero(Node *p)
{
    Node *temp,*cur=p;
    int i=1;
    temp=cur->next;
    while (temp!=NULL)
    {
        cur=temp;
        temp=temp->next;
        i++;
    }
    while(i<4)
    {
        temp=(Node *)malloc(sizeof(Node));
        temp->num=0;
        cur=temp;
        temp=temp->next;
        i++;
    }
}