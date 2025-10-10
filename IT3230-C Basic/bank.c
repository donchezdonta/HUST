#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACC 1001

struct List {
    int to;
    struct List* next;
};

char accounts[MAX_ACC][21];
int account_count = 0;
struct List* adj[MAX_ACC];
long long sum_from[MAX_ACC];

int get_id(char* acc) {
    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i], acc) == 0) return i;
    }
    strcpy(accounts[account_count], acc);
    return account_count++;
}

void add_edge(int from, int to) {
    struct List* p = malloc(sizeof(struct List));
    p->to = to;
    p->next = adj[from];
    adj[from] = p;
}

int cmp_acc(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

int has_cycle(int start, int k, int current, int depth, int visited[]) {
    if (depth == k) {
        return current == start;
    }
    for (struct List* p = adj[current]; p; p = p->next) {
        if (!visited[p->to]) {
            visited[p->to] = 1;
            if (has_cycle(start, k, p->to, depth + 1, visited)) return 1;
            visited[p->to] = 0;
        }
    }
    return 0;
}

int main() {
    char line[200];
    int count = 0;
    long long total_money = 0;
    memset(sum_from, 0, sizeof(sum_from));
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        char from[21], to[21], time[9], atm[11];
        int money;
        sscanf(line, "%s %s %d %s %s", from, to, &money, time, atm);
        int fid = get_id(from), tid = get_id(to);
        add_edge(fid, tid);
        sum_from[fid] += money;
        count++;
        total_money += money;
    }
    qsort(accounts, account_count, 21, cmp_acc);
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        char from[21];
        int kk;
        if (strstr(line, "?number_transactions")) {
            printf("%d\n", count);
        } else if (strstr(line, "?total_money_transaction")) {
            printf("%lld\n", total_money);
        } else if (strstr(line, "?list_sorted_accounts")) {
            for (int i = 0; i < account_count; i++) {
                if (i) printf(" ");
                printf("%s", accounts[i]);
            }
            printf("\n");
        } else if (sscanf(line, "?total_money_transaction_from %s", from) == 1) {
            int id = get_id(from);
            printf("%lld\n", sum_from[id]);
        } else if (sscanf(line, "?inspect_cycle %s %d", from, &kk) == 2) {
            int id = get_id(from);
            int visited[MAX_ACC] = {0};
            visited[id] = 1;
            int res = has_cycle(id, kk, id, 0, visited);
            printf("%d\n", res);
        }
    }
    return 0;
}