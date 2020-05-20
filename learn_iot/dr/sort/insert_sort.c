#include <stdio.h>
#include <stdlib.h>

void insert_sort(int *arr, int size);

int main()
{
	int arr[8]={50,36,66,76,95,12,25,36};
	int size=sizeof(arr)/sizeof(int);


	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");

	insert_sort(arr, size);

	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}


void insert_sort(int *arr, int size)
{
	int j=0,i=1,temp;
	for(;i<size;i++)
	{
		temp=arr[i];
		for(j=i-1;j>=0;j--)
			if(arr[j] > temp)
				arr[j+1] = arr[j];
			else
				break;
		arr[j+1]=temp;
	}
	/*个人版
	for(;i<size;i++)
	{
		temp=arr[i];
		j=i-1;
		if(arr[j] <= temp)
			continue;
		else
		{
			while(j >= 0 && arr[j] > temp)
			{
				arr[j+1]=arr[j];
				j--;
			}
			arr[j+1]=temp;
		}
	}
	*/
}
