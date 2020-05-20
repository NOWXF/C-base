#include <stdio.h>
#include <stdlib.h>

void show(int *arr,int size);
void bubble_pro_sort(int *arr, int size);

int main()
{
	int arr[8]={50,36,66,76,95,12,25,36};
	int size=sizeof(arr)/sizeof(int);

	show(arr,size);
	bubble_pro_sort(arr, size);
	show(arr,size);

	return 0;
}

void show(int *arr,int size)
{
	for(int i=0;i<size;i++)
		printf("%d ",arr[i]);
	printf("\n");
}

//冒泡排序的升级版
void bubble_pro_sort(int *arr, int size)
{
	int flag=1;
	for(int i=0;i<size;i++)
	{
		//设置标志位
		flag=1;
		for(int j=0;j<size-i-1;j++)
		{
			if(arr[j] > arr[j+1])
			{
				int temp=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;
				//如果进行了交换，说明有可以交换的数
				flag=0;
			}
		}
		//如果遍历了一遍都没有交换，说明所有数据已经是有序
		if(flag)
			break;
	}
}
