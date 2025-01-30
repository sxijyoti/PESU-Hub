// The adventurer has discovered a map leading to hidden treasure,
//  but the coordinates of the potential treasure locations are not aligned with his compass grid. 
//  Each point on the map represents a potential treasure location, with x and y values that could be 
//  scattered across the grid. To align these points with the adventurer’s compass, 
//  you must adjust the coordinates so that the smallest x-coordinate and the smallest y-coordinate 
//  become the new origin (0, 0).

// Your task is to translate the entire map in such a way that the point with the lowest x and y values moves to the origin, 
// and all other points are adjusted accordingly while maintaining their relative positions. 
// This transformation will allow the adventurer to better understand the map and navigate to the treasure efficiently.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void adjustCoordinates(int coordinates[][2], int n) {
    int minx = coordinates[0][0];
    int miny = coordinates[0][1];
    for(int i = 1 ; i < n ; i++){
        if(coordinates[i][0] < minx){
            minx = coordinates[i][0];
        }
        if(coordinates[i][1] < miny){
            miny = coordinates[i][1];
        }
    }
    
    for(int i = 0 ; i < n ; i++){
        coordinates[i][0] -= minx;
        coordinates[i][1] -= miny;
    }
}

void printCoordinates(int coordinates[][2], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %d\n", coordinates[i][0], coordinates[i][1]);
    }
}

int main() {
    int n;
    scanf("%d", &n); 
    int coordinates[n][2];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coordinates[i][0], &coordinates[i][1]);
    }
    adjustCoordinates(coordinates, n);
    printCoordinates(coordinates, n);
    return 0;
}
