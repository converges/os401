#include <stdio.h>
#include <unistd.h>

int main(void) {

	int count=0;

	for (int i=0; i<10; i++) {

		printf("%d\n", count++);
		sleep(1);
	}

	return 0;
}
