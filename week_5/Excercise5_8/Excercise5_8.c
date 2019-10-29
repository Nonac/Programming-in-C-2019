#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(char *a,char *b);
int countdiff(char *a,char *b);
char **wordladders(FILE *fp,char *start,char *end,char **res,int diff);
int notin(char *temp, char **res);

int main()
{
    FILE *fp=fopen("/home/ff19085/CLionProjects/clion/test.txt","r");
    char *start="wild",*end="tame";
    int i,j,flag,diff=countdiff(start,end);
    char **res=(char **)malloc(sizeof(char *)*diff);
    for(i=0;i<diff;i++)
    {
        *(res+i)=(char *)malloc(sizeof(char)*strlen(start));
    }
    *(res)=start;
    *(res+1)=end;
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
    int i,j;
    fseek(fp,0,SEEK_SET);
    if(compare(start,end))
    {

        for(i=0;i<5;i++)
        {
            for (j = 0; j <4 ; ++j) {
                printf("%c",*(*(res+i)+j));
            }
            printf("\n");
        }
        return res;
    }
    do
    {
        fscanf(fp, "%s", temp);
        if(compare(start,temp) && notin(temp,res))
        {
            *(res+diff-1)=temp;
            wordladders(fp,temp,end,res,diff-1);
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
    return (diff==0)?0:1;
}

int notin(char *temp, char **res)
{
    int i;
    for(i=0;i<strlen(res);i++)
    {
        if(!strcmp(*(res+i),temp))
        {
            return 0;
        }
    }
    return 1;
}
