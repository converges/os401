#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void* block(void* block);

sem_t sem[4];

int main() {

    for (int i=0; i<4; i++) {
        sem_init(&sem[i], 0, 1);
    }

    pthread_t car[4][3];
    // 0: go down, 1: go right, 2: go up, 3: go left

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {

            if (i==0) {
                // block2 -> block3
                pthread_create(&car[i][j], NULL, block, (void *) 2);
                pthread_create(&car[i][j], NULL, block, (void *) 3);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
            }
            else if (i==1) {
                // block2 -> block 3 -> block 4
                pthread_create(&car[i][j], NULL, block, (void *) 2);
                pthread_create(&car[i][j], NULL, block, (void *) 3);
                pthread_create(&car[i][j], NULL, block, (void *) 4);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
            }
            else if (i==2) {
                // block 4 -> block 1
                pthread_create(&car[i][j], NULL, block, (void *) 4);
                pthread_create(&car[i][j], NULL, block, (void *) 1);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
            }
            else if (i==3) {
                // block 4 -> block 1 -> block 2
                pthread_create(&car[i][j], NULL, block, (void *) 4);
                pthread_create(&car[i][j], NULL, block, (void *) 1);
                pthread_create(&car[i][j], NULL, block, (void *) 2);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
                pthread_join(car[i][j], NULL);
            }
        }
    }
    
    for (int i=0; i<4; i++) {
        sem_destroy(&sem[i]);
    }

}

/* block
 * 2 | 1
 * -----
 * 3 | 4
 */

void* block(void* block) {

    int block_num = *((int *)block);

    // wait P
    sem_wait(&sem[block_num]);
    printf("BLOCK %d has been locked\n", block_num);

    // critical section
    sleep(1);
    printf("BLOCK %d has been released\n", block_num);

    // V
    sem_post(&sem[block_num]);
    free(block);
}

