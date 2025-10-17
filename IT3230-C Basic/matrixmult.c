#include <stdio.h>

int main()
{
    int n, k, m;
    int A[100][100], B[100][100], C[100][100];

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    scanf("%d %d", &k, &m);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            C[i][j] = 0;
            for (int p = 0; p < k; p++)
            {
                C[i][j] += A[i][p] * B[p][j];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d", C[i][j]);
            if (j < m - 1)
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}