/* May 21, 2023
 * OS 401
 * Homework 3
 * Woohyuk An, Mathematics, 201902097
 */

#include <stdio.h>
#include <stdlib.h>
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
        int train_num = i+1;
        int* intPtr = (int*)malloc(sizeof(int));
        *intPtr = i+1;
        pthread_create(&car_thread[0][i], NULL, thread_go_east, (void*)intPtr);
        pthread_create(&car_thread[1][i], NULL, thread_go_west, (void*)intPtr);
        pthread_create(&car_thread[2][i], NULL, thread_go_south, (void*)intPtr);
        pthread_create(&car_thread[3][i], NULL, thread_go_north, (void*)intPtr);
    }

    for (int i=0; i<4; i++) {
        pthread_join(car_thread[0][i], NULL);
        pthread_join(car_thread[1][i], NULL);
        pthread_join(car_thread[2][i], NULL);
        pthread_join(car_thread[3][i], NULL);
    }

	sem_destroy(&sem[0]);
	sem_destroy(&sem[1]);
	sem_destroy(&sem[2]);
	sem_destroy(&sem[3]);

	return 0;
}


void* thread_go_north(void* i) {
	int train_num = *((int*)i);

    // Block: 3 -> 0
    sem_wait(&sem[3]);
    sem_wait(&sem[0]);

    printf("A car from south no.%d has been to pass through the intersection\n", train_num);

    /* Critical Section */
    sleep(1);
    printf("A car from south no.%d has been passed through the intersection\n", train_num);

    sem_post(&sem[0]);
    sem_post(&sem[3]);

    free(i);
}

void* thread_go_south(void* i) {
	int train_num = *((int*)i);

    // Block 1 -> 2
    sem_wait(&sem[1]);
    sem_wait(&sem[2]);

    printf("A car from north no.%d has been to pass through the intersection\n", train_num);

    /* Critical Section */
    sleep(1);
    printf("A car from north no.%d has been passed through the intersection\n", train_num);

    sem_post(&sem[1]);
    sem_post(&sem[2]);

    free(i);
}

void* thread_go_east(void* i) {
    int train_num = *((int*)i);

    // Block 1 -> 2 -> 3
    sem_wait(&sem[1]);
    sem_wait(&sem[2]);
    sem_wait(&sem[3]);

    printf("A car from North no.%d has turned left passing through the intersection\n", train_num);

    /* Critical Section */
    sleep(1);
    printf("A car from North no.%d has been turned left passing through the intersection\n", train_num);

    sem_post(&sem[1]);
    sem_post(&sem[2]);
    sem_post(&sem[3]);

    free(i);
}

void* thread_go_west(void* i) {
    int train_num = *((int*)i);

    // Block 3 -> 0 -> 1
    sem_wait(&sem[3]);
    sem_wait(&sem[0]);
    sem_wait(&sem[1]);

    printf("A car from South no.%d has turned left passing through the intersection\n", train_num);

    /* Critical Section */
    sleep(1);
    printf("A car from South no.%d has been turned left passing through the intersection\n", train_num);

    sem_post(&sem[3]);
    sem_post(&sem[0]);
    sem_post(&sem[1]);

    free(i);
}

void* thread_go_east(void* i) {
    int train_num = *((int*)i);

    // Block 1 -> 2 -> 3
    sem_wait(&sem[1]);
    sem_wait(&sem[2]);
    sem_wait(&sem[3]);

    printf("A car from North no.%d has turned left passing through the intersection\n", train_num);

    /* Critical Section */
    sleep(1);
    printf("A car from North no.%d has been turned left passing through the intersection\n", train_num);

    sem_post(&sem[1]);
    sem_post(&sem[2]);
    sem_post(&sem[3]);

    free(i);
}