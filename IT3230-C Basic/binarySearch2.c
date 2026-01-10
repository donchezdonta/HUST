#include <stdio.h>
#include <stdlib.h>

#define N 1000001

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(int a[], int L, int R, int k) {
    if (L > R) return -1;
    
    int m = (L + R) / 2;
    
    if (a[m] == k) return m;
    if (a[m] < k) return binarySearch(a, m + 1, R, k);
    else return binarySearch(a, L, m - 1, k);
}

int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    
    int *a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), compare);

    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        int idx = binarySearch(a, i + 1, n - 1, Q - a[i]);
        if (idx != -1) cnt++;
    }
    
    printf("%d\n", cnt);
    
    free(a);
    return 0;
}