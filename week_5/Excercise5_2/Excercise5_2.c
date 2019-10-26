#include <stdio.h>
#include <stdlib.h>
#define ALPHABET 26
#define LONGESTWORD 45

typedef struct Node{
    unsigned long product;
    char **anagrams;
    struct Node *next;
}Node;

int *createprime(int *prime);
Node *create();
void search(Node *p, unsigned long mumultiply,char *wordp);

int main()
{
    int *prime=(int *)malloc(sizeof(int)*ALPHABET);
    FILE *fp;
    char word[LONGESTWORD];
    int i;
    unsigned long multiply=1;
    Node *p;

    char *wordp=word;
    prime=createprime(prime);
    p=create();
    fp=fopen("eng_370k_shuffle.txt","r");
    do{
        for(i=0;i<LONGESTWORD;i++)
        {
            word[i]=EOF;
        }
        fscanf(fp,"%s",word);
        for(i=0;word[i]!=EOF;i++)
        {
            multiply*=prime[word[i]-'a'];
        }
        search(p,multiply,wordp);
    }while(word[0]!=EOF);
}

Node *create()
{
    Node *head;
    head=(Node *)malloc(sizeof(Node));
    head->product=1;
    head->anagrams=(char **)malloc(sizeof(char*));
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

void search(Node *p, unsigned long mumultiply,char *wordp)
{

}

