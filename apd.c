#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int apd(const char* src, const char* target) {
    FILE *source, *dest;
    int ch;
    
    source = fopen(src, "rb");
    if (source == NULL) {
        printf("Cannot open source file '%s'\n", src);
        return 0;
    }
    
    dest = fopen(target, "ab");
    if (dest == NULL) {
        printf("Cannot open target file '%s' for appending\n", target);
        fclose(source);
        return 0;
    }
    
    int bytes_copied = 0;
    while ((ch = fgetc(source)) != EOF) {
        if (fputc(ch, dest) == EOF) {
            printf("Error: Write failed after %d bytes\n", bytes_copied);
            fclose(source);
            fclose(dest);
            return 0;
        }
        bytes_copied++;
    }
    
    fclose(source);
    fclose(dest);
    
    printf("Successfully appended %d bytes from '%s' to '%s'\n", bytes_copied, src, target);
    return 1;
}
 
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments (got %d, expected 2)\n", argc - 1);
        return 1;
    }
    
    char *source = argv[1];
    char *target = argv[2];
    
    if (strlen(source) == 0) {
        printf("Source filename cannot be empty\n");
        return 1;
    }
    
    if (strlen(target) == 0) {
        printf("Target filename cannot be empty\n");
        return 1;
    }
    
    if (strcmp(source, target) == 0) {
        printf("Source and target are the same file\n");
        return 1;
    }
    
    FILE *test = fopen(source, "rb");
    if (test == NULL) {
        printf("Source file '%s' does not exist or cannot be read\n", source);
        return 1;
    }
    fclose(test);
    
    printf("About to append '%s' to '%s'. Continue? (y/n): ", source, target);
    char ans;
    scanf(" %c", &ans);
    if (ans != 'y' && ans != 'Y') {
        printf("Operation cancelled\n");
        return 0;
    }
    
    if (apd(source, target)) {
        return 0;
    }
    
    return 1;
}
