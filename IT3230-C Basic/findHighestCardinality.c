#include <stdio.h>

#define N 100001

int a[N], b[N];
int n, m;

void input() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &b[i]);
    }
}

void swap(int* a[], int i, int j) {
    int* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int* arr[], int i, int size) {
    int L = 2 * i;
    int R = 2 * i + 1;
    int maxIdx = i;

    if (L <= size && *arr[L] > *arr[maxIdx]) {
        maxIdx = L;
    }
    if (R <= size && *arr[R] > *arr[maxIdx]) {
        maxIdx = R;
    }

    if (maxIdx != i) {
        swap(arr, i, maxIdx);
        heapify(arr, maxIdx, size);
    }
}

void buildHeap(int* arr[], int size) {
    for (int i = size / 2; i >= 1; i--)
        heapify(arr, i, size);
}

void heapSort(int* arr[], int size) {
    buildHeap(arr, size);
    for (int i = size; i >= 2; i--) {
        swap(arr, 1, i);
        heapify(arr, 1, i - 1);
    }
}

int maxCommonSubset(int* a[], int* b[], int n, int m) {
    heapSort(a, n);
    heapSort(b, m);
    int count = 0;
    int i = 1, j = 1;
    while (i <= n && j <= m) {
        if (*a[i] == *b[j]) {
            count++;
            i++;
            j++;
        } else if (*a[i] < *b[j]) {
            i++;
        } else {
            j++;
        }
    }
    return count;
}

int main() {
    input();
    int* arrA[N];
    int* arrB[N];
    for (int i = 1; i <= n; i++) {
        arrA[i] = &a[i];
    }
    for (int i = 1; i <= m; i++) {
        arrB[i] = &b[i];
    }
    int result = maxCommonSubset(arrA, arrB, n, m);
    printf("%d\n", result);
    return 0;
}
