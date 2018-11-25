
#include <stdio.h>
#include "actdb.h"
#include "/usr/include/mysql/mysql.h"

#define DB_IP "192.168.226.128"
#define DB_NAME "test"
#define DB_PASS "12345"


int connect_db_server(MYSQL **connect) {
	*connect = mysql_init(NULL);
	if(!(mysql_real_connect(*connect, DB_IP, DB_NAME, DB_PASS, "mydb", 0, NULL, 0))) {
		printf("error : %s\n", mysql_error(*connect));
		return 1;
	}
	else {
		printf("connection success\n");
		return 0;
	}
}

