// Given an integer array nums, return the most frequent even element. 
// If there is a tie, return the smallest one. If there is no such element, return -1.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n,c2=0,max=-1; // c1 is the count of the current num and c2 is for checking
    scanf("%d\n",&n);
    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d ",&a[i]);
    }
    for(int i=0;i<n;i++){
        if(a[i]%2==0){
            int c1=0;
            for(int j=0;j<n;j++){
                if(a[j]==a[i]){
                    c1++;
                }
            if(c2<c1){
                 c2=c1;
                max=a[i];
            }
            if(c2==c1){
                if(max>a[i]){
                    max=a[i];
                }
            }
            }
        }
    }
    printf("%d",max);
    return 0;
}
