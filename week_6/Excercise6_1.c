#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENTH 46

int readinline(FILE *fp, char **array,int cnt);
char **insert(char **array,char *temp,int cnt);
int compare(char *a, char *b);
void change(char *a, char *b);
int tomin(int x, int y);

int main()
{
    char **array;
    int cnt=0;
    FILE *fp=fopen("D:\\Coding Practise\\Clion_practise\\eng_370k_shuffle.txt","r");
    cnt=readinline(fp,array,cnt);
}

int readinline(FILE *fp, char **array,int cnt)
{
    char *temp=(char *)malloc(sizeof(char)*MAXLENTH);
    while(!feof(fp))
    {
        fscanf(fp,"%s",temp);
        cnt++;
        array=insert(array,temp,cnt);

    }
    return cnt;
}

char **insert(char **array,char *temp,int cnt)
{
    int i,lenth=strlen(temp);
    array=(char **)realloc(array, sizeof(char *)*cnt);
    *(*array+cnt-1)=(char *)malloc(sizeof(char)*lenth);
    for(i=0;i<lenth;i++)
    {
        *(*(array+i)+cnt-1)=*(temp+i);
    }
    for(i=cnt-1;i>0;i--)
    {
        if(compare(*(*array+i),*(*array+i-1)))
        {
            change(*(*array+i),*(*array+i-1));
        }
    }
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
    
}
