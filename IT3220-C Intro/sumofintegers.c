#include <stdio.h>

int main()
{
	int n;
	const int MOD = 1000000007;
	scanf("%d", &n);
	
	int a[100000];
	long long count = 0;
	
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	//count pairs 
	for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] + 1 == a[j] || a[j] + 1 == a[i]) {
                count = (count + 1) % MOD;
            }
        }
    }
    printf("%lld\n", count);
	return 0;
}
