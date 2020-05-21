#include <stdio.h>

int main(int argc,const char * argv[])
{
	if(argc < 3)
	{
		printf("usga:mycp <file1> <file2>\n");
		return -1;
	}
	FILE *src,*dest;
	if((src=fopen(argv[1],"r")) == NULL)
	{
		perror("fopen src failed");
		return -1;
	}
	if((dest=fopen(argv[2],"w")) == NULL)
	{
		perror("fopen dest failed");
		return -1;
	}
	char buf[1024];
	//size用于存储每次读取到的对象数量
	//如果到达末尾，可能出现不足的情况，只需要使用实际获取的对象数量
	int size=0;
	while((size = fread(buf,sizeof(char),1024,src)) != 0)
	{
		fwrite(buf,sizeof(char),size,dest);
	}

	fclose(src);
	fclose(dest);
	return 0;
}

