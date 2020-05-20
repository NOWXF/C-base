#include <stdio.h>

int fab(int n);
int main()
{
	int n;
	printf("input:");
	scanf("%d",&n);

	int i=1;
	while(i<=n)
	{
		printf("result:%d\n",fab(i));
		i++;
	}
	printf("\n");

	return 0;
}


int fab(int n)
{
 	if(n==1 || n==2)
		return 1;
	return fab(n-1)+fab(n-2);
}
