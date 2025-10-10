#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define MAX_USERS 1000
#define MAX_PROBLEMS 100
#define MAX_SUBMISSIONS 100000
 
typedef struct {
    char userID[11];
    char problemID[4];
    int time_sec;
    char status[4];
    int point;
} Submission;
 
typedef struct {
    char userID[11];
    int max_points[100];
} UserData;
 
Submission submissions[MAX_SUBMISSIONS];
UserData users[MAX_USERS];
int num_submissions = 0;
int num_users = 0;
 
int time_to_seconds(char *time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}
 
int get_problem_index(char *problemID) {
    return atoi(problemID + 1);
}
 
int find_user(char *userID) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].userID, userID) == 0)
            return i;
    }
    return -1;
}
 
int add_user(char *userID) {
    strcpy(users[num_users].userID, userID);
    for (int i = 0; i < 100; i++)
        users[num_users].max_points[i] = 0;
    return num_users++;
}
 
void process_submission() {
    for (int i = 0; i < num_submissions; i++) {
        int user_idx = find_user(submissions[i].userID);
        if (user_idx == -1)
            user_idx = add_user(submissions[i].userID);
        int prob_idx = get_problem_index(submissions[i].problemID);
        if (submissions[i].point > users[user_idx].max_points[prob_idx])
            users[user_idx].max_points[prob_idx] = submissions[i].point;
    }
}
 
int main() {
    char line[100];
    char userID[11], problemID[4], timePoint[9], status[4];
    int point;
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (line[0] == '#') break;
        sscanf(line, "%s %s %s %s %d", userID, problemID, timePoint, status, &point);
        strcpy(submissions[num_submissions].userID, userID);
        strcpy(submissions[num_submissions].problemID, problemID);
        submissions[num_submissions].time_sec = time_to_seconds(timePoint);
        strcpy(submissions[num_submissions].status, status);
        submissions[num_submissions].point = point;
        num_submissions++;
    }
    process_submission();
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (line[0] == '#') break;
        if (strncmp(line, "?total_number_submissions", 25) == 0) {
            printf("%d\n", num_submissions);
        }
        else if (strncmp(line, "?number_error_submision_of_user", 31) == 0) {
            sscanf(line + 32, "%s", userID);
            int count = 0;
            for (int i = 0; i < num_submissions; i++) {
                if (strcmp(submissions[i].userID, userID) == 0 && 
                    strcmp(submissions[i].status, "ERR") == 0)
                    count++;
            }
            printf("%d\n", count);
        }
        else if (strncmp(line, "?number_error_submision", 23) == 0) {
            int count = 0;
            for (int i = 0; i < num_submissions; i++) {
                if (strcmp(submissions[i].status, "ERR") == 0)
                    count++;
            }
            printf("%d\n", count);
        }
        else if (strncmp(line, "?total_point_of_user", 20) == 0) {
            sscanf(line + 21, "%s", userID);
            int user_idx = find_user(userID);
            int total = 0;
            if (user_idx != -1) {
                for (int i = 0; i < 100; i++)
                    total += users[user_idx].max_points[i];
            }
            printf("%d\n", total);
        }
        else if (strncmp(line, "?number_submission_period", 25) == 0) {
            char from_time[9], to_time[9];
            sscanf(line + 26, "%s %s", from_time, to_time);
            int from_sec = time_to_seconds(from_time);
            int to_sec = time_to_seconds(to_time);
            int count = 0;
            for (int i = 0; i < num_submissions; i++) {
                if (submissions[i].time_sec >= from_sec && 
                    submissions[i].time_sec <= to_sec)
                    count++;
            }
            printf("%d\n", count);
        }
    }
    return 0;
}
