#include <stdio.h>
#include <unistd.h>


int main(void) {

	for (int i=0; i<101; i++) {

		printf("%d\n", i);
		sleep(3);

	}

	return 0;

}
