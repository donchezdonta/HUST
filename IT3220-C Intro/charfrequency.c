#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char str[1000];
    int freq[26] = {0};
    int i, hasLetter = 0;

    fgets(str, sizeof(str), stdin);

    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("Empty\n");
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            freq[tolower(str[i]) - 'a']++;
            hasLetter = 1;
        }
    }

    if (!hasLetter) {
        printf("No alphabet\n");
        return 0;
    }

    for (i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", 'a' + i, freq[i]);
        }
    }
    
    return 0;
}
