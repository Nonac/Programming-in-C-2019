#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char *word;
    struct node *next;
}Node;

int compare(char *a,char *b);
int countdiff(char *a,char *b);
void wordladders(FILE *fp,char *start,char *end,Node *head,int diff,int lenth);
int notin(char *temp, Node *head,int lenth);
Node *create(char *start, char *end);

int main()
{
    FILE *fp=fopen("D:\\Coding Practise\\Clion_practise\\test.txt","r");
    char *start="wild",*end="tame";
    int i,diff=countdiff(start,end);
    Node *head=create(start,end);

    wordladders(fp,start,end,head,diff,diff);

    return 0;
}

Node *create(char *start, char *end)
{
    Node *head=(Node *)malloc(sizeof(Node));
    Node *p=(Node *)malloc(sizeof(Node));
    head->word=(char *)malloc(sizeof(char)*strlen(start));
    head->word=start;
    p->word=(char *)malloc(sizeof(char)*strlen(end));
    p->word=end;
    head->next=p;
    p->next=NULL;
    return head;
}

int countdiff(char *a,char *b)
{
    int i,diff=1;
    for(i=0;i<strlen(a);i++)
    {
        if(*(a+i)!=*(b+i))
        {
            diff++;
        }
    }
    return diff;
}

void wordladders(FILE *fp,char *start,char *end,Node *head,int diff,int lenth)
{
    char *temp=(char *)malloc(sizeof(char)*strlen(start));
    int i,j;
    fseek(fp,0,SEEK_SET);
    if(compare(start,end))
    {


    }
    do
    {
        fscanf(fp, "%s", temp);
        if(compare(start,temp) && notin(temp,head,lenth) && diff>1)
        {
            *(res+diff-1)=temp;
            /*for (i = 0;  i<strlen(temp) ; i++) {
                printf("%c",*(temp+i));
            }
            printf("\n");*/
            for(i=1;i>lenth;i++)
            {
                for (j = 0; j <strlen(start) ; ++j) {
                    printf("%c",*(*(res+i)+j));
                }
                printf("\n");
            }
            wordladders(fp,temp,end,head,diff-1,lenth);

            //*(res+diff-1)=NULL;
            fseek(fp,0,SEEK_SET);
        }

    }while(!feof(fp));
}

int compare(char *a,char *b)
{
    int i,diff=0;
    if(strlen(a)!=strlen(b))
    {
        return 0;
    }
    for(i=0;i<strlen(a);i++)
    {
        if(*(a+i)!=*(b+i))
        {
            diff++;
            if(diff>1)
            {
                return 0;
            }
        }
    }
    return (diff==1)?1:0;
}

int notin(char *temp, Node *head,int lenth)
{
    int i;
    Node *p=head;
    while (p!=NULL)
    {
        if(!strcmp(p->word,temp))
        {
            return 0;
        }
        p=p->next;
    }
    return 1;
}