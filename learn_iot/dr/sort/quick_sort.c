#include <stdio.h>
#include <stdlib.h>

void show(int *arr,int size);
int quick_pass(int *arr, int low, int high);
void quick_sort(int *arr, int low, int high);

int main()
{
	int arr[8]={50,36,66,76,95,12,25,36};
	int size=sizeof(arr)/sizeof(int);

	show(arr,size);
	quick_sort(arr, 0, size-1);
	show(arr,size);

	return 0;
}


void show(int *arr,int size)
{
	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");
}


int quick_pass(int *arr, int low, int high)
{
	int mid=low,temp;
	temp=arr[low];
	while(low < high)
	{
		while(low < high && temp <= arr[high])
		{
			high--;
		}
		if(low < high)
			arr[low]=arr[high];
		while(low < high && temp >= arr[low])
		{
			low++;
		}
		if(low < high)
			arr[high]=arr[low];
		show(arr,8);
	}
	mid=low;
	arr[mid]=temp;
	return mid;
}

void quick_sort(int *arr, int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = quick_pass(arr,low,high);
		quick_sort(arr,low,mid-1);
		quick_sort(arr,mid+1,high);
	}
}
