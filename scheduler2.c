#include <stdio.h>

typedef struct
{
    int p_id;
    int a_t;   // arrival time
    int b_t;   // burst time
    int c_t;   // completion time
    int t_a_t; // turn around time
    int w_t;   // waiting time
    int is_completed;
    int remaining_t;
    int priority;

} Process;

void sortByArrival(Process p[], int n)
{

    Process temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (p[j].a_t > p[j + 1].a_t)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void FCFS(Process p[], int n)
{

    int timeline[200];
    int time_idx = 0;
    int current_time = 0;
    float a_wt = 0;  // average waiting time
    float a_tat = 0; // average turn around time

    

    printf("\n\n\t\tFCFS METHOD OF CPU SCHEDULING IS RUNNING \n\n");

    printf("\n PROCESS NO. \t ARRIVAL_TIME \t BURST_TIME \t COMPLETITION_TIME \t TURNAROUND_TIME \t WAITING_TIME\n");

    for (int i = 0; i < n; i++)
    {

        if (p[i].a_t > current_time)
        {
            current_time = p[i].a_t;
        }

        timeline[time_idx] = current_time;

        p[i].w_t = 0;
        p[i].t_a_t = 0;

        current_time = current_time + p[i].b_t;

        p[i].c_t = current_time;
        p[i].t_a_t = p[i].c_t - p[i].a_t;
        p[i].w_t = p[i].t_a_t - p[i].b_t;
        a_wt = a_wt + p[i].w_t;
        a_tat = a_tat + p[i].t_a_t;

        printf(" P%d  \t\t %d  \t\t %d \t\t %d  \t\t\t %d \t\t\t %d\n", p[i].p_id, p[i].a_t, p[i].b_t, p[i].c_t, p[i].t_a_t, p[i].w_t);

        time_idx++;
    }
    printf("\n [FCFS GANTT CHART] ---------\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("|");
        printf("  P%d  ", p[i].p_id);
    }
    printf("|");
    timeline[time_idx] = current_time;

    printf("\n");

    // printing timeline below ganttchart
    for (int i = 0; i <= time_idx; i++)
    {
        printf("%d", timeline[i]);
        printf("      ");
    }

    a_wt = a_wt / n;
    a_tat = a_tat / n;

    printf("\n\n");
    printf("\n Average Waiting Time = %.3f ", a_wt);
    printf("\n Average Turn Around Time = %.3f \n", a_tat);

    for(int i=0; i<17; i++) printf("-------");
        printf("\n");
}

void s_j_f(Process p[], int n){
    printf("\n\n\t SJF METHOD OF CPU SCHEDULING IS RUNNING \n\n");
//  int n;
//     printf("Enter desired number of processes: ");
//     scanf("%d",&n);
//     Process p[n];//creating array for storing all the processess
    
    int gantt_p[100]; // To store the sequence of process IDs
    int gantt_t[100]; // To store the timeline points
    int g_idx = 0;    // Counter for the chart

    gantt_t[0] = 0; // The chart starts at time 0

    // for(int i=0;i<n;i++){
    //     p[i].p_id= i+1;
    //     printf("Enter Arrival time for P%d: ",i+1);
    //     scanf("%d",&p[i].a_t);
    //     printf("Enter Burst time for P%d: ",i+1);
    //     scanf("%d",&p[i].b_t);
    //     p[i].is_completed=0;
    // }
    int completed=0;
    int current_time=0;
    float total_wt=0;
    float total_tat=0;
    while(completed!=n){
        int idx=-1;
        int min_burst=99999;

        for(int i=0;i<n;i++){
            if(p[i].a_t<=current_time && p[i].is_completed==0){
                if(p[i].b_t<min_burst){
                min_burst=p[i].b_t;
                idx=i;
            }
            }
        }
    
    if(idx!=-1){
        current_time+=p[idx].b_t;
        p[idx].c_t= current_time;                         //updating all parameters
        p[idx].t_a_t= p[idx].c_t-p[idx].a_t;
        p[idx].w_t= p[idx].t_a_t-p[idx].b_t;

        p[idx].is_completed=1;                       
        completed++;
        total_tat+=p[idx].t_a_t;
        total_wt+=p[idx].w_t;
        
        gantt_p[g_idx] = p[idx].p_id;
        gantt_t[g_idx + 1] = current_time;               //storing all values for gantt table
        g_idx++;
    }
    else{
        current_time++;
    }
}
        printf("\n%-18s %-18s %-18s %-18s %-18s %-18s\n", 
                "Process_ID", "Arrival_Time", "Burst_Time", "Completion_Time", "Turnaround_Time", "Waiting_Time");


        for(int i = 0; i < n; i++) {
            printf("%-18d %-18d %-18d %-18d %-18d %-18d\n",                                         //printing the table for SJF 
                    p[i].p_id, p[i].a_t, p[i].b_t, p[i].c_t, p[i].t_a_t, p[i].w_t);
}
        printf("\nAverage Waiting time: %.2f",total_wt/n);
        printf("\nAverage Turnaround Time: %.2f",total_tat/n);

        printf("\n\n--- GANTT CHART(for SFJ) ---\n\n ");
        // Print the top bar
        for(int i=0; i<g_idx; i++) printf("-------");                          //printing Gantt table
        printf("\n|");
        
        // Print the Process IDs
        for(int i=0; i<g_idx; i++) {
            printf("  P%d  |", gantt_p[i]);
        }
        
        printf("\n ");
        // Print the bottom bar
        for(int i=0; i<g_idx; i++) printf("-------");
        printf("\n");
        
        // Print the time points
        for(int i=0; i<=g_idx; i++) {
            printf("%d      ", gantt_t[i]);
        }
        printf("\n");
        for(int i=0; i<17; i++) printf("-------");
        printf("\n");
}

void round_robin(Process p[], int n, int tq)
{
    printf("\n\n\t ROUND ROBIN METHOD IS RUNNING (TQ=%d)\n", tq);
    int gantt_p[200], gantt_t[200], g_idx = 0;
    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) p[i].remaining_t = p[i].b_t;

    gantt_t[0] = 0;

    while (completed < n)
    {
        int executed = 0;
        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining_t > 0 && p[i].a_t <= current_time)
            {
                executed = 1;
                gantt_p[g_idx] = p[i].p_id;
                gantt_t[g_idx] = current_time;

                if (p[i].remaining_t > tq)
                {
                    current_time += tq;
                    p[i].remaining_t -= tq;
                }
                else
                {
                    current_time += p[i].remaining_t;
                    p[i].remaining_t = 0;
                    p[i].c_t = current_time;
                    p[i].t_a_t = p[i].c_t - p[i].a_t;
                    p[i].w_t = p[i].t_a_t - p[i].b_t;
                    completed++;
                    total_tat += p[i].t_a_t;
                    total_wt += p[i].w_t;
                }
                gantt_t[g_idx + 1] = current_time;
                g_idx++;
            }
        }
        if (!executed) current_time++;
    }

    printf("\n PROCESS_ID \t ARRIVAL_TIME \t BURST_TIME \t COMPLETION_TIME \t TURNAROUND_TIME \t WAITING_TIME\n");
    for (int i = 0; i < n; i++)
        printf(" P%d \t\t %d \t\t  %d  \t\t %d  \t\t\t %d  \t\t\t %d\n", p[i].p_id, p[i].a_t, p[i].b_t, p[i].c_t, p[i].t_a_t, p[i].w_t);

    printf("\n GANTT CHART (FOR ROUND ROBIN METHOD)\n\n |");
    for (int i = 0; i < g_idx; i++) printf(" P%d |", gantt_p[i]);
    printf("\n");

    for (int i = 0; i <= g_idx; i++) printf(" %d   ", gantt_t[i]);
    printf("\n\n Average Waiting Time = %.2f \nAverage Turn Around Time = %.2f\n", total_wt / n, total_tat / n);
    for(int i=0; i<17; i++) printf("-------");
        printf("\n");
}


void multi_level_scheduling(Process p[], int n, int tq){
    printf("\n\t\tMulti Level Scheduling is running.\n\n");
    printf("Level 1: Highest Priority (Priority>6) : Round Robin\n");
    printf("Level 2: Medium Priority (6>Priority>4) : SJF\n");
    printf("Level 3: Lowest Priority (Priority<4) : FCFS\n\n");

    
    int current_time =0;
    int total_wt = 0;
    int total_tat = 0;
    int completed = 0;
    
    for (int i = 0; i < n; i++)
    {
        p[i].remaining_t = p[i].b_t;
        p[i].is_completed = 0;
    }
    
    printf("%-10s %-15s %-10s %-10s %-15s\n", "PID", "Queue", "AT", "BT", "Completion");

    while(completed<n){

        int executed = 0;

        // Highest Priority: RR
        for (int i = 0; i < n; i++)
        {
            if(p[i].priority >=7 && p[i].remaining_t >0 && p[i].a_t <= current_time){

                executed = 1;

                if(p[i].remaining_t > tq){

                    p[i].remaining_t = p[i].remaining_t - tq;
                    current_time = current_time + tq;
                }
                else{
                    
                    current_time = current_time + p[i].remaining_t;
                    p[i].remaining_t = 0;
                    p[i].is_completed = 1;
                    p[i].c_t = current_time;

                    printf("P%-9d Level-1 (RR)   %-11d %-11d %-16d \n", p[i].p_id, p[i].a_t, p[i].b_t, p[i].c_t);
                    completed++;                    
                }
                break; // so that it doesnt go to next priority without completing this priority tasks
            }
        }

            if(executed == 0){
                // Mid level priority
                
                
                int min_bt = 99999;
                int idx = -1;
                
                for (int i = 0; i < n; i++)
                {
                    if((p[i].priority <7 && p[i].priority >=4) && p[i].remaining_t >0 && p[i].a_t <= current_time){                  
                        if(p[i].b_t< min_bt){
                            min_bt = p[i].b_t;
                            idx = i;                            
                        }
                    }
                }
                if(idx != -1){
                    executed = 1;
                    p[idx].remaining_t--;
                    current_time ++;
                    if(p[idx].remaining_t == 0){
                        p[idx].c_t = current_time;
                        p[idx].is_completed = 1;
    
                        printf("P%-9d Level-2 (SJF)  %-11d %-11d %-16d \n", p[idx].p_id, p[idx].a_t, p[idx].b_t, p[idx].c_t);
                        completed ++;
                    }
                }
            }
            if(executed == 0){
                //Lowest Priority 
                
                int earliest_at = 9999;
                int idx = -1;
                for (int i = 0; i < n; i++)
                {
                    if(p[i].priority < 4 && p[i].remaining_t > 0 && p[i].a_t <= current_time){

                        if(p[i].a_t < earliest_at){
                            earliest_at = p[i].a_t;
                            idx = i;
                        }
                    }
                }
                if(idx != -1){
                    executed = 1;
                    p[idx].remaining_t --;
                    current_time ++;

                    if(p[idx].remaining_t == 0){
                        p[idx].c_t = current_time;
                        p[idx].is_completed = 1;
                        printf("P%-9d Level-3 (FCFS) %-11d %-11d %-16d \n", p[idx].p_id, p[idx].a_t, p[idx].b_t, p[idx].c_t);
                        completed++;
                    }
                }
            }

            if(executed == 0){
                // cpu idle
                current_time ++;
            }
                
    }
    
    float a_wt=0;
    float a_tat=0;
    for (int i = 0; i < n; i++)
    {
        p[i].t_a_t = p[i].c_t - p[i].a_t;
        p[i].w_t = p[i].t_a_t - p[i].b_t;   
        a_wt = a_wt + p[i].w_t;
        a_tat = a_tat + p[i].t_a_t;
    }
    a_wt = a_wt/n;
    a_tat =a_tat/n;
    printf("\nAverage Turn Around Time = %.2f \n", a_tat);
    printf("Average Waiting Time = %.2f \n", a_wt);
    
}

int main()
{

    int n;
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    Process p[n];
    Process temp[n];    

    for (int i = 0; i < n; i++)
    {
        p[i].p_id = i + 1;

        printf("Enter the arrival time of P%d: ", p[i].p_id);
        scanf("%d", &p[i].a_t);

        printf("Enter the burst time of P%d: ", p[i].p_id);
        scanf("%d", &p[i].b_t);

        printf("Enter the priority of P%d: ", p[i].p_id);
        scanf("%d", &p[i].priority);

        p[i].is_completed=0;

        printf("\n");
    }

    int time_quantum;
    printf("Enter time quantum : ");
    scanf("%d", &time_quantum);

    // FCFS
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }
    sortByArrival(temp, n);
    FCFS(temp, n);

    // SJF
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }
    s_j_f(temp, n);

    //Round Robin
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }
    round_robin(temp,n,time_quantum);

    // MultiLevel
    for (int i = 0; i < n; i++) {
        temp[i] = p[i];
    }
    multi_level_scheduling(temp, n, time_quantum);
    return 0;
}