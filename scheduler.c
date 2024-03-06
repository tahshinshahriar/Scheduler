#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10
#define QUANTUM 2

typedef struct
{
    int taskId;
    int burstTime;     // The total execution time required by the task
    int remainingTime; // The remaining execution time for the task
} Task;

Task taskQueue[MAX_TASKS];
int taskCount = 0;

void addTask(Task task)
{
    if (taskCount < MAX_TASKS)
    {
        taskQueue[taskCount++] = task;
    }
    else
    {
        printf("Task queue is full!\n");
    }
}

void roundRobinScheduling()
{
    int time = 0;
    int tasksCompleted = 0;

    while (tasksCompleted < taskCount)
    {
        for (int i = 0; i < taskCount; i++)
        {
            if (taskQueue[i].remainingTime > 0)
            {
                printf("Time %d: Task %d is running\n", time, taskQueue[i].taskId);

                // Execute the task for a time slice (quantum) or until completion
                int executionTime = (taskQueue[i].remainingTime > QUANTUM) ? QUANTUM : taskQueue[i].remainingTime;
                time += executionTime;
                taskQueue[i].remainingTime -= executionTime;

                if (taskQueue[i].remainingTime <= 0)
                {
                    printf("Time %d: Task %d is completed\n", time, taskQueue[i].taskId);
                    tasksCompleted++;
                }
            }
        }
    }

    printf("All tasks completed at time %d\n", time);
}

int main()
{
    // Example tasks
    Task task1 = {1, 5, 5}; // Task 1 with burst time 5
    Task task2 = {2, 3, 3}; // Task 2 with burst time 3
    Task task3 = {3, 8, 8}; // Task 3 with burst time 8

    addTask(task1);
    addTask(task2);
    addTask(task3);

    roundRobinScheduling();

    return 0;
}
