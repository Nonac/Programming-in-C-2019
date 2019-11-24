/*00001(00002(00003(*)(00004(*)(00005(*)(*))))(*))(00006(00007(*)(*))(*))*/

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define MAXDEPTH 20
#define LEFT 9
#define RIGHT 8

typedef struct node
{
    char c[5];
    int code[MAXDEPTH];
    int width;
    int height;
    int widthplus;
    int rightfatherplus;
    struct node *left;
    struct node *right;
}Node;

Node *readin(char *s);
int findflag(char *s);
Node *maketreenode(char *num);
void divleaf(char *lefts,char *rights,char *s);
void copy(char *lefts,char *s,int begin, int end);
int strlenth(char *s);
void heightcount(Node *treehead);
void widthcount(Node *treehead);
void printtree(Node *treehead);
void widthcorrect(Node *treehead);
int maxleft(Node *head,int len);
void codecount(Node *head,int len);
void rightfathercorrect(Node *head,int num);
//void leftfathercorrect(Node *head,int num);

int main()
{
    char *s="00001(00002(00003(*)(00004(*)(00005(*)(*))))(*))(00006(00007(00011)(*))(00008(00009)(00010))";
    Node *treehead=readin(s);
    codecount(treehead,0);
    heightcount(treehead);
    widthcount(treehead);
    widthcorrect(treehead);
    //先进行左节点偏移计算，再计算右节点
    rightfathercorrect(treehead,treehead->widthplus);
   // leftfathercorrect(treehead,treehead->rightfatherplus);
    printtree(treehead);
    return 0;
}

/*void leftfathercorrect(Node *head,int num)
{
    if(head!=NULL)
    {
        if(head->left!=NULL)
        {
            head->left->rightfatherplus += num;
            leftfathercorrect(head->left,num);
        }
        if(head->right!=NULL)
        {
            rightfathercorrect(head->right,head->rightfatherplus);
        }
    }
}*/

void rightfathercorrect(Node *head,int num)
{
    if(head!=NULL)
    {
        if(head->right!=NULL)
        {
            head->right->rightfatherplus = num;
            rightfathercorrect(head->right,head->right->rightfatherplus);
        }
        if(head->left!=NULL)
        {
            rightfathercorrect(head->left,head->rightfatherplus);
        }
    }
}

void widthcorrect(Node *treehead)
{
    if(treehead!=NULL)
    {
        treehead->widthplus = treehead->widthplus+maxleft(treehead->left,treehead->width)\
            -treehead->width;
        widthcorrect(treehead->left);
        widthcorrect(treehead->right);
    }
}

int maxleft(Node *head,int max)
{

    int temp=0;
    if(head==NULL)
    {
        return max;
    }

    if(head->width>max)
    {
        max=head->width;
    }
    temp=maxleft(head->left,max);
    if(temp>max)
    {
        max=temp;
    }
    temp=maxleft(head->right,max);
    if(temp>max)
    {
        max=temp;
    }
    if(head->right==NULL && head->left==NULL)
    {
        return max;
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

void widthcount(Node *treehead)
{
    int w=0,i;
    if(treehead!=NULL)
    {
        for(i=0;i<MAXDEPTH;i++)
        {
            if(treehead->code[i]==RIGHT)
            {
                w++;
            }
        }
        treehead->width=w;
        widthcount(treehead->left);
        widthcount(treehead->right);
    }
}


void heightcount(Node *treehead)
{
    int h=0,i;
    if(treehead!=NULL)
    {
        for(i=0;i<MAXDEPTH;i++)
        {
            if(treehead->code[i]==LEFT)
            {
                h++;
            }
        }
        treehead->height=h;
        heightcount(treehead->left);
        heightcount(treehead->right);
    }
}

void printtree(Node *treehead)
{

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
