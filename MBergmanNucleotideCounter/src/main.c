/*
 ============================================================================
 Name        : MBergmanNucleotideCounter.c
 Author      : Mitchell Bergman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char nextchar;
	char inFile[BUFSIZ];
	printf("Enter an INPUT file  name:\n");
	fgets(inFile, BUFSIZ, stdin);
	inFile[strlen(inFile) - 1] = '\0';

	char outFile[BUFSIZ];
	printf("Enter an OUTPUT file  name:\n");
	fgets(outFile, BUFSIZ, stdin);
	outFile[strlen(outFile) - 1] = '\0';

	FILE* ifp = fopen(inFile, "r");
	FILE* ofp = fopen(outFile, "w");

	int numA = 0, numC = 0, numG = 0, numT = 0;

	if (ifp == NULL) {

		printf("FILE COULD NOT BE FOUND.\n");
	} else {
		while (!feof(ifp)) {
			nextchar = fgetc(ifp);

			switch (nextchar) {

			case 'A':
				numA++;
				break;
			case 'C':
				numC++;
				break;
			case 'G':
				numG++;
				break;
			case 'T':
				numT++;
				break;
			default:
				fprintf(ofp, "%d %d %d %d\n", numA, numC, numG, numT);
				numA = 0, numC = 0, numG = 0, numT = 0;
			}
		}
	}
	fclose(ifp);
	fclose(ofp);
	printf("Complete\n");
	return 0;
}
