#include <stdio.h>

#define MAX_N 1000
#define MAX_X 1000
#define INF 1001

int n, x, d[MAX_N];
int dp[MAX_X + 1], best_count;

void solution() {
    for (int i = 0; i <= x; i++) {
        dp[i] = INF;
    }

    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = d[i]; j <= x; j++) {
            if (dp[j - d[i]] + 1 < dp[j]) {
                dp[j] = dp[j - d[i]] + 1;
            }
        }
    }

    if (dp[x] == INF) {
        best_count = -1;
    } else {
        best_count = dp[x];
    }
}

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }
    solution();
    printf("%d\n", best_count);
    return 0;
}   