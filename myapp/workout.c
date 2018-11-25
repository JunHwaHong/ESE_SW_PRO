
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include <string.h>



int main(void)
{
  
  int choice = 0;
  char your_id[20] = "\0";
  char your_pw[20] = "\0";
  printf("환영합니다 \n");
  printf("Workout Program for Novice\n");
 
  printf("1. 로그인   2. 가입하기  \n");
  scanf("%d",&choice);
     fgets(your_id,sizeof(your_id),stdin);//왜 넣어야 되는지 모르겠음
   if(choice == 1)
  {
     //로그인 하는 경우...
     printf("Enter your ID : ");
     fgets(your_id,sizeof(your_id),stdin);
     printf("Enter your PW : ");
     fgets(your_pw,sizeof(your_pw),stdin);

     puts(your_id);
     puts(your_pw);
   }
  else
  {
     char buf[256] = "\0";	 
     //회원가입하는 경우...
     MYSQL *conn = mysql_init(NULL);
     if( conn == NULL)
     {
        fprintf(stderr, "%s\n",mysql_error(conn));
	exit(1);
     }  
 
     if( mysql_real_connect(conn,"222.121.186.100","test","1234",NULL,2222,NULL,0) == NULL)
     {
        fprintf(stderr, "%s\n",mysql_error(conn));
	mysql_close(conn);
	exit(1);
     }
     printf("Enter your ID : ");
     fgets(your_id,sizeof(your_id),stdin);
     your_id[strlen(your_id)-1] = '\0';
     printf("Enter your PW : ");
     fgets(your_pw,sizeof(your_pw),stdin);
     your_pw[strlen(your_pw)-1] = '\0';
     
     sprintf(buf,"create user '%s'@'%s' identified by '%s'",your_id,"%",your_pw);

    if( mysql_query(conn,buf))
    {
	fprintf(stderr,"%s \n",mysql_error(conn));
	mysql_close(conn);
	
    }
     mysql_close(conn);
    
    
  }

  return 0;
}
