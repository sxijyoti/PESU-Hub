// In the Labyrinth of Numbers, a magical lock requires the adventurer to determine the number of possible sequences of positive integers 
// that sum up to a given number N. The sequence must use only positive integers. 
// The order of integers in the sequence matters. For example, (2+1 is considered different from 1+2). 
// Your task is to calculate the total number of such sequence using recursion.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int totalCombinations(int n) {
  // Enter your code here
    if(n == 0){
        return 1;
    }
    int res = 0;
    for(int i = 1; i<=n ; i++ ){
        res += totalCombinations(n-i);
    }
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    int result = totalCombinations(n);
    printf("%d\n",result);
    return 0;
}
