#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* thread_train(void* i) {
	int train_num = *((int*)i);

	// wait P
	sem_wait(&semaphore);
	printf("Train no.%d has been to pass through the intersection\n", train_num);

	/* Critical Section */
	sleep(4);
	printf("Train no.%d has been passed through the intersection\n", train_num);

	// V
	sem_post(&semaphore);
	free(i);
}

int main(void) {

	sem_init(&semaphore, 0, 1);
	pthread_t t[3];
	int* intPtr;

	for (int i=0; i<3; i++) {
		int train_num = i+1;
		intPtr = (int*)malloc(sizeof(int));
		*intPtr = i+1;
		pthread_create(&t[i], NULL, thread_train, (void*)intPtr);
	}

	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	pthread_join(t[2], NULL);

	sem_destroy(&semaphore);

	return 0;
}
