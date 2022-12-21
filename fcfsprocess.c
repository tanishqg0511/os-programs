#include<stdio.h>
#include<stdlib.h>

struct Process{
    int pid,at,bt,ct,tat,wt,rt,st; // process id, arrival time , burst time, compiletion time , trun round time , waiting time , response time, start time
};

int compare(const void *p1 , const void *p2){
    int a = ((struct Process *) p1)->at;
    int b = ((struct Process *) p2)->at;
    if(a < b) return -1;
    else return 1;
}
int main(){
    int n, idealTime = 0;
    float sumWT = 0 , sumTat = 0 , sumrt = 0;
    float avgrt = 0, avgWT = 0 , avgTat = 0, cpuUtilization , Throughput;

    printf("Enter the number of processes : ");
    scanf("%d" , &n);
    struct Process p[n];
    
    for(int i = 0 ; i < n ; i++){
        p[i].pid = i+1;
        printf("Enter the Arrival Time and Burst time for process = %d : ",i);
        scanf("%d%d", &p[i].at , &p[i].bt);
    }

    // sorting the processes according to their arrival time
    qsort((void*)p , n , sizeof(struct Process) , compare);
    
    for(int i = 0 ; i < n ; i++){
        //first time process Getting CPU
        if(i == 0)
            p[i].st = p[i].at;

        // Process getting CPU after Context Switch
        else if(p[i-1].ct < p[i].at){
            p[i].st = p[i].at;
            idealTime += p[i].at - p[i-1].ct;
        }

        // Process getting CPU without Context Switch aka directly after some other process
        else
            p[i].st = p[i-1].ct;

        // calculation of ct, rt, tat, wt
        p[i].ct = p[i].st + p[i].bt;
        p[i].tat = p[i].ct-p[i].at;
        p[i].wt = p[i].tat-p[i].bt;
        p[i].rt = p[i].st-p[i].at;
    }
    
    for(int i = 0 ; i <n ; i++){
        sumWT += p[i].wt;
        sumTat +=p[i].tat;
        sumrt += p[i].rt;
    }
    avgWT = sumWT/n;
    avgTat = sumTat/n;
    avgrt = sumrt/n;
    int totalTime = p[n-1].ct - p[0].st;
    cpuUtilization = ((float)(totalTime - idealTime) / totalTime )*100;
    Throughput = (float)n/(float)totalTime;


    printf("process\tat\tbt\tst\tct\trt\ttat\twt\n");
    for(int i = 0 ; i < n ; i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid , p[i].at , p[i].bt , p[i].st , p[i].ct , p[i].rt , p[i].tat , p[i].wt);
    }
    printf("Average Response Time =  %0.2f\nAverage TurnAround Time = %0.2f\nAverage Waiting Time = %0.2f\n" , avgrt , avgTat , avgWT);
    printf("CPU Utilitzation = %.2f\nThroughput = %.4f" , cpuUtilization , Throughput);

}
