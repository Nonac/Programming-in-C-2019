#include<stdio.h>


int main()
{
	
	double a,b,c,temp,Pythagorean;
	printf("Enter three integer values which represent sides of a triangle:");
	scanf("%lf",&a);
	while(a<=0)
	{
		printf("Invalid value.Please enter a positive number:");
		scanf("%lf",&a);
	}
	getchar();
	scanf("%lf",&b);
	while(b<=0)
	{
		printf("Invalid value.Please enter a positive number:");
		scanf("%lf",&b);
	}
	getchar();
	scanf("%lf",&c);
	while(c<=0)
	{
		printf("Invalid value.Please enter a positive number:");
		scanf("%lf",&c);
	}

	if (b<c)
	{
		temp=b;
		b=c;
		c=temp;
	}
	if (a<b)
	{
		temp=a;
		a=b;
		b=temp;
	}
	
	if(a>b+c) 
	{
		printf("These three values do not form a triangle.\n");
		return 0;
	}
	
	Pythagorean=b*b+c*c;	

	if (((a>=b)&&(a<=b))&&((a>=c)&&(a<=c)))
	{
		printf("The values of the three sides are %f %f and %f. This is an equilateral.\n",a,b,c);
	}else if((Pythagorean>=(a*a))&&(Pythagorean<=(a*a)))
	{
		if (((a>=b)&&(a<=b))||((a>=c)&&(a<=c))||((b>=c)&&(b<=c)))
		{
			printf("The values of the three sides are %f %f and %f. This is a right angled isosceles.\n",a,b,c);
		}else printf("The values of the three sides are %f %f and %f. This is a right angled.\n",a,b,c);
	}else
	{ 
		if (((a>=b)&&(a<=b))||((a>=c)&&(a<=c))||((b>=c)&&(b<=c)))
		{
			printf("The values of the three sides are %f %f and %f. This is an isosceles.\n",a,b,c);
		}else printf("The values of the three sides are %f %f and %f. This is a scalene.\n",a,b,c);
	}
	return 0;
}
