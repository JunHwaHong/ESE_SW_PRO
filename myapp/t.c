#include <stdio.h>

int main(void) {
	char id[20];
	char pass[20];
	printf("id : ");
	scanf("%s", id);
	printf("password : ");
	scanf("%s", pass);

	printf("id: %s, pass : %s\n",id,pass);

	return 0;
}
