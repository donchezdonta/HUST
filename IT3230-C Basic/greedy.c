#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//salesman
int n; //cities
int dist[10][10];
int visited[10];

int nearest(int current) {
    int next = -1;
    int min_dist = 999999;
    for (int j = 0; j < n; j++) {
        if (!visited[j] && dist[current][j] < min_dist) {
            min_dist = dist[current][j];
            next = j;
        }
    }
    return next;
}

int TSP() {
    memset(visited, 0, sizeof(visited));

    int current = 0;
    int total = 0;
    visited[0] = 1;

    for (int i= 1; i < n; i++) {
        int next = nearest(current);
        total += dist[current][next];
        current = next;
        visited[current] = 1;
    }

    total += dist[current][0];
    return total;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    printf("%d\n", TSP());
}