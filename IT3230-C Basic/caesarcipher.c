#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int caesar(const char* src, int offset, const char* dst) {
    FILE *source, *dest;
    int ch;
    int chars_processed = 0;
    
    source = fopen(src, "rb");
    if (source == NULL) {
        printf("Cannot open source file '%s'\n", src);
        return 0;
    }
    
    dest = fopen(dst, "wb");
    if (dest == NULL) {
        printf("Cannot create destination file '%s'\n", dst);
        fclose(source);
        return 0;
    }
    
    while ((ch = fgetc(source)) != EOF) {
        int new_ch = ch;
        
        if (ch >= 'A' && ch <= 'Z') {
        new_ch = ((ch - 'A' + offset) % 26 + 26) % 26 + 'A';
    	}
    	else if (ch >= 'a' && ch <= 'z') {
        new_ch = ((ch - 'a' + offset) % 26 + 26) % 26 + 'a';
    	}
        
        if (fputc(new_ch, dest) == EOF) {
            printf("Write failed after %d characters\n", chars_processed);
            fclose(source);
            fclose(dest);
            return 0;
        }
        
        chars_processed++;
    }
    
    fclose(source);
    fclose(dest);
    
    if (offset > 0) {
        printf("Successfully encrypted %d characters from '%s' to '%s' (offset: +%d)\n",
               chars_processed, src, dst, offset);
    } else {
        printf("Successfully decrypted %d characters from '%s' to '%s' (offset: %d)\n",
               chars_processed, src, dst, offset);
    }
    return 1;
}
 
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Wrong number of arguments (got %d, expected 3)\n", argc - 1);
        return 1;
    }
    
    char *source = argv[1];
    char *offset_str = argv[2];
    char *destination = argv[3];
    
    if (strlen(source) == 0) {
        printf("Source filename cannot be empty\n");
        return 1;
    }
    
    if (strlen(destination) == 0) {
        printf("Destination filename cannot be empty\n");
        return 1;
    }
    
    if (strcmp(source, destination) == 0) {
        printf("Source and destination files are the same\n");
        return 1;
    }
    
    int offset = atoi(offset_str);
    if (offset == 0 && strcmp(offset_str, "0") != 0) {
        printf("Invalid offset value '%s'\n", offset_str);
        return 1;
    }
    
    FILE *test = fopen(source, "rb");
    if (test == NULL) {
        printf("Source file '%s' does not exist or cannot be read\n", source);
        return 1;
    }
    fclose(test);
    
    FILE *dest_test = fopen(destination, "rb");
    if (dest_test != NULL) {
        fclose(dest_test);
        printf("Destination file '%s' already exists and will be overwritten. Continue? (y/n): ", destination);
        char answer;
        scanf(" %c", &answer);
        if (answer != 'y' && answer != 'Y') {
            printf("Operation cancelled\n");
            return 0;
        }
    }
    
    if (offset > 0) {
        printf("Encrypting '%s' with offset +%d to '%s'...\n", source, offset, destination);
    } else {
        printf("Decrypting '%s' with offset %d to '%s'...\n", source, offset, destination);
    }
    
    if (caesar(source, offset, destination)) {
        return 0;
    }
    
    return 1;
}
