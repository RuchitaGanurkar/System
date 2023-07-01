#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_PARTICIPANTS 25

typedef struct {
    char name[50];
    int assignedIndex;
} Participant;

void assignRecipients(Participant participants[], int n) {
    bool isAssigned[MAX_PARTICIPANTS] = { false };

    for (int i = 0; i < n; ++i) {
        int recipientIndex;
        do {
            recipientIndex = rand() % n;
        } while (recipientIndex == i || isAssigned[recipientIndex]);

        participants[i].assignedIndex = recipientIndex;
        isAssigned[recipientIndex] = true;
    }
}

void printAssignments(Participant participants[], int n) {
    printf("Secret Santa Assignments:\n");
    for (int i = 0; i < n; ++i) {
        printf("%s -> %s\n", participants[i].name, participants[participants[i].assignedIndex].name);
    }
}

int main() {
    int n; // Number of participants

    printf("Enter the number of participants: ");
    scanf("%d", &n);
    getchar(); // Clear the input buffer

    Participant participants[MAX_PARTICIPANTS];

    // Input participant names
    for (int i = 0; i < n; ++i) {
        printf("Enter participant %d name: ", i + 1);
        fgets(participants[i].name, sizeof(participants[i].name), stdin);
        participants[i].name[strcspn(participants[i].name, "\n")] = '\0'; // Remove trailing newline character
    }

    srand(time(NULL)); // Seed the random number generator
    assignRecipients(participants, n);
    printAssignments(participants, n);

    return 0;
}

