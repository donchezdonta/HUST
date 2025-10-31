#include <stdio.h>
#include <stdbool.h>

#define SIM_LENGTH 11

bool checkPhoneNumber(const char *sim, int menh) {
    // Lookup tables for compatible and conflicting numbers
    static const char compatible[6][5] = {
        "",   // unused
        "67", // Kim
        "34", // Mộc
        "01", // Thủy
        "9",  // Hỏa
        "258" // Thổ
    };
    
    static const char sinh[6][5] = {
        "",   // unused
        "01", // Kim sinh Thủy
        "01", // Thủy sinh Mộc
        "34", // Mộc sinh Hỏa
        "258",// Hỏa sinh Thổ
        "67"  // Thổ sinh Kim
    };
    
    static const char khac[6][5] = {
        "",   // unused
        "34", // Kim khắc Mộc
        "258",// Mộc khắc Thổ
        "9",  // Thủy khắc Hỏa
        "67", // Hỏa khắc Kim
        "01"  // Thổ khắc Thủy
    };
    
    bool hasGoodNumber = false;
    
    // Check each digit starting from index 1 (skip leading 0)
    for (int i = 1; sim[i]; i++) {
        // Check for conflicting numbers
        for (int j = 0; khac[menh][j]; j++) {
            if (sim[i] == khac[menh][j]) {
                return false;
            }
        }
        
        // Check for compatible or supportive numbers
        if (!hasGoodNumber) {
            for (int j = 0; compatible[menh][j] || sinh[menh][j]; j++) {
                if (sim[i] == compatible[menh][j] || sim[i] == sinh[menh][j]) {
                    hasGoodNumber = true;
                    break;
                }
            }
        }
    }
    
    return hasGoodNumber;
}

int main() {
    char sim[SIM_LENGTH];
    int menh;
    
    scanf("%s %d", sim, &menh);
    
    bool isCompatible = checkPhoneNumber(sim, menh);
    
    printf("%d\n", isCompatible);
    return 0;
}