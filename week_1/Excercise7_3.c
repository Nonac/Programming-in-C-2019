#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct
{
	int wallet;
	BOOL odd,even;
	int number;
}Status;

void bet(Status *status);
void game(int res,Status *status);

int main()
{
	int res,cnt=0;
	Status status;
	status.wallet=10;
	
	srand((unsigned)time(NULL));	
	printf("Now you have $%d.\n",status.wallet);

	while(status.wallet>0)
	{
		res=rand()%36;
		status.wallet--;

		bet(&status);
		game(res,&status);
		cnt++;
		printf("\nNow you have $%d.\n",status.wallet);
	}

	printf("You played %d times.\n",cnt);
	return 0;
}

void bet(Status *status)
{
	int key1,key2,key3;
	status->odd=FALSE;
	status->even=FALSE;
	status->number=36;
	printf("\nPlace an odd/even bet, or a bet on a particular number?\n1.odd/even bet\n2.particular number");
	scanf("%d",&key1);

	while(!(key1==1)&&!(key1==2))
	{
		printf("Invalid number, please re-enter:\n1.odd/even bet\n2.particular number");
		getchar();
		scanf("%d",&key1);
	}
	if (key1==1)
	{
		printf("\nPlace an odd bet or an even bet?\n1.odd bet\n2.even bet");
		scanf("%d",&key2);
		while(!(key2==1)&&!(key2==2))
		{
			printf("Invalid number, please re-enter:\n1.odd bet\n2.even bet");
			getchar();
			scanf("%d",&key2);
		}
		if (key2==1) status->odd=TRUE;
		else status->even=TRUE;
	}
	else
	{
		printf("\nEnter a number between 0 and 35:");
		scanf("%d",&key3);
		while(!(key3<=35)||!(key3>=0))
		{
			printf("Invalid number, please re-enter a number between 0 and 35:");
			getchar();
			scanf("%d",&key3);
		}
		status->number=key3;
	}
}

void game(int res,Status *status)
{
	if ((status->odd==TRUE)&&(res%2==1)&&(res!=0)) 
	{
		status->wallet=status->wallet+2;
		printf("The result is %d. You win $1.\n",res);
	}
	else if ((status->even==TRUE)&&(res%2==0)&&(res!=0))
	{
		status->wallet=status->wallet+2;
		printf("The result is %d. You win $1.\n",res);
	}
	else if (status->number==res) 
	{
		status->wallet=status->wallet+35;
		printf("The result is %d. You win $34.\n",res);
	}
	else printf("The result is %d. You lose $1.\n",res);
}


