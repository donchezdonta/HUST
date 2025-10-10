#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX 100
int M[MAX][MAX];
long long cnt1 = 0;  
long long cnt2 = 0;  

int C(int k, int n) {
    if (k == 0 || k == n)
        return 1;
    cnt1++;  
    return C(k - 1, n - 1) + C(k, n - 1);
}

int Cmemo(int k, int n) {
    if (k == 0 || k == n)
        return 1;   
    else if (M[k][n] != 0)
        return M[k][n];
    else {
        cnt2++;  
        M[k][n] = Cmemo(k - 1, n - 1) + Cmemo(k, n - 1);
        return M[k][n];
    }
}

int main() {
    int n, k;
    clock_t start, end;
    double time1 = 0, time2 = 0;
    int res1, res2;
    
    scanf("%d %d", &k, &n);
    
    if (k < 0 || n < 0 || k > n || k >= MAX || n >= MAX) {
        return 1;
    }
    
    cnt1 = 0;
    start = clock();
    res1 = C(k, n);
    end = clock();
    time1 = (double) (end - start) / CLOCKS_PER_SEC;
    
    memset(M, 0, sizeof(M));
    cnt2 = 0;
    start = clock();
    res2 = Cmemo(k, n);
    end = clock();
    time2 = (double) (end - start) / CLOCKS_PER_SEC;
    
    printf("Recursive:  Result: %d, Operations: %lld, Time: %.4lf seconds\n", res1, cnt1, time1);
    printf("Memoized:   Result: %d, Operations: %lld, Time: %.4lf seconds\n", res2, cnt2, time2);
    return 0;
}