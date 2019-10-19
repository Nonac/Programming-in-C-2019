#include<stdio.h>
#include<stdlib.h>
#define LENGTH 40
#define EMPTY 0
#define HEAD 1
#define TAIL 2
#define COPPER 3

int **create(int **array);
int **readin(int **array);
int **nextarray(int **array,int **next);
int nextelem(int **array,int arrayx,int arrayy);
int findhead(int **array,int arrayx,int arrayy);

int main()
{
    int **array,**next;
    array=create(array);
    next=create(next);

    array=readin(array);
    next=nextarray(array,next);

}

int **create(int **array)
{
    int i;
    array=(int**)malloc(sizeof(int*)*LENGTH);
    for(i=0;i<LENGTH;i++)
    {
        *(array+i)=(int*)malloc(sizeof(int)*LENGTH);
    }
    return array;
}

int **readin(**array)
{
    FILE *fp;
    fp=fopen();

    fclose(fp);
    return array;
}

int **nextarray(int **array,int **next)
{
    int arrayx,arrayy,nextx,nexty;
    for(arrayx=0;arrayx<LENGTH;arrayx++)
    {
        for(arrayy=0;arrayy<LENGTH;arrayy++)
        {
            for(nextx=0;nextx<LENGTH;nextx)
            {
                for(nexty=0;nexty<LENGTH;nexty++)
                {
                    *(*(next+nextx)+nexty)=nextelem(array,arrayx,arrayy);
                }
            }
        }
    }
    return next;
}

int nextelem(int **array,int arrayx,int arrayy)
{
    switch (*(*(array+arrayx)+arrayy)) {
        case EMPTY:
            return EMPTY;
        case HEAD:
            return TAIL;
        case TAIL:
            return COPPER;
        case COPPER:
            if (findhead(array,arrayx,arrayy))
            {
                return HEAD;
            }else
            {
                return COPPER;
            }
        default:
            return -1;
    }
}

int findhead(int **array,int arrayx,int arrayy)
{
    int i,j,cnt=0;
    for(i=arrayx-1;i<arrayx+1;i++)
    {
        for (j =arrayy-1;j<arrayy+1; j++)
        {
            if (!(i<0 || j<0 || i>=LENGTH || j>=LENGTH || (i==arrayx && j==arrayy)))
            {
                if(*(*(array+i)+j)==HEAD) cnt++;
            }
        }
    }
    if((cnt==1)||(cnt==2)) return 1;
    else return 0;
}