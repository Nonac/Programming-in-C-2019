#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define STRSIZE 5000
struct node{
    char c;
    struct node *left;
    struct node *right;
};
typedef struct node Node;
Node *MakeNode(char c);
void InsertRandom(Node *t, Node *n);
char *PrintTree(Node *t);
int maxDepth(Node* root);

int main(void)
{
    char c;
    Node *head = MakeNode('A');
    Node *n;
    srand(time(NULL));
    for(c = 'B'; c < 'G'; c++){
        n = MakeNode(c);
        InsertRandom(head, n);
    }
    printf("%s\n", PrintTree(head));
    printf("The max depth is %d\n",maxDepth(head));
    return 0;
}

Node *MakeNode(char c)
{
    Node *n = (Node *)calloc(1, sizeof(Node));
    assert(n != NULL);
    n->c = c;
    return n;
}
void InsertRandom(Node *t, Node *n)
{
    if((rand()%2) == 0){ /* Left */
        if(t->left == NULL){
            t->left = n;
        }
        else{
            InsertRandom(t->left, n);
        }
    }
    else{ /* Right */
        if(t->right == NULL){
            t->right = n;
        }
        else{
            InsertRandom(t->right, n);
        }
    }
}
char *PrintTree(Node *t)
{
    char *str;
    assert((str = calloc(STRSIZE, sizeof(char))) != NULL);
    if(t == NULL)
    {
        strcpy(str, "*");
        return str;
    }
    sprintf(str, "%c (%s) (%s)", t->c, PrintTree(t->left), PrintTree(t->right));
    return str;
}
int maxDepth(Node* root){
    int l=0,r=0;
    if(root==NULL) return 0;
    l=maxDepth(root->left)+1;
    r=maxDepth(root->right)+1;
    return l>r?l:r;
}