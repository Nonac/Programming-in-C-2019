#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 5
#define LEFT 9
#define RIGHT 8
#define MAXDEPTH 20
#define LENGTH 100
#define WIDTH 100

typedef struct node
{
    char c[SIZE];
    int code[MAXDEPTH];
    int depth;
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
int widthcount(Node *head);
void printtree(Node *head,char array[LENGTH][WIDTH],int i,int j);
void writein(Node *head,char **map,int len);
void find_depth(Node *tree_head);

int main()
{
    char *s="00001(00002(00003(00004(00005(*)(00009))(00007(*)(00008)))(00006))(*))(00010(00011(00012)(*))(00013(*)(*)))";
    Node *treehead=readin(s);
    int i,j;
    char map[LENGTH][WIDTH];
    codecount(treehead,0);
    find_depth(treehead);
    for(i=0;i<LENGTH;i++){
        for(j=0;j<WIDTH;j++){
            map[i][j] = ' ';
        }
    }
    printtree(treehead,map,0,0);
    for(i=0;i<LENGTH;i++){
        for(j=0;j<WIDTH;j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void find_depth(Node *tree_head)
{
    static depth = 1;
    if(tree_head == NULL){
        return;
    }
    tree_head->depth = depth;
    depth++;
    find_depth(tree_head->left);
    find_depth(tree_head->right);
    depth--;
}

void printtree(Node *head,char array[LENGTH][WIDTH],int i,int j)
{
    int k= 0;
    int m = 0;
    if(head ==NULL){
        return;
    }
    for(k=0;k<SIZE;k++){
        array[i][j+k] = head->c[k];
    }
    if(head->left != NULL){
        for(k=1;k<10/head->depth;k++){
            array[i+k][j] = '|';
        }
    }
    if(head->right != NULL){
        for(k=SIZE;k<SIZE+SIZE;k++){
            array[i][j+k] = '-';
        }
    }

    printtree(head->left,array,i+10/head->depth,j);
    printtree(head->right,array,i,j+10);
}

void writein(Node *head,char **map,int len)
{
    int i,j;
    if(head!=NULL)
    {
        for(i=0;i<SIZE;i++)
        {
            *(*(map+len*2)+i)=head->c[i];
        }
        if(head->left)
        {
            for(i=0;i<SIZE;i++)
            {
                *(*(map+2*len+1)+2)='|';
            }
        }
        writein(head->left,map,len+1);
        if(head->right)
        {
            for(i=0;i<SIZE;i++)
            {
                *(*(map+2*len)+SIZE)='-';
            }
            for(i=0;i<SIZE;i++)
            {
                *(*(map+len*2)+i)=head->c[i];
            }
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
