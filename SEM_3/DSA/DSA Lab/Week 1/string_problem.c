// Hotel structure accepts the name of a room, its price per night and the area of the room in square feet. 
// Write a code to initialise an array of 'n' hotel rooms from input. Pass the array to a function Ratio_Order. 
// Calculate the squarefeet/price ratio for each of the rooms. Larger the ratio, the better it is for a customer. 
// So sort the array in Descending order based on the ratios calculated and display. The displayed ratio must have two decimal values. 
// Note that the price for a room is never 0. In case of a tie maintain the order same as in input.

#include <stdio.h>
#include <string.h>

typedef struct hotel {
    char name[50];
    int price;
    int squarefeet;
    double ratio;
} HOTEL;

void Ratio_Order(HOTEL *h, int n);

int main() {
    int n;
    scanf("%d", &n);
    HOTEL h[n];
    //complete initialising the array by accepting input
    for(int i=0;i<n;i++){
       scanf("%s %d %d\n",h[i].name,&h[i].price,&h[i].squarefeet);
        // printf("\n");
    }
   // call the function Ratio_Order
    Ratio_Order(h,n);
   //print the Output
    for(int i=0;i<n;i++){
       printf("%s %d %d %.2lf\n",h[i].name,h[i].price,h[i].squarefeet,h[i].ratio); 
    }
   return 0;
}

void Ratio_Order(HOTEL *h, int n) {
//complete code
    for(int i=0;i<n;i++){
        h[i].ratio=(double)h[i].squarefeet/h[i].price;
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(h[j].ratio<h[j+1].ratio){
                HOTEL temp;
                temp = h[j];
                h[j]=h[j+1];
                h[j+1]=temp;
            }}
    }

}