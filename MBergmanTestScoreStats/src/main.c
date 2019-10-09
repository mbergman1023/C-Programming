/*
 ============================================================================
 Name        : MBergmanTestScoreStats.c
 Author      : Mitchell Bergman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	char n[BUFSIZ]; // Score Entered
	float avgScore = 0; // Average Score
	float minScore = 99999; // Minimum Score
	float maxScore = 0; // Maximum Score
	int numTests = 0; // Number of Tests (minus one because it counts 0 entry)
	float stdDev = 0; // Standard Deviation
	float totPoints = 0; // Total Points
	float sumSquares = 0; // Sum Squares calculation
	float scoreEnt;
	int exit = 1;

	printf(
			"Enter scores one at a time, then press <ENTER>, Press <ENTER> when complete.\n"); //Prompts user how to input

	do { //Start of loop
		fgets(n, BUFSIZ, stdin);
		if (n[0] == '\n') {
			exit = 0;
		} else {

			scoreEnt = atof(n);
			numTests++; // increase tests by one each loop
			totPoints += scoreEnt; // accumulating points
			avgScore = totPoints / numTests; // calculate average
			if (scoreEnt <= minScore)
				minScore = scoreEnt; // calculate min
			if (scoreEnt >= maxScore)
				maxScore = scoreEnt; // calculate max
			sumSquares += (scoreEnt * scoreEnt);
		}

		// calculate sum of squares for each entry

	} while (exit == 1); // End of loop

	if(numTests!=0){
	stdDev = sqrt(
			(sumSquares - ((totPoints * totPoints) / numTests)) / numTests); // Standard Dev Calculation

	}
	else {
		minScore=0;
	}
	//Print out scores and other calculations

	printf("%d\t%f\t%f\t%f\t%f\t\n", numTests, minScore, maxScore,
			avgScore, stdDev);

	return 0;
}
