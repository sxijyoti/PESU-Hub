// You are a robot navigating through a maze represented as a 2D grid. The maze consists of open cells and walls. 
// You start at the top-left corner and need to reach the bottom-right corner.
// Write a recursive function to find if there is a path from the start to the destination.
// Open cells are denoted by 0.
// Walls are denoted by 1.
// You can move up, down, left, or right, but not diagonally.

#include <stdio.h>
#define N 100
#define M 100
// Recursive function to solve the maze
int solveMaze(int maze[N][M], int x, int y, int n, int m, int visited[N][M]) {
    // Write the code
    if ( maze[x][y] == 1 || visited[x][y] == 1 || x < 0 || y < 0 || x >= n || y >= m) {
        return 0;
    }
    if (x == n - 1 && y == m - 1) {
        return 1;
    }
    visited[x][y] = 1;
    if (solveMaze(maze, x + 1, y, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x, y + 1, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x - 1, y, n, m, visited)) {
        return 1;
    }
    if (solveMaze(maze, x, y - 1, n, m, visited)) {
        return 1;
    }
    visited[x][y] = 0;
    return 0;
}
    
int main() {
  int n, m;
   scanf("%d %d", &n, &m);
  
   int maze[N][M];
   int visited[N][M] = {0};
  
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < m; j++) {
           scanf("%d", &maze[i][j]);
       }
   }
  
   // Solve the maze
   if (solveMaze(maze, 0, 0, n, m, visited)) {
       printf("YES\n");
   } else {
       printf("NO\n");
   }
   return 0;
}