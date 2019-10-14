#include <stdio.h>
#include<string.h>

int romanToArabic(char *roman );
int main(int argc, char **argv)
{
	if( argc==2 )
	{
		printf("The roman numeral %s is equal to %d\n", \
		argv[1], romanToArabic(argv[1]));
	}
	else
	{
		printf("ERROR: Incorrect usage, try e.g. %s XXI\n", argv[0]);
	}
	return 0;
}

int romanToArabic(char *roman) {
	int i,res = 0;
	int n = strlen(roman);
	for (i = 0; i < n; i++)
	{
		switch (roman[i])
		{
			case 'V':res += 5; break;
			case 'L':res += 50; break;
			case 'D':res += 500; break;
			case 'M':res += 1000; break;
			case 'I':
				if ((roman[i + 1] == 'V') || roman[i + 1] == 'X') res -= 1;
				else res += 1;
				break;
			case 'X':
				if ((roman[i + 1] == 'L') || (roman[i + 1] == 'C')) res -= 10;
				else res += 10;
				break;
			case 'C':
				if ((roman[i + 1] == 'D') || (roman[i + 1] == 'M')) res -= 100;
				else res += 100;
				break;
		}
	}
	return res;
}
