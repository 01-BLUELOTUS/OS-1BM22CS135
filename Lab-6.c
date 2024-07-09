#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 100 

int mutex = 1;
int mutex2 = 2; 

int philosophers[MAX_PHILOSOPHERS]; 

void wait(int *sem) {
    while (*sem <= 0); 
    (*sem)--;
}

void signal(int *sem) {
    (*sem)++;
}

void* one_eat_at_a_time(void* arg) {
    int philosopher = ((int) arg);

    wait(&mutex); 
    printf("Philosopher %d is granted to eat\n", philosopher + 1); 
    sleep(1); 
    printf("Philosopher %d has finished eating\n", philosopher + 1);
    signal(&mutex);
    return NULL;
}

void* two_eat_at_a_time(void* arg) {
    int philosopher = ((int) arg);

    wait(&mutex2);
    printf("Philosopher %d is granted to eat\n", philosopher + 1); 
    sleep(1); 
    printf("Philosopher %d has finished eating\n", philosopher + 1);
    signal(&mutex2); 

    return NULL;
}

int main() {
    int N;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &N);

    int hungry_count;
    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    int hungry_philosophers[hungry_count];
    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, N);
        scanf("%d", &hungry_philosophers[i]);
        hungry_philosophers[i]--; 
    }

    pthread_t thread[hungry_count];

    int choice;

    do {
        printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Allow one philosopher to eat at any time\n");
                for (int i = 0; i < hungry_count; i++) {
                    philosophers[i] = hungry_philosophers[i]; 
                    pthread_create(&thread[i], NULL, one_eat_at_a_time, &philosophers[i]);
                }
                for (int i = 0; i < hungry_count; i++) {
                    pthread_join(thread[i], NULL);
                }
                break;
            case 2:
                printf("Allow two philosophers to eat at the same time\n");
                for (int i = 0; i < hungry_count; i++) {
                    philosophers[i] = hungry_philosophers[i]; 
                    pthread_create(&thread[i], NULL, two_eat_at_a_time, &philosophers[i]);
                }
                for (int i = 0; i < hungry_count; i++) {
                    pthread_join(thread[i], NULL);
                }
                break;
            case 3:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
