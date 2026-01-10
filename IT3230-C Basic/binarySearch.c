#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100001

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(int a[], int L, int R, int k) {
    if (L > R) return -1;
    if (L == R) {
        if (a[L] == k) return L;
        else return -1;
    }
    
    int m = (L + R) / 2;
    
    if (a[m] == k) return 1;
    if (a[m] < k) return binarySearch(a, m + 1, R, k);
    else return binarySearch(a, L, m - 1, k);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int *a = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    qsort(a, n, sizeof(int), compare);
    
    int results[N];
    int count = 0;
    
    char cmd[10];
    while (1) {
        scanf("%s", cmd);
        if (strcmp(cmd, "#") == 0) break;
        if (strcmp(cmd, "find") == 0) {
            int k;
            scanf("%d", &k);
            results[count++] = binarySearch(a, 0, n-1, k);
        }
    }
    
    for (int i = 0; i < count; i++) {
        printf("%d\n", results[i]);
    }
    
    free(a);
    return 0;
}

