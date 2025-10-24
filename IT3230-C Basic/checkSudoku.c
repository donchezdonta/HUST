#include <stdio.h>
#include <stdlib.h>

int X[9][9] = {0};
int T;
int markR[9][10] = {0};
int markC[9][10] = {0};
int markS[3][3][10] = {0};

void input()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &X[i][j]);
}

int checkInput() // kiểm tra tính hợp lệ của dữ liệu đầu vào
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (X[i][j] < 1 || X[i][j] > 9)
                return 0;
    return 1;
}

void printSudokuMatrix()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (j)
                putchar(' ');
            printf("%d", X[i][j]);
        }
        putchar('\n');
    }
}

void reset() // reset lại các mảng markR, markC, markS
{
    for (int i = 0; i < 9; i++)
    {
        for (int v = 1; v <= 9; v++)
        {
            markR[i][v] = 0;
            markC[i][v] = 0;
        }
    }
    for (int bi = 0; bi < 3; bi++)
        for (int bj = 0; bj < 3; bj++)
            for (int v = 1; v <= 9; v++)
                markS[bi][bj][v] = 0;
}

int check(int v, int r, int c) // check phần tử v có thể đưa vào ô hàng r cột c không?
{
    int br = r / 3, bc = c / 3;
    if (markR[r][v] || markC[c][v] || markS[br][bc][v])
        return 0;
    markR[r][v] = 1;
    markC[c][v] = 1;
    markS[br][bc][v] = 1;
    return 1;
}

int checkSudoku() // check toàn bộ ma trận
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!check(X[i][j], i, j))
                return 0;
    return 1;
}

int main()
{
    scanf("%d", &T);

    int *ans = (int *)malloc((size_t)T * sizeof *ans);
    if (!ans)
        return 1;

    for (int k = 0; k < T; k++)
    {
        input();
        if (!checkInput())
        {
            ans[k] = 0;
            continue;
        }
        reset();
        ans[k] = checkSudoku();
    }

    for (int k = 0; k < T; k++)
        puts(ans[k] ? "1" : "0");

    free(ans);
    return 0;
}