#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int countPairs(int* arr, int n, int x) {
    int count = 0;
    int i = 1;
    int j = n;
    while (i < j) {
        if (arr[i] + arr[j] <= x) {
            count += (j - i);
            i++;
        } else {
            j--;
        }
    }
    return count;
}

void input() {
    int n, x;
    scanf("%d", &n);
    int arr[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    
    qsort(&arr[1], n, sizeof(int), compare);
    
    int q;
    scanf("%d", &q);
    int results[q];
    
    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        results[i] = countPairs(arr, n, x);
    }
    
    for (int i = 0; i < q; i++) {
        printf("%d\n", results[i]);
    }
}

int main() {
    input();
    return 0;
}