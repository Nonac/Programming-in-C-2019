#include<stdio.h>
#include<string.h>
#define _LABIAL {'b','f','p','v'}
#define _GUTTERALS_SIBILANTS {'c','g','j','k','q','s','x','z'}
#define _DENTAL {'d','t'}
#define _LONG_LIQUID {'l'}
#define _NASAL {'m','n'}
#define _SHORT_LIQUID {'r'}
#define _SKIPPED {'a','e','h','i','o','u','w','y'}
#define STORELEN 4

int ReadIn(char *sp);
void Soundex(char *sp,char *resp);

int main()
{
	char res[STORELEN]={0},*resp=res;
	char *sp=(char *)malloc(sizeof(char));
	int len=ReadIn(sp);
:
	Soundex(sp,resp);	
	printf("%s",resp);	
}

int ReadIn(char *sp)
{
	char str;
	int len=0;
	printf("Please enter the name:\n");
	
	while((str=getchar())!='\n')
	{
		sp[str]=str;
		sp=(char *)realloc(sq,(++len+1)*sizeof(char));	
	}
	return len;
}

void Soundex(char *sp,char *resp)
{
	int k=0,i=1,j=1,splen=strlen(sp);
	resp[0]=sp[0];
	
	while((i<4)&&(j<splen))
	{
		while(k<(sizeof(_LABIAL)/sizeof(char)))
		{
			if(sp[j]==_LABIAL[k]&&resp[i-1]!='1') 
			{
				resp[i++]='1';
				j++;
			}else if(resp[i-1]=='1') j++;
			k++;
		}
		k=0;
		while(k<(sizeof(_GUTTERALS_SIBILANTS)/sizeof(char)))
		{
			if(sp[j]==_GUTTERALS_SIBILANTS[k]&&resp[i-1]!='2')
			{
				resp[i++]='2';
				j++;
			} else if(resp[i-1]=='2') j++;
		}
		k=0;	
		while(k<(sizeof(_DENTAL)/sizeof(char)))
		{
			if(sp[j]==_DENTAL[k]&&resp[i-1]!='3') 
			{
				resp[i++]='3';
				j++;
			}else if(resp[i-1]=='3') j++;
			k++;
		}
		k=0;
		while(k<(sizeof(_LONG_LIQUID)/sizeof(char)))
		{
			if(sp[j]==_LONG_LIQUID[k]&&resp[i-1]!='4') 
			{
				resp[i++]='4';
				j++;
			}else if(resp[i-1]=='4') j++;
			k++;
		}
		k=0;
		while(k<(sizeof(_NASAL)/sizeof(char)))
		{
			if(sp[j]==_NASAL[k]&&resp[i-1]!='5') 
			{
				resp[i++]='5';
				j++;
			}else if(resp[i-1]=='5') j++;
			k++;
		}
		k=0;
		while(k<(sizeof(_SHORT_LIQUID)/sizeof(char)))
		{
			if(sp[j]==_SPORT_LIQUID[k]&&resp[i-1]!='6') 
			{
				resp[i++]='6';
				j++;
			}else if(resp[i-1]=='6') j++;
			k++;
		}
		k=0;
		while(k<(sizeof(_SKIPPED)/sizeof(char)))
		{
			if(sp[j]==_SKIPPED[k]) 
			{
				j++;
			}
			k++;
		}
		k=0;	
	}
}
