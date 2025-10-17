#include <stdio.h>
#include <string.h>

int checkEqual(int a[], int n, int b[], int m)
{
    if (n != m)
    {
        return 0;
    }

    return memcmp(a, b, n * sizeof(int)) == 0 ? 1 : 0;
}

void readArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
}

int main()
{
    int T, t;
    int res[102];

    scanf("%d", &T);

    for (t = 0; t < T; t++)
    {
        int n, m;
        int a[1000], b[1000];

        scanf("%d %d", &n, &m);

        readArray(a, n);
        readArray(b, m);

        res[t] = checkEqual(a, n, b, m);
    }

    for (t = 0; t < T; t++)
        printf("%d\n", res[t]);

    return 0;
}