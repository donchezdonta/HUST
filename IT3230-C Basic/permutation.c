#include <stdio.h>

int n;

int x[11];

int used[11];

void printSolution()
{

    for (int i = 1; i <= n; i++)

        printf("%d", x[i]);

    printf("\n");
}

void TRY(int k)
{

    for (int v = 1; v <= n; v++)
    {

        if (!used[v])
        {

            x[k] = v;

            used[v] = 1;

            if (k == n)
            {

                printSolution();
            }
            else
            {

                TRY(k + 1);
            }

            used[v] = 0;
        }
    }
}

int main()
{

    scanf("%d", &n);

    if (n < 1 || n > 10)
    {

        return 1;
    }

    TRY(1);

    return 0;
}