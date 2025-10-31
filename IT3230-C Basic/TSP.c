#include <stdio.h>
#include <limits.h>

int n;
int d[100][100];
int x[100];
int mark[100];
int f;
int f_min;
int Cm;

//Backtracking
void Try1(int k) {
    for (int v = 1; v <= n; v++) {
        if (mark[v] == 0) {
            x[k] = v;
            f += d[x[k - 1]][x[k]];
            mark[v] = 1;
            if (k == n) {
                if (f_min > f + d[x[n]][x[1]])
                    f_min = f + d[x[n]][x[1]];
            } else Try1(k + 1);
        }
        f -= d[x[k - 1]][x[k]];
        mark[v] = 0;
    }
}

//Branch and Bound
void Try2(int k){ 
    for (int v = 1; v <= n; v++) {
        if (mark[v] == 0) {
            x[k] = v;
            f += d[x[k - 1]][x[k]];
            mark[v] = 1;
            if (k == n) {
                int total_cost = f + d[x[n]][x[1]];
                if (total_cost < f_min) {
                    f_min = total_cost;
                }
            } else {
                if (f + (n - k + 1) * Cm < f_min) {
                    Try2(k + 1);
                }
            }
            
            f -= d[x[k - 1]][x[k]];
            mark[v] = 0;
        }
    }
}

void input() {
    scanf("%d", &n);
    if (n < 1 || n > 20) {
        return;
    }
    
    Cm = INT_MAX;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &d[i][j]);
            if (d[i][j] < Cm && i != j) {
                Cm = d[i][j];
            }
        }
    }
}

int main() {
    input();
    f = 0;
    f_min = INT_MAX;
    for (int i = 1; i <= n; i++) {
        mark[i] = 0;
    }
    x[1] = 1;
    mark[1] = 1;
    Try2(2);
    printf("%d\n", f_min);
    return 0;
}