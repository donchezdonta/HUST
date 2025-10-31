#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Submission {
    char userID[11];
    char problemID[4];
    char timePoint[9];
    char status[4];
    int point;
    int time_sec;
};

struct UserData {
    int err_count;
    int prob_max[100];
    int total_point;
};

struct HashEntry {
    char key[11];
    int value;
    struct HashEntry* next;
};

struct HashEntry* hash_table[10007];

int user_count = 0;
struct UserData user_data[10001];
struct Submission sub[100001];
int sub_count = 0;
int total_err = 0;

unsigned int hash(char* str) {
    unsigned int h = 0;
    while (*str) h = h * 31 + *str++;
    return h % 10007;
}

int get_user_id(char* user) {
    unsigned int h = hash(user);
    struct HashEntry* e = hash_table[h];
    while (e) {
        if (strcmp(e->key, user) == 0) return e->value;
        e = e->next;
    }
    e = malloc(sizeof(struct HashEntry));
    strcpy(e->key, user);
    e->value = user_count++;
    e->next = hash_table[h];
    hash_table[h] = e;
    return e->value;
}

int timeToSeconds(char* time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

int cmp(const void* a, const void* b) {
    struct Submission* sa = (struct Submission*)a;
    struct Submission* sb = (struct Submission*)b;
    return sa->time_sec - sb->time_sec;
}

int main() {
    char line[100];
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        struct Submission s;
        sscanf(line, "%s %s %s %s %d", s.userID, s.problemID, s.timePoint, s.status, &s.point);
        s.time_sec = timeToSeconds(s.timePoint);
        sub[sub_count++] = s;
        total_err += strcmp(s.status, "ERR") == 0;
        int uid = get_user_id(s.userID);
        user_data[uid].err_count += strcmp(s.status, "ERR") == 0;
        int pid = (s.problemID[1] - '0') * 10 + (s.problemID[2] - '0');
        if (s.point > user_data[uid].prob_max[pid]) user_data[uid].prob_max[pid] = s.point;
    }
    for (int i = 0; i < user_count; i++) {
        for (int j = 0; j < 100; j++) user_data[i].total_point += user_data[i].prob_max[j];
    }
    qsort(sub, sub_count, sizeof(struct Submission), cmp);
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;
        char uid[11], from[9], to[9];
        if (strcmp(line, "?total_number_submissions\n") == 0) {
            printf("%d\n", sub_count);
        } else if (strcmp(line, "?number_error_submision\n") == 0) {
            printf("%d\n", total_err);
        } else if (sscanf(line, "?number_error_submision_of_user %s", uid) == 1) {
            int id = get_user_id(uid);
            printf("%d\n", user_data[id].err_count);
        } else if (sscanf(line, "?total_point_of_user %s", uid) == 1) {
            int id = get_user_id(uid);
            printf("%d\n", user_data[id].total_point);
        } else if (sscanf(line, "?number_submission_period %s %s", from, to) == 2) {
            int from_sec = timeToSeconds(from);
            int to_sec = timeToSeconds(to);
            int low = 0, high = sub_count;
            while (low < high) {
                int mid = (low + high) / 2;
                if (sub[mid].time_sec >= from_sec) high = mid;
                else low = mid + 1;
            }
            int start = low;
            low = 0, high = sub_count;
            while (low < high) {
                int mid = (low + high) / 2;
                if (sub[mid].time_sec > to_sec) high = mid;
                else low = mid + 1;
            }
            int end = low;
            printf("%d\n", end - start);
        }
    }
    return 0;
}
