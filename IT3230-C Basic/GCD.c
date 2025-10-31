#include <stdio.h>
#include <math.h>

int GCD(int a, int b)
{
    if (a == 0 | b == 0)
        return a + b;
    while (a != b)
    {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

int LCM(int a, int b)
{
    return a * b / GCD(a, b);
}

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d", GCD(a, b));
    return 0;
}