/*Biểudiễnphươngán: x[1..n], trongđóx[i] làchỉsốhàngcủaquânhậutrêncộti
•Ràngbuộc
    •x[i] ≠ x[j]
    •x[i] + i≠ x[j] + j
    •x[i] –i≠ x[j] -j
•Mảngđánhdấu:
    •markR[r] = 1: hàngrcóquânhậu
    •markD1[d] = 1: nghĩalàcóquânhậutrênhàngr, cộtkvớid= n–k+ r
    •markD2[d] = 1: nghĩalàcóquânhậutrênhàngr, cộtkvớik+ r= d
*/
#include <stdio.h>
int x[15] = {0};
int N;
int markR[15] = {0};
int markD1[30] = {0};
int markD2[30] = {0};
int cnt = 0;

int inputData()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int val;
            scanf("%d", &val);
            if (val == 1)
            {
                x[j] = i + 1;
                markR[i] = 1;
                markD1[N + j - i] = 1;
                markD2[j + i] = 1;
            }
        }
    }
    return 1;
}

void printData()
{
    for (int k = 0; k < N; k++)
        printf("x[%d] = %d\n", k, x[k]);
}

int check(int r, int k)
{
    int d1 = N + k - r;
    int d2 = k + r;
    return !markR[r] && !markD1[d1] && !markD2[d2];
}

int checkBoard()
{
    for (int k = 0; k < N; k++)
    {
        if (x[k] > 0)
        {
            int r = x[k] - 1;
            if (!check(r, k))
                return 0;
            markR[r] = 1;
            markD1[N + k - r] = 1;
            markD2[k + r] = 1;
        }
    }
    return 1;
}

void Try(int k)
{
    if (x[k] > 0)
    {
        if (k == N - 1)
            cnt = cnt + 1;
        else
            Try(k + 1);
        return;
    }
    for (int r = 0; r < N; r++)
    {
        if (check(r, k))
        {
            x[k] = r + 1;
            markR[r] = 1;
            markD1[N + k - r] = 1;
            markD2[k + r] = 1;
            if (k == N - 1)
                cnt = cnt + 1;
            else
                Try(k + 1);
            x[k] = 0;
            markR[r] = 0;
            markD1[N + k - r] = 0;
            markD2[k + r] = 0;
        }
    }
}

int main()
{
    inputData();
    Try(0);
    printf("%d\n", cnt);
    return 0;
}
