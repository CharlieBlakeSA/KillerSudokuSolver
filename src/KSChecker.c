#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

void usage();
FILE* attemptOpen(char* filename);
void checkKSFile(FILE* ksFile, char* filename);
void checkSolFile(FILE* solFile, char* filename);

int main(int argc, char *argv[]) {
	if (argc != 3) usage();

	// attempts to treat args as filenames and opens
	FILE* ksFile = attemptOpen(argv[1]);
	FILE* solFile = attemptOpen(argv[2]);

	checkKSFile(ksFile, argv[1]);
	//checkSolFile(solFile, argv[2]);
}

void usage() {
	printf("usage: KSChecker [killer sudoku file] [solution file]\n");
	exit(EXIT_FAILURE);
}

FILE* attemptOpen(char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Error: %s for file \"%s\"\n", strerror(errno), filename);
		usage();
	}
	return f;
}

void checkKSFile(FILE* f, char* name) {
	char line[200];
	const char delim[2] = ",";
	char* token;
	char* restOfToken;

	if (fgets(line, 200, f) == NULL) {
		printf("Error: \"%s\" empty\n", name);
		exit(EXIT_FAILURE);
	}

	// check the first line (indicates the size of a box)
	token = strtok(line, delim);
	const int boxLength = strtol(token, &restOfToken, 10);
	const int gridLength = pow(boxLength, 2);
	const int numberOfCells = pow(gridLength, 2);

	if (boxLength < 2 || boxLength == (int) LONG_MAX) {
		printf("Error: value in first line of \"%s\" must be a number > 1\n", name);
		exit(EXIT_FAILURE);
	}
	else if (restOfToken != NULL || strtok(NULL, delim) != NULL) {
		printf("Error: first line contains too many values\n");
		exit(EXIT_FAILURE);
	}

	// check each subsequent line
	// the format is as follows:
	// cage size,cage sum,cell1X.cell1Y,cell2X.cell2y...
	int totalCageSizes = 0;
	int totalCageSum = 0;
	const int sumOfCageSums = numberOfCells * (gridLength + 1) / 2;

	// a 2D boolean array representing each square. We first
	// zero it out then use it to check off each cell we see
	bool cellCheck[boxLength][boxLength];
	for (int i = 0; i < boxLength; i++)
		for (int j = 0; j < boxLength; j++)
			cellCheck[i][j] = false;

	// iterate through each line in the file
	for (int lineCount = 2; fgets(line, 200, f) != NULL; lineCount++) {
		// gets the cage size
		token = strtok(line, delim);
		int cageSize = strtol(token, &restOfToken, 10);
		if (cageSize < 1 || cageSize > numberOfCells || restOfToken != NULL) {
			printf("Error: invalid cage size in line %d\n", lineCount);
			exit(EXIT_FAILURE);
		}
		totalCageSizes += cageSize;

		// gets the cage sum
		token = strtok(NULL, delim);
		int cageSum = strtol(token, &restOfToken, 10);
		if (cageSum < 1 || cageSum > sumOfCageSums || restOfToken != NULL) {
			printf("Error: invalid cage sum in line %d\n", lineCount);
			exit(EXIT_FAILURE);
		}
		totalCageSum += cageSum;

	}

	// check if there are any unfilled cells
	int unfilled = false;
	for (int i = 0; i < boxLength; i++) {
		for (int j = 0; j < boxLength; j++) {
			if (!cellCheck[i][j]) {
				printf("Error: cage in position [%d,%d] is not covered\n", i+1, j+1);
				exit(EXIT_FAILURE);
			}
		}
	}

	if (totalCageSizes != sumOfCageSizes) {
		printf("Error: cages do not cover correct number of squares\n");
		exit(EXIT_FAILURE);
	}
	else if (totalCageSum != sumOfCageSums) {
		printf("Error: cage sums do not add to correct value\n");
		exit(EXIT_FAILURE);
	}
}

//void checkSolFile(FILE* f, char* name);
