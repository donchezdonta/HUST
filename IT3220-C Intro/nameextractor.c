#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 50
#define MAX_TEXT_LENGTH 2000

int isMultilingualLetter(unsigned char c) {
    return isalpha(c) || (c >= 128); 
}

int isValidNameChar(unsigned char c) {
    return isMultilingualLetter(c) || c == '-';
}

// Remove all punctuation and periods
void stripPunct(char *s) {
    int i, j = 0;
    for (i = 0; s[i]; i++) {
        if (isValidNameChar((unsigned char)s[i]))
            s[j++] = s[i];
    }
    s[j] = '\0';
}

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    setlocale(LC_ALL, "");
    char text[MAX_TEXT_LENGTH];
    char *names[MAX_NAMES];
    int nameCount = 0;

    for (int i = 0; i < MAX_NAMES; i++) names[i] = NULL;

    if (!fgets(text, MAX_TEXT_LENGTH, stdin)) {
        printf("EMPTY\n");
        return 0;
    }

    char *token = strtok(text, " \t\n");
    while (token != NULL) {
        if (isupper((unsigned char)token[0])) {
            char cleaned[MAX_NAME_LENGTH];
            strncpy(cleaned, token, MAX_NAME_LENGTH - 1);
            cleaned[MAX_NAME_LENGTH - 1] = '\0';
            stripPunct(cleaned);

            if (strlen(cleaned) > 0) {
                int isDuplicate = 0;
                for (int i = 0; i < nameCount; i++) {
                    if (strcmp(names[i], cleaned) == 0) {
                        isDuplicate = 1;
                        break;
                    }
                }
                if (!isDuplicate && nameCount < MAX_NAMES) {
                    names[nameCount] = strdup(cleaned);
                    nameCount++;
                }
            }
        }
        token = strtok(NULL, " \t\n");
    }

    qsort(names, nameCount, sizeof(char *), compareStrings);

    if (nameCount == 0) {
        printf("EMPTY\n");
    } else {
        for (int i = 0; i < nameCount; i++) {
            printf("%s", names[i]);
            if (i < nameCount - 1) printf(" ");
        }
        printf("\n");
    }

    for (int i = 0; i < nameCount; i++) free(names[i]);
    return 0;
}