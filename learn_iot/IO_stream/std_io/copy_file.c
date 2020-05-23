#include <stdio.h>

int main(int argc,const char *argv[])
{
	FILE *src,*dest;
	//提示输入方式
	if(argc < 3)
	{
		printf("usage:./copy <file1> <file2>\n");
		return -1;
	}
	//打开输入流
	if((src=fopen(argv[1],"r")) == NULL)
	{
		perror("src open failed");
	}
	//打开输出流
	if((dest=fopen(argv[2],"w")) == NULL)
	{
		perror("dest open failed");
	}
	char c;
	//复制文件
	while((c=fgetc(src)) != EOF)
	{
		fputc(c,dest);
	}

	//关闭文件流
	fclose(src);
	fclose(dest);
	return 0;
}
