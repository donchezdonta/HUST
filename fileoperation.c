#include <stdio.h>
#include <ctype.h>
#include "const.h"

enum { SUCCESS, FAIL};
 
/*main() {
	FILE* fptr;
	char name[] = "C:\\Users\\SinhVien\\Documents\\NLNM 202421619\\const.h";
	int res = SUCCESS;
	if ((fptr = fopen(name, "r")) == NULL) {
		printf("Cannot open %s!\n", name);
		res = FAIL;
	} else {
		printf("fptr value: 0x%p\n", fptr);
		printf("The value of Pi is: %f", pi);
		printf("Closing file...");
		fclose(fptr);
	}
	return res;
}*/

void charReadWrite(FILE *fin, FILE *fout) {
	int c;
	while ((c=fgetc(fin)) != EOF) {
		fputc(c, fout);
		putchar(c);
	} 
}

void fileCapitalization(FILE *fin, FILE *fout) {
	int c;
	while ((c = fgetc(fin)) != EOF) {
		if (islower(c)) c  = toupper(c);
		else if (isupper(c)) c = tolower(c);
		fputc(c, fout);
		putchar(c);
	}
}

int main(void) {
	FILE *fptr1, *fptr2;
	char name1[] = "C:\\Users\\SinhVien\\Documents\\NLNM 202421619\\dest.txt";
	char name2[] = "C:\\Users\\SinhVien\\Documents\\NLNM 202421619\\org.txt";
	int res = SUCCESS;
	
	if ((fptr1 = fopen(name1, "w")) == NULL) {
		printf("Cannot open %s!\n", name1);
		res = FAIL;
	} else if ((fptr2 = fopen(name2, "r")) == NULL) {
		printf("Cannot open %s!\n", name2);
		res = FAIL;
	} else {
		fileCapitalization(fptr2, fptr1);
		fclose(fptr1);
		fclose(fptr2);
	}
	return res;
}
