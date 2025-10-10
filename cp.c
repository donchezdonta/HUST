#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cp(const char* src, const char* dst) {
	FILE *source; 
	FILE *dest;
	
	source = fopen(src, "rb");
	if (source == NULL) {
		printf("Cannot open file '%s'\n", src);
	}
	
	dest = fopen(dst, "rb");
	if (dest != NULL) {
		fclose(dest);
		printf("Destination '%s' already exists? Overwrite? (y/n):", dst);
		char ans;
		scanf(" %c", &ans);
		if (ans != 'y' && ans != 'Y') {
			printf("Operation cancelled\n");
			fclose(source);
			return 0;
		}
	}
	dest = fopen(dst, "wb");
	if (dest == NULL) {
		printf("Cannot create destination file '%s'\n");
		fclose(source);
		return 0;
	}
	
	int c;
	while ((c = fgetc(source)) != EOF) {
		if (fputc(c, dest) == EOF) {
			printf("Write failed!");
			fclose(source);
			fclose(dest);
			return 0;
		}
	}
	
	fclose(source);
	fclose(dest);
	
	printf("Successfully copied: '%s' to '%s'\n", src, dst);
	return 1;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Invalid number of arguments! (Got %d, expected 2)\n", argc - 1);
	}
	
	char *src = argv[1];
	char *dest = argv[2];
	
	if (strlen(src) == 0) {
		printf("Empty source filename!");
		return 1;
	}
	if (strlen(dest) == 0) {
		printf("Empty destination filename!");
		return 1;
	}
	
	if (strcmp(src, dest) == 0) {
		printf("Source and destination files share the same name!");
		return 1;
	}
	
	if (cp(src, dest)) return 0;
	return 1;
}
