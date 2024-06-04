#include <stdio.h>

typedef struct
{
  char name[5];
  int T;
} Task;

int main()
{
  int n;
  float total_T = 0.0;

  printf("Enter the number of Processes: ");
  scanf("%d", &n);

  Task p[n];

  for (int i = 0; i < n; i++)
{
    printf("\nProcess %d:\n", i + 1);
    sprintf(p[i].name, "p%d", i + 1);
    printf("Ticket: ");
    scanf("%d", &p[i].T);
    total_T += p[i].T;
  }

  for (int i = 0; i < n; i++)
{
    printf("\nThe Process: %s gets %0.3f%% of Processor Time.\n", p[i].name, ((p[i].T / total_T) * 100));
  }

  return 0;
}
