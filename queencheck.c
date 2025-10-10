#include <stdio.h>
#include <stdlib.h>

int n;
int x[100];

int isSafe(int k, int v) {
    for (int i = 1; i < k; i++) {
        if (x[i] == v || abs(x[i] - v) == abs(i - k))
            return 0;
    }
    return 1;
}

void printSolution() {
    for (int i = 1; i <= n; i++)
        printf("%d", x[i]);
    printf("\n");
}

void TRY(int k) {
    for (int v = 1; v <= n; v++) {
        if (isSafe(k, v)) {
            x[k] = v;
            if (k == n) {
                printSolution();
            } else {
                TRY(k + 1);
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    

    TRY(1);
    
    return 0;
}