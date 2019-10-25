#include<stdio.h>
#include<string.h>
#define LONGESTWORD 45

/*Longest word in a major dictionary is Pneumonoultramicroscopicsilicovolcanoconiosis with 45 letters.*/

int isAnagrams(char *target,char *dict);
void printword(char *word);

int main(int argc,char **argv)
{
	char word[LONGESTWORD];
	char temp;
	FILE *fp;
	int i;
	if(argc==2)
	{
		fp=fopen("eng_370k_shuffle.txt","r");
		do{
		for(i=0;i<LONGESTWORD;i++)
		{
			word[i]=EOF;
		}
		
		fscanf(fp,"%s",word);		
		if(isAnagrams(argv[1],word))
		{
			printword(word);
		}
		}while(word[0]!=EOF);				
	}
	else
	{
		printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
	}
}

int isAnagrams(char *target, char *dict)
{
	int i,Alphabet[26]={0};
	if(target==NULL && dict==NULL) return 1;
	if(((strlen(target))!=(strlen(dict)))) return 0;

	for(i=0;i<strlen(target);i++)
	{
		Alphabet[target[i]-'a']++;
		Alphabet[dict[i]-'a']--;
	}

	for(i=0;i<26;i++)
	{
		if(Alphabet[i]<0)
		{
			return 0;
		}
	}
	return 1;
}

void printword(char *word)
{
	int i=0;
	while(word[i]!=EOF)
	{
		printf("%c",word[i]);
		i++;
	}
	printf("\n");
}
