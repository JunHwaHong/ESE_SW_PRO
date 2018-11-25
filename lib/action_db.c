
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actdb.h"
#include "/usr/include/mysql/mysql.h"

#define DB_IP "192.168.226.128"


int connect_db_server(MYSQL **connect, char *DB_NAME, char *DB_PASS) {
	*connect = mysql_init(NULL);
	if(!(mysql_real_connect(*connect, DB_IP, DB_NAME, DB_PASS, "userdata", 0, NULL, 0))) {
		printf("error : %s\n", mysql_error(*connect));
		return 1;
	}
	else {
		printf("connection success\n");
		return 0;
	}
}

int access_login(MYSQL **connect) {
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	char id_buf[20];
	char pass_buf[20];
	printf("ID : ");
	scanf("%s", id_buf);
	printf("PASSWD : ");
	scanf("%s", pass_buf);
	mysql_server_end();
	return connect_db_server(connect, id_buf, pass_buf);
}

int access_make_account(MYSQL **connect) {
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	char id_buf[20];
	char pass_buf[20];
	char query[256];
	printf("MAKE ID : ");
	scanf("%s", id_buf);
	printf("MAKE PASSWD : ");
	scanf("%s", pass_buf);
	mysql_query(*connect, "use mysql");
	mysql_query(*connect, "select user on from user");
	printf("one\n)");
	myresult = mysql_store_result(*connect);
	printf("two\n");
	while(row = mysql_fetch_row(myresult)) {
		printf("gg\n");
		if(strcmp(row[0], id_buf)) {
			printf("Duplicated id\n");
			return 1;
		}
	}
	printf(" before three\n");
	mysql_free_result(myresult);
	printf("three\n");
	mysql_query(*connect,"use userdata");
	sprintf(query, "create table %s (id INT PRITMARY KEY, name VARCHAR(20))",id_buf);
	mysql_query(*connect, query);
	memset(query, 0, sizeof(query));

	sprintf(query, "create user '%s'@'%c' identified by '%s'",id_buf,'%', pass_buf);
	mysql_query(*connect, query);
	memset(query, 0, sizeof(query));

	sprintf(query, "grant all privileges on userdata.%s to '%s'@'%c'", id_buf, id_buf, '%');

	mysql_query(*connect, query);
	memset(query, 0, sizeof(query));

	mysql_query(*connect, "flush privileges");

	mysql_server_end();
	return 0;
}






