#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(char *a,char *b);
int countdiff(char *a,char *b);
char **wordladders(FILE *fp,char *start,char *end,char **res,int diff);

int main()
{
    FILE *fp=fopen("D:\\Coding Practise\\Clion_practise\\34words.txt","r");
    char *start="wild",*end="tame";
    int i,diff=countdiff(start,end);
    char **res=(char **)malloc(sizeof(char *)*diff);
    for(i=0;i<diff;i++)
    {
        *(res+i)=(char *)malloc(sizeof(char)*strlen(start));
    }

    res=wordladders(fp,start,end,res,diff);
    return 0;
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

char **wordladders(FILE *fp,char *start,char *end,char **res,int diff)
{
    char *temp=(char *)malloc(sizeof(char)*strlen(start));
    if(compare(start,end))
    {
        *(res)=start;
        *(res+1)=end;
        for(int i=0;i<5;i++)
        {
            for (int j = 0; j <4 ; ++j) {
                printf("%c",*(*(res+j)+i));
            }
            printf("\n");
        }
        return res;
    }
    do
    {
        fscanf(fp, "%s", temp);
        if(compare(start,temp))
        {
            *(res+diff-1)=temp;
            res=wordladders(fp,temp,end,res,diff-1);
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
    return 1;
}
