
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actdb.h"
#include "/usr/include/mysql/mysql.h"
#define DB_IP "222.121.186.100"


int connect_db_server(MYSQL **connect, char *DB_NAME, char *DB_PASS) {
	*connect = mysql_init(NULL);
	if(!(mysql_real_connect(*connect, DB_IP, DB_NAME, DB_PASS, NULL, 2222, NULL, 0))) {
		printf("error : %s\n", mysql_error(*connect));
		return 1;
	}
	else {
		printf("connection success\n");
		return 0;
	}
}

int access_login(MYSQL **connect) {
	char id_buf[20];
	char pass_buf[20];
	printf("ID : ");
	scanf("%s", id_buf);
	printf("PASSWD : ");
	scanf("%s", pass_buf);
	//mysql_server_end();
	return connect_db_server(connect, id_buf, pass_buf);
}

int access_make_account(MYSQL **connect) {
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int fields = 0;
	int count = 0;

	char coach_name[15];
	char coach_sex[8];
	int coach_age;
	int coach_career;
	
	char id_buf[20];
	char pass_buf[20];
	int choice=0;
	char buf[256];

	char wantCoach[10];
	printf("1. Novice     2. Coach   :  ");
	scanf("%d",&choice);
	printf("MAKE ID : ");
	scanf("%s", id_buf);
	printf("MAKE PASSWD : ");
	scanf("%s", pass_buf);
	connect_db_server(connect, "test", "1234");

	sprintf(buf, "create user '%s'@'%s' identified by '%s'",id_buf, "%", pass_buf);
	mysql_query(*connect, buf);
	memset(buf, 0, sizeof(buf));

	mysql_query(*connect, "use workout");

	if(choice == 1) // if, Novice
	{
		sprintf(buf, "create table %s (date CHAR(15))",id_buf);
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));
	
		sprintf(buf, "grant all privileges on workout.%s to '%s'@'%s'", id_buf, id_buf, "%");
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "grant select on workout.CoachList to '%s'@'%s'",id_buf, "%");
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "grant select,insert,update on workout.WhoIsMyCoach to '%s'@'%s'",id_buf,"%");
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));

		mysql_query(*connect, "flush privileges");
		
		printf("===================Coach List ====================  \n");
		mysql_query(*connect,"select * from CoachList");
		myresult = mysql_store_result(*connect);
		fields = mysql_num_fields(myresult);

		while( row = mysql_fetch_row(myresult))
		{
			
		       	printf(" Name: %s Sex: %s Age: %s Career: %s \n",row[0],row[1],row[2],row[3]);
			
		}
		
		printf("=======================================  \n");
		printf("Who is the Coach that you want? : ");
		scanf("%s",wantCoach);
		sprintf(buf, "insert into WhoIsMyCoach values('%s','%s')",id_buf,wantCoach);
		mysql_query(*connect,buf);
		
		mysql_free_result(myresult);
		mysql_server_end();
	}
	else if(choice == 2)//if, Coach
	{

		sprintf(buf, "grant all privileges on workout.CoachList to '%s'@'%s'",id_buf, "%");
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));

		sprintf(buf, "grant select on workout.WhoIsMyCoach to '%s'@'%s'",id_buf, "%");
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));


		mysql_query(*connect, "flush privileges");

		printf("Enter Your Name : ");
		scanf("%s",coach_name);
		printf("Enter Your Sex : ");
		scanf("%s",coach_sex);
		printf("Enter Your age : ");
		scanf("%d",&coach_age);
		printf("Enter Your career duration : ");
		scanf("%d",&coach_career);

		sprintf(buf, "insert into CoachList values('%s','%s',%d,%d)",coach_name,coach_sex,coach_age,coach_career);
		mysql_query(*connect, buf);
		memset(buf, 0, sizeof(buf));
	
		mysql_server_end();
	}
	else
	{
	}
	return 0;
}






