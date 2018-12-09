#ifndef ACTCOACH_H
#define ACTCOACH_H
#include "/usr/include/mysql/mysql.h"

void add_id_Node(char *id);
void add_date_Node(char *date);
void deleteNode();
void showIdNode();
void showDateNode();
void View_My_Novice(MYSQL *connect);
int View_Novice_date(MYSQL *connect,int choice);
int View_Novice_List(MYSQL *connect, int choice);
void goCoach(MYSQL **connect);




#endif
