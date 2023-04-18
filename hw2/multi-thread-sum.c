#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int sum = 0;

struct NumberRange {
	int start;
	int end;
	int result;
};

void* runner(void* numbers);


int main(void) {

	pthread_t tid[5]; // Thread IDs

	struct NumberRange range[5] = {{1, 200},{201, 400}, {401, 600}, {601, 800}, {801, 1000}};

	for (int i=0; i<5; i++) {
		pthread_create(&tid[i], NULL, runner, (void *) &range[i]);
	}	

	
	for (int j=0; j<5; j++) {
		pthread_join(tid[j], NULL);
		sum += range[j].result;
	}

	printf("sum = %d\n", sum);

	return 0;

}

void* runner(void* numbers) {

	struct NumberRange *range = (struct NumberRange *) numbers;
	int start = range->start;
	int end = range->end;
	int sum = 0;

	printf("start: %d, end: %d", start, end);

	for (int i=start; i<=end; i++) {
		sum += i;
		usleep(100000);
	}
	
	range->result = sum;

	pthread_exit(0);

}



