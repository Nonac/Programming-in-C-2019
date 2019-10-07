#include<stdio.h>
#include<math.h>
#include <time.h>
#define TARGET_MAX 3.141592654
#define TARGET_MIN 3.141592645

double Pi(int cnt, double res);
int Check(double res);

int main()
{
	clock_t startTime,endTime;      
	double res=0.0;
        unsigned int cnt=0;
        startTime = clock();
	
	while(!Check(res))
	{
		res=Pi(cnt,res);
		cnt++;
		/*printf("%d ",cnt);*/
	}

	printf("\n\nThere are %d iterations to get p correctly approximated to 9 digits.(%.10f)\n",cnt,res);
        endTime = clock();
        printf("Total time is:%.10f",(double)(endTime - startTime) / CLOCKS_PER_SEC);
        return 0;
}

int Check(double res)
{
	return (res<=TARGET_MAX&&res>=TARGET_MIN);	
}

double  Pi(int cnt,double res)
{
	res = res + 4*pow((-1),(double)cnt)/(2*cnt+1);
	/*printf("%.10f\n",res);*/
	return res;	
}


/*
  
void Pi(int cnt,int *res);
int Check(int *target,int *res);

int main()
{
	clock_t startTime,endTime; 	
	int i,res[10],target[10]={3,1,4,1,5,9,2,6,5,4};
	unsigned int cnt=0;
	startTime = clock();
    	for(i=0;i<10;i++)
   	{
        	res[i]=0;
    	}

    	while(Check(target,res))
    	{
        		Pi(cnt,res);
        		cnt++;
		printf("%d ",cnt);
	}

    	printf("\n\nThere are %d iterations to get p correctly approximated to 9 digits.\n",cnt);
	endTime = clock();
    	printf("Total time is:%.10f",(double)(endTime - startTime) / CLOCKS_PER_SEC);
    	return 0;
}

void Pi(int cnt,int *res)
{
    	int i;
    	double sum=0.0;
    	for(i=0;i<(cnt+1);i++)
    	{
        		sum = sum + 4*pow((-1),(double)i)/(2*i+1);
    	}
    	printf("%.10f\n",sum);
    	for(i=0;i<10;i++)
    	{
        		res[i]=(int)sum;
        		sum=sum-res[i];
        		sum=sum*10;
        		i++;
    	}
}

int Check(int *target,int *res)
{
    	int i;
    	for(i=0;i<10;i++)
    	{
        		if (res[i]!=target[i]) return 1;
    	}
    	return 0;
}*/
