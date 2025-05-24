// transform and conquer algorithm
// check for element uniqueness - either by sorting or bruteforce comparison

// instant simplification
// representation change
// problem reduction

// ALGORITHM presort
/*

O(nlogn)

by sorting:

presort(A[0..n-1])
for i - 0 to n-2 do
if A[i] == A[i+1] then false
return true

presortMode(A[0..n-1])



*/

#include <stdio.h>

void sort(int A[], int n) {
    // Bubble sort implementation
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (A[j] > A[j+1]) {
                // Swap A[j] and A[j+1]
                int temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

int presortunique(int A[], int n) {
    // First sort the array
    sort(A, n);
    
    // Check for any adjacent equal elements
    for (int i = 0; i < n-1; i++) {
        if (A[i] == A[i+1]) {
            return 0; // Not unique
        }
    }
    
    return 1; // All elements are unique
}

int main() {
    int arr1[] = {5, 2, 9, 1, 7, 3};
    int arr2[] = {5, 2, 9, 1, 7, 5}; // Contains duplicate 5
    
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("Array 1 has unique elements: %s\n", presortunique(arr1, n1) ? "Yes" : "No");
    printf("Array 2 has unique elements: %s\n", presortunique(arr2, n2) ? "Yes" : "No");
    
    return 0;
}

