#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_cyclone_word(char *word) {
    int len = strlen(word);
    if (len <= 1) return 1;
    
    char arranged[len + 1];
    int left = 0, right = len - 1;
    int idx = 0;
    
    // Alternate taking from left and right
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            arranged[idx++] = word[left++];
        } else {
            arranged[idx++] = word[right--];
        }
    }
    arranged[idx] = '\0';
    
    // Check if arranged string is in alphabetical order
    for (int i = 1; i < len; i++) {
        if (arranged[i] < arranged[i-1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);
    
    // Remove newline
    input[strcspn(input, "\n")] = '\0';
    
    char *token = strtok(input, " ");
    while (token != NULL) {
        if (!is_cyclone_word(token)) {
            printf("false\n");
            return 0;
        }
        token = strtok(NULL, " ");
    }
    
    printf("true\n");
    return 0;
}