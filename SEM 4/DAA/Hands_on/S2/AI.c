#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 15

void readInput(int *n, int latency[MAX][MAX]) {
    scanf("%d", n);
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            scanf("%d", &latency[i][j]);
        }
    }
}

int calculateLatency(int n, int latency[MAX][MAX], int path[]) {
    // Logic to calculate latency for a given path
      int total = 0;
    for (int i = 0; i < n - 1; i++) {
        total += latency[path[i]][path[i + 1]];
    }
    total += latency[path[n - 1]][path[0]];
    return total;
}

void generatePermutations(int n, int *minLatency, int latency[MAX][MAX], int start) {
    // Logic to generate permutations and calculate minimum latency
     int path[MAX];
        for (int i = 0; i < n; i++) {
            path[i] = i;
        }

        while (1) {
            int currentLatency = calculateLatency(n, latency, path);
            if (currentLatency < *minLatency) {
                *minLatency = currentLatency;
            }
            int i = n - 2;
            while (i >= 0 && path[i] > path[i + 1]) {
                i--;
            }
            if (i < 0) {
                break;
            }
            int j = n - 1;
            while (path[i] > path[j]) {
                j--;
            }
            int temp = path[i];
            path[i] = path[j];
            path[j] = temp;

            int left = i + 1, right = n - 1;
            while (left < right) {
                temp = path[left];
                path[left] = path[right];
                path[right] = temp;
                left++;
                right--;
            }
        }
    
    
}

int main() {
    int n;
    int latency[MAX][MAX];
    int minLatency = INT_MAX; // inf

    readInput(&n, latency);

    generatePermutations(n, &minLatency, latency,0);

    printf("%d\n", minLatency);

    return 0;
}
