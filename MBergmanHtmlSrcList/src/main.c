/*
 ============================================================================
 Name        : MBergmanHtmlSrcList.c
 Author      : Mitchell Bergman
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Declarations
int count(char* pSrc);
void gSrc(char*pSrc, int a);
void gTag(char *pTag, int a);
void gUrl(char*pUrl);
void fCount(char tag[]);
void pFreq();
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	char site[BUFSIZ + 1];
	char curl[BUFSIZ + 1] = "curl -s ";
	char buf[BUFSIZ + 1];
	FILE* fp;
	puts("URL:\n");
	fgets(site, BUFSIZ, stdin); //gets website
	site[strlen(site) - 1] = '\0';
	strcat(curl, site); //appends site to end of curl -s
	fp = popen(curl, "r"); //opens html text
	fgets(buf, BUFSIZ, fp); //gets source code
	if (!fp) {
		printf("File not found.");
		return 0;
	}
	fseek(fp, 0, SEEK_END);	//find end of the file
	int sizeofFile = ftell(fp);
	char* String = (char*) malloc(sizeofFile + 1);	//allocate memory
	rewind(fp);	//start at beginning of file
	while (fgets(buf, BUFSIZ, fp) != NULL)
		strcat(String, buf);	//append strings to end of file

	printf("Ready\n");

	do {	//get character from user, output info and ready/complete

		switch (fgetc(stdin)) {
		case 'c':
			printf("%d\n", count(String));
			printf("Ready\n");
			break;
		case 't':
			gSrc(String, 0);
			printf("Ready\n");
			break;
		case 'u':
			gSrc(String, 1);
			printf("Ready\n");
			break;
		case 'f':
			gSrc(String, 2);
			pFreq();
			printf("Ready\n");
			break;
		case 'q':
			printf("Complete\n");
			return EXIT_SUCCESS;
		}
	} while (String);
	pclose(fp);
	free(String);
	return EXIT_SUCCESS;
}
char freq[BUFSIZ];
char *pC = freq;
char tags[BUFSIZ];
int count(char* pSrc) {	//func to count valid src
	int counter = 0;
	while (pSrc != NULL) {
		pSrc = strstr(pSrc, "src=\"");	//find src
		if (pSrc == NULL)
			continue;
		pSrc--;
		if (*pSrc != '.') {	//make sure it isn't .src
			counter++;
		}

		pSrc += 2;

	}

	return counter;

}

void gSrc(char*pSrc, int a) {	//func to find tags and urls
	int exit = 1;
	char*pTag;
	pSrc = strstr(pSrc, "src=\"");	//start at src
	while (exit != 0 && pSrc != NULL) {
		pTag = pSrc;
		if (*(pSrc - 1) != '.') {	//make sure it isn't .src
			if (a == 0 || a == 2) {	//choice of char t or f
				while (*pTag != '<') {	//find <
					pTag--;
				}
				pTag++;
				if (a == 0)
					gTag(pTag, 0);
				else
					gTag(pTag, 1);

			}

			if (a == 1)
				gUrl(pSrc);

		}
		pSrc = strstr(++pSrc, "src=\"");
	}
}

void gTag(char *pTag, int a) {	//func to extract tags

	char temp[BUFSIZ] = "";
	int i = 0;
	while (isalpha(*pTag)) {	//checks for letter character
		temp[i] = *pTag;
		pTag++;
		i++;

	}

	if (a == 1) {
		strcat(tags, temp);
		fCount(temp);	//find frequency
	}
	if (a == 0) {
		printf("%s\n", temp);
	}
}

void gUrl(char*pUrl) {	//func to extract urls


	char temp[BUFSIZ] = "";
	int size, i = 0;
	pUrl += 5;	//start at first "
	while (*pUrl != '\"') {	//looks for second "
		temp[i] = *pUrl;
		i++;
		pUrl++;

	}
	size = strlen(temp);
	temp[size] = '\0';

	//appends url

	printf("%s\n", temp);

}

void fCount(char tag[]) {//count frequency of tags

	char*pFind = strstr(pC, tag);//append tag
	if (pFind != NULL) {
		while (*pFind != '\t') {

			pFind++;

		}

		pFind++;
		*pFind = (int) *pFind + 1;

	}

	else {

		strcat(freq, tag);
		strcat(freq, "\t1\n");
	}
}
void pFreq() {//function to pring freq outside of loop

	printf("%s\n", freq);

}
