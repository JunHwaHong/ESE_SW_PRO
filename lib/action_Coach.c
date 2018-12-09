#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "actcoach.h"
#include "/usr/include/mysql/mysql.h"
#define DB_IP "222.121.186.100"
struct node{
	char novice_id[20];
	char date[15];
	struct node *next;

};
struct node *chead = 0;
char ex_novice_id[20];
int choice_novice = 0;
int first = 0;
void add_id_Node(char *id)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	strcpy(new_node->novice_id, id);
	new_node->next = 0;

	if(chead == 0)
	{
		chead = new_node;
		return;
	}
	struct node *temp = chead;
	while(temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

void add_date_Node(char *date)
{
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	strcpy(new_node->date, date);
	new_node->next = 0;

	if(chead == 0)
	{
		chead = new_node;
		return;
	}
	struct node *temp = chead;
	while(temp->next != 0)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

void deleteNode()
{
	struct node *temp = chead;
	while(1)
	{
		if(chead == 0)
		{
			break;
		}
		chead = chead->next;
		free(temp);
		temp = chead;
	}
	return;
}

void showIdNode()
{
	int i = 1;
	struct node *temp = chead;
	printf("============My Novice List==========\n");
	while(1)
	{
		if(temp == 0)
		{
			printf("==================================\n");
			return;
		}
		printf("%d. %s\n", i, temp->novice_id);
		temp = temp->next;
		i++;
	}
}
void showDateNode()
{
	int i = 1;
	struct node *temp = chead;
	printf("============Date List=============\n");
	while(1)
	{
		if(temp == 0)
		{
			printf("==================================\n");
			return;
		}
		printf("%d. %s\n", i, temp->date);
		temp = temp->next;
		i++;
	}
}


void View_My_Novice(MYSQL *connect)
{
	char id_buf[20];
	char name_buf[20];
	char buf[256];
	MYSQL_RES *myresult;
	MYSQL_ROW row;

	mysql_query(connect, "use workout");
	sprintf(buf, "select COACH_NAME from CoachList where COACH_ID='%s'",connect->user);
	mysql_query(connect, buf);
	memset(buf, 0, sizeof(buf));

	myresult = mysql_store_result(connect);
	row = mysql_fetch_row(myresult);
	strcpy(name_buf, row[0]);

	printf("name: %s\n",name_buf);
	mysql_free_result(myresult);
	row = 0;

	mysql_query(connect, "use workout");
	sprintf(buf, "select NOVICE_ID from WhoIsMyCoach where COACH_ID='%s'",name_buf);
	mysql_query(connect, buf);
	memset(buf, 0, sizeof(buf));

	myresult = mysql_store_result(connect);
	while(row = mysql_fetch_row(myresult))
	{
		add_id_Node((char *)row[0]);
	}
	showIdNode();
	return;
}

int View_Novice_date(MYSQL *connect, int choice)
{
	char novice_id[20];
	char buf[256];
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int num = 1;
	struct node *temp = chead;
	if(first == 0)
	{
		first++;
	while(1)
	{
		if(temp == 0)
		{
			return -1;
		}
		if(num == choice)
		{
			strcpy(novice_id, temp->novice_id);
			break;
		}
		temp = temp->next;
		num++;
	}
	
	strcpy(ex_novice_id, novice_id);
	}
	printf("Selected Novice : %s\n", ex_novice_id);
	mysql_query(connect, "use workout");
	sprintf(buf, "select date from %s", ex_novice_id);
	mysql_query(connect, buf);
	myresult = mysql_store_result(connect);
	deleteNode();
	while(row = mysql_fetch_row(myresult))
	{
		add_date_Node((char *)row[0]);
	}
	showDateNode();
	return 0;
}


int View_Novice_List(MYSQL *connect, int choice)
{
	char select_date[15];
	char buf[256];
	int choice_list = 0;
	char comment[50];
	MYSQL_RES *myresult;
	MYSQL_ROW row;
	int fields;
	int num = 1;
	struct node *temp = chead;
	while(1)
	{
		if(temp == 0)
		{
			return -1;
		}
		if(num == choice)
		{
			strcpy(select_date, temp->date);
			break;
		}
		temp = temp->next;
		num++;
	}
	printf("Selected Date : %s\n", select_date);
	
	mysql_query(connect, "use workout");

	sprintf(buf, "show columns from workout.%s", ex_novice_id);
	mysql_query(connect, buf);
	memset(buf, 0, sizeof(buf));
	myresult = mysql_store_result(connect);
	row = mysql_fetch_row(myresult);
	row = mysql_fetch_row(myresult);
	printf("================================\n");
	while(row = mysql_fetch_row(myresult))
	{
		printf("%s\t", row[0]);
	}
	printf("\n");
	printf("--------------------------------\n");

	
	mysql_free_result(myresult);
	row = 0;

	sprintf(buf, "select * from %s where date='%s'",ex_novice_id, select_date );
	mysql_query(connect, buf);
	memset(buf, 0, sizeof(buf));
	myresult = mysql_store_result(connect);
	fields = mysql_num_fields(myresult);

	while(row = mysql_fetch_row(myresult))
	{
		for(int j = 2; j < fields; j++)
		{
			printf("%s\t",row[j]);
		}
	}
	printf("\n");
	printf("================================\n");


	printf("1. Write Comment 2. back to select data 3. Select Novice\n");
	scanf("%d", &choice_list);
	if(choice_list == 1)
	{
		printf("comment : ");
		scanf("%s",comment);
		sprintf(buf, "update workout.%s set comment='%s' where date='%s'", ex_novice_id, comment, select_date);		   mysql_query(connect, buf);
		memset(buf, 0, sizeof(buf));
		memset(comment, 0, sizeof(comment));
	}
	else if(choice_list == 2)
	{
		return 0;
	}
	else if(choice_list == 3)
	{
		return 1;
	}


}


void goCoach(MYSQL **connect)
{
	int choice = 0;
	int status = 0;
	int choice_date = 0;
	char novice_id[20];

	mysql_query(*connect, "use workout");

	printf("===========Welcome Coach==========\n");
	while(1)
	{
		printf("1. Select the Novice to manage\n");
		printf("2. exit\n");

		printf("Enter : ");
		scanf("%d", &choice);
		if(choice == 1)
		{
			View_My_Novice(*connect);
			printf("select the index of Novice : ");
			scanf("%d", &choice_novice);
			while(1)
			{
			if(View_Novice_date(*connect, choice_novice) == -1)
			{
				printf("wrong Novice index\n");
				return;
			}
			printf("select the index of date to show : ");
			scanf("%d", &choice_date);
			status = View_Novice_List(*connect, choice_date);
			if(status == -1)
			{
				printf("wrong date index\n");
				return;

			}
			else if(status == 1)
			{
				break;
			}
			}
			memset(ex_novice_id, 0, sizeof(ex_novice_id));
			deleteNode();
			first = 0;
		}

		else if(choice == 2)
		{
			printf("bye\n");
			return;
		}
	}
	return;
}
	

