#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 200

int n, m;
char s[MAX + 1];

int hashCode(char *str, int mod) {
    int code = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        code = (code * 256 + str[i]) % mod;
    }
    return code;
}

void solve() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        printf("%d\n", hashCode(s, m));
    }
}

int main() {
    solve();
    return 0;
}