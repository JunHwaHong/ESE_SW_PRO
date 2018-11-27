
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

	char id_buf[20];
	char pass_buf[20];
	char buf[256];
	printf("MAKE ID : ");
	scanf("%s", id_buf);
	printf("MAKE PASSWD : ");
	scanf("%s", pass_buf);
	
	connect_db_server(connect, "test", "1234");

	sprintf(buf, "create user '%s'@'%s' identified by '%s'",id_buf, "%", pass_buf);
	mysql_query(*connect, buf);
	memset(buf, 0, sizeof(buf));

	mysql_query(*connect, "use workout");

	sprintf(buf, "create table %s (date INT)",id_buf);
	mysql_query(*connect, buf);
	memset(buf, 0, sizeof(buf));

	sprintf(buf, "grant all privileges on workout.%s to '%s'@'%s'", id_buf, id_buf, "%");
	mysql_query(*connect, buf);
	memset(buf, 0, sizeof(buf));

	mysql_query(*connect, "flush privileges");

	mysql_server_end();
	return 0;
}






