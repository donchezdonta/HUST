#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100001

typedef struct Candidate {
    char code[10];
    int score;
} Candidate;

int n;
Candidate* a[N];

void swap(int i, int j) {
    Candidate* tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void heapify(int i, int size) {
    int L = 2 * i;
    int R = 2 * i + 1;
    int minIdx = i;

    if (L <= size && (a[L]->score < a[minIdx]->score || 
        (a[L]->score == a[minIdx]->score && strcmp(a[L]->code, a[minIdx]->code) > 0))) {
        minIdx = L;
    }
    if (R <= size && (a[R]->score < a[minIdx]->score || 
        (a[R]->score == a[minIdx]->score && strcmp(a[R]->code, a[minIdx]->code) > 0))) {
        minIdx = R;
    }

    if (minIdx != i) {
        swap(i, minIdx);
        heapify(minIdx, size);
    }
}

void buildHeap() {
    for (int i = n / 2; i >= 1; i--)
        heapify(i, n);
}

void sortCandidates() {
    buildHeap();
    for (int i = n; i >= 2; i--) {
        swap(1, i);
        heapify(1, i - 1);
    }
}

void inputCandidates() {
    n = 0;
    char code[10];
    int score;
    while (scanf("%s", code) == 1 && code[0] != '#') {
        scanf("%d", &score);
        n++;
        a[n] = (Candidate*)malloc(sizeof(Candidate));
        strcpy(a[n]->code, code);
        a[n]->score = score;
    }
}

void printCandidates() {
    for (int i = 1; i <= n; i++) {
        printf("%s %d\n", a[i]->code, a[i]->score);
    }
}

int main() {
    inputCandidates();
    sortCandidates();
    printCandidates();

    for (int i = 1; i <= n; i++) {
        free(a[i]);
    }
    return 0;
}