#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(void) {

	pid_t pid;

	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "FORK Failed\n");
		return 1;
	}
	else if (pid == 0) {
		printf("Child executes wait10\n");
		execlp("./wait10", "wait10", NULL);
		printf("Child completed and terminated\n");
	}
	else {
		printf("Parent waits\n");
		wait(NULL); // If deleted, it may be an orphan-process
		printf("Child completed and parent continued\n");
		printf("Parent do something\n");
		printf("Parent Completed\n");
	}
	
	return 0;
}
