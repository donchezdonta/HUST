#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int min_x = 101, max_x = 0, min_y = 101, max_y = 0;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 < min_x) min_x = x1;
        if (x2 < min_x) min_x = x2;
        if (x1 > max_x) max_x = x1;
        if (x2 > max_x) max_x = x2;
        if (y1 < min_y) min_y = y1;
        if (y2 < min_y) min_y = y2;
        if (y1 > max_y) max_y = y1;
        if (y2 > max_y) max_y = y2;
    }
    int area = (max_x - min_x) * (max_y - min_y);
    printf("%d\n", area);
    return 0;
}