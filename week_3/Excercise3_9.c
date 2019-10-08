#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _tolower(c) ((c)+'a'-'A')
#define _toupper(c) ((c)+'A'-'a')

void Soundex(char *sp,char *resp,int len);
void Search(char *sp,char *target,int position,char mark);


int main()
{
    char *resp;
    char *sp=(char *)malloc(sizeof(char));
    char str;
    int i,len=0;
    printf("Please enter the name:\n");

    while((str=getchar())!='\n' )
    {
        sp[len]=((str<='z')&&(str>='a'))?str:_tolower(str);
        sp=(char *)realloc(sp,(++len+1)*sizeof(char));
    }
    resp=(char *)malloc(len* sizeof(char));
    Soundex(sp,resp,len);
    resp[0]=_toupper(resp[0]);
    resp[4]='\0';
    printf("%s",resp);
}

void Soundex(char *sp,char *resp,int len)
{
    int i,j,k,splen= len;
    char first;
    char _LABIAL[]={'b','f','v','p','\0'};
    char _GUTTERALS_SIBILANTS[]={'c','g','j','k','q','s','x','z','\0'};
    char _DENTAL[]={'d','t','\0'};
    char _LONG_LIQUID[]={'l','\0'};
    char _NASAL[]={'m','n','\0'};
    char _SHORT_LIQUID[]={'r','\0'};
    char _SKIPPED[]={'a','e','h','i','o','u','w','y','\0'};

    first=sp[0];

    for(i=0;i<splen;i++)
    {
        Search(sp,_LABIAL,i,'1');
        Search(sp,_GUTTERALS_SIBILANTS,i,'2');
        Search(sp,_DENTAL,i,'3');
        Search(sp,_LONG_LIQUID,i,'4');
        Search(sp,_NASAL,i,'5');
        Search(sp,_SHORT_LIQUID,i,'6');
        Search(sp,_SKIPPED,i,'7');
    }

    resp[0]=sp[0];
    /* remove repeat char */
    j=0;
    for(i=1;(i<splen);i++)
    {
        if((sp[i]!=resp[j]))
        {
            resp[++j]=sp[i];
        }
    }
    /* remove skipped char */
    for(i=1;i<splen;i++)
    {
        if(resp[i]=='7')
        {
            for(k=i;k<splen;k++)
            {
                resp[k]=resp[k+1];
            }
            splen--;
        }
    }
    /* fill in with zero */
    if(j<3)
    {
        for(;j<4;j++)
        {
            resp[j]='0';
        }
    }

    resp[0]=first;
}

void Search(char *sp,char *target,int position,char mark)
{
    int j;
    for(j=0;j<strlen(target);j++)
    {
        if (sp[position] == target[j]) sp[position]=mark;
    }
}
