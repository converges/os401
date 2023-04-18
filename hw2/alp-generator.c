#include <stdio.h>
#include <unistd.h>


int main(void) {

	char letter = 'A';


	for (int i=0; i<26; i++) {

		printf("%c\n", letter);
		sleep(5);

	}

	return 0;

}
