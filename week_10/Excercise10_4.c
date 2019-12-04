#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZSIZE 46
#define ALPHABET 26

typedef struct hashmap
{
    char **word;
    int curnum;
    int totalnum;
}Hashmap;

Hashmap *init(int m);
Hashmap *readin(Hashmap *hashmap, char *s,int *prime);
int *createprime(int *prime);
unsigned long countmul(char *word,int *prime);
int hashcount(Hashmap *hashmap,char *word,int *prime,int i);
int lettervalue(char c);
int countpow(char *word,int i,int m);
void insert(char *target, char *word);
Hashmap *resize(Hashmap *hashmap,int *prime);
int getnextprime(int n);
void copy(char *a, char *b);
float resizeVaild(int cur,int total);
int search(Hashmap *hashmap,char *temp,int *prime);
int compare(char *a,char *b);

int main()
{
    int *prime=(int *)malloc(sizeof(int)*ALPHABET);
    char *s="/Users/nickyang/CLionProjects/Clion_practise/eng_370k_shuffle.txt";
    char *temp=(char *)calloc(1,MAZSIZE* sizeof(char));
    int begin=getnextprime(ALPHABET);
    Hashmap *hashmap=init(begin);
    prime = createprime(prime);
    hashmap=readin(hashmap,s,prime);

    printf("Please input the word:\n");
    scanf("%s",temp);

    if(search(hashmap,temp,prime))
    {
        printf("It is correct.\n");
    }else{
        printf("It is wrong.\n");
    }
    return 0;
}
int search(Hashmap *hashmap,char *temp,int *prime)
{
    int i,hash;
    for(i=0;i<hashmap->totalnum;i++)
    {
        hash=hashcount(hashmap,temp,prime,i);
        if(compare(hashmap->word[hash],temp))
        {
            return 1;
        }
    }
    return 0;
}

int compare(char *a,char *b)
{
    int i;
    if(strlen(a)!=strlen(b))
    {
        return 0;
    }
    for(i=0;i<strlen(a);i++)
    {
        if(a[i]!=b[i])
        {
            return 0;
        }
    }
    return 1;
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

Hashmap *init(int m)
{
    int i;
    Hashmap *hashmap=(Hashmap *)calloc(1, sizeof(Hashmap));
    hashmap->totalnum=m;
    hashmap->word=(char **)calloc(1, hashmap->totalnum*sizeof(char *));
    for(i=0;i<hashmap->totalnum;i++)
    {
        *(hashmap->word+i)=(char *)calloc(1,MAZSIZE* sizeof(char));
    }
    return hashmap;
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

Hashmap *readin(Hashmap *hashmap, char *s,int *prime)
{
    char *word=(char *)calloc(1,MAZSIZE* sizeof(char));
    int key;
    FILE *fp;
    fp=fopen(s,"r");
    int i;
    while(!feof(fp))
    {
        i=0;
        fscanf(fp,"%s",word);
        if(resizeVaild(hashmap->curnum,hashmap->totalnum)>0.6)
        {
            hashmap=resize(hashmap,prime);
        }
        do
        {
            key=hashcount(hashmap,word,prime,i++);
            if(i+hashmap->curnum>=hashmap->totalnum)
            {
                hashmap=resize(hashmap,prime);
                i=0;
            }
        }while(hashmap->word[key][0]!='\0');
        insert(hashmap->word[key],word);
        hashmap->curnum++;
    }
    return hashmap;
}

float resizeVaild(int cur,int total)
{
    return (float)cur/(float)total;
}


Hashmap *resize(Hashmap *hashmap,int *prime)
{
    int m=getnextprime(2*hashmap->totalnum);
    Hashmap *hashmapnew=init(m);
    int i,j;
    int hash;

    for(i=0;i<hashmap->totalnum;i++)
    {
        if(hashmap->word[i][0]!='\0')
        {
            j=0;
            do{
                hash=hashcount(hashmapnew,hashmap->word[i],prime,j++);
            }while (hashmapnew->word[hash][0]!='\0');
            copy(hashmapnew->word[hash],hashmap->word[i]);
            hashmapnew->curnum++;
        }
    }
    if(hashmapnew->curnum!=hashmap->curnum)
    {
        exit(EXIT_FAILURE);
    }
    return hashmapnew;
}

void copy(char *a, char *b)
{
    int i;
    for(i=0;i<strlen(b);i++)
    {
        a[i]=b[i];
    }
}


void insert(char *target, char *word)
{
    int j;
    for (j = 0; word[j] >= 'a' && word[j] <= 'z'; j++)
    {
        target[j]=word[j];
    }
}

unsigned long countmul(char *word,int *prime)
{
    int i;
    unsigned long mul=1;
    for(i=0;i<strlen(word);i++)
    {
        mul *= prime[word[i]-'a'];
    }
    return mul;
}

int hashcount(Hashmap *hashmap,char *word,int *prime,int i)
{
    unsigned long hash1=countmul(word,prime);
    unsigned long hash2=countpow(word,i,hashmap->totalnum);
    unsigned long res=(hash1+hash2)%hashmap->totalnum;
    return (int)res;
}

int countpow(char *word,int i,int m)
{
    int j,k;
    unsigned long temp;
    unsigned long res=0;
    for (j = 0; word[j] >= 'a' && word[j] <= 'z'; j++)
    {
        temp=1;
        for(k=0;k<j;k++)
        {
            temp*=ALPHABET;
        }
        res+=temp*lettervalue(word[j]);
    }
    res%=m;
    return i*res;
}

int lettervalue(char c)
{
    return c-'a';
}

