#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char id[11];
    int grade;
    int pos;
};

int cmp_grade(const void* a, const void* b) {
    return ((struct Student*)a)->grade - ((struct Student*)b)->grade;
}

int cmp_id(const void* a, const void* b) {
    return strcmp(((struct Student*)a)->id, ((struct Student*)b)->id);
}

int main() {
    int n;
    scanf("%d", &n);
    struct Student students[100001];
    for (int i = 0; i < n; i++) {
        scanf("%s %d", students[i].id, &students[i].grade);
    }
    qsort(students, n, sizeof(struct Student), cmp_grade);
    for (int i = 0; i < n; i++) {
        students[i].pos = i;
    }
    qsort(students, n, sizeof(struct Student), cmp_id);
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].id, students[i].pos);
    }
    return 0;
}