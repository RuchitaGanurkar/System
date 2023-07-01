#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int processID;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void roundRobin(Process processes[], int n, int timeQuantum) {
    int completed = 0;
    int currentTime = 0;

    while (completed != n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].burstTime > 0) {
                int executionTime = (processes[i].burstTime < timeQuantum) ? processes[i].burstTime : timeQuantum;

                processes[i].burstTime -= executionTime;
                currentTime += executionTime;

                if (processes[i].burstTime == 0) {
                    completed++;
                    processes[i].waitingTime = currentTime - executionTime;
                    processes[i].turnaroundTime = processes[i].waitingTime + executionTime;
                }
            }
        }
    }
}

void calculateAverageTimes(Process processes[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

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
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].processID,
               processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
    }
}

int main() {
    int n; // Number of processes
    int timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    Process processes[MAX_PROCESSES];

    // Input process details
    for (int i = 0; i < n; ++i) {
        printf("Process %d\n", i + 1);
        processes[i].processID = i + 1;
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    roundRobin(processes, n, timeQuantum);
    calculateAverageTimes(processes, n);
    displayProcessTable(processes, n);

    return 0;
}

