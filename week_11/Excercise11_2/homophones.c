/**********************************************************************************************
* Code by ff19085, Yinan Yang. 
*To create a generic version towards mvm and fmvm, I need use function in mvm.h as much as 
*I can.     
* There are steps in this program:
* 1.analysis the argv, find out if there is a '-n' and 'n'.
* 2.serach the dictionary file with target word fisrt to find out how many phones it owns.
* 3.passing the apposite parameter to the main function.
* 4.Search to whole dictionary to create mapfirst and mapsecond at the same time,which:
*    mapfirst:    key:word    value:phonemes(limit in n number)
*    mapsecond:   key:phonemes(limit in n number)    key:word
* 5.search mapfirst with target word, to find phonemes.
* 6.multisearch mapsecond with the phonemes, and print it out.
*
* This program could easyly change the mvm.h to fmvm.h.
* And it could print out each multisearch time and totally run time.
*
**********************************************************************************************/
#include "mvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#define MAXBUFF 1000
#define PRINTLINEWIDTH 50
#define DEC 10
#define DEFAULT 3

/*find out how many phonemes the target word have*/
int findphonemes(char *address,char *s);
/*read in from dictionary, and create mapfirst and mapsecond*/
void readin(mvm *mapfirst,mvm *mapsecond, char *address,int n);
/*count phonemes by space*/
int countspace(char *s);
/*find word in buff*/
char *findkey(char *buff);
/*find phonemes with limited numbers*/
char *finddata(char *buff,int n);
/*printout the multisearch result*/
void printout(mvm *mapsecond,char *key,char *data);
/*main function*/
void homophones(char *address,char *key,int n);
/*pass apposite parameter to main function*/
void parameterpassing(int i,int argc,char **argv,int n,char *address);
/*change -n number to int*/
int stoint(char *s);
void test(char *address);

int main(int argc,char **argv)
{
    clock_t startTime,endTime;
    char *address="cmudict.txt";
    int n=0;
    int i,flag=1;
    test(address);
    startTime = clock();
/*find -n position*/
    for(i=0;i<argc&&flag;i++)
    {
        if(!strcmp(argv[i],"-n"))
        {
            n=stoint(argv[i+1]);
            flag=0;
        }
    }
/*pass parameters*/
    parameterpassing(i,argc,argv,n,address);
    endTime = clock();
    printf("Total time is:%fms\n",(double)(endTime - startTime)*1000 / CLOCKS_PER_SEC);
    return 0;
}

void test(char *address)
{
    char *s;
    int i;
    assert(findphonemes(address,"STANO")==5);
    assert(findphonemes(address,"FURGERSON")==7);
    assert(countspace("STANO#S T AA1 N OW0")==5);
    assert(countspace("FURGERSON#F ER1 G ER0 S AH0 N")==7);

    s=findkey("STANO#S T AA1 N OW0");
    i=strcmp(s,"STANO");
    assert(i==0);
    free(s);
    s=findkey("FURGERSON#F ER1 G ER0 S AH0 N");
    i=strcmp(s,"FURGERSON");
    assert(i==0);
    free(s);
    s=finddata("STANO#S T AA1 N OW0",3);
    i=strcmp(s,"AA1 N OW0");
    assert(i==0);
    free(s);
    s=finddata("FURGERSON#F ER1 G ER0 S AH0 N",3);
    i=strcmp(s,"S AH0 N");
    assert(i==0);
    free(s);
    assert(stoint("5")==5);
    assert(stoint("15")==15);
}


/*change -n number to int*/
int stoint(char *s)
{
    int res=0,mul=1;
    int i,j,p=0;
    for(i=strlen(s);i>=0;i--)
    {
	if(s[i]>='0'&&s[i]<='9')
	{
	    for(j=0;j<p;j++)
	    {
	        mul*=DEC;
	    }
	    p++;
	    res+=mul*(s[i]-'0');
	}
	
    }
    return res;
}

void parameterpassing(int i,int argc,char **argv,int n,char *address)
{
    int j,nword;
    if(i==argc) 
    {
/*If there is not any -n in argv, n will be the min between 3 and the phones numbers.*/
        n = DEFAULT;
        for (j = 1; j < argc; j++) 
	{
            nword = findphonemes(address, argv[j]);
            if (nword >= n) 
	    {
                homophones(address, argv[j], n);
            } else 
            {
                homophones(address, argv[j], nword);
            }
        }
    } else
    {
/*If there is a -n, but target word has a less phones, return an ERROR undefined.*/
        for (j = 1; j < argc; j++) 
        {
            if ((j != i - 1) && (j != i)) 
            {
                nword = findphonemes(address, argv[j]);
                if (nword >= n) 
		{
                    homophones(address, argv[j], n);
                } else 
		{
                    ON_ERROR("Undefined result, please check the input word.");
                }
            }
        }
    }
}

/*main function*/
void homophones(char *address,char *key,int n)
{

    char *data;
    mvm *mapfirst=mvm_init();
    mvm *mapsecond=mvm_init();
    readin(mapfirst,mapsecond,address,n);
    data=(char *)calloc(1, strlen(mvm_search(mapfirst,key))* sizeof(char));
    data=mvm_search(mapfirst,key);
    printout(mapsecond,key,data);
    printf("\n");
/*free the two map*/
    mvm_free(&mapfirst);
    mvm_free(&mapsecond);
    free(data);
}

void printout(mvm *mapsecond,char *key,char *data)
{
    clock_t startTime,endTime;
    int n=0;
    char *str=(char *)calloc(1,1);
    char *temp=(char *)calloc(1,MAXBUFF* sizeof(char));
    char **dataarray;
    int i,j,linewidth=0;

/*Multisearch function, test the time.*/
    startTime = clock();
    dataarray=mvm_multisearch(mapsecond,data,&n);
    endTime = clock();
/*print the target word and its phones in a formal grammer*/
    sprintf(temp,"%s (%s): ",key,data);
    str=(char *)realloc(str,(strlen(str)+strlen(temp))* sizeof(char));
    strcat(str,temp);

/*print out beauty, if print is greater than line width, find a space and print a \n*/
    for(i=0;i<(int)strlen(str);i++)
    {
        printf("%c",str[i]);
        linewidth++;
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<(int)strlen(dataarray[i]);j++)
        {
            printf("%c",dataarray[i][j]);
            linewidth++;
        }
        printf(" ");
        if(linewidth>PRINTLINEWIDTH)
        {
            printf("\n");
            linewidth=0;
        }
    }

    printf("\n");
    printf("Total search time is:%fms",(double)(endTime - startTime)*1000 / CLOCKS_PER_SEC);
    printf("\n");
}
/*read in from dictionary and create two maps*/
void readin(mvm *mapfirst,mvm *mapsecond, char *address,int n)
{
    FILE *fp;
    char *buff=(char *)calloc(1,MAXBUFF* sizeof(char));
    char *key,*data;
    fp=fopen(address,"r");

    while (!feof(fp))
    {
        fgets(buff, MAXBUFF, fp);
        if(countspace(buff)>=n)
        {
            key=findkey(buff);
            data=finddata(buff,n);
            mvm_insert(mapfirst,key,data);
            mvm_insert(mapsecond,data,key);
        }
    }
}

/*find data from buff, count the space and '#'*/
char *finddata(char *buff,int n)
{
    int p,end=0,cnt=0,flag=1;
    char *data;
    for(p=(int)strlen(buff);p>0;p--)
    {
        if(((buff[p]<='Z'&&buff[p]>='A')||(buff[p]<='9'&&buff[p]>='0'))&&flag)
        {
            end=p;
            flag=0;
        }
        if(buff[p]==' '||buff[p]=='#')
        {
            cnt++;
        }
        if(cnt==n)
        {
            data=(char *)calloc(1,(end-p+1)* sizeof(char));
            memcpy(data,buff+p+1,end-p);
            return data;
        }
    }
    ON_ERROR("Can not find in dictionary.");
}

/*find key from buff, force on '#'*/
char *findkey(char *buff)
{
    int p;
    char *key;
    for(p=0;p<(int)strlen(buff);p++)
    {
        if(buff[p]=='#')
        {
            key=(char *)calloc(1,(p+1)* sizeof(char));
            memcpy(key,buff,p);
            return key;
        }
    }
    ON_ERROR("Can not find in dictionary.");
}

/*count space*/
int countspace(char *s)
{
    int i,cnt=0;
    for(i=0;i<(int)strlen(s);i++)
    {
        if(s[i]==' ')
        {
            cnt++;
        }
    }
    return ++cnt;
}

/*search the file at the first time to find out how many phones it has.
 *if can not find, give an Error.*/
int findphonemes(char *address,char *s)
{
    FILE *fp;
    int i;
    int flag;
    char *buff=(char *)calloc(1,MAXBUFF* sizeof(char));
    fp=fopen(address,"r");
    while (!feof(fp))
    {
        fgets(buff,MAXBUFF,fp);
        flag=1;
        for(i=0;i<(int)strlen(s)&&flag;i++)
        {
            if(s[i]!=buff[i])
            {
                flag=0;
            }
        }
        if(i==(int)strlen(s)&&flag&&buff[i]=='#')
        {
            return countspace(buff);
        }
    }
    ON_ERROR("Can not find in dictionary.");
}
