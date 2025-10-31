#include <stdio.h>
#include <limits.h>

#define MAX_N 30
#define MAX_M 10

int N, M;
int c[MAX_N];
int A[MAX_N][MAX_N];
int x[MAX_N];
int f_best;
int load[MAX_M];

void input() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
}

int check(int v, int k) {
    // preq for i
    for (int i = 0; i < k; i++) {
        if (A[i][k] == 1 && x[i] >= v) {
            return 0;
        }
    }
    // preq for k
    for (int i = k + 1; i < N; i++) {
        if (x[i] != -1 && A[k][i] == 1 && v >= x[i]) {
            return 0;
        }
    }
    return 1;
}

void solution() {
    int max_load = 0;
    for (int i = 0; i < M; i++) {
        if (load[i] > max_load) {
            max_load = load[i];
        }
    }
    if (max_load < f_best) {
        f_best = max_load;
    }
}

void TRY(int k) {
    for (int v = 0; v < M; v++) {
        if (check(v, k)) {
            x[k] = v;
            load[v] += c[k];
            if (k == N - 1) {
                solution();
            } else {
                TRY(k + 1);
            }
            load[v] -= c[k];
        }
    }
}

void solve() {
    f_best = INT_MAX;
    for (int i = 0; i < N; i++) {
        x[i] = -1;
    }
    for (int i = 0; i < M; i++) {
        load[i] = 0;
    }
    TRY(0);
    printf("%d\n", f_best);
}

int main() {
    input();
    solve();
    return 0;
}