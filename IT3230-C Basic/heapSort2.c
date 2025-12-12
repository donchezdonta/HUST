#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 101
#define N 100001

char* s[N]; //can use 2D arrays instead for simpler memory management
int n;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int i, int n) {
    int L = 2*i;
    int R = 2*i + 1;
    int maxIdx = i;
    
    if (L <= n && strcmp(s[a[L]], s[a[maxIdx]]) > 0) maxIdx = L;
    if (R <= n && strcmp(s[a[R]], s[a[maxIdx]]) > 0) maxIdx = R;
    
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
    scanf("%d", &n);
    
    int idx[N];
    char buffer[MAX_LEN];
    
    for (int i = 1; i <= n; i++) {//very prone to memory leak in-between each iteration
        scanf("%s", buffer);
        s[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char)); //no need for multiple malloc calls if 2d arrays were used
        strcpy(s[i], buffer);
        idx[i] = i;
    }
    
    heapSort(idx, n);
    
    for (int i = 1; i <= n; i++) {
        printf("%s\n", s[idx[i]]);
    }
    
    for (int i = 1; i <= n; i++) {
        free(s[i]);
    }
    
    return 0;
}