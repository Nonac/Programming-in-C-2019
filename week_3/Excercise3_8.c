#include <stdio.h>
#include<string.h>

int romanToArabic( char *roman );

int main()
{
	char str[100],*sp=str;
	printf("Please enter a Roman number:");
	scanf("%s",sp);
	
	printf("The result if %d.\n",romanToArabic(sp));
	/*if( )
	{	
		printf("The roman numeral %s is equal to %d\n", \
			, romanToArabic());
	}else{
		printf("ERROR: Incorrect usage, try e.g. %s XXI\n", );
	}*/
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
