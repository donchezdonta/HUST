#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define BUFFER_SIZE 8192

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
 
void displayMenu() {
    printf("\n=== CHUONG TRINH SAO CHEP TAP TIN ===\n");
    printf("1. Copy by character\n");
    printf("2. Copy by line\n");
    printf("3. Copy by block - optional size\n");
    printf("4. Quit\n");
    printf("Lua chon cua ban: ");
}
 
long getFileSize(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return -1;
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}
 
int copyByCharacter(const char* source, const char* dest) {
    FILE *src = fopen(source, "r");
    FILE *dst = fopen(dest, "w");
    
    if (src == NULL || dst == NULL) {
        if (src) fclose(src);
        if (dst) fclose(dst);
        return 0;
    }
    
    int ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }
    
    fclose(src);
    fclose(dst);
    return 1;
}
 
int copyByLine(const char* source, const char* dest) {
    FILE *src = fopen(source, "r");
    FILE *dst = fopen(dest, "w");
    
    if (src == NULL || dst == NULL) {
        if (src) fclose(src);
        if (dst) fclose(dst);
        return 0;
    }
    
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, src)) != -1) {
        fputs(line, dst);
    }
    
    free(line);
    fclose(src);
    fclose(dst);
    return 1;
}
 
int copyByBlock(const char* source, const char* dest, size_t block_size) {
    FILE *src = fopen(source, "rb");
    FILE *dst = fopen(dest, "wb");
    
    if (src == NULL || dst == NULL) {
        if (src) fclose(src);
        if (dst) fclose(dst);
        return 0;
    }
    
    char* buffer = (char*)malloc(block_size);
    if (buffer == NULL) {
        fclose(src);
        fclose(dst);
        return 0;
    }
    
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, block_size, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }
    
    free(buffer);
    fclose(src);
    fclose(dst);
    return 1;
}
 
double measureCopyTime(int (*copyFunc)(const char*, const char*, size_t),
                       const char* src, const char* dst, size_t block_size) {
    clock_t start = clock();
    
    if (block_size > 0) {
        copyFunc(src, dst, block_size);
    }
    
    clock_t end = clock();
    return ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
}
 
int main() {
    char source[256], destination[256];
    int choice;
    size_t block_size;
    clock_t start, end;
    double time_elapsed;
    
    printf("Nhap ten tap tin nguon: ");
    scanf("%s", source);
    
    long file_size = getFileSize(source);
    if (file_size < 0) {
        printf("Loi: Khong the mo tap tin nguon!\n");
        return 1;
    }
    
    printf("Kich thuoc tap tin: %ld bytes (%.2f KB)\n",
           file_size, file_size / 1024.0);
    
    if (file_size < 655360) {
        printf("Canh bao: Tap tin nho hon 640KB. Ket qua do thoi gian co the khong chinh xac.\n");
    }
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        if (choice == 4) {
            printf("Ket thuc chuong trinh.\n");
            break;
        }
        
        printf("Nhap ten tap tin dich: ");
        scanf("%s", destination);
        
        switch (choice) {
            case 1:
                printf("\nDang sao chep theo ky tu...\n");
                start = clock();
                if (copyByCharacter(source, destination)) {
                    end = clock();
                    time_elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
                    printf("Sao chep thanh cong!\n");
                    printf("Thoi gian thuc hien: %.2f ms\n", time_elapsed);
                } else {
                    printf("Loi khi sao chep tap tin!\n");
                }
                return 0;
                
            case 2:
                printf("\nDang sao chep theo dong...\n");
                start = clock();
                if (copyByLine(source, destination)) {
                    end = clock();
                    time_elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
                    printf("Sao chep thanh cong!\n");
                    printf("Thoi gian thuc hien: %.2f ms\n", time_elapsed);
                } else {
                    printf("Loi khi sao chep tap tin!\n");
                }
                return 0;
                
            case 3:
                printf("Nhap kich thuoc block (bytes, default 8192): ");
                scanf("%zu", &block_size);
                
                if (block_size <= 0) {
                    block_size = BUFFER_SIZE;
                }
                
                printf("\nDang sao chep theo block (%zu bytes)...\n", block_size);
                start = clock();
                if (copyByBlock(source, destination, block_size)) {
                    end = clock();
                    time_elapsed = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
                    printf("Sao chep thanh cong!\n");
                    printf("Thoi gian thuc hien: %.2f ms\n", time_elapsed);
                } else {
                    printf("Loi khi sao chep tap tin!\n");
                }
                return 0;
                
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
    
    return 0;
}
