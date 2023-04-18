#include <stdio.h>
#include <unistd.h>


int main(void) {

	char at = '@';

	while (1) {

		printf("%c\n", at);
		sleep(7);

	}

	return 0;

}
