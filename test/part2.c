#include <assert.h>
#include <string.h>

void passwp(char *a,char *b);

int main()
{
    	char b[100];
    	passwp("ABCdefghijklmnopqrstuvwxyz",b);
    	assert(strcmp(b,"@BCdefghijklmn0pqr5tuvwxyz")==0);
    	passwp("ABCdefghijklmnopqrstuvwxyz",b);
    	assert(strcmp(b,"@BCdefghijklmn0pqr5tuvwxyz")==0);
    	return 0;
}

/*just replace the char,and add a EOF at the end.*/
void passwp(char *a,char *b)
{
    	int i,lenth;
    	lenth=strlen(a);
    	for(i=0;i<lenth;i++)
    	{
        	switch (*(a+i))
        	{
			case 'A':	
				*(b+i)='@';
		                break;
		        case 'a':
        		        *(b+i)='@';
        		        break;
        		case 'O':
                		*(b+i)='0';
                		break;
            		case 'o':
                		*(b+i)='0';
                		break;
            		case 's':
                		*(b+i)='5';
                		break;
            		case 'S':
                		*(b+i)='5';
                		break;
            		default:
                		*(b+i)=*(a+i);
                		break;
        	}
    	}
    	b[lenth]='\0';
}
