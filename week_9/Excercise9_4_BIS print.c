#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 5

typedef struct node
{
    char c[SIZE];
    struct node *left;
    struct node *right;
}Node;

Node *readin(char *s);
int findflag(char *s);
Node *maketreenode(char *num);
void divleaf(char *lefts,char *rights,char *s);
void copy(char *lefts,char *s,int begin, int end);
int strlenth(char *s);
void Display(struct node* root, int ident);
int isVaild(char c);


int vec_left[100] = {0};

int main()
{
    char *s="00001(00002(00003(00004(00005(*)(00009))(00007(*)(00008)))(00006))(*))(00010(00011(00012)(*))(00013(*)(*)))";
    Node *treehead=readin(s);

    Display(treehead,0);
    return 0;
}

void Display(struct node* root, int ident)
{
    int i;
    if(ident > 0)
    {
        for(i = 0; i < ident - 1; ++i)
        {
            printf(vec_left[i] ? "│   " : "    ");
        }
        printf(vec_left[ident-1] ? "├── " : "└── ");
    }

    if(!root)
    {
        printf("\n");
        return;
    }

    for(i=0;isVaild(root->c[i])||i<SIZE;i++)
    {
        printf("%c", root->c[i]);
    }
    printf("\n");
    if(!root->left && !root->right)
    {
        return;
    }

    vec_left[ident] = 1;
    Display(root->right, ident + 1);
    vec_left[ident] = 0;
    Display(root->left, ident + 1);
}

int isVaild(char c)
{
    if(c>='0'&&c<='9')
    {
        return 1;
    }
    return 0;
}

Node *readin(char *s)
{
    Node *head;
    char num[5]={'\0'};
    int i;
    char *lefts=(char *)malloc(strlenth(s)*sizeof(char));
    char *rights=(char *)malloc(strlenth(s)*sizeof(char));
    if(s[0]=='*')
    {
        return NULL;
    }
    if(findflag(s))
    {
        for(i=0;(s[i]>='0' && s[i]<='9');i++)
        {
            num[i]=s[i];
        }
        head=maketreenode(num);
        divleaf(lefts,rights,s);
        head->left=readin(lefts);
        head->right=readin(rights);
    } else
    {
        head=maketreenode(s);
    }
    return head;
}

void divleaf(char *lefts,char *rights,char *s)
{
    int begin=0,end,cnt=0;
    while (s[begin]!='(')
    {
        begin++;
    }
    for(end=1;!(s[end-1]==')'&&cnt==0);end++)
    {
        if(s[end]=='(')
        {
            cnt++;
        }
        if(s[end]==')')
        {
            cnt--;
        }
    }
    copy(lefts,s,begin,end);
    lefts[end-begin-2]='\0';
    begin=end;
    end=strlenth(s);
    copy(rights,s,begin,end);
    rights[end-begin-2]='\0';
}

int strlenth(char *s)
{
    int cnt=0;
    while ((s[cnt]>='0'&&s[cnt]<='9')||s[cnt]=='('||s[cnt]==')'||s[cnt]=='*')
    {
        cnt++;
    }
    return cnt;
}

void copy(char *leaf,char *s,int begin, int end)
{
    int i;
    for(i=begin+1;i<end-1;i++)
    {
        leaf[i-begin-1]=s[i];
    }
}

int findflag(char *s)
{
    int i,lenth=strlen(s);
    for(i=0;i<lenth;i++)
    {
        if(s[i]=='('||s[i]==')')
        {
            return 1;
        }
    }
    return 0;
}

Node *maketreenode(char *num)
{
    Node *head=(Node *)calloc(1,sizeof(Node));
    int i,lenth=strlenth(num);
    assert(head != NULL);
    for(i=0;i<lenth;i++)
    {
        head->c[i]=num[i];
    }
    return head;
}
