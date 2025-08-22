#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    int front = 0, count = 0, pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // frame intialization
    }

    printf("Reference String | Frames     | Status\n");
    printf("-----------------|------------|--------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // page in frame or not
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // page fault
            frames[front] = page;
            front = (front + 1) % capacity;
            pageFaults++;
        }

        printf("   %2d             | ", page);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) {
                printf("%2d ", frames[j]);
            } else {
                printf(" - ");
            }
        }
        printf(" | %s\n", found ? "Hit" : "Fault");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", n - pageFaults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    fifoPageReplacement(pages, n, capacity);

    return 0;
}

// 12 -> 1 2 3 4 1 2 5 1 2 3 4 5 -> 9 f and 3 m
// 22 -> 7 0 1 2 0 3 0 4 2 3 0 3 0 3 2 1 2 0 1 7 0 1 -> 15 f and 7 m