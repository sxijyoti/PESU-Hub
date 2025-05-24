// heap is partially ordered ds used for priority queue
// binary tree shaped with only last level rightmost leaf missing 
// and node should be greater than or equal to children
//  array by recording its elements in the topdown, left-to right pos 1 to n leaving pos[0]
// first n/2 -> parent and next n/2 -> leaves
// for "i" parent node -> children at 2i or 2i + 1

/*
bottom up approach:
HeapBotUp(H[1....n]):
// construct heap through bottom up for ele in array
// input : array H[1..n]
// output : heap H[1...n]

for i <- n/2 down to 1 do
    k <- i; v <- H[k]
    heap <- false
    while not heap and 2*k <= n do
        j <- 2*k
        if j < n then
            if H[j] < H[j+1] then
                j <- j + 1
        if v >= H[j] then
            heap <- true
        else
            H[k] <- H[j]
            k <- j
    H[k] <- v

*/

/*
top down approach:

HeapTopDown(H[1...n]):
// construct heap through top down for ele in array
// input : array H[1..n]
// output : heap H[1...n]

time complexity: O(logn) for insertion

void HeapTopDown(int H[], int n) {
    // Construct heap through top-down approach
    // Each element is inserted and bubbled up to its correct position
    
    for (int i = 2; i <= n; i++) {
        // Insert the i-th element into the heap of the first i-1 elements
        int j = i;
        int v = H[j]; // Save the value being promoted
        
        // Bubble up: compare with parent and swap if needed
        while (j > 1 && v > H[j/2]) {
            H[j] = H[j/2]; // Move parent down
            j = j/2;       // Move up to parent position
        }
        H[j] = v; // Place value in its correct position
    }
}
*/

/*
// Function to delete the maximum key (root) from the heap
int DeleteMax(int H[], int *n) {
    // Save the maximum value to return
    int maxVal = H[1];
    
    // Replace the root with the last element
    H[1] = H[*n];
    
    // Decrease heap size
    (*n)--;
    
    // Restore heap property (sift down)
    int k = 1;
    int v = H[k];
    int heap = 0; // false
    
    while (!heap && 2*k <= *n) {
        int j = 2*k; // Left child
        
        // Find the larger child
        if (j < *n && H[j] < H[j+1]) {
            j++; // Right child is larger
        }
        
        // If v is greater than or equal to larger child, heap property is satisfied
        if (v >= H[j]) {
            heap = 1; // true
        } else {
            // Move the larger child up
            H[k] = H[j];
            k = j;
        }
    }
    
    // Place v in its final position
    H[k] = v;
    
    return maxVal;
}
*/
    
/*
heap sort:


*/