#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int i, int n) {
    int L = 2*i;
    int R = 2*i + 1;
    int maxIdx = i;
    
    if (L <= n && a[L] > a[maxIdx]) maxIdx = L;
    if (R <= n && a[R] > a[maxIdx]) maxIdx = R;
    
    if (maxIdx != i) {
        swap(&a[i], &a[maxIdx]);
        heapify(a, maxIdx, n);
    }
}

void buildHeap(int a[], int n) {
    for (int i = n/2; i >= 1; i--) {
        heapify(a, i, n);
    }
}

void heapSort(int a[], int n) {
    buildHeap(a, n);
    for (int i = n; i >= 2; i--) {
        swap(&a[1], &a[i]);
        heapify(a, 1, i-1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    int a[n+1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    heapSort(a, n);
    
    for (int i = 1; i <= n; i++) {
        printf("%d", a[i]);
        if (i < n) printf(" ");
    }
    printf("\n");
    
    return 0;
}