#include<stdio.h>
#include<string.h>

typedef struct
{
	int hours;
	int minutes;  
}Time;

int checkTime(Time time);
void printTime(Time time);
Time subtract(Time *first,Time *second);

int main()
{
	Time time1,time2,time3;
	int again=1;
	printf("Enter two times :");
	while(again)
	{
		scanf("%d:%d",&time1.hours,&time1.minutes);
		if(checkTime(time1))
		{
			printf("Invalid format, please re-enter:");
			again=1;
		}
		else again=0;
	}
	again=1;
        	while(again)
        	{
            		scanf("%d:%d",&time2.hours,&time2.minutes);
		if(checkTime(time2))
            		{
                			printf("Invalid format, please re-enter:");
                			again=1;
            		}
            		else again=0;
	}
	time3=subtract(&time1,&time2);
	printf("Difference is:");
	printTime(time3);
	printf("\n");
}

int checkTime(Time time)
{
    return ((time.hours>24||time.hours<0)||(time.minutes>=60||time.minutes<0));
}
void printTime(Time time)
{
    printf("%d:%d",time.hours,time.minutes);
}

Time subtract(Time *first,Time *second)
{
    	Time result;

    	if(second->minutes>=first->minutes)
    	{
        		result.minutes=second->minutes-first->minutes;
    	}
    	else
    	{
        		second->hours--;
        		second->minutes=second->minutes+60;
        		result.minutes=second->minutes-first->minutes;
   	 }

	if(second->hours>=first->hours)
    	{
        		 result.hours=second->hours-first->hours;
    	}
    	else
    	{
        		second->hours+=24;
		result.hours=second->hours-first->hours;
   	 }

    return result;
}
