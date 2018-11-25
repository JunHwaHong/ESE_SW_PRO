
#include <stdio.h>
//#include <mysql/mysql.h>
#include "/usr/include/mysql/mysql.h"

#define DB_IP "192.168.226.128"
#define DB_NAME "test"
#define DB_PASS "12345"

int main(void) {
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	unsigned int num_fields;
	unsigned int num_rows;

	char query[256];
	MYSQL *cons = mysql_init(NULL);
	if(!(mysql_real_connect(cons, DB_IP, DB_NAME, DB_PASS, "mydb", 0, NULL, 0)))
		printf("error : %s\n", mysql_error(cons));
	else
		printf("success\n");
	
	//if(mysql_select_db(cons, "mydb"))
	//	printf("db error : %s\n", mysql_error(cons));

	sprintf(query, "SELECT id, name FROM mytable");

	mysql_query(cons,query);
	myresult = mysql_store_result(cons);
	while(row = mysql_fetch_row(myresult))
		printf("%s\t %s\n", row[0], row[1]);
	mysql_free_result(myresult);
	mysql_close(cons);

	return 0;
}
