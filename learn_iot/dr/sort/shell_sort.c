#include <stdio.h>
#include <stdlib.h>

void show(int *arr,int size);
void insert_sort(int *arr, int size);
void shell_sort(int *arr, int size);

int main()
{
	int arr[8]={50,36,66,76,95,12,25,36};
	int size=sizeof(arr)/sizeof(int);

	show(arr,size);
	shell_sort(arr, size);
	show(arr,size);

	return 0;
}


void show(int *arr,int size)
{
	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");
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
}

void shell_sort(int *arr, int size)
{
	int d=size,i,j=0,temp;
	for(d=d/2;d>0;d/=2)
	{
		for(i=d;i<size;i++)
		{
			temp=arr[i];
			for(j=i-d;j>=0;j-=d)
				if(arr[j] > temp)
					arr[j+d] = arr[j];
				else
					break;
			arr[j+d]=temp;
			//show(arr,size);
		}
	}
}
