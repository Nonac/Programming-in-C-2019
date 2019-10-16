#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char c;
    int num;
    struct node *next;
}Node;

Node *create(char *s);
void soundex(Node *p);
int replace(char c);
void search(char c,char *target,char re);

int main()
{
    Node *p=NULL;
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
    int i=0;
    head=(Node *)malloc(sizeof(Node));
    p=head;

    while(s[i]!='\0')
    {
        temp=(Node *)malloc(sizeof(Node));
        temp->c=s[i];
        temp->num=replace(s[i]);
        p->next=temp;
        p=temp;
    }
    free(temp);
    return head;
}

int replace(char c)
{
    char _LABIAL[]={'b','f','v','p','\0'};
    char _GUTTERALS_SIBILANTS[]={'c','g','j','k','q','s','x','z','\0'};
    char _DENTAL[]={'d','t','\0'};
    char _LONG_LIQUID[]={'l','\0'};
    char _NASAL[]={'m','n','\0'};
    char _SHORT_LIQUID[]={'r','\0'};
    char _SKIPPED[]={'a','e','i','o','u','y','\0'};
    char _SKIPPED_SPECIAL[]={'h','w','\0'};

    search(c,_LABIAL,'1');
    search(c,_GUTTERALS_SIBILANTS,'2');
    search(c,_DENTAL,'3');
    search(c,_LONG_LIQUID,'4');
    search(c,_NASAL,'5');
    search(c,_SHORT_LIQUID,'6');
    search(c,_SKIPPED,'7');
    search(c,_SKIPPED_SPECIAL,'8');

    return (c-'0');
}

void search(char c,char *target,char re)
{
    int i;
    while(target[i++]!='\0')
    {
        if (c == target[i]) c=re;
    }
}

void soundex(Node *p)
{
    
}
