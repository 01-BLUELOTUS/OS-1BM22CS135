#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct
{
    int Ti;
    int Ci;
    int deadline;
    int RT; //Remaining_Time
    int id;
} Task;

void Input(Task tasks[], int *n_tasks)
{
    printf("Enter number of tasks: ");
    scanf("%d", n_tasks);

    for (int i = 0; i < *n_tasks; i++)
    {
        tasks[i].id = i + 1;
        printf("Enter Ti of task %d: ", i + 1);
        scanf("%d", &tasks[i].Ti);
        printf("Enter execution time of task %d: ", i + 1);
        scanf("%d", &tasks[i].Ci);
        tasks[i].deadline = tasks[i].Ti; // In RM, deadline is equal to Ti
        tasks[i].RT = tasks[i].Ci;
    }
}

int compare_by_period(const void *a, const void *b)
{
    return ((Task*)a)->Ti - ((Task*)b)->Ti;
}

void RMS(Task tasks[], int n_tasks, int time_frame)
{
    qsort(tasks, n_tasks, sizeof(Task), compare_by_period);

    printf("\nRate-Monotonic Scheduling:\n");
    for (int time = 0; time < time_frame; time++)
    {
        int s_task = -1;
        for (int i = 0; i < n_tasks; i++)
        {
            if (time % tasks[i].Ti == 0)
            {
                tasks[i].RT = tasks[i].Ci;
            }
            if (tasks[i].RT > 0 && (s_task == -1 || tasks[i].Ti < tasks[s_task].Ti))
            {
                s_task = i;
            }
        }

        if (s_task != -1)
        {
            printf("Time %d: Task %d\n", time, tasks[s_task].id);
            tasks[s_task].RT--;
        } else
        {
            printf("Time %d: Idle\n", time);
        }
    }
}

int main()
{
    Task tasks[MAX_TASKS];
    int n_tasks;
    int time_frame;

    Input(tasks, &n_tasks);

    printf("Enter time frame for simulation: ");
    scanf("%d", &time_frame);

    RMS(tasks, n_tasks, time_frame);

    return 0;
}
