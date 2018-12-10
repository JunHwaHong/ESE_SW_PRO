#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actnovice.h"
#include "/usr/include/mysql/mysql.h"
#include "actdb.h"

#define DB_IP "222.121.186.100"

struct node{
	char *exercise;
	int idx;
	struct node *next;
};
struct node *head = 0;

void addNode(char *Exercise,int idx)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->exercise = Exercise;
	new_one->idx = idx;
	new_one->next = 0;

	if(head == 0)
	{
		head = new_one;
		return;
	}
	struct node *temp = head;


	while(temp->next != 0)
	{
		temp =temp->next;
	}

	temp->next = new_one;
}

struct node *findNodebyIdx(int idx)
{
	struct node *temp = head;

	while(1)
	{
		if(temp->idx == idx)
		{
			return temp;
		}
	temp= temp->next;
	}
	return 0;

}

void CreateJournal(MYSQL *connect)
{
	int i=1;
	int exercise_idx=0;
	int choice;
	int choice_2;
	int choice2;
	char AddToExercise[10];
	char buf[256];
	char *user_id;
	char *real_user_id;
	char date[15];
	char journal_buf[25];

	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int fields;

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
			printf("Please Enter the Date : ");
			scanf("%s",date);
			sprintf(buf,"insert into workout.%s (date) values('%s')",real_user_id,date);
			mysql_query(connect,buf);
			memset(buf,0,sizeof(buf));



			sprintf(buf,"show columns from workout.%s",real_user_id);
			mysql_query(connect,buf);
			memset(buf,0,sizeof(buf));

			myresult = mysql_store_result(connect);
			fields = mysql_num_fields(myresult);

			row = mysql_fetch_row(myresult);//date를 빼주기 위함
			row = mysql_fetch_row(myresult);//comment를 빼주기 위함
			while(row = mysql_fetch_row(myresult))
			{
				printf("%d: %s ",i,row[0]);
				addNode((char *)row[0],i);
				i++;
			}
			printf("\n");

			while(1)
			{
				printf("Select Exercise idx : ");
				scanf("%d",&exercise_idx);

				struct node *temp = findNodebyIdx(exercise_idx);
				if(temp == 0)
				{
					printf("wrong idx \n");
				}

				printf("Write a %s journal : ",temp->exercise);
			 	scanf("%s",journal_buf);
			
				sprintf(buf,"update workout.%s set %s='%s' where date='%s'",real_user_id, temp->exercise, journal_buf, date);
				mysql_query(connect,buf);
				memset(buf,0,sizeof(buf));

				printf(" 1.Continue 2. exit \n");
				printf("Enter : ");
				scanf("%d",&choice_2);

				if(choice_2 == 2)
				{
					break;
				}
				else
				{
					continue;
				}
			}	
			
			memset(date,0,sizeof(date));

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
			head = 0;
			return;
		}
	}
}

void ViewJournal(MYSQL *connect)
{
	int i =0;
	int choice;
	char buf[256];
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int fields;
	char *user_id;
	char *real_user_id;
	char date[15];

	mysql_query(connect,"use workout");

	mysql_query(connect,"select user()");
	myresult = mysql_store_result(connect);
	row = mysql_fetch_row(myresult);
	user_id = (char *)row[0];
	real_user_id = strtok(user_id,"@");
	

	while(1)
	{

		printf("1.Exercise Log List 2.Back \n");
		printf("Enter : ");
		scanf("%d",&choice);

		if(choice ==1)
		{

			printf("==================Log List====================\n");
			//운동목록 가져오기
			if(head == 0)
			{
				sprintf(buf,"show columns from workout.%s",real_user_id);
				mysql_query(connect,buf);
				memset(buf,0,sizeof(buf));
				myresult = mysql_store_result(connect);
				fields = mysql_num_fields(myresult);

				row = mysql_fetch_row(myresult);//date를 빼주기 위함
				row = mysql_fetch_row(myresult);//comment를 빼주기 위함
				while(row = mysql_fetch_row(myresult))
				{
					addNode((char *)row[0],i);
					i++;
				}
			}
		//===============================


	
			sprintf(buf,"select date from %s",real_user_id);
			mysql_query(connect,buf);
			myresult = mysql_store_result(connect);
			memset(buf,0,sizeof(buf));

			while(row = mysql_fetch_row(myresult))
			{
				printf("Date : %s \n",row[0]);
			}

			printf("Please Enter Date you want : ");
			scanf("%s",date);

			
			printf("================Journal==================\n");
			sprintf(buf,"select * from %s where date='%s'",real_user_id, date);
			mysql_query(connect, buf);

			myresult = mysql_store_result(connect);
			row = mysql_fetch_row(myresult);
			fields = mysql_num_fields(myresult);
			struct node *temp = head;

			printf("%s \n",row[0]);

			while(temp != NULL)
			{
				for(i=2;i<fields ; i++)
				{
					if(row[i] != NULL)
					{
						printf(" %s : %s\n",temp->exercise,row[i]);
					}
					temp =temp->next;
				}
			}

		}
		else
		{
			head = 0;
			break;
		}
	}
}

void ViewComment(MYSQL *connect)
{
	int choice;
	char buf[256];
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int fields;
	char *user_id;
	char *real_user_id;
	char date[15];

	mysql_query(connect,"use workout");

	mysql_query(connect,"select user()");
	myresult = mysql_store_result(connect);
	row = mysql_fetch_row(myresult);
	user_id = (char *)row[0];
	real_user_id = strtok(user_id,"@");
	

	while(1)
	{
			
			sprintf(buf,"select date from %s",real_user_id);
			mysql_query(connect,buf);
			myresult = mysql_store_result(connect);
			memset(buf,0,sizeof(buf));

			while(row = mysql_fetch_row(myresult))
			{
				printf("Date : %s \n",row[0]);
			}

			printf("Please Enter Date you want : ");
			scanf("%s",date);

			
			sprintf(buf,"select comment from %s where date='%s'",real_user_id, date);
			mysql_query(connect, buf);

			myresult = mysql_store_result(connect);
			row = mysql_fetch_row(myresult);
			fields = mysql_num_fields(myresult);

			printf("================Comment==================\n");
			printf("Coach Comment : %s \n",row[0]);
			printf("=========================================\n");
			printf("Do you Want view another comment? \n");
			printf("1.Yes 2.No\n");
			scanf("%d",&choice);

			if(choice ==1)
			{
				continue;
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
		printf("1. Create a journal 2.View Journal 3.View Coach Advice 4.exit \n");
		printf("Enter : ");
		scanf("%d",&choice);
		if(choice ==1)
		{
			printf("================Create Journal==================\n");
			CreateJournal(*connect);
		}
		else if(choice ==2)
		{
			printf("=================View Jouranl===================\n");
			ViewJournal(*connect);
		}
		else if(choice ==3)
		{
			printf("=================View Comment===================\n");
			ViewComment(*connect);
		}
		else if(choice ==4)
		{
			return;
		}
		else
		{}
	}
}
