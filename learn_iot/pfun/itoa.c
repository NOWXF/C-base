#include <stdio.h>

char * itoa(int n);

int main()
{
	int n;
	char *s;

	printf("input:");
	scanf("%d",&n);

	s = itoa(n);
	puts(s);

	return 0;
}


char * itoa(int n)
{
	static char ret[50];
	int i=0;

	while(n!=0)
	{
		ret[i]=n%10+48;
		n=n/10;
		i++;
	}
	//printf("%s\n",ret);

	ret[i]='\0';
	int j=i-1;
	char temp;
	i=0;
	while(i<j)
	{
		temp=ret[i];
		ret[i]=ret[j];
		ret[j]=temp;
		i++;
		j--;
	}
	//printf("%s\n",ret);
	
	return ret;
}
