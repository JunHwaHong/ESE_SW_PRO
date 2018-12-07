#ifndef ACTNOVICE_H
#define ACTNOVICE_H
#include "/usr/include/mysql/mysql.h"
void ViewJournal(MYSQL *connect);
void goNovice(MYSQL **connect);
void CreateJournal(MYSQL *connect);
#endif
