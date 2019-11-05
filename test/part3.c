#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define ADD 3

char *pwdextend(char *a);

int main()
{
    	char *p1,*p2;
    	p1=pwdextend("password");
    	p2=pwdextend("hackable");
    	assert(strcmp(p1,"password808")==0);
    	assert(strcmp(p2,"hackable808")==0);
    	return 0;
}

/*give a new string to add the "808" at the end*/
char *pwdextend(char *a)
{
    	int lenth=strlen(a),i;
    	char *res=(char *)malloc(sizeof(char)*(lenth+ADD));
    	for(i=0;i<(lenth);i++)
    	{
        	*(res+i)=*(a+i);
    	}
    	res[lenth]='8';
    	res[lenth+1]='0';
    	res[lenth+2]='8';
    	return res;
}
