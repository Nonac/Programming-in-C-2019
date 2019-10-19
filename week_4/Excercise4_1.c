#include<stdio.h>
#include<stdlib.h>
#define LENGTH 40
#define EMPTY 0
#define HEAD 1
#define TAIL 2
#define COPPER 3
#define GENERATION 1000

int **create(int **array);
int **readin(int **array,char *argv);
int **nextarray(int **array,int **next);
int **change(int **array,int **next);
int nextelem(int **array,int arrayx,int arrayy);
int findhead(int **array,int arrayx,int arrayy);
int elemtoint(char elem);
void printout(int **next,FILE *ofp);
char inttoelem(int elem);

int main(int argc,char **argv)
{
    int **array,**next;
    int i;
    FILE *ofp;
    if( argc==2 )
    {
        ofp=fopen("wireworld_out.txt","r");
        array=create(array);
        next=create(next);

        array=readin(array,argv[1]);
        for (i = 0; i < GENERATION; ++i) {
            next=nextarray(array,next);
            printout(next,ofp);
            array=change(array,next);
        }
        fclose(ofp);
    }
    else
    {
        printf("ERROR: Incorrect usage.\n");
    }
    return 0;
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

int **readin(int **array,char *argv)
{
    FILE *fp;
    int arrayx,arrayy;
    char elem;
    fp=fopen(argv,"r");
    for(arrayx=0;arrayx<LENGTH;arrayx++)
    {
        for(arrayy=0;arrayy<LENGTH;arrayy++) {
            fscanf(fp,"%c",&elem);
            *(*(array+arrayx)+arrayy)=elemtoint(elem);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    return array;
}

int elemtoint(char elem)
{
    switch (elem){
        case ' ':
            return EMPTY;
        case 'H':
            return HEAD;
        case 't':
            return TAIL;
        case 'c':
            return COPPER;
        default:
            return -1;
    }
}

void printout(int **next,FILE *ofp)
{
    int nextx,nexty;
    char elem;
    for(nextx=0;nextx<LENGTH;nextx)
    {
        for(nexty=0;nexty<LENGTH;nexty++) {
            elem=inttoelem(*(*(next+nextx)+nexty));
            fprintf(ofp,"%c",elem);
        }
        fprintf(ofp,"\n");
    }
}

char inttoelem(int elem)
{
    switch (elem){
        case EMPTY:
            return ' ';
        case HEAD:
            return 'H';
        case TAIL:
            return 't';
        case COPPER:
            return 'c';
        default:
            return -1;
    }
}

int **nextarray(int **array,int **next)
{
    int arrayx,arrayy;
    for(arrayx=0;arrayx<LENGTH;arrayx++)
    {
        for(arrayy=0;arrayy<LENGTH;arrayy++)
        {
            *(*(next+arrayx)+arrayy)=nextelem(array,arrayx,arrayy);
        }
    }
    return next;
}

int **change(int **array,int **next)
{
    int arrayx,arrayy;
    for(arrayx=0;arrayx<LENGTH;arrayx++)
    {
        for(arrayy=0;arrayy<LENGTH;arrayy++)
        {
            *(*(array+arrayx)+arrayy)=*(*(next+arrayx)+arrayy);
        }
    }
    return array;
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