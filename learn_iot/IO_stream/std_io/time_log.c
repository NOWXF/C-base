#include <stdio.h>
#include <unistd.h> //sleep
#include <time.h>   //time  /  localtime
#include <string.h>

int main(int argc,const char *argv[])
{
	FILE *fp;
	int line=0;
	char buf[64];
	time_t t;
	struct tm * tms;

	//打开文件
	if((fp=fopen("time_log.txt","a+")) == NULL)
	{
		perror("open time_log.txt failed");
		return -1;
	}

	//读取行数
	while(fgets(buf,64,fp) != NULL)
	{
		if(buf[strlen(buf)-1] == '\n') line++;
	}

	//写入时间
	while(1)
	{
		//获取当前秒数
		time(&t);
		//将当前秒数进行本地化
		tms=localtime(&t);
		//使用流输出方法输出到文件
		fprintf(fp,"%02d,%d-%02d-%02d %02d:%02d:%02d\n",++line, tms->tm_year+1900,tms->tm_mon+1,tms->tm_mday,tms->tm_hour,tms->tm_min,tms->tm_sec);
		//刷新流缓冲区，以便数据真正写入
		fflush(fp);
		//睡眠1秒
		sleep(1);
	}

	return 0;
}
