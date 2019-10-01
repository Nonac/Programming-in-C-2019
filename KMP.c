#include<stdio.h>
#include<string.h>

void Next(char *T,int *next);
int KMP(char *S,char *T);


int main()
{
	int i=KMP("aaaaa","bba");
	printf("%d\n",i);
	return 0;
}

void Next(char *T,int *next)
{
        int i=1,j=0;
        next[1]=0;
        while(i<strlen(T))
        {
                if(j==0||T[i-1]==T[j-1])
                {
                        i++;
                        j++;
                        next[i]=j;
                }else{
                        j=next[j];
                }
	}

}

int KMP(char *S,char *T)
{
	int next[10];
	Next(T,next);
	int i=1,j=1;
	while(i<=strlen(S)&&j<=strlen(T))
	{
		if(j==0||S[i-1]==T[j-1])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
	}	
	if(j>strlen(T))
	{
		return (i-(int)strlen(T)-1);
	}
	return -1;
}
