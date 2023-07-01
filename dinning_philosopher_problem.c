#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define PHILOSOPHERS 7

pthread_mutex_t forks[PHILOSOPHERS];

void* philosopher(void* arg) {
    int index = *(int*)arg;
    int leftFork = index;
    int rightFork = (index + 1) % PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", index);

        // Pick up left fork
        pthread_mutex_lock(&forks[leftFork]);
        printf("Philosopher %d picked up left fork (%d)\n", index, leftFork);

        // Pick up right fork
        pthread_mutex_lock(&forks[rightFork]);
        printf("Philosopher %d picked up right fork (%d)\n", index, rightFork);

        // Eating
        printf("Philosopher %d is eating\n", index);

        // Put down right fork
        pthread_mutex_unlock(&forks[rightFork]);
        printf("Philosopher %d put down right fork (%d)\n", index, rightFork);

        // Put down left fork
        pthread_mutex_unlock(&forks[leftFork]);
        printf("Philosopher %d put down left fork (%d)\n", index, leftFork);

        // Philosophers think and eat in a cyclic manner
        usleep(1000000);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[PHILOSOPHERS];

    // Initialize mutex locks for forks
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        int* index = malloc(sizeof(int));
        *index = i;
        pthread_create(&philosophers[i], NULL, philosopher, index);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks for forks
    for (int i = 0; i < PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

