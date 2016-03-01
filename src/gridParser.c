#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

void createCage(int cageSize, int cageSum, KSData* ksData);

void parseGridFile(FILE* f, char* name, KSData* ksData) {
	char line[200];
	const char delim[2] = ",";
	char* token;
	char* restOfToken;

	if (fgets(line, 200, f) == NULL) {
		printf("Error: \"%s\" empty\n", name);
		exit(EXIT_FAILURE);
	}

	// checks the first line (size of a box, number of cages)
	token = strtok(line, delim);
	int boxLength = strtol(token, &restOfToken, 10);
	int gridLength = pow(boxLength, 2);
	int numberOfCells = pow(gridLength, 2);
	ksData->boxLength = boxLength;
	ksData->gridLength = gridLength;
	ksData->numberOfCells = numberOfCells;

	if (boxLength < 2 || boxLength == (int) LONG_MAX) {
		printf("Error: value in first line of \"%s\". "
				"Box length must be a number > 1\n", name);
		exit(EXIT_FAILURE);
	}

	token = strtok(NULL, delim);
	int numberOfCages = strtol(token, &restOfToken, 10);
	ksData->numberOfCages = numberOfCages;

	if (numberOfCages < 1 || numberOfCages > gridLength) {
		printf("Error: value in first line of \"%s\". "
				"Number of cages must be a number > 1\n", name);
		exit(EXIT_FAILURE);
	}

	else if (*restOfToken != '\n' || strtok(NULL, delim) != NULL) {
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
	bool cellCheck[gridLength][gridLength];
	for (int i = 0; i < gridLength; i++)
		for (int j = 0; j < gridLength; j++)
			cellCheck[i][j] = false;

	int lineCount = 2;
	// iterates through each line in the file
	while (fgets(line, 200, f) != NULL) {
		// if we have more cages than specified in the first line,
		// send an error
		if (lineCount - 1 > numberOfCages) {
			printf("Error: mismatched number of cages specified\n");
			exit(EXIT_FAILURE);
		}

		// gets the cage size
		token = strtok(line, delim);
		int cageSize = strtol(token, &restOfToken, 10);
		if (cageSize < 1 || cageSize > numberOfCells
				|| token == NULL || *restOfToken != '\0') {
			printf("Error: invalid cage size in line %d\n", lineCount);
			exit(EXIT_FAILURE);
		}
		totalCageSizes += cageSize;

		// gets the cage sum
		token = strtok(NULL, delim);
		int cageSum = strtol(token, &restOfToken, 10);
		if (cageSum < 1 || cageSum > sumOfCageSums
				|| token == NULL || *restOfToken != '\0') {
			printf("Error: invalid cage sum in line %d\n", lineCount);
			exit(EXIT_FAILURE);
		}
		totalCageSum += cageSum;

		// create a corresponding cage object in the data struct
		createCage(cageSize, cageSum, ksData);


		// reads the cell co-ordinates
		for (int i = 0; i < cageSize; i++) {
			// x co-ordinate
			char* xToken = strtok(NULL, ".");
			int x = strtol(xToken, &restOfToken, 10);

			if (x < 1 || x > gridLength || xToken == NULL || *restOfToken != '\0') {

				printf("Error: invalid cell co-ordinates in line %d\n", lineCount);
				exit(EXIT_FAILURE);
			}

			// y co-ordinate
			char* yToken = strtok(NULL, delim);
			int y = strtol(yToken, &restOfToken, 10);

			if (y < 1 || y > gridLength || yToken == NULL ||
					!(*restOfToken == '\0' || (i==cageSize-1 && *restOfToken == '\n'))) {

				printf("Error: invalid cell co-ordinates in line %d\n", lineCount);
				exit(EXIT_FAILURE);
			}

			// check off the cell we're currently looking at and add the current
			// cage to our data struct. If we've already seen the cell, send an error
			if (cellCheck[x-1][y-1]) {
				printf("Error: in line %d. A cage already covers cell "
						"[%d,%d]\n", lineCount, x, y);
				exit(EXIT_FAILURE);
			}
			else {
				cellCheck[x-1][y-1] = true;
			}
		}
		lineCount++;
	}

	// checks if there are any unfilled cells
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (!cellCheck[i][j]) {
				printf("Error: cage in position [%d,%d] is not covered\n", i+1, j+1);
				exit(EXIT_FAILURE);
			}
		}
	}

	if (totalCageSizes != numberOfCells) {
		printf("Error: cages do not cover correct number of squares\n");
		exit(EXIT_FAILURE);
	}
	else if (totalCageSum != sumOfCageSums) {
		printf("Error: cage sums do not add to correct value\n");
		exit(EXIT_FAILURE);
	}
}

void createCage(int cageSize, int cageSum, KSData* ksData) {
	//
}
