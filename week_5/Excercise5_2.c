#include<stdio.h>
#include<string.h>
#define LONGESTWORD 45
#define BUFFSIZE 1024

/*Longest word in a major dictionary is Pneumonoultramicroscopicsilicovolcanoconiosis with 45 letters.*/

int isAnagrams(char *target,char *dict);
void printword(char *word);
void copyfile(FILE *fin, FILE *fout);

int main()
{
	char word[LONGESTWORD];
	char temp;
	FILE *fp,*fout;
	int i;
	fp=fopen("eng_370k_shuffle.txt","r");
	fout=fopen("copydictory.txt","w");

	copyfile(fp,fout);

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


void copyfile(FILE *fin, FILE *fout)
{
	char *buff=malloc(BUFFSIZE);		
	int ret;
	
	do{
		ret=fread(buff,1,BUFFSIZE,fin);
		if(ret!=BUFFSIZE)
		{
			fwrite(buff,ret,1,fout);
		}else{
			fwrite(buff,BUFFSIZE,1,fout);
		}
	while(!(feof(fin)));
}
