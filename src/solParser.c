#include "../headers/KillerSudokuChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

int parseSolFile(FILE* f, char* name, KSData* ksData) {
	char line[200];
	const char delim[2] = ",";
	char* token;
	char* restOfToken;

	// check each line. the format is csv, with
	// each line representing a row. '-' means
	// a value is not supplied
	for (int row = 0; fgets(line, 200, f) != NULL; row++) {
		// if we have too many rows print an error
		if (row >= ksData->gridLength) {
			printf("Error: too many rows in solution file\n");
			return(-1);
		}

		token = strtok(line, delim);
		for (int column = 0; column < ksData->gridLength; column++,
		token = strtok(NULL, delim)) {
			// gets the value in the cell
			if (*token == '-') continue;

			int cellValue = strtol(token, &restOfToken, 10);
			if (cellValue < 1 || cellValue > ksData->gridLength
				|| token == NULL || (*restOfToken != '\0' && *restOfToken != '\n')) {
				printf("Error: invalid value in [%d,%d] of solution file\n",
						column + 1, ksData->gridLength - row);
				return(-1);
			}
			else {
				Cell* currentCell = ksData->grid[column][ksData->gridLength - row - 1];
				currentCell->value = cellValue;
				currentCell->filled = true;
			}
		}
	}
	return 0;
}
