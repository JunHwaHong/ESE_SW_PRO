#ifndef ACTDB_H
#define ACTDB_H
#include "/usr/include/mysql/mysql.h"


int connect_db_server(MYSQL **connect, char *DB_NAME, char *DB_PASS);
int access_login(MYSQL **connect);
int access_make_account(MYSQL **connect);

#endif
