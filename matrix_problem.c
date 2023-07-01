#include <stdio.h>
#include <pthread.h>

#define ROWS 10
#define COLS 10
#define NUM_THREADS ROWS * COLS

int matrix[ROWS][COLS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fill_matrix(void* arg) {
    int thread_id = *(int*)arg;
    int row = thread_id / COLS;
    int col = thread_id % COLS;
    
    // Perform some computation to determine the matrix element
    int element = (row + col) % 2;
    
    pthread_mutex_lock(&mutex);
    matrix[row][col] = element;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, fill_matrix, &thread_ids[i]);
        sleep(5);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
        sleep(5);
    }

    // Print the resulting matrix
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

