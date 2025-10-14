#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i = l, j = m + 1, k = 0;
    int *temp = (int *)malloc((r - l + 1) * sizeof(int));
    
    while (i <= m && j <= r)
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    
    for (int i = 0; i < k; i++)
        arr[l + i] = temp[i];
    
    free(temp);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    scanf("%d\n", &n);
    
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    mergeSort(arr, 0, n - 1);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    free(arr);
    return 0;
}