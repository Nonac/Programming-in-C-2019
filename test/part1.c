#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define TYPE 3

int pwdok(char *s);

int main()
{
    	assert(pwdok("Ab1") ==1);
    	assert(pwdok("Ab#") ==1);
    	assert(pwdok("Ab") ==0);
    	assert(pwdok("#abndsjksd2434") ==0);
    	return 0;
}



/*in this function, use an array to save the record, if record
is not zero return 1.else return 0*/
int pwdok(char *s)
{
    	int i,lenth;
    	int array[TYPE]={0};
    	lenth=strlen(s);
    	for(i=0;i<lenth;i++)
    	{
        	if((*(s+i)-'A')<=('Z'-'A') && (*(s+i)-'A')>=0)
        	{
            		array[0]++;
        	}
        	else if((*(s+i)-'a')<=('z'-'a') &&(*(s+i)-'a')>=0)
        	{
                	array[1]++;
        	}
        	else
        	{
            		array[2]++;
        	}
    	}
    	for(i=0;i<TYPE;i++)
    	{
        	if(array[i]==0)
        	{
        	    return 0;
        	}
    	}
    	return 1;
}
