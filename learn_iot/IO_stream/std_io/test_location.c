#include <stdio.h>

int main(int argc,const char *argv[])
{
	FILE *fp;
	if((fp=fopen("test.txt","r+")) == NULL)
	{
		perror("open test.txt");
		return -1;
	}
	fseek(fp,0,SEEK_END);
	fputc('t',fp);
	fflush(fp);
	fclose(fp);
	return 0;
}

