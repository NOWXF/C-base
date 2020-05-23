#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *p;
	p=(char *)malloc(10*sizeof(char));
	if(p == NULL)
	{
		printf("malloc failed\n");
		return 0;
	}

	printf("%p\n",p);
	scanf("%s",p);

	printf("%s\n",p);

	free(p);
	return 0;
}
