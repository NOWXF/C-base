#include <stdio.h>

int add(int a,int b){
	return a+b;
}

int sub(int a,int b){
	return a-b;
}

int mul(int a,int b){
	return a*b;
}

int main()
{
	int a=10,b=20;
	int (*p)(int,int);

	p=add;

	//printf("result:%d\n",add(a,b));
	printf("result:%d\n",(*p)(a,b));
	p=sub;
	printf("result:%d\n",(*p)(a,b));

	return 0;
}
