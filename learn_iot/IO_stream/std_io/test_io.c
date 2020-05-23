#include <stdio.h>

int main(int argc,const char *argv[])
{
	FILE *fp;
	int count=0;
	do{
		if((fp=fopen("test.txt","r+")) == NULL)
		{
			perror("open test.txt failed");
			break;
		}
		count++;
	}while(fp != NULL);
	printf("total:%d\n",count+3);
	return 0;
}
