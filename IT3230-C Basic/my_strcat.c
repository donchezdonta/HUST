#include <stdio.h>
#include <string.h>

char* my_strcat(char *dest, char *src){
    int idx = strlen(dest);
    for(int i = 0; i < strlen(src); i++){
        dest[idx] = src[i];
        ++idx;
    }
    dest[idx] = '\0';
    return dest;
}

int main(){
    char s[1000] = "Robert";
    char t[1000] = "Ziegler";
    my_strcat(s, t);
    printf("%s\n", s);
    return 0;
}
