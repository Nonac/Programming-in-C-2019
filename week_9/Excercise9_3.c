#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define POSITIVE 9
#define NEGATIVE 8
#define MAXDEPTH 20
typedef struct node{
    char c;
    int cnt;
    int code[MAXDEPTH];
    int depth;
    struct node *left;
    struct node *right;
    struct node *next;
}Node;

Node *createlist();
Node *MakeNode(char c);
Node *readin(char *s);
Node *delzero(Node *listhead);
Node *Huffman(Node *listhead);
Node *makeTreeNode(int cnt,Node *a,Node *b);
int mintest(Node *a,Node *b);
Node *insert(Node *temp,Node *listhead);
Node *delnode(Node *listhead,Node *p);
void PrintTree(Node *head);
int depthcount(Node *treehead, int len);
void codecount(Node *head,int len);

int maxDepth(Node* root);

int main(int argc,char **argv)
{
    char *s;
    Node *listhead;
    Node *treehead;
    if(argc!=2)
    {
        printf("Error argc.");
    }
    s=argv[1];
    listhead=readin(s);
    listhead=delzero(listhead);
    treehead=Huffman(listhead);
    depthcount(treehead,0);
    codecount(treehead,0);
    PrintTree(treehead);
    return 0;
}

int depthcount(Node *treehead, int len)
{
    if(treehead==NULL)
    {
        return 0;
    }
    if(treehead->left==NULL&&treehead->right==NULL)
    {
        treehead->depth=len;
    } else
    {
        depthcount(treehead->left,len+1);
        depthcount(treehead->right,len+1);
    }
    return 0;
}

void codecount(Node *head,int len)
{
    static int a[MAXDEPTH];
    int i;
    if(head!=NULL)
    {
        if(head->right==NULL&&head->left==NULL)
        {
            for(i=0;i<MAXDEPTH;i++)
            {
                head->code[i]=a[i];
            }
        } else
        {
            a[len]=POSITIVE;
            codecount(head->left,len+1);
            a[len]=NEGATIVE;
            codecount(head->right,len+1);
	    a[len]=0;
        }
    }

}

void PrintTree(Node *head)
{
    int i;
    if(head->c!='\0')
    {
        printf("\'%c\' : ",head->c);
        for(i=MAXDEPTH;i>head->depth-1;i--)
        {
            printf(" ");
        }
        for(i=head->depth-1;i>=0;i--)
        {
            if(head->code[i]==POSITIVE)
            {
                printf("1");
            }
            if(head->code[i]==NEGATIVE)
            {
                printf("0");
            }
        }
        printf("(%d * %d)\n",head->depth,head->cnt);
    }
    if(head->left!=NULL)
    {
        PrintTree(head->left);
    }
    if(head->right!=NULL)
    {
        PrintTree(head->right);
    }
}

Node *Huffman(Node *listhead) {
    Node *min1;
    Node *min2;
    Node *swaptemp;
    Node *p;
    Node *temp;
    while (listhead->next != NULL)
    {
        min1 = listhead;
        min2 = listhead->next;
        p = listhead;
        if (mintest(min1, min2)) {
            swaptemp = min1;
            min1 = min2;
            min2 = swaptemp;
        }
        while (p != NULL) {
            if (p->cnt < min1->cnt) {
                min2 = min1;
                min1 = p;
            } else if (p->cnt < min2->cnt && p!=min1) {
                min2 = p;
            }
            p = p->next;
        }
        temp = makeTreeNode(min1->cnt + min2->cnt, min1, min2);
        listhead = insert(temp, listhead);
        listhead = delnode(listhead, min1);
        listhead = delnode(listhead, min2);
        temp->right->next = NULL;
        temp->left->next = NULL;
    }
    return listhead;
}

Node *delnode(Node *listhead,Node *p)
{
    Node *cur=listhead;
    if(cur==p)
    {
        return listhead->next;
    }
    while (cur->next!=p)
    {
        cur=cur->next;
    }
    cur->next=cur->next->next;
    return listhead;
}

Node *insert(Node *temp,Node *listhead)
{
    temp->next=listhead;
    return temp;
}

int mintest(Node *a,Node *b)
{
    if(a->cnt>b->cnt)
    {
        return 1;
    }
    return 0;
}

Node *delzero(Node *listhead)
{
    Node *temp;
    Node *cur;
    while(listhead->cnt==0)
    {
        listhead=listhead->next;
    }
    cur=listhead;
    temp=listhead->next;
    while(temp!=NULL)
    {
        if(temp->cnt==0)
        {
            cur->next=temp->next;
            temp=temp->next;
        } else
        {
            temp=temp->next;
            cur=cur->next;
        }
    }
    return listhead;
}

Node *readin(char *s)
{
    FILE *fp;
    Node *head=createlist();
    Node *p=head;
    char letter;
    int flag=1;
    if((fp=fopen(s, "r"))==NULL)
    {
        printf("Cannot open the file!\n");
        exit(0);
    }
    while (!feof(fp))
    {
        fscanf(fp, "%c", &letter);
        while(p!=NULL&&flag)
        {
            if(p->c==letter)
            {
                p->cnt++;
                flag=0;
            }
            p=p->next;
        }
        flag=1;
        p=head;
    }
    return head;
}

Node *createlist()
{
    Node *head=(Node *)calloc(1, sizeof(Node));
    Node *temp;
    Node *p=head;
    char c;
    for(c=' ';c<='~';c++)
    {
        temp=MakeNode(c);
        p->next=temp;
        p=p->next;
    }
    return head->next;
}

Node *MakeNode(char c)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    assert(node != NULL);
    node->c = c;
    node->cnt=0;
    return node;
}

Node *makeTreeNode(int cnt,Node *a,Node *b)
{
    Node *node = (Node *)calloc(1, sizeof(Node));
    assert(node != NULL);
    node->cnt=cnt;
    node->left=a;
    node->right=b;
    return node;
}
