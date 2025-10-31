#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
int uconvert(const char* filename) {
    FILE *source, *temp;
    int ch;
    char temp_name[256];
    int chars_processed = 0;
    
    source = fopen(filename, "rb");
    if (source == NULL) {
        printf("Cannot open source file '%s'\n", filename);
        return 0;
    }
    
    snprintf(temp_name, sizeof(temp_name), "%s.tmp", filename);
    
    temp = fopen(temp_name, "wb");
    if (temp == NULL) {
        printf("Cannot create temporary file '%s'\n", temp_name);
        fclose(source);
        return 0;
    }
    
    while ((ch = fgetc(source)) != EOF) {
        if (isalpha(ch)) {
            ch = toupper(ch);
        }
        
        if (fputc(ch, temp) == EOF) {
            printf("Write failed after %d characters\n", chars_processed);
            fclose(source);
            fclose(temp);
            remove(temp_name);
            return 0;
        }
        
        chars_processed++;
    }
    
    fclose(source);
    fclose(temp);
    
    if (remove(filename) != 0) {
        printf("Cannot remove original file '%s'\n", filename);
        remove(temp_name);
        return 0;
    }
    
    if (rename(temp_name, filename) != 0) {
        printf("Cannot rename temporary file to '%s'\n", filename);
        return 0;
    }
    
    printf("Successfully capitalized %d characters in '%s'\n", chars_processed, filename);
    return 1;
}
 
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments (got %d, expected 1)\n", argc - 1);
        return 1;
    }
    
    char *filename = argv[1];
    
    if (strlen(filename) == 0) {
        printf("Filename cannot be empty\n");
        return 1;
    }
    
    FILE *test = fopen(filename, "rb");
    if (test == NULL) {
        printf("File '%s' does not exist or cannot be read\n", filename);
        return 1;
    }
    fclose(test);
    
    printf("About to convert all letters to uppercase in '%s' (original will be overwritten). Continue? (y/n): ", filename);
    char ans;
    scanf(" %c", &ans);
    if (ans != 'y' && ans != 'Y') {
        printf("Operation cancelled\n");
        return 0;
    }
    
    if (uconvert(filename)) {
        return 0;
    }
    
    return 1;
}
