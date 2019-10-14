#include<stdio.h>
#include<string.h>
#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

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

/*Only IV IX XL XC CD CM represant a special subtraction.*/

int romanToArabic(char *roman) {
	int i,res = 0;
	int n = strlen(roman);
	for (i = 0; i < n; i++)
	{
		switch (roman[i])
		{
			case 'V':res += V; break;
			case 'L':res += L; break;
			case 'D':res += D; break;
			case 'M':res += M; break;
			case 'I':
				if ((roman[i + 1] == 'V') || roman[i + 1] == 'X') res -= I;
				else res += I;
				break;
			case 'X':
				if ((roman[i + 1] == 'L') || (roman[i + 1] == 'C')) res -= X;
				else res += X;
				break;
			case 'C':
				if ((roman[i + 1] == 'D') || (roman[i + 1] == 'M')) res -= C;
				else res += C;
				break;
		}
	}
	return res;
}
