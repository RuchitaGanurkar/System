#include <stdio.h>

typedef struct {
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void calculateTimes(Process processes[], int n) {
    int remainingTime[n];
    int completed = 0;
    int currentTime = 0;
    int shortestJob;

    for (int i = 0; i < n; ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    while (1) {
        shortestJob = -1;
        int minBurstTime = 100000;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && remainingTime[i] < minBurstTime) {
                shortestJob = i;
                minBurstTime = remainingTime[i];
            }
        }

        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        remainingTime[shortestJob]--;

        if (remainingTime[shortestJob] == 0) {
            completed++;
            processes[shortestJob].waitingTime = currentTime - processes[shortestJob].arrivalTime - processes[shortestJob].burstTime;
            processes[shortestJob].turnaroundTime = processes[shortestJob].waitingTime + processes[shortestJob].burstTime;
        }

        currentTime++;
    }
}

void calculateAverageTimes(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    calculateTimes(processes, n);

    for (int i = 0; i < n; ++i) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    float averageWaitingTime = (float)totalWaitingTime / n;
    float averageTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}

void displayProcessTable(Process processes[], int n) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].arrivalTime,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n; // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input process details
    for (int i = 0; i < n; ++i) {
        printf("Process %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    calculateAverageTimes(processes, n);
    displayProcessTable(processes, n);

    return 0;
}

