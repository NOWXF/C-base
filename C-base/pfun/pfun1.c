#include <stdio.h>

char *delspace(char *str);
int main()
{
	char s[20];

	//scanf("%s",s);
	gets(s);

	delspace(s);

	puts(s);

	return 0;
}


char *delspace(char *str)
{
	char *temp=str;
	char *t2=temp;
	while(*t2 != '\0')
	{
		if(*temp == ' ')
		{
			temp++;
		}
		else
		{
			*t2=*temp;
			t2++;
			temp++;
		}
	}
	return str;
}
