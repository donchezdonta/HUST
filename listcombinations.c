#include <stdio.h>
#include <stdlib.h>

int n, k;
int temp[100];
int **res;
int resCount = 0;

void combineUtil(int start, int pos, int remaining) {
    if (remaining == 0) {
        res[resCount] = (int *)malloc((k + 1) * sizeof(int));
        for (int i = 0; i < k; i++) {
            res[resCount][i] = temp[i];
        }
        resCount++;
        return;
    }

    for (int i = start; i <= n; i++) {
        temp[pos] = i;

        combineUtil(i + 1, pos + 1, remaining - 1);
    }
}

void getCombinations(int n_val, int k_val) {
    n = n_val;
    k = k_val;
    resCount = 0;
    
    res = (int **)malloc(1000 * sizeof(int *));
    
    combineUtil(1, 0, k);
}

int main() {
    int n_input, k_input;
    scanf("%d %d", &k_input, &n_input);
    if (k_input < 0 || n_input < 0 || k_input > n_input) {

        return 1;
    }
    
    if (k_input == 0) {
        return 0;
    }
    
    getCombinations(n_input, k_input);
    
    for (int i = 0; i < resCount; i++) {
        for (int j = 0; j < k_input; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
        free(res[i]);
    }
    
    free(res);
    
    return 0;
}