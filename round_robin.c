#include <stdio.h>
#include <stdbool.h>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};
void calculateTimes(struct Process p[], int n, int time_quantum)
{
    int current_time = 0;
    int completed_processes = 0;
    int front = 0, rear = -1;
    int queue[100];
    bool in_queue[n];
    for (int i = 0; i < n; i++)
    {
        in_queue[i] = false;
        p[i].remaining_time = p[i].burst_time;
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival_time <= current_time && !in_queue[i])
        {
            rear++;
            queue[rear] = i;
            in_queue[i] = true;
        }
    }
    while (completed_processes < n)
    {
        // If no process is in the queue, jump to the next arrival time
        if (front > rear)
        {
            current_time++;
            for (int i = 0; i < n; i++)
            {
                if (!in_queue[i] && p[i].arrival_time <= current_time)
                {
                    rear++;
                    queue[rear] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int current_index = queue[front];
        front++;

        int exec_time = (p[current_index].remaining_time < time_quantum) ? p[current_index].remaining_time : time_quantum;

        p[current_index].remaining_time -= exec_time;
        current_time += exec_time;

        // Add any newly arrived processes to the queue
        for (int i = 0; i < n; i++)
        {
            if (!in_queue[i] && p[i].arrival_time <= current_time)
            {
                rear++;
                queue[rear] = i;
                in_queue[i] = true;
            }
        }

        // If process completed
        if (p[current_index].remaining_time == 0)
        {
            completed_processes++;
            p[current_index].completion_time = current_time;
            p[current_index].turnaround_time = p[current_index].completion_time - p[current_index].arrival_time;
            p[current_index].waiting_time = p[current_index].turnaround_time - p[current_index].burst_time;
        }
        else
        {
            // Re-add to the end of the queue
            rear++;
            queue[rear] = current_index;
        }
    }
}

int main()
{
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &p[i].arrival_time);
        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &p[i].burst_time);
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    calculateTimes(p, n, time_quantum);

    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
};
