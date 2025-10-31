#include <stdio.h>

#define MAX 1000

int n, m, r, c;
int A[MAX][MAX];
int visited[MAX][MAX];
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

typedef struct {
    int r, c, dist;
} Node;

Node queue[MAX * MAX];
int front, rear;

void input() {
    scanf("%d %d %d %d", &n, &m, &r, &c);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &A[i][j]);
        }
    }
}

int bfs() {
    front = rear = 0;
    queue[rear++] = (Node){r, c, 0};
    visited[r][c] = 1;
    
    while (front < rear) {
        Node cur = queue[front++];
        
        // try 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i];
            int nc = cur.c + dc[i];
            
            if (nr < 1 || nr > n || nc < 1 || nc > m) {
                return cur.dist + 1;
            }
            if (A[nr][nc] == 0 && !visited[nr][nc]) {
                visited[nr][nc] = 1;
                queue[rear++] = (Node){nr, nc, cur.dist + 1};
            }
        }
    }
    
    return -1;
}

int main() {
    input();
    printf("%d\n", bfs());
    return 0;
}