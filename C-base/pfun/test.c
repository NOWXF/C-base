#include <stdio.h>
#include <string.h>

int main()
{
	char str[30]="hello world";
	printf("strlen=%d\n",strlen(str));
	printf("sizeof=%d\n",sizeof(str)/sizeof(char));
	return 0;
}
