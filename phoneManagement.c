#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MODEL 50

typedef struct {
	char model[MAX_MODEL];
	int memory;
	float screensize;
	int price;
} Phone;

void CLI() {
	printf("\n==PHONE DATABASE MANAGEMENT==\n");
	printf("1. Import DB from text\n");
	printf("2. Import from DB\n");
	printf("3. Print All Databse\n");
	printf("4. Search phone by Phone Model\n");
	printf("5. Exit");
	printf("Choose an option: ");
}

int countRecords(const char* filename) {
	FILE* fptr = fopen(filename, "r");
	if (file == NULL) return 0;
	
	int count = 0;
	char buffer[256];
	while (fgets(buffer, 256, file) != NULL) count++;
	fclose(file);
	return count;
}

int importFromText(const char* txt_file, const char* dat_file) {
	FILE* fin = fopen(txt_file, "r");
	if (fin == NULL) {
		printf("Cannot open %s\n", txt_file);
		return 0;
	}
	
	file* fout = fopen(dat_file, "wb");
	if (fout == NULL) {
		printf("")
	}
}

int main() {

	return 0;
}


