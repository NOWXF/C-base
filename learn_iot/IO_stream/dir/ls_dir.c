#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

#define DEBUG 0

int main(int argc,const char *argv[])
{
	struct stat s;
	struct tm *time;
	if(argc < 2)
	{
		printf("usage:%s <file>\n",argv[0]);
		return -1;
	}
	if(lstat(argv[1],&s) < 0)
	{
		perror("lstat failed");
		return -1;
	}

	switch(s.st_mode&S_IFMT)
	{
		case S_IFREG:
			printf("-");
			break;
		case S_IFDIR:
			printf("d");
			break;
	}

	for(int n=8;n>0;n--)
	{
		if(s.st_mode & (1<<n))
		{
			switch(n%3)
			{
				case 2:
					printf("r");
					break;
				case 1:
					printf("w");
					break;
				case 0:
					printf("x");
					break;
			}
		}
		else
		{
			printf("-");
		}
	}
#if DEBUG
	puts("2");
#endif
	/*个人版
	switch(s.st_mode&00700)
	{
		case S_IRWXU:
			printf("rwx");
			break;
		case S_IRUSR:
			printf("r--");
			break;
		case S_IWUSR:
			printf("-w-");
			break;
		case S_IXUSR:
			printf("--x");
			break;
		default:
			printf("---");
	}

	switch(s.st_mode&00070)
	{
		case S_IRWXG:
			printf("rwx");
			break;
		case S_IRGRP:
			printf("r-");
			break;
		case S_IWGRP:
			printf("-w-");
			break;
		case S_IXGRP:
			printf("--x");
			break;
		default:
			printf("---");
	}

	switch(s.st_mode&0007)
	{
		case S_IRWXO:
			printf("rwx");
			break;
		case S_IROTH:
			printf("r--");
			break;
		case S_IWOTH:
			printf("-w-");
			break;
		case S_IXOTH:
			printf("--x");
			break;
		default:
			printf("---");
	}
	*/

#if DEBUG
	puts("3");
#endif

	printf(" %d",s.st_size);
	time = localtime(&s.st_ctime);
	printf(" %d-%02d-%02d",time->tm_year+1900,time->tm_mon+1,time->tm_mday);
	printf(" %s\n",argv[1]);
	return 0;
}

