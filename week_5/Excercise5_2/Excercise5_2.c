#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26
#define LONGESTWORD 45

typedef struct Node{
    unsigned long product;
    int cnt;
    char **anagrams;
    struct Node *next;
}Node;

int *createprime(int *prime);
Node *create();
void search(Node *head, unsigned long mumultiply,char *wordp);
void printelem(Node *head);

int main()
{
    int *prime=(int *)malloc(sizeof(int)*ALPHABET);
    FILE *fp;
    char word[LONGESTWORD];
    int i;
    unsigned long multiply;
    Node *head;

    char *wordp=word;
    prime=createprime(prime);
    head=create();
    fp=fopen("D:\\Coding Practise\\Clion_practise\\eng_370k_shuffle.txt","r");
    do{
        multiply=1;
        for(i=0;i<LONGESTWORD;i++)
        {
            word[i]=EOF;
        }
        fscanf(fp,"%s",word);
        for(i=0;word[i]!=EOF;i++)
        {
            multiply*=prime[word[i]-'a'];
        }
        search(head,multiply,wordp);
    }while(word[0]!=EOF);
    printelem(head);
    return 0;
}

Node *create()
{
    Node *head;
    head=(Node *)malloc(sizeof(Node));
    head->product=1;
    head->cnt=0;
    head->anagrams=(char **)malloc(sizeof(char*));
    *(head->anagrams)=(char *)malloc(sizeof(char));
    head->next=NULL;
    return head;
}

int *createprime(int *prime)
{
    int temp,cnt=0,flag=0,sqt;
    for (temp=2;cnt<ALPHABET;temp++)
    {
        for(sqt=2;((sqt<temp)&&(flag==0));sqt++)
        {
            if(temp%sqt==0) flag=1;
        }
        if((sqt>=temp)&&(flag==0))
        {
            *(prime+cnt)=temp;
            cnt++;
        }
        flag =0;
    }
    return prime;
}

void search(Node *head, unsigned long multiply,char *wordp)
{
    Node *p,*next;
    int flag=0,i;
    for(p=head;p->next!=NULL;p=p->next)
    {
        if(p->product==multiply)
        {
            p->cnt++;
            p->anagrams=(char **)realloc(p->anagrams,p->cnt* sizeof(char *));
            *(p->anagrams)=(char *)realloc(*(p->anagrams), strlen(wordp)+strlen(*(p->anagrams)));
            *(p->anagrams+p->cnt-1)=wordp;
            flag=1;
        }
    }
    if((p->next==NULL)&&(flag==0))
    {
        next=create();
        p->next=next;
        p=p->next;
        p->cnt++;
        p->anagrams=(char **)realloc(p->anagrams,p->cnt* sizeof(char *));
        *(p->anagrams)=(char *)realloc(*(p->anagrams), strlen(wordp)+strlen(*(p->anagrams)));
        *(p->anagrams+p->cnt-1)=wordp;
    }
}

void printelem(Node *head)
{
    Node *p;
    int i,len;
    for(p=head;p->next!=NULL;p=p->next)
    {
        printf("%d ",p->cnt);
        for(i=0;i<p->cnt;i++)
        {
            for(len=0;len<strlen(*(p->anagrams+i));len++)
            {
                printf("%c",*(*(p->anagrams+i)+len));
            }
            printf(" ");
        }
    }
    printf("\n");
}
