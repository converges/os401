#include <stdio.h>
#include <unistd.h>

int main(void) {
	
	int count =0;

	while(1) {
		printf("%d\n", count++);
		sleep(1);

	}

	return 0;

}
