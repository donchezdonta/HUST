#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100001
#define MAX_E 100001

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX_E];
int parent[MAX_V];

// Compare function for qsort
int compare(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

// Find root with path compression
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// Union by rank
void unite(int x, int y) {
    parent[find(x)] = find(y);
}

long long kruskal(int n, int m) {
    // Initialize disjoint set
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    // Sort edges by weight
    qsort(edges, m, sizeof(Edge), compare);
    
    // Process edges in ascending order
    long long total_weight = 0;
    int edges_used = 0;
    
    for (int i = 0; i < m && edges_used < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (find(u) != find(v)) {
            unite(u, v);
            total_weight += edges[i].w;
            edges_used++;
        }
    }
    
    return total_weight;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    // Read edges
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }
    
    printf("%lld\n", kruskal(n, m));
    
    return 0;
}