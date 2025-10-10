#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int grid[3][3][3];
long long solutionCount = 0;

bool usedInXPlane[3][9]; // [x][num-1]
bool usedInYPlane[3][9]; // [y][num-1]
bool usedInZPlane[3][9]; // [z][num-1]

// progress reporting
unsigned long long attempts = 0;
time_t lastUpdate = 0;

bool isValid(int x, int y, int z, int num) {
    return !usedInXPlane[x][num-1] && 
           !usedInYPlane[y][num-1] && 
           !usedInZPlane[z][num-1];
}

// recursive
void solve(int pos) {
    attempts++;
    time_t now = time(NULL);
    if (now - lastUpdate >= 3) {  // updates every 3 seconds for debugging
        printf("Progress: %llu attempts, %lld solutions found so far...\n", 
               attempts, solutionCount);
        fflush(stdout);
        lastUpdate = now;
    }
    
    if (pos == 27) { 
        solutionCount++;
        printf("Solution found! Total so far: %lld\n", solutionCount);
        fflush(stdout);
        return;
    }
    
    // convert pos to 3D coords
    int x = pos / 9;
    int y = (pos % 9) / 3;
    int z = pos % 3;
    
    // try each number in current cell
    for (int num = 1; num <= 9; num++) {
        if (isValid(x, y, z, num)) {
            grid[x][y][z] = num;
            usedInXPlane[x][num-1] = true;
            usedInYPlane[y][num-1] = true;
            usedInZPlane[z][num-1] = true;
            
            solve(pos + 1);
            
            grid[x][y][z] = 0;
            usedInXPlane[x][num-1] = false;
            usedInYPlane[y][num-1] = false;
            usedInZPlane[z][num-1] = false;
        }
    }
}

int main() {
    memset(grid, 0, sizeof(grid));
    memset(usedInXPlane, false, sizeof(usedInXPlane));
    memset(usedInYPlane, false, sizeof(usedInYPlane));
    memset(usedInZPlane, false, sizeof(usedInZPlane));

    printf("Starting 3D Sudoku solver...\n");
    fflush(stdout);
    
    lastUpdate = time(NULL);
    clock_t start = clock();
    
    solve(0);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Finished! Number of possible 3D Sudoku solutions: %lld\n", solutionCount);
    printf("Execution time: %.2f seconds\n", time_spent);
    printf("Total attempts: %llu\n", attempts);
    fflush(stdout);
    
    return 0;
}