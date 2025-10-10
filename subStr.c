#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
char* subStr(char* s1, int offset, int number) {
    if (s1 == NULL || offset < 0 || number < 0) {
        return NULL;
    }
    
    int len = strlen(s1);
    
    if (offset >= len) {
        return NULL;
    }
    
    int remaining = len - offset;
    int actual_length = (number > remaining) ? remaining : number;
    
    char* result = (char*)malloc((actual_length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < actual_length; i++) {
        result[i] = s1[offset + i];
    }
    result[actual_length] = '\0';
    
    return result;
}
 
int main() {
    char original[256];
    int offset, length;
    char* result;
    char choice;
    
    do {
        printf("\n=== Substring separator ===\n");
        printf("Input original string: ");
        fgets(original, sizeof(original), stdin);
        
        size_t len = strlen(original);
        if (len > 0 && original[len-1] == '\n') {
            original[len-1] = '\0';
        }
        
        printf("Input offset: ");
        scanf("%d", &offset);
        
        printf("Input length: ");
        scanf("%d", &length);
        
        result = subStr(original, offset, length);
        
        if (result != NULL) {
            printf("\nResults: \"%s\"\n", result);
            free(result);
        } else {
            printf("\nInvalid parameters.\n");
        }
        
        while (getchar() != '\n');
        
        printf("\nContinue? (y/n): ");
        scanf("%c", &choice);
        while (getchar() != '\n');
        
    } while (choice == 'y' || choice == 'Y');
    
    printf("Operation successful!.\n");
    return 0;
}
