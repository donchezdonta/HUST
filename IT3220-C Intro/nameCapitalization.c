#include <stdio.h>
#include <ctype.h>
#include <string.h>

void normalize(char *s) {
    int i = 0;
    while (s[i]) {
        while (s[i] == ' ') i++;
        if (!s[i]) break;
        if (i == 0 || s[i-1] == ' ') s[i] = toupper(s[i]);
        else s[i] = tolower(s[i]);
        i++;
    }

    int j = 0, space = 0;
    for (i = 0; s[i]; i++) {
        if (s[i] != ' ') {
            s[j++] = s[i];
            space = 0;
        } else if (!space) {
            s[j++] = ' ';
            space = 1;
        }
    }
    if (j > 0 && s[j-1] == ' ') j--;
    s[j] = 0;
}

int main() {
    int n;
    char names[100][51];
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        fgets(names[i], 51, stdin);
        int l = strlen(names[i]);
        if (l && names[i][l-1] == '\n') names[i][l-1] = 0;
        normalize(names[i]);
    }
    for (int i = 0; i < n; i++)
        puts(names[i]);
    return 0;
}