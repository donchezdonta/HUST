#include <stdio.h>
#include <ctype.h>
#include <string.h>

void normalize(char* s, int len){
    int space = 1;
    int i = 0;
    for(int j = 0; j<len;j++){
        if(space == 1) {
            if (s[j] != ' '){
                s[i] = toupper(s[j]);
                i++;
                space = 0;
            }
            else{
                space = 1;
            }
        }
        else {
            s[i] = tolower(s[j]);
            i++;
            if (s[j] == ' ') space = 1;
        }
    }
    if (s[i-1] == ' ') s[i-1] = '\0';
    s[i] = '\0';
}

int main(){
    int len;
    scanf("%d\n", &len);
    char name[51][100];
    int len_str = 0;
    for(int i = 0 ; i < len;i++){
        fgets(name[i],51,stdin);
        len_str = strlen(name[i]);
        if(len_str > 0){
            name[i][len_str-1] = '\0';
        }
    }
    int space = 1;
    for(int i = 0; i<len;i++){
        normalize(name[i], strlen(name[i]));
    }
    for (int i = 0; i<len; i++) {
        printf("%s\n",name[i]);
    }
    return 0;
}
