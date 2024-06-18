#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // for sleep function
#include <semaphore.h>

pthread_t *P;
pthread_mutex_t *CS;
int num_Ps, num_Cs;

void dine(int n);

int main()
{
  int i, status_message;
  void *msg;

  printf("Enter the number of philosophers: ");
  scanf("%d", &num_Ps);
  num_Cs = num_Ps; 
  P = (pthread_t *)malloc(num_Ps * sizeof(pthread_t));
  CS = (pthread_mutex_t *)malloc(num_Cs * sizeof(pthread_mutex_t));

  for (i = 0; i < num_Cs; i++)
  {
    status_message = pthread_mutex_init(&CS[i], NULL);
    if (status_message != 0)
    {
      printf("\n Mutex initialization failed");
      exit(1);
    }
  }

  for (i = 0; i < num_Ps; i++)
  {
    status_message = pthread_create(&P[i], NULL, (void *)dine, (void *)(intptr_t)(i + 1));
    if (status_message != 0)
    {
      printf("\n Thread creation error \n");
      exit(1);
    }
  }

  for (i = 0; i < num_Ps; i++)
  {
    status_message = pthread_join(P[i], &msg);
    if (status_message != 0)
    {
      printf("\n Thread join failed \n");
      exit(1);
    }
  }

  for (i = 0; i < num_Cs; i++)
  {
    status_message = pthread_mutex_destroy(&CS[i]);
    if (status_message != 0)
    {
      printf("\n Mutex Destroyed \n");
      exit(1);
    }
  }

  free(P);
  free(CS);

  return 0;
}

void dine(int n)
{
  printf("\nPhilosopher %d is thinking ", n);

  pthread_mutex_lock(&CS[n - 1]); 
  pthread_mutex_lock(&CS[n % num_Cs]); 

  printf("\nPhilosopher %d is eating ", n);
  sleep(3); 

  pthread_mutex_unlock(&CS[n - 1]); 
  pthread_mutex_unlock(&CS[n % num_Cs]); 
  
  printf("\nPhilosopher %d Finished eating ", n);
}
