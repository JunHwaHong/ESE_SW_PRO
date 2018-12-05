#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actnovice.h"
#include "/usr/include/mysql/mysql.h"
#include "actdb.h"

#define DB_IP "222.121.186.100"

void CreateJournal(MYSQL *connect)
{
	int choice;
	int choice2;
	char AddToExercise[10];
	char buf[256];
	char *user_id;
	char *real_user_id;
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	//해당 유저의 아이디 정보를 가져온다.
	mysql_query(connect,"select user()");
	myresult = mysql_store_result(connect);
	row = mysql_fetch_row(myresult);
	user_id = (char *)row[0];
	real_user_id = strtok(user_id,"@");


	while(1)
	{
		printf(" 1. Create a Journal  2. Add Workout Exercise 3.Back \n");
		printf("Enter : ");
		scanf("%d", &choice);

		if(choice == 1)
		{
		}
		else if(choice == 2)
		{
			while(1)
			{
				printf(" What kind of exercise do you want to add? \n");
				printf("Enter : ");
				scanf("%s",AddToExercise);
 		
		

				sprintf(buf,"alter table workout.%s add %s char(15)",real_user_id,AddToExercise);
				mysql_query(connect,buf);
				memset(buf,0,sizeof(buf));

				printf(" 1.Continue Add   2.No \n");
				printf("Enter : ");
				scanf("%d",&choice2);
				if(choice2 == 2)
				{
					break;
				}
			}

		}
		else
		{	
			return;
		}
	}
}


void goNovice(MYSQL **connect)
{
	int choice = 0;

	
	printf("================Welcome Novice==================\n");
	while(1)
	{
		printf("1. Create a journal 2. View Journal 3.View Coach Advice 4.exit \n");
		printf("Enter : ");
		scanf("%d",&choice);
		if(choice ==1)
		{
			CreateJournal(*connect);
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
