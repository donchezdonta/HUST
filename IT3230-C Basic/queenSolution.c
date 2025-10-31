#include <stdio.h>
#include <stdlib.h>
/*Biểudiễnphươngán: x[1..n], trongđóx[i] làchỉsốhàngcủaquânhậutrêncộti
•Ràngbuộc
    •x[i] ≠ x[j] (rowi≠ rowj)
    •x[i] + i≠ x[j] + j (rowi+ coli≠ rowj+ colj)
    •x[i] –i≠ x[j] -j(rowi-coli≠ rowj-colj)
•Mảngđánhdấu:
    •markR[r] = 1: hàngrcóquânhậu
    •markD1[d] = 1: nghĩalàcóquânhậutrênhàngr, cộtkvớid= n–k+ r (các đường chéo màu xanh)
    •markD2[d] = 1: nghĩalàcóquânhậutrênhàngr, cộtkvớik+ r= d (các đường chéo màu đỏ)
    •D: Diagonal
check(r, k) {return (mark[r] = 0) and (markD1[n+k-r] = 0) and (markD2[k+r] = 0); } */

#define MAX_N 200
int T, N;
int board[MAX_N][MAX_N] = {0};
int X[MAX_N] = {0};
int markR[MAX_N] = {0};
int markD1[MAX_N * 2] = {0};
int markD2[MAX_N * 2] = {0};

int check(int r, int k)
{
    int d1 = N + k - r;
    int d2 = k + r;
    return !markR[r] && !markD1[d1] && !markD2[d2];
}

void input()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &board[i][j]);
}

void reset()
{
    for (int i = 0; i < MAX_N; i++)
    {
        markR[i] = 0;
        X[i] = 0;
    }
    for (int i = 0; i < MAX_N * 2; i++)
    {
        markD1[i] = 0;
        markD2[i] = 0;
    }
}

int checkBoard()
{
    reset();
    for (int k = 0; k < N; k++)
    {
        for (int r = 0; r < N; r++)
        {
            if (board[r][k] == 1)
            {
                if (!check(r, k))
                    return 0;
                markR[r] = 1;
                markD1[N + k - r] = 1;
                markD2[k + r] = 1;
                X[k] = r;
            }
        }
    }
    return 1;
}

int main()
{
    scanf("%d", &T);
    int *ans = (int *)malloc((size_t)T * sizeof *ans);
    if (!ans)
        return 1;

    for (int t = 0; t < T; t++)
    {
        input();
        ans[t] = checkBoard();
    }

    for (int t = 0; t < T; t++)
        printf("%d\n", ans[t]);

    free(ans);
    return 0;
}