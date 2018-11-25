
#include <stdio.h>

int main(void)  {
	int select_menu=0;
	//connect_db_server();
	// if connected
	while(1) {
		printf("1. show my info\n");
		printf("2. insert my info\n");
		printf("3. quit\n");

		scanf("%d", &select_menu);
		switch(select_menu) {
			case 1:
				//showMyInfo();
				printf("select menu 1\n");
				break;
			case 2:
				//insertMyInfo();
				printf("select menu 2\n");
				break;
			case 3:
				printf("select menu 3\n");
				return 0;
				break;
			default:
				printf("Wrong menu number\n");
				break;

		}
	}


	return 0;
}
