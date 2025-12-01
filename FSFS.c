 #include <stdio.h>
 
 struct Process 
 {
    int pid;
    int arrival_time;
    int turnaround_time;
    int waiting_time;
    int completion_time;
    int burst_time;
 };

 void SortByArrivalTime( struct Process p[],int n)
 {
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrival_time>p[j+1].arrival_time)
            {
                struct Process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
 }

 int main()
 {
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct Process p[n];
    for(int i=0;i<n;i++)
    {
        p[i].pid=i;
        printf("Enter Arrival Time of Process %d : ",i+1);
        scanf("%d",&p[i].arrival_time);
        printf("Enter Burst Time of Process %d : ",i+1);
        scanf("%d",&p[i].burst_time);
    }

    SortByArrivalTime(p,n);

    int current_time=0;
    float total_waiting_time=0;
    float total_turnaround_time=0;

    
    for(int i=0;i<n;i++)
    {
        if(current_time<p[i].arrival_time)
        {
            current_time=p[i].arrival_time;
        }
        p[i].completion_time=current_time+p[i].burst_time;
        p[i].turnaround_time=p[i].completion_time-p[i].arrival_time;
        p[i].waiting_time=p[i].turnaround_time-p[i].burst_time;

        total_turnaround_time+=p[i].turnaround_time;
        total_waiting_time+=p[i].waiting_time;
        current_time=p[i].completion_time;
    }
    printf("\n Result");
    printf("Pid \t Arrival Time \t Burst Time \t Completion Time \t Turnaround Time \t Waiting Time\n");
    for(int i=0;i<n;i++)
    {
        printf("%d \t %d \t\t %d \t\t %d \t\t\t %d \t\t %d \n",p[i].pid,p[i].arrival_time,
            p[i].burst_time,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }

    printf("Average Waiting Time: %f\n",total_waiting_time/n);
    printf("Average Turnaound Time: %f\n",total_turnaround_time/n);
    return 0;
 }
 