#include "fmvm.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXSIZE 46
#define BEGINARRAYSIZE 2
#define ALPHABET 37
#define LOADFACTOR 0.6
#define LENTH 3


int getnextprime(int n);
int countpow(char *word,int i,int m);
int hashcount(mvm *hashmap,char *word,int *prime,int i);
unsigned long countmul(char *word,int *prime);
int *createprime(int *prime);
float resizeVaild(mvm *hashhead);
mvm *resize(mvm *hashmap,int *prime);
int uppertolower(char c);

mvm* mvm_init(void)
{
    mvm *head=(mvm *)calloc(1, sizeof(mvm));
    head->totalblocks=getnextprime(BEGINARRAYSIZE);
    head->head=(mvmcell *)calloc(1,head->totalblocks* sizeof(mvmcell));
    return head;
}

int mvm_size(mvm* m)
{
    if(m==NULL)
    {
        return 0;
    }
    return m->numkeys;
}

void mvm_insert(mvm* m, char* key, char* data)
{
    int *prime=(int *)calloc(1,ALPHABET* sizeof(int));
    int i=0,hash;
    if (m == NULL || key == NULL || data == NULL) {
        return;
    }
    prime=createprime(prime);

    if(resizeVaild(m)>LOADFACTOR)
    {
        m=resize(m,prime);
    }
    do{
        hash=hashcount(m,key,prime,i++);
        if(i+m->numkeys>=m->totalblocks)
        {
            m=resize(m,prime);
            i=0;
        }
    }while (m->head[hash].data!=NULL);

    m->head[hash].key=(char *)calloc(1, (strlen(key)+1)* sizeof(char));
    m->head[hash].data=(char *)calloc(1, (strlen(data)+1)* sizeof(char));
    memcpy(m->head[hash].key,key,strlen(key));
    memcpy(m->head[hash].data,data,strlen(data));
    m->numkeys++;
}

char* mvm_search(mvm* m, char* key)
{
    int i=0;
    int hash;
    int *prime=(int *)calloc(1,ALPHABET* sizeof(int));
    prime=createprime(prime);
    do{
        hash=hashcount(m,key,prime,i++);
        if(m->head[hash].key==NULL||i>m->totalblocks)
        {
            return NULL;
        }
    }while (strcmp(m->head[hash].key,key)!=0);

    return m->head[hash].data;
}

char* mvm_print(mvm* m)
{
    int i;
    char *str=(char *)calloc(1,1);
    char *temp=(char *)calloc(1,(LENTH*MAXSIZE)* sizeof(char));
    for(i=0;i<m->totalblocks;i++)
    {
        if(m->head[i].data!=NULL)
        {
            sprintf(temp,"[%s](%s) ",m->head[i].key,m->head[i].data);
            str=(char *)realloc(str,(strlen(str)+strlen(temp))* sizeof(char));
            strcat(str,temp);
        }
    }
    return str;
}

void mvm_delete(mvm* m, char* key)
{
    int flag=1;
    int i=0;
    int hash;
    int *prime=(int *)calloc(1,ALPHABET* sizeof(int));
    if (m == NULL || key == NULL || key[0] == '\0')
    {
        return;
    }
    prime=createprime(prime);
    do{
        hash=hashcount(m,key,prime,i++);
        if(i>m->totalblocks)
        {
            return ;
        }
        if(m->head[hash].key!=NULL)
        {
            flag=strcmp(m->head[hash].key,key);
        }
    }while (m->head[hash].key==NULL && flag);

    m->head[hash].key=NULL;
    m->head[hash].data=NULL;
    m->numkeys--;
    resize(m,prime);
}

char** mvm_multisearch(mvm* m, char* key, int* n)
{
    int *prime=(int *)calloc(1,ALPHABET* sizeof(int));
    char *str=mvm_search(m,key);
    char **res=(char **)calloc(1, sizeof(char*));
    int i=0,hash;
    prime=createprime(prime);
    *res=(char *)calloc(1, strlen(str)*sizeof(char));
    if(str==NULL)
    {
        return NULL;
    }

    memcpy(*res,str,strlen(str));
    (*n)++;

    do{
        hash=hashcount(m,key,prime,i++);
    }while (strcmp(m->head[hash].key,key)!=0);

    while (m->head[hash].key!=NULL)
    {
        hash=hashcount(m,key,prime,i++);
        if(m->head[hash].key==NULL)
        {
            return res;
        }
        if(!strcmp(m->head[hash].key,key))
        {
            res=(char**)realloc(res,(++*n)*sizeof(char*));
            *(res+*n-1)=(char*)calloc(1,strlen(m->head[hash].data)* sizeof(char));
            memcpy(*(res+*n-1),m->head[hash].data,strlen(m->head[hash].data));
        }
    }
    return res;
}

void mvm_free(mvm** p)
{
    mvm **a;
    if (p == NULL) {
        return;
    }
    a=p;
    free((*a)->head->key);
    free((*a)->head->data);
    free((*a)->head);
    *p=NULL;
}

int getnextprime(int n)
{
    int temp=n+1,sqt,flag=0;
    while (1)
    {
        for(sqt=2;((sqt<temp)&&(flag==0));sqt++)
        {
            if(temp%sqt==0)
            {
                flag=1;
            }
        }
        if((sqt==temp)&&(flag==0))
        {
            return temp;
        } else
        {
            temp++;
            flag=0;
        }
    }
}

unsigned long countmul(char *word,int *prime)
{
    int i;
    unsigned long mul=1;
    for(i=0;i<(int)strlen(word);i++)
    {
        mul *= prime[uppertolower(word[i])];
    }
    return mul;
}

int hashcount(mvm *hashmap,char *word,int *prime,int i)
{
    unsigned long hash1=countmul(word,prime);
    unsigned long hash2=countpow(word,i,hashmap->totalblocks);
    unsigned long res=(hash1+hash2)%hashmap->totalblocks;
    return (int)res;
}

int countpow(char *word,int i,int m)
{
    int j,k;
    unsigned long temp;
    unsigned long res=0;
    for (j = 0; j<(int)strlen(word); j++)
    {
        temp=1;
        for(k=0;k<j;k++)
        {
            temp*=ALPHABET;
        }
        res+=temp*(uppertolower(word[j]));
    }
    res%=m;
    return i*res;
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

float resizeVaild(mvm *hashhead)
{
    return (float)hashhead->numkeys/(float)hashhead->totalblocks;
}

mvm *resize(mvm *hashmap,int *prime)
{
    mvm *hashmapnew=(mvm *)calloc(1, sizeof(mvm));
    int i,j;
    int hash;
    hashmapnew->totalblocks=getnextprime(2*hashmap->totalblocks);
    hashmapnew->head=(mvmcell *)calloc(1,hashmapnew->totalblocks* sizeof(mvmcell));

    for(i=0;i<hashmap->totalblocks;i++)
    {
        if(hashmap->head[i].key!=NULL)
        {
            j=0;
            do{
                hash=hashcount(hashmapnew,hashmap->head[i].key,prime,j++);
                if(j+hashmapnew->numkeys>=hashmapnew->totalblocks)
                {
                    hashmapnew=resize(hashmapnew,prime);
                    i=0;
                }
            }while (hashmapnew->head[hash].data!=NULL);
            hashmapnew->head[hash].key=(char *)calloc(1,(strlen(hashmap->head[i].key+1))* sizeof(char));
            hashmapnew->head[hash].data=(char *)calloc(1,(strlen(hashmap->head[i].data+1))* sizeof(char));
            memcpy(hashmapnew->head[hash].key,hashmap->head[i].key,strlen(hashmap->head[i].key));
            memcpy(hashmapnew->head[hash].data,hashmap->head[i].data,strlen(hashmap->head[i].data));
            hashmapnew->numkeys++;
        }
    }
    hashmap=(mvm *)realloc(hashmap, sizeof(mvm));
    hashmap->numkeys=0;
    hashmap->head=(mvmcell *)calloc(1,hashmapnew->totalblocks* sizeof(mvmcell));
    hashmap->totalblocks=hashmapnew->totalblocks;
    for(i=0;i<hashmap->totalblocks;i++)
    {
        if(hashmapnew->head[i].key!=NULL)
        {
            hashmap->head[i].key=(char *)calloc(1,(strlen(hashmapnew->head[i].key+1))* sizeof(char));
            hashmap->head[i].data=(char *)calloc(1,(strlen(hashmapnew->head[i].data+1))* sizeof(char));
            memcpy(hashmap->head[i].key,hashmapnew->head[i].key,strlen(hashmapnew->head[i].key));
            memcpy(hashmap->head[i].data,hashmapnew->head[i].data,strlen(hashmapnew->head[i].data));
            hashmap->numkeys++;
        }
    }
    return hashmap;
}

int uppertolower(char c)
{
    if(c>='a'&&c<='z')
    {
        return c-'a';
    } else if(c==' ')
    {
        return 'z'+1-'a';
    } else if(c>='0'&&c<='9')
    {
        return 'z'+2-'a'+c-'0';
    }else if(c>='A'&&c<='Z')
    {
        return c-'A';
    }
}

