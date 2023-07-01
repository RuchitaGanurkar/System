#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type; // 0 for arrival, 1 for departure
} Event;

int optimizeTrainSchedule(Event events[], int n) {
    int platforms = 0;
    int maxPlatforms = 0;

    for (int i = 0; i < n; ++i) {
        if (events[i].type == 0) {
            platforms++;
        } else {
            platforms--;
        }

        if (platforms > maxPlatforms) {
            maxPlatforms = platforms;
        }
    }

    return maxPlatforms;
}

int main() {
    int n; // Number of trains
    printf("Enter the number of trains: ");
    scanf("%d", &n);

    Event events[2 * n];

    // Input train arrival and departure times
    for (int i = 0; i < n; ++i) {
        printf("Train %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &events[2 * i].time);
        events[2 * i].type = 0; // Arrival event

        printf("Departure Time: ");
        scanf("%d", &events[2 * i + 1].time);
        events[2 * i + 1].type = 1; // Departure event
    }

    int maxPlatforms = optimizeTrainSchedule(events, 2 * n);
    printf("Maximum Platforms Required: %d\n", maxPlatforms);

    return 0;
}

