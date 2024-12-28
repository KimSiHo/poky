#include <stdio.h>
#include <unistd.h>

int main(){
	int i = 0;
	while (i < 10) {
		printf("Hello world!\n");
		sleep(1);
	}

	return 0;
}

