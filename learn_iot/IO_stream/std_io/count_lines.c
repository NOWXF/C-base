#include <stdio.h>
#include <string.h>

int main(int argc,const char *argv[])
{
	FILE *fp;
	if(argc < 2)
	{
		printf("usage:./count <file>\n");
		return -1;
	}
	if((fp=fopen(argv[1],"r")) == NULL)
	{
		perror("open failed");
		return -1;
	}
	int count=0;
	char buf[1024];
	while(fgets(buf, 1024, fp) != NULL)
	{
		//读取一行后，判断是否存在换行符
		if('\n' == buf[strlen(buf)-1])
		count++;
	}
	printf("lins:%d\n",count);
	fclose(fp);
	return 0;
}

