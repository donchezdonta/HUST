#include <stdio.h>
#include <stdlib.h>

void hanoi(int n, char src, char dst, char aux) {
    if (n == 1) {
        printf("%c => %c\n", src, dst);
        return;
    }
    
    hanoi(n - 1, src, aux, dst);
    printf("%c => %c\n", src, dst);
    hanoi(n - 1, aux, dst, src);
}

int main() {
    int n;
    scanf("%d", &n);
    if (n <= 0 || n > 20) 
        return 1;
    
    hanoi(n, 'A', 'B', 'C');
    return 0;
}