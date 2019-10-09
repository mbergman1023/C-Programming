/*
 ============================================================================
 Name        : MBergmanThreeNPlusOne.c
 Author      : Mitchell Bergman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int computeNextValue(int n);//declarations
int computeSequenceLength(int x);
int computeMaxSequenceLength(int f, int h);
int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	int f, g, h;
	char buf[BUFSIZ];
	char outFile[BUFSIZ];
	printf("Enter an OUTPUT file  name:\n");
	fgets(outFile, BUFSIZ, stdin); // gets file name
	outFile[strlen(outFile) - 1] = '\0';//ends file with tab
	FILE* ofp = fopen(outFile, "w"); // opens file

	do {
		f = atoi(fgets(buf, BUFSIZ, stdin));// input to integer
		if (f == 0)
			break;
		g = atoi(fgets(buf, BUFSIZ, stdin));// input to integer

		if (f != 0) {
			h = computeMaxSequenceLength(f, g);//input range of values
			fprintf(ofp, "%d\t%d\t%d\n", f, g, h);
		}
	} while (f != 0);
	fclose(ofp);
	puts("Complete\n");
	return 0;
}
int computeNextValue(int n) {//compute values of n
	if (n == 1)
		return n;
	if (n % 2 == 0) {
		n = n / 2;
	} else {
		n = n * 3 + 1;
	}
	return n;
}
int computeSequenceLength(int x) {//compute amount of cycles
	int cycle = 1;
	while (x != 1) {
		x = computeNextValue(x);
		cycle++;
	}
	return cycle;
}
int computeMaxSequenceLength(int f, int g) {// compute max cycle length
	if (f > g) {// swap integers least to greatest
		int temp = f;
		f = g;
		g = temp;
	}
	int maxCycle = 0;
	for (; f <= g; f++) {
		int CycleSize = computeSequenceLength(f);
		if (CycleSize > maxCycle) {//compares sequence lengths
			maxCycle = CycleSize;
		}
	}
	return maxCycle;
}
