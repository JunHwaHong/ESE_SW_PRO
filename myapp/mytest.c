
#include "actdb.h"
#include "show.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include "actnovice.h"

#define Novice 1
#define Coach 2
//char *DB_NAME = "test";
//char *DB_PASS = "1234";

int main(void) {
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	MYSQL *cons = mysql_init(NULL);	
	int select_menu = 0;
	unsigned int num_fields;
	unsigned int num_rows;
	int choice =0;
	char query[256];
	show_enter_window();
	scanf("%d", &select_menu);
	switch (select_menu) {
		case 1:
			printf("Are you 1.Novice or 2.Coach ?? \n");
			scanf("%d",&choice);
			
			if(choice == Novice)
			{
				if(access_login(&cons)) {
				printf("Cannot login Account\n");
				return 0;
				}
	
				goNovice(&cons);				
			}
			else
			{
				//if Coach
			}

			break;
		case 2:
			if(access_make_account(&cons)) {
				printf("Cannot make Account\n");
				return 0;
			}
			printf("success to make new one");
			return 0;
			break;
		case 3:
			return 0;
			break;

	}


	mysql_close(cons);

	return 0;
}
