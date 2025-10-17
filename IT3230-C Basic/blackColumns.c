#include <stdio.h>

static int a[1000][1000];

void matrix(int a[][1000], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    }
}

int blackColumns(int a[][1000], int n, int m)
{
    int count = 0;

    for (int j = 0; j < m; j++)
    {
        int isBlack = 1;
        for (int i = 0; i < n; i++)
        {
            if (a[i][j] == 0)
            {
                isBlack = 0;
                break;
            }
        }
        if (isBlack)
            count++;
    }
    return count;
}

int main()
{
    int n, m;
    if (scanf("%d%d", &n, &m) != 2)
        return 0;

    if (n <= 0 || m <= 0 || n > 1000 || m > 1000)
    {
        return 1;
    }

    matrix(a, n, m);
    printf("%d\n", blackColumns(a, n, m));

    return 0;
}