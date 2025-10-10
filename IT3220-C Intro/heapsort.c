#include <stdio.h>

#define MAX_VAL 100000
#define BUFFER_SIZE 1048576  // 1MB buffer for faster I/O

static int count[MAX_VAL + 1];
static char buffer[BUFFER_SIZE];
static int pos = 0;

// Fast output function
void write_int(int x) {
    int len = 0;
    char digits[10];
    
    // Convert to digits
    do {
        digits[len++] = x % 10 + '0';
        x /= 10;
    } while (x);
    
    // Write digits in reverse
    while (len--) {
        buffer[pos++] = digits[len];
    }
    buffer[pos++] = ' ';
    
    // Flush buffer if nearly full
    if (pos > BUFFER_SIZE - 20) {
        fwrite(buffer, 1, pos, stdout);
        pos = 0;
    }
}

int main() {
    // Fast input setup
    setvbuf(stdin, NULL, _IOFBF, BUFFER_SIZE);
    
    int n;
    scanf("%d", &n);
    
    // Count frequencies
    int num;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        count[num]++;
    }
    
    // Write sorted sequence
    int remaining = n;
    for (int i = 0; i <= MAX_VAL; i++) {
        while (count[i]--) {
            write_int(i);
            remaining--;
            if (remaining == 0) {
                buffer[pos-1] = '\n';  // Replace last space with newline
                break;
            }
        }
    }
    
    // Flush remaining output
    fwrite(buffer, 1, pos, stdout);
    
    return 0;
}