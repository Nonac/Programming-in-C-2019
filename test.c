#include <stdio.h>
#include <time.h>

int i=1;

void printi(char x,char y)
{
    printf("%d.%c-->%c\n",i,x,y);
    i++;
}

void move(int n,int i,char x,char y,char z)
{
    if (n == 1)
    {
        printi(x,z);
    } else
    {
        move(n-1,i,x,z,y);
        printi(x,z);
        move(n-1,i,y,x,z);
    }
}

int main()
{
    clock_t startTime,endTime;
    startTime = clock();
    int n;
    printf("请输入汉诺塔的层数：");
    scanf("%d",&n);
    printf("移动的步骤如下:\n");

    move(n,i,'X','Y','Z');

    endTime = clock();
    printf("Total time is:%lf",(double)(endTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}
