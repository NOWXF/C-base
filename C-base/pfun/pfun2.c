#include <stdio.h>

char * strcat(char *dest, char *src);

int main()
{
	char s1[100]="welcome ";
	char s2[20]="root's world";

	printf("%s\n",strcat(s1, s2));

	return 0;
}


char * strcat(char *dest, char *src)
{
	char *p=dest;
	while(*p != '\0')
	{
		p++;
	}

	*p = *src;
	while(*p != '\0')
	{
		p++;
		src++;
		*p = *src;
	}
	return dest;
}

