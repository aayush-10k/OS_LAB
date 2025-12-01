#include <stdio.h>
struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void SJF(struct Process p[], int n)
{
    int current_time = 0, completed = 0;
    int burst_remaining[n];

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    // Copy burst times
    for (int i = 0; i < n; i++)
        burst_remaining[i] = p[i].burst_time;

    while (completed < n)
    {
        int idx = -1, min_bt = 99999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && burst_remaining[i] > 0)
            {
                if (burst_remaining[i] < min_bt)
                {
                    min_bt = burst_remaining[i];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        { // No process has arrived yet
            current_time++;
            continue;
        }

        
        p[idx].completion_time =current_time + burst_remaining[idx];
        burst_remaining[idx] = 0;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
        current_time=p[idx].completion_time;

        completed++;
    }

    float total_wait = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

        total_wait += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time = %.2f", total_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time & Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    SJF(p, n);

    return 0;
}
