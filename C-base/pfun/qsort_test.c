#include <stdio.h>
#include <stdlib.h>

int compare(const void *num1, const void *num2);

int main()
{
	int arr[]={23, 345,12, -34, 223, 32};

	qsort(arr, sizeof(arr)/sizeof(int), sizeof(int), compare);

	for(int n=0;n<sizeof(arr)/sizeof(int);n++)
	{
		printf("%d ",arr[n]);
	}
	printf("\n");
	return 0;
}


int compare(const void *num1, const void *num2)
{
	return (*(int *)num1)-(*(int *)num2);
}

