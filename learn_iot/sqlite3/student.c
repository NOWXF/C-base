#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <strings.h>

#define STU_PATH "student.db"


void do_insert(sqlite3 *db)
{
	char sql[64];
	char *errmsg;
	int id;
	char name[32];
	int score;

	printf("input id:");
	scanf("%d",&id);
	while(getchar()!='\n');

	printf("input name:");
	scanf("%s",name);
	while(getchar()!='\n');

	printf("input score:");
	scanf("%d",&score);
	while(getchar()!='\n');

	bzero(sql,sizeof(sql));
	sprintf(sql,"insert into stu values(%d,'%s',%d);",id,name,score);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return;
	}
	else
	{
		printf("insert done!\n");
	}
}

void do_delete(sqlite3 *db)
{
	char sql[64];
	char *errmsg;
	int id;

	printf("input delete id:");
	scanf("%d",&id);
	while(getchar()!='\n');

	bzero(sql,sizeof(sql));
	sprintf(sql,"delete from stu where id=%d;",id);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return;
	}
	else
	{
		printf("delete done!\n");
	}
}

int callback(void *arg,int f_num,char **f_value,char **f_name)
{
	for(int i=0;i<f_num;i++)
	{
		printf("%-11s ",f_value[i]);
	}
	putchar(10);
	return 0;
}

void do_query(sqlite3 *db)
{
	char sql[64];
	char *errmsg;

	bzero(sql,sizeof(sql));
	sprintf(sql,"select * from stu;");
	if(sqlite3_exec(db,sql,callback,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return;
	}
	else
	{
		printf("query done!\n");
	}
}


//不使用回调函数进行查询
void do_query_v1(sqlite3 *db)
{
	char sql[64];
	char *errmsg;
	char **resultp;
	int nrow;
	int ncolumn;

	bzero(sql,sizeof(sql));
	sprintf(sql,"select * from stu;");
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncolumn,&errmsg) != 0)
	{
		printf("%s\n",errmsg);
		return;
	}

	int i,j;
	for(j=0;j<ncolumn;j++)
	{
		printf("%-11s ",resultp[j]);
	}
	putchar(10);

	int index=ncolumn;
	for(i=0;i<nrow;i++)
	{
		for(j=0;j<ncolumn;j++)
		{
			printf("%-11s ",resultp[index++]);
		}
		putchar(10);
	}
	
	printf("query done!\n");
}

void do_update(sqlite3 *db)
{
	char sql[64];
	char *errmsg;
	int id;
	char name[32];
	int score;

	printf("input update id:");
	scanf("%d",&id);
	while(getchar()!='\n');

	printf("input name:");
	scanf("%s",name);
	while(getchar()!='\n');

	printf("input score:");
	scanf("%d",&score);
	while(getchar()!='\n');

	bzero(sql,sizeof(sql));
	sprintf(sql,"update stu set name='%s',score=%d where id=%d;",name,score,id);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		return;
	}
	else
	{
		printf("update done!\n");
	}
}

int main()
{
	sqlite3 *db;
	//打开数据库
	if(sqlite3_open(STU_PATH,&db) != SQLITE_OK)
	{
		perror("sqlite3_open");
		exit(-1);
	}
	else{
		printf("sqlite3 open success!\n");
	}

	//创建数据表
	char *errmsg;
	if(sqlite3_exec(db,"create table stu(id Integer,name char,score Integer);",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else
	{
		printf("create table success!\n");
	}
	//根据命令执行增删改查
	int cmd=0;
	while(1)
	{
		printf("**********************************************\n");
		printf("1.insert  2.delete  3.query  4.update  5.quit\n");
		printf("**********************************************\n");
		printf("input cmd:");
		scanf("%d",&cmd);
		while(getchar()!='\n');
		switch(cmd)
		{
			case 1:
				do_insert(db);
				break;
			case 2:
				do_delete(db);
				break;
			case 3:
				//do_query(db);
				do_query_v1(db);
				break;
			case 4:
				do_update(db);
				break;
			case 5:
				sqlite3_close(db);
				exit(0);
			default:
				printf("cmd invalid!!!\n");
		}
	}
				
	return 0;
}
