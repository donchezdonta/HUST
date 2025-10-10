#include <stdio.h>

int main() {
    double num, total = 0.0;
    
    printf("Enter numbers (end with 0):\n");
    
    do {
        scanf("%lf", &num);
        total += num;
    } while (num != 0);
    
    // Since we included 0 in the sum, we need to subtract it
    total -= 0.0;  
    
    printf("Total: %.2f\n", total);
    
    return 0;
}