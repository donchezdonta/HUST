#include <stdio.h>
#include <stdlib.h>

int *a[100005];
int n, m;

int cmp(int i, int j)
{
    for(int k = 1; k <= m; k++)
        if(a[i][k] < a[j][k]) return -1;
        else if(a[i][k] > a[j][k]) return 1;
    return 0;
}

void swap(int i, int j)
{
    int* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int i, int n)
{
    int L = 2 * i;
    int R = 2 * i + 1;
    int maxIdx = i;

    if (L <= n && cmp(maxIdx, L) < 0) maxIdx = L;
    if (R <= n && cmp(maxIdx, R) < 0) maxIdx = R;

    if (maxIdx != i) {
        swap(i, maxIdx);
        heapify(maxIdx, n);
    }
}

void buildHeap()
{
    for(int i = n / 2; i >= 1; i--)
        heapify(i, n);
}

void heapSort()
{
    buildHeap();
    for(int i = n; i >= 2; i--) {
        swap(1, i);
        heapify(1, i - 1);
    }
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        a[i] = (int*)malloc(sizeof(int) * (m + 1));
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    }

    heapSort();

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }

    for(int i = 1; i <= n; i++)
        free(a[i]);

    return 0;
}
