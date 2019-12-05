#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZSIZE 46
#define ALPHABET 26

typedef struct hashmap
{
    char **word;
    unsigned long *anagram;
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
void print(FILE *fp,char *c);
void printout(Hashmap *hashmap,int *prime);

int main()
{
    int *prime=(int *)malloc(sizeof(int)*ALPHABET);
    char *s="/Users/nickyang/CLionProjects/Clion_practise/eng_370k_shuffle.txt";
    char *temp=(char *)calloc(1,MAZSIZE* sizeof(char));
    int begin=getnextprime(ALPHABET);
    Hashmap *hashmap=init(begin);
    prime = createprime(prime);
    hashmap=readin(hashmap,s,prime);

    printout(hashmap,prime);

    return 0;
}

void printout(Hashmap *hashmap,int *prime)
{
    FILE *fp=fopen("/Users/nickyang/CLionProjects/Clion_practise/result.txt","w");
    int i,j;
    int hashnext;
    unsigned long tempmul,temppow;
    for(i=0;i<hashmap->totalnum;i++)
    {
        if(hashmap->anagram[i]!=0)
        {
            print(fp,hashmap->word[i]);
            tempmul=hashmap->anagram[i];
            j=1;
            do{
                temppow=countpow(hashmap->word[i],j,hashmap->totalnum);
                hashnext=(int)((tempmul+temppow)%hashmap->totalnum);
                if(hashmap->anagram[i]==hashmap->anagram[hashnext])
                {
                    print(fp,hashmap->word[hashnext]);
                    hashmap->anagram[hashnext]=0;
                }
                j++;
            }while(hashmap->anagram[i]==hashmap->anagram[hashnext]);
            print(fp,"\n");
            hashmap->anagram[i]=0;
        }


    }
}

void print(FILE *fp,char *c)
{
    int i;
    for(i=0;i<strlen(c);i++)
    {
        fprintf(fp,"%c",c[i]);
    }
    if(c[0]!='\n')
    {
        fprintf(fp," ");
    }
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
    hashmap->anagram=(unsigned long *)calloc(1,hashmap->totalnum*sizeof(unsigned long));
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
        hashmap->anagram[key]=countmul(word,prime);
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
            hashmapnew->anagram[hash]=hashmap->anagram[i];
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
    int j;
    unsigned long res=0;
    for (j = 0; word[j] >= 'a' && word[j] <= 'z'; j++)
    {
        res+=lettervalue(word[j]);
    }
    res%=m;
    return i*res;
}

int lettervalue(char c)
{
    return c-'a'+1;
}