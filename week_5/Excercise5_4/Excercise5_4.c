#include <stdlib.h>
#include <stdio.h>

int  calcPattens(int last, int lenth,int *used);
int isValid(int i,int last,int *used);

int main()
{
    int lenth,i,head;
    int *used=(int *)malloc(sizeof(int)*9);
    printf("How many lenth do you need?\n");
    scanf("%d",&lenth);
    printf("Which number do you want to begin with?\n");
    scanf("%d",&head);
    head--;
    lenth--;
    for (i = 0; i < 9; ++i) {
        used[i]=0;
    }
    used[head]=1;
    printf("There are %d patterns.\n",calcPattens(head,lenth,used));
}

int calcPattens(int last, int lenth, int *used)
{
    int sum=0,i;
    if(lenth == 0)
    {
        return 1;
    }
    for(i=0;i<9;i++)
    {
        if(isValid(i,last,used))
        {
            used[i]=1;
            sum+=calcPattens(i,lenth-1,used);
            used[i]=0;
        }
    }
    return sum;
}

int isValid(int i,int last,int *used)
{
    if(used[i])
    {
        return 0;
    }
    if(((i-last==1)&&((last!=2)&&(last!=5)))||((last-i==1)&&((i!=2)&&(i!=5))))
    {
        return 1;
    }
    if((i-last==3)||(last-i==3))
    {
        return 1;
    }
    return 0;
}