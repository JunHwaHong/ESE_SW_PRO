#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actnovice.h"
#include "/usr/include/mysql/mysql.h"
#define DB_IP "222.121.186.100"


void goNovice(void)
{
	int choice = 0;
	MYSQL *cons = mysql_init(NULL);
	if(access_login(&cons)) {
		printf("login error\n");
		return 0;
	}//login
	
	
	printf("================Welcome Novice==================\n");
	while(1)
	{
		printf("1. Create a journal 2. View Journal 3.View Coach Advice 4.exit \n");
		printf("Enter : ");
		scanf("%d",&choice);
		if(choice ==1)
		{
	
		}
		else if(choice ==2)
		{
		}
		else if(choice ==3)
		{
		}
		else if(choice ==4)
		{
			return;
		}
		else
		{}
	}
}
