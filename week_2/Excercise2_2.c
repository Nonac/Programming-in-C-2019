#include<stdio.h>
#include<math.h>

void Createletter(char *letter);
void Createunvowel(char *unvowel,char *vowel);
int Sub(char c);
int Isprime(int k);

int main()
{
        char unvowel[21],vowel[5]={'a','e','i','o','u'};
	char letter[26];
	int i,j,cnt=1;
	Createletter(letter);
        Createunvowel(unvowel,vowel);
        for(i=0;i<26;i++)
        {
                for(j=0;j<5;j++)
                {
			if(Isprime(Sub(letter[i])*2+Sub(vowel[j]))&&(letter[i]!=vowel[j]))
			{
				printf("%d %c%c%c\n",cnt,letter[i],vowel[j],letter[i]);
				cnt++;
			}		
                }
        }
	return 0;
}

void Createletter(char *letter)
{
	int i;
	for(i=0;i<26;i++)
	{
		letter[i]='a'+i;
	}
}

void Createunvowel(char *unvowel,char *vowel)
{
        int i,j=0,k=0;
        char temp;
        for(i=0;i<26;i++)
        {
                temp='a'+i;
                if(temp!=vowel[j])
                {
                        unvowel[k]=temp;
                        k++;
                }
                else
                {
                        j++;
                }
        }
}

int Sub(char c)
{
	return (c-'a'+1);
}

int Isprime(int k)
{
	int temp;
	for(temp=2;temp<k;temp++)
	{
		if(k%temp==0) return 0;
	}
	return 1;
}
