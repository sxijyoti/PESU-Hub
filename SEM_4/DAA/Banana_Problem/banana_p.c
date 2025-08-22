#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

bool next_permutation(int arr[], int size) {
    int pivot = -1;
    for (int i = size - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            pivot = i;
            break;
        }
    }

    if (pivot == -1)
        return false;

    int successor = -1;
    for (int i = size - 1; i > pivot; i--) {
        if (arr[i] > arr[pivot]) {
            successor = i;
            break;
        }
    }

    swap(&arr[pivot], &arr[successor]);
    reverse(arr, pivot + 1, size - 1);

    return true;
}

int compute_cost(int districts, int **travelcost, int route[]) {
    int total = 0;
    for (int i = 0; i < districts - 1; i++) {
        if (travelcost[route[i]][route[i + 1]] == -1)
            return -1;
        total += travelcost[route[i]][route[i + 1]];
    }

    if (travelcost[route[districts - 1]][route[0]] == -1)
        return -1;

    total += travelcost[route[districts - 1]][route[0]];
    return total;
}

void find_optimal_route(int districts, int **travelcost, int *optimalcost, int bestroute[]) {
    int *route = (int *)malloc(districts * sizeof(int));
    if (!route) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < districts; i++) {
        route[i] = i;
    }

    *optimalcost = -1;

    do {
        int current = compute_cost(districts, travelcost, route);
        if (current != -1 && (*optimalcost == -1 || current < *optimalcost)) {
            *optimalcost = current;
            for (int i = 0; i < districts; i++) {
                bestroute[i] = route[i];
            }
        }
    } while (next_permutation(route, districts));

    free(route);
}

int main() {
    int districts;
    scanf("%d", &districts);

    int **travelcost = (int **)malloc(districts * sizeof(int *));
    if (!travelcost) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < districts; i++) {
        travelcost[i] = (int *)malloc(districts * sizeof(int));
        if (!travelcost[i]) {
            printf("Memory allocation failed.\n");
            return 1;
        }
    }

    for (int i = 0; i < districts; i++) {
        for (int j = 0; j < districts; j++) {
            scanf("%d", &travelcost[i][j]);
        }
    }

    int optimalcost;
    int *bestroute = (int *)malloc(districts * sizeof(int));
    if (!bestroute) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    find_optimal_route(districts, travelcost, &optimalcost, bestroute);

    if (optimalcost == -1) {
        printf("No valid path exists.\n");
    } else {
        printf("Minimum cost: %d\n", optimalcost);
        printf("Optimal route: ");
        for (int i = 0; i < districts; i++) {
            printf("%d ", bestroute[i]);
        }
        printf("%d\n", bestroute[0]);
    }

    for (int i = 0; i < districts; i++) {
        free(travelcost[i]);
    }
    free(travelcost);
    free(bestroute);

    return 0;
}
