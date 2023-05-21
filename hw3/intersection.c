/* May 21, 2023
 * OS 401
 * Homework 3
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3

void* thread_go_north(void* i);
void* thread_go_south(void* i);
void* thread_go_east(void* i);
void* thread_go_west(void* i);


sem_t sem[4];
bool block_available[4] = {true, true, true, true};
/*
 1 | 0
 -----
 2 | 3
 */

int main(void) {

    for (int i=0; i<4; i++) {
        sem_init(&sem[i], 0, 1);
    }

	pthread_t car_thread[4][3];
    /* FIRST INDEX: EAST 0, WEST 1, SOUTH 2, NORTH 3
     * SECOND INDEX: 0, 1, 2 -th car from each direction
     */

    for (int i=0; i<3; i++) {
        int* intPtr = (int*)malloc(sizeof(int));
        *intPtr = i+1;
        pthread_create(&car_thread[0][i], NULL, thread_go_east, (void*)intPtr);

        intPtr = (int*)malloc(sizeof(int));
        *intPtr = i+1;
        pthread_create(&car_thread[1][i], NULL, thread_go_west, (void*)intPtr);

        intPtr = (int*)malloc(sizeof(int));
        *intPtr = i+1;
        pthread_create(&car_thread[2][i], NULL, thread_go_south, (void*)intPtr);

        intPtr = (int*)malloc(sizeof(int));
        *intPtr = i+1;
        pthread_create(&car_thread[3][i], NULL, thread_go_north, (void*)intPtr);
    }

    for (int i=0; i<3; i++) {
        pthread_join(car_thread[0][i], NULL);
        pthread_join(car_thread[1][i], NULL);
        pthread_join(car_thread[2][i], NULL);
        pthread_join(car_thread[3][i], NULL);
    }

    for (int i=0; i<4; i++) {
        sem_destroy(&sem[i]);
    }

    return 0;
}


void* thread_go_north(void* i) {
	int train_num = *((int*)i);

    while (!block_available[0] || !block_available[3]) {
        sleep(0.5);
    }

    // Block: 3 -> 0
    sem_wait(&sem[3]);
    printf("BLOCK 3: Car %d to North has passed\n", train_num);
    sem_wait(&sem[0]);
    printf("BLOCK 0: Car %d to North has passed\n", train_num);

    sleep(1);

    sem_post(&sem[0]);
    sem_post(&sem[3]);
    printf("BLOCK 3 -> 0: Car %d has been passed through the intersection\n", train_num);


    free(i);
    pthread_exit(NULL);
}

void* thread_go_south(void* i) {
	int train_num = *((int*)i);

    // Block 1 -> 2
    sem_wait(&sem[1]);
    printf("BLOCK 1: Car %d to South has passed\n", train_num);
    sem_wait(&sem[2]);
    printf("BLOCK 2: Car %d to South has passed\n", train_num);

    sleep(1);

    sem_post(&sem[1]);
    sem_post(&sem[2]);
    printf("BLOCK 1 -> 2: Car %d has been passed through the intersection\n", train_num);

    free(i);
    pthread_exit(NULL);
}

void* thread_go_east(void* i) {
    int train_num = *((int*)i);

    // Block 1 -> 2 -> 3
    sem_wait(&sem[1]);
    printf("BLOCK 1: Car %d to East has passed\n", train_num);
    sem_wait(&sem[2]);
    printf("BLOCK 2: Car %d to East has passed\n", train_num);
    sem_wait(&sem[3]);
    printf("BLOCK 3: Car %d to East has passed\n", train_num);

    sleep(1);

    sem_post(&sem[1]);
    sem_post(&sem[2]);
    sem_post(&sem[3]);
    printf("BLOCK 1 -> 2 -> 3: Car %d has been passed through the intersection\n", train_num);

    free(i);
    pthread_exit(NULL);
}

void* thread_go_west(void* i) {
    int train_num = *((int*)i);

    // Block 3 -> 0 -> 1
    sem_wait(&sem[3]);
    printf("BLOCK 3: Car %d to West has passed\n", train_num);
    sem_wait(&sem[0]);
    printf("BLOCK 0: Car %d to West has passed\n", train_num);
    sem_wait(&sem[1]);
    printf("BLOCK 1: Car %d to West has passed\n", train_num);

    sleep(1);

    sem_post(&sem[3]);
    sem_post(&sem[0]);
    sem_post(&sem[1]);
    printf("BLOCK 3 -> 0 -> 1: Car %d has been passed through the intersection\n", train_num);

    free(i);
    pthread_exit(NULL);
}
