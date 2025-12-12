#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100001

typedef struct Student {
    char ID[11];
    int grade;
    int pos;
} Student;

Student S[N];
int n;

void swapStudent(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyGrade(Student S[], int i, int n) {
    int L = 2*i, R = 2*i+1, maxIdx = i;
    if (L <= n && S[L].grade > S[maxIdx].grade) maxIdx = L;
    if (R <= n && S[R].grade > S[maxIdx].grade) maxIdx = R;
    if (maxIdx != i) {
        swapStudent(&S[i], &S[maxIdx]);
        heapifyGrade(S, maxIdx, n);
    } 
}

void heapifyID(Student S[], int i, int n) {
    int L = 2*i, R = 2*i+1, maxIdx = i;
    if (L <= n && strcmp(S[L].ID, S[maxIdx].ID) > 0) maxIdx = L;
    if (R <= n && strcmp(S[R].ID, S[maxIdx].ID) > 0) maxIdx = R;
    if (maxIdx != i) {
        swapStudent(&S[i], &S[maxIdx]);
        heapifyID(S, maxIdx, n);
    } 
}

void heapSortGrade(Student S[], int n) {
    for (int i = n/2; i >= 1; i--) heapifyGrade(S, i, n);
    for (int i = n; i >= 2; i--) {
        swapStudent(&S[1], &S[i]);
        heapifyGrade(S, 1, i-1);
    }
}

void heapSortID(Student S[], int n) {
    for (int i = n/2; i >= 1; i--) heapifyID(S, i, n);
    for (int i = n; i >= 2; i--) {
        swapStudent(&S[1], &S[i]);
        heapifyID(S, 1, i-1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s%d", S[i].ID, &S[i].grade);
    }

    heapSortGrade(S, n);
    for (int i = 1; i <= n; i++) {
        S[i].pos = i - 1;
    }
    
    heapSortID(S, n);
    for (int i = 1; i <= n; i++) {
        printf("%s %d\n", S[i].ID, S[i].pos);
    }
    
    return 0;
}