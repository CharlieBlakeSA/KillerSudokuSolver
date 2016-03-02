#include "../headers/KillerSudokuChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

KSState parseGridFile(FILE* f, KSData* ksData) {
	char line[200];
	const char delim[2] = ",";
	char* token;
	char* restOfToken;

	if (fgets(line, 200, f) == NULL) {
		printf("Error: grid file empty\n");
		return INVALIDSYNTAX;
	}

	// checks the first line (size of a box, number of cages)
	token = strtok(line, delim);
	int boxLength = strtol(token, &restOfToken, 10);
	int gridLength = pow(boxLength, 2);
	int numberOfCells = pow(gridLength, 2);
	setupGridDimensions(boxLength, gridLength, numberOfCells, ksData);

	if (boxLength < 2 || boxLength == (int) LONG_MAX) {
		printf("Error: value in first line of grid file. "
				"Box length must be a number > 1\n");
		return INVALIDSYNTAX;
	}

	token = strtok(NULL, delim);
	int numberOfCages = strtol(token, &restOfToken, 10);
	setupCages(numberOfCages, ksData);

	if (numberOfCages < 1 || numberOfCages > numberOfCells) {
		printf("Error: value in first line of grid file. "
				"Number of cages must be a number > 1\n");
		return INVALIDSYNTAX;
	}

	else if (*restOfToken != '\n' || strtok(NULL, delim) != NULL) {
		printf("Error: first line in grid file contains too many values\n");
		return INVALIDSYNTAX;
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
			printf("Error: mismatched number of cages specified in grid file\n");
			return INVALIDSYNTAX;
		}

		// gets the cage size
		token = strtok(line, delim);
		int cageSize = strtol(token, &restOfToken, 10);
		if (cageSize < 1 || cageSize > numberOfCells
				|| token == NULL || *restOfToken != '\0') {
			printf("Error: invalid cage size in line %d of grid file\n", lineCount);
			return INVALIDSYNTAX;
		}
		totalCageSizes += cageSize;

		// gets the cage sum
		token = strtok(NULL, delim);
		int cageSum = strtol(token, &restOfToken, 10);
		if (cageSum < 1 || cageSum > sumOfCageSums
				|| token == NULL || *restOfToken != '\0') {
			printf("Error: invalid cage sum in line %d of grid file\n", lineCount);
			return INVALIDSYNTAX;
		}
		totalCageSum += cageSum;

		// create a corresponding cage object in the data struct
		Cage* currentCage = createCage(cageSize, cageSum, lineCount-2, ksData);

		// reads the cell co-ordinates
		for (int i = 0; i < cageSize; i++) {
			// x co-ordinate
			char* xToken = strtok(NULL, ".");
			int x = strtol(xToken, &restOfToken, 10);

			if (x < 1 || x > gridLength || xToken == NULL || *restOfToken != '\0') {

				printf("Error: invalid cell co-ordinates in line %d of grid file\n", lineCount);
				return INVALIDSYNTAX;
			}

			// y co-ordinate
			char* yToken = strtok(NULL, delim);
			int y = strtol(yToken, &restOfToken, 10);

			if (y < 1 || y > gridLength || yToken == NULL ||
					!(*restOfToken == '\0' || (i==cageSize-1 && *restOfToken == '\n'))) {

				printf("Error: invalid cell co-ordinates in line %d of grid file\n", lineCount);
				return INVALIDSYNTAX;
			}

			// check off the cell we're currently looking at and add the current
			// cage to our data struct. If we've already seen the cell, send an error
			if (cellCheck[x-1][y-1]) {
				printf("Error: in line %d of grid file. A cage already covers cell "
						"[%d,%d]\n", lineCount, x, y);
				return INVALIDPROBLEM;
			}
			else {
				cellCheck[x-1][y-1] = true;
				createCell(x, y, i, currentCage, ksData);
			}
		}
		lineCount++;
	}

	// checks if there are any unfilled cells
	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridLength; j++) {
			if (!cellCheck[i][j]) {
				printf("Error: cage in position [%d,%d] of grid file is not covered\n", i+1, j+1);
				return INVALIDPROBLEM;
			}
		}
	}

	if (totalCageSizes != numberOfCells) {
		printf("Error: cages in grid file do not cover correct number of squares\n");
		return INVALIDPROBLEM;
	}
	else if (totalCageSum != sumOfCageSums) {
		printf("Error: cage sums in grid file do not add to correct value\n");
		return INVALIDPROBLEM;
	}

	return VALID;
}
