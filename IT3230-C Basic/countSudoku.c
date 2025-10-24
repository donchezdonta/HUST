#include <stdio.h>
/*Thứ tự duyệt các biến: từ trên xuống dưới và từ trái qua phải
    •Hàm try(r, c): thử giá trị cho X[r, c]
       •Xét các giá trị v từ 1 đến 9
    •Hàm check(v, r, c):
        •Giá trị v chỉ hợp lệ khi nó chưa xuất hiện
        •Trên hàng r: markR[r, v] = 0
        •Trên cột c: markC[c, v] = 0
        •Trên bảng 3 x 3 ở tọa độ (r/3, c/3): markS[r/3, c/3, v] = 0 */
int X[9][9];
int markR[9][10];
int markC[9][10];
int markS[3][3][10];
int cnt;

void init()
{
    for (int i = 0; i < 9; i++)
        for (int v = 0; v <= 9; v++)
        {
            markR[i][v] = 0;
            markC[i][v] = 0;
        }
    for (int bi = 0; bi < 3; bi++)
        for (int bj = 0; bj < 3; bj++)
            for (int v = 0; v <= 9; v++)
                markS[bi][bj][v] = 0;
    cnt = 0;
}

void input()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            scanf("%d", &X[i][j]);
            if (X[i][j] != 0)
            {
                int v = X[i][j];
                markR[i][v] = 1;
                markC[j][v] = 1;
                markS[i / 3][j / 3][v] = 1;
            }
        }
}

int checkInput()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (X[i][j] < 0 || X[i][j] > 9)
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

int check(int v, int r, int c)
{
    int br = r / 3, bc = c / 3;
    return !markR[r][v] && !markC[c][v] && !markS[br][bc][v];
}

void Try(int r, int c)
{
    if (r == 9)
    {
        ++cnt;
        return;
    }
    int nr = (c == 8) ? r + 1 : r;
    int nc = (c == 8) ? 0 : c + 1;
    if (X[r][c] != 0)
    {
        Try(nr, nc);
        return;
    }
    for (int v = 1; v <= 9; v++)
    {
        if (check(v, r, c))
        {
            X[r][c] = v;
            int br = r / 3, bc = c / 3;
            markR[r][v] = markC[c][v] = markS[br][bc][v] = 1;
            Try(nr, nc);
            markR[r][v] = markC[c][v] = markS[br][bc][v] = 0;
            X[r][c] = 0;
        }
    }
}

int main()
{
    init();
    input();
    if (!checkInput())
    {
        printf("0\n");
        return 0;
    }
    Try(0, 0);
    printf("%d\n", cnt);
    return 0;
}