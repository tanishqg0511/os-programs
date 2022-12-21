#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
typedef struct Process{
	int pid, at, bt, ct ,tat ,wt ,st ,rt, remaining_time,priority;
}P;
int findmax(int a, int b){
	return a > b ? a : b;
}
int findmin(int a, int b){
	return a < b ? a : b;
}
int Find(P arr[], int n, bool iscomplete[], int current){
	int In = -1, maxPriority = INT_MIN;
	for (int i = 0; i < n; i++){
		if (arr[i].at <= current && !iscomplete[i]){
			if (arr[i].priority > maxPriority){
				maxPriority = arr[i].priority;
				In = i;
			}
			if (arr[i].priority == maxPriority){
				if (arr[In].at > arr[i].at){
					maxPriority = arr[i].priority;
					In = i;
				}
			}
		}
	}
	return In;
}
int main(){
	printf("Enter No. of Processes\n");
	int n;
	scanf("%d", &n);
	P arr[n];
	bool iscomplete[n], isFirst = true;
	float sum_rt = 0, sum_wt = 0, sum_tat = 0;
	for (int i = 0; i < n; i++){
		printf("Enter Arrival Burst Time and priority of %d process \n", i + 1);
		scanf("%d%d%d", &arr[i].at, &arr[i].bt,&arr[i].priority);
		arr[i].remaining_time = arr[i].bt;
		arr[i].pid = i;
	}
	int completed = 0, prev_c, current = 0, IdleTym = 0;
	while (completed != n){
		int Index = Find(arr, n, iscomplete, current);
		if (Index != -1){
			if (arr[Index].remaining_time == arr[Index].bt){
				arr[Index].st = current;
				IdleTym += (isFirst == true) ? 0 : (arr[Index].st - prev_c);
				isFirst = false;
			}
			current++;
			prev_c = current;
			arr[Index].remaining_time--;
			if (arr[Index].remaining_time == 0){
				completed++;
				iscomplete[Index] = true;
				arr[Index].ct = current;
				arr[Index].tat = arr[Index].ct - arr[Index].at;
				arr[Index].wt = arr[Index].tat - arr[Index].bt;
				arr[Index].rt = arr[Index].st - arr[Index].at;
				sum_wt += arr[Index].wt;
				sum_tat += arr[Index].tat;
				sum_rt += arr[Index].rt;
			}
		}
		else
		current++;
	}
	int max_completion_time = INT_MIN;
	int min_arrival_time = INT_MAX;
	for (int i = 0; i < n; i++){
		max_completion_time = findmax(max_completion_time, arr[i].ct);
		min_arrival_time = findmin(min_arrival_time, arr[i].at);
	}
	int length_cycle = max_completion_time - min_arrival_time;
	printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n");
	for (int i = 0; i < n; i++)
		printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat,arr[i].wt, arr[i].rt);
	printf("\n");
	float cpu_utilization = (float)(length_cycle - IdleTym)/ length_cycle;
	printf("\nAverage Turn Around time= %f ",(float)sum_tat/n);
	printf("\nAverage Waiting Time= %f ",(float)sum_wt/n);
	printf("\nAverage Response Time= %f ",(float)sum_rt/n);
	printf("\nThroughput= %f",n/(float)length_cycle);
	printf("\nCPU Utilization(Percentage)= %f",cpu_utilization*100);
	return 0;
}
