#include <stdio.h>

int main(int argc,const char *argv[])
{
	FILE *fp;
	char buf[64];
	int year,month,day;
	year=2020;
	month=5;
	day=21;
	if((fp=fopen("test.txt","r+")) == NULL)
	{
		perror("open test.txt failed");
		return -1;
	}
	fseek(fp,0,SEEK_END);

	fprintf(fp,"%4d-%02d-%2d\n",year,month,day);
	sprintf(buf,"%4d-%02d-%2d\n",year,month,day);
	printf("%s",buf);
	fclose(fp);
	return 0;
}
