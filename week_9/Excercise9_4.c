#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 5
#define LEFT 9
#define RIGHT 8
#define MAXDEPTH 20

typedef struct node
{
    char c[SIZE];
    int code[MAXDEPTH];
    struct node *left;
    struct node *right;
}Node;

Node *readin(char *s);
int findflag(char *s);
Node *maketreenode(char *num);
void divleaf(char *lefts,char *rights,char *s);
void copy(char *lefts,char *s,int begin, int end);
int strlenth(char *s);
void codecount(Node *head,int len);
int depthcount(Node *head);
int widthcount(Node *head);
void printtree(Node *head,int depth,int width);
char **createmap(int depth,int width);
void writein(Node *head,char **map,int len);

int main()
{
    char *s="00001(00002(00003(00004(00005(*)(00009))(00007(*)(00008)))(00006))(*))(00010(00011(00012)(*))(00013(*)(*)))";
    Node *treehead=readin(s);
    int depth,width;
    codecount(treehead,0);
    depth=depthcount(treehead);
    width=widthcount(treehead);
    printtree(treehead,depth,width);
    return 0;
}

char **createmap(int depth,int width)
{
    int i,j;
    char **map=(char **)malloc((depth*2+1)*sizeof(char *));
    for(i=0;i<depth*2+1;i++)
    {
        *(map+i)=(char *)malloc((width*(SIZE+1)-1)*sizeof(char));
    }
    for(i=0;i<depth*2+1;i++)
    {
        for(j=0;j<width*(SIZE+1)-1;j++)
        {
            *(*(map+i)+j)=' ';
        }
    }
    return map;
}

void printtree(Node *head,int depth,int width)
{
    char **map=createmap(depth,width);
    writein(head,map,0);


}

void writein(Node *head,char **map,int len)
{
    int i,j;
    if(len==0)
    {
        for(i=0;i<SIZE;i++)
        {
            *(*(map+len)+i)=head->c[i];
        }
    }
    if(head->left)
    {
        for(i=0;i<SIZE;i++)
        {
            *(*(map+2*len+1)+2)='|';
        }
    }
}

int widthcount(Node *head)
{
    static int width=1;
    int temp;
    if(head!=NULL)
    {
        if(head->right!=NULL)
        {
            width++;
        }
        temp=widthcount(head->left);
        width=(width<temp)?temp:width;
        temp=widthcount(head->right);
        width=(width<temp)?temp:width;
    }
    return width;
}

int depthcount(Node *head)
{
    static int max=0;
    int i,temp=0;
    if(head!=NULL)
    {
        if(head->left==NULL&&head->right==NULL)
        {
            for(i=0;i<MAXDEPTH;i++)
            {
                if(head->code[i]==LEFT)
                {
                    temp++;
                }
            }
            max=(max<temp)?temp:max;
        }
        max=depthcount(head->left);
        max=depthcount(head->right);
    }
    return max;
}

void codecount(Node *head,int len)
{
    static int a[MAXDEPTH];
    int i;
    if(head!=NULL)
    {
        for(i=0;i<MAXDEPTH;i++)
        {
            head->code[i]=a[i];
        }
        a[len]=LEFT;
        codecount(head->left,len+1);
        a[len]=RIGHT;
        codecount(head->right,len+1);
        a[len]=0;
    }
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
