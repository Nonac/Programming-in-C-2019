#include<stdio.h>
#include<string.h>
int isAnagrams(char *target,char *dict);
void printword(char *dict);

int main(int argc,char **argv)
{
	char **dict
	FILE *fp;
	if(argc==2)
	{
		
		if(isAnagrams(argv[1],dict))
		{
			printword(dict);
		}				
	}
	else
	{
		printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
	}
}

int isAnagrams(char *target, char *dict)
{
	int Alphabet[26]={0};
	if(target==NULL && dict==NULL) return 1;
	if((strlen(target)!=strlen(diction))) return 0;
	
	for(i=0;i<strlen(target);i++)
	{
		Alphabet[target[i]-'a']++;
		Alphabet[dict[i]-'a']--;
	}

	for(i=0;i<strlen(target);i++)
	{
		if(Alphabet[i]<0)
		{
			return ;
		}
	}
	return 1;	
}

void printword(char *word)
{
	int i=0;
	while(word[i]!=NULL)
	{
		printf("%c",word[i]);
	}
	printf("\n");	
}
