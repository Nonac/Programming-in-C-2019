#include<stdio.h>
#include<stdint.h>

int main()
{
	uint32_t a = 16;
	uint32_t b = 0x10;

	if(a==b) printf("Equal.");
	else printf("Unequal.");
	return 0;
}
