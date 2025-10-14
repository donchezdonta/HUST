#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int deadline;
    int profit;
} Job;

int compare(const void *a, const void *b) {
    return ((Job *)b)->profit - ((Job *)a)->profit;
}

void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);
    
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }
    
    int *slot = (int *)malloc((maxDeadline + 1) * sizeof(int));
    int *result = (int *)malloc(n * sizeof(int));
    memset(slot, -1, (maxDeadline + 1) * sizeof(int));
    
    int totalProfit = 0;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                result[count++] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    
    printf("Selected jobs: ");
    for (int i = 0; i < count; i++)
        printf("%d ", result[i]);
    printf("\nTotal profit: %d\n", totalProfit);
    
    printf("Schedule:\n");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != -1)
            printf("Time %d: Job %d (profit: %d)\n", i, jobs[slot[i]].id, jobs[slot[i]].profit);
    }
    
    free(slot);
    free(result);
}

int main() {
    int n;
    printf("Number of jobs: ");
    scanf("%d", &n);
    
    Job *jobs = (Job *)malloc(n * sizeof(Job));
    
    for (int i = 0; i < n; i++) {
        jobs[i].id = i + 1;
        printf("Job %d - Deadline: ", i + 1);
        scanf("%d", &jobs[i].deadline);
        printf("Job %d - Profit: ", i + 1);
        scanf("%d", &jobs[i].profit);
    }
    
    jobSequencing(jobs, n);
    
    free(jobs);
    return 0;
}