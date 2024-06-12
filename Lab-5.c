#include <stdlib.h>
#include <stdio.h>

#define BufferSize 10

int buffer[BufferSize];
int in = 0, out = 0;

int maxP, maxC;
int empty = BufferSize, full = 0, mutex = 1;

void wait(int *S)
{
    while (*S <= 0);
    (*S)--;
}

void signal(int *S)
 {
    (*S)++;
}

void producer()
{
    int pItems = 0;
    while (pItems < maxP)
    {
        int item = rand();
        wait(&empty);
        wait(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d at %d\n", item, in);
        in = (in + 1) % BufferSize;
        signal(&mutex);
        signal(&full);
        pItems++;
    }
}

void consumer()
{
    int cItems = 0;
    while (cItems < maxC)
    {
        wait(&full);
        wait(&mutex);
        int item = buffer[out];
        printf("Consumer consumed item %d from %d\n", item, out);
        out = (out + 1) % BufferSize;
        signal(&mutex);
        signal(&empty);
        cItems++;
    }
}

int main()
{
    int numPs, numCs;
    printf("Enter number of producers: ");
    scanf("%d", &numPs);
    printf("Enter number of consumers: ");
    scanf("%d", &numCs);

    printf("Enter maximum items each producer can produce: ");
    scanf("%d", &maxP);

    printf("Enter maximum items each consumer can consume: ");
    scanf("%d", &maxC);
    for(int i=1;i<=numPs;i++)
    {
        producer();
    }
    for(int i=1;i<=numCs;i++)
    {
        consumer();
    }


    return 0;
}






/*
Using Thread

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

#define BufferSize 5

sem_t empty, full, mutex;
int buffer[BufferSize];
int in = 0, out = 0;

int maxP, maxC;

void *producer(void *pno) {
    int pItems = 0;
    while (pItems < maxP) {
        int item = rand();
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer produced item %d at %d\n", item, in);
        in = (in + 1) % BufferSize;
        sem_post(&mutex);
        sem_post(&full);
        pItems++;
    }
    return NULL;
}

void *consumer(void *cno) {
    int cItems = 0;
    while (cItems < maxC) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("Consumer consumed item %d from %d\n", item, out);
        out = (out + 1) % BufferSize;
        sem_post(&mutex);
        sem_post(&empty);
        cItems++;
    }
    return NULL;
}

int main() {
    int numPs, numCs;
    printf("Enter number of producers: ");
    scanf("%d", &numPs);
    printf("Enter number of consumers: ");
    scanf("%d", &numCs);

    printf("Enter maximum items each producer can produce: ");
    scanf("%d", &maxP);

    printf("Enter maximum items each consumer can consume: ");
    scanf("%d", &maxC);

    pthread_t pro[numPs], con[numCs];
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < numPs; i++)
        pthread_create(&pro[i], NULL, producer, NULL);
    for (int i = 0; i < numCs; i++)
        pthread_create(&con[i], NULL, consumer, NULL);
    for (int i = 0; i < numPs; i++)
        pthread_join(pro[i], NULL);
    for (int i = 0; i < numCs; i++)
        pthread_join(con[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
*/
