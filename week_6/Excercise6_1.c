#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENTH 46

char **readinline(FILE *fp, char **array,int cnt);
char **insert(char **array,char *temp,int cnt);
int compare(char *a, char *b);
void change(char *a, char *b);
int tomin(int x, int y);
void printarray(char **array, int cnt);
int countwords(FILE *fp,int cnt);
int isletter(char c);

int main()
{
    char **array=(char **)malloc(sizeof(char *));
    int cnt=0;
    FILE *fp=fopen("/home/ff19085/CLionProjects/clion/34words.txt","r");
    array=readinline(fp,array,cnt);
    cnt=countwords(fp,cnt);
    printarray(array,cnt);
}

char **readinline(FILE *fp, char **array,int cnt)
{
    char *temp=(char *)malloc(sizeof(char)*MAXLENTH);
    while(!feof(fp))
    {
        fscanf(fp,"%s",temp);
        cnt++;
        array=insert(array,temp,cnt);

    }
    return array;
}

char **insert(char **array,char *temp,int cnt)
{
    int i,lenth=strlen(temp);
    array=(char **)realloc(array, sizeof(char *)*cnt);
    *(array+cnt-1)=(char *)malloc(sizeof(char)*lenth);
    for(i=0;i<lenth;i++)
    {
        *(*(array+cnt-1)+i)=*(temp+i);
    }
    for(i=cnt-1;i>0;i--)
    {
        if(compare(*(array+i),*(array+i-1)))
        {
            change(*(array+i),*(array+i-1));
        }
    }
    return array;
}

int compare(char *a, char *b)
{
    int lentha=strlen(a);
    int lenthb=strlen(b);
    int min=tomin(lentha,lenthb);
    int i;
    for (i = 0;  i<min ; i++)
    {
        if((*(a+i)-*(b+i))<0)
        {
            return 1;
        }else if ((*(a+i)-*(b+i))>0)
        {
            return 0;
        }
    }
    return (lenthb>lentha)?1:0;

}

int tomin(int x, int y)
{
    return (x>y)?y:x;
}

void change(char *a, char *b)
{
    int lentha=strlen(a);
    int lenthb=strlen(b);
    int i;
    char *tempa=(char *)malloc(sizeof(char)*lentha);
    char *tempb=(char *)malloc(sizeof(char)*lenthb);
    for(i=0;i<lentha;i++)
    {
        *(tempa+i)=*(a+i);
    }
    for(i=0;i<lenthb;i++)
    {
        *(tempb+i)=*(b+i);
    }
    a=(char *)realloc(a, sizeof(char)*lenthb);
    b=(char *)realloc(b, sizeof(char)*lentha);
    for(i=0;i<lenthb;i++)
    {
        *(a+i)=*(tempb+i);
    }
    for(i=0;i<lentha;i++)
    {
        *(b+i)=*(tempa+i);
    }
}

void printarray(char **array, int cnt)
{
    int i,j,lenth;
    for(i=0;i<cnt;i++)
    {
        lenth=strlen(*(array+i));
        for (j=0;  j<lenth; j++) {
            if (isletter(*(*(array + i) + j)))
            {
                printf("%c", *(*(array + i) + j));
            }
        }
        printf("\n");
    }
}

int countwords(FILE *fp,int cnt)
{
    char *temp=(char *)malloc(sizeof(char)*MAXLENTH);
    fseek(fp,0,SEEK_SET);
    while(!feof(fp))
    {
        fscanf(fp,"%s",temp);
        cnt++;
    }
    return cnt;
}

int isletter(char c)
{
    if((c-'a'>=0)&&('z'-c<=0))
    {
        return 1;
    }
    if((c-'A'>=0)&&('Z'-c<=0))
    {
        return 1;
    }
    return 0;
}
