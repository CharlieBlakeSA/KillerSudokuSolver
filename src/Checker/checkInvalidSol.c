#include "../headers/KillerSudoku.h"
#include "../headers/SudokuStates.h"
#include <stdbool.h>

int checkRowsColumns(KSData* ksData);
int checkBoxes(KSData* ksData);
int checkCage(KSData* ksData);
int checkCageSum(KSData* ksData);

KSState checkInvalidSol(KSData* ksData) {
	if (checkRowsColumns(ksData) == -1) {
		printf("Error: row/column contains duplicate values in solution file\n");
		return INVALIDSOL;
	}
	else if (checkBoxes(ksData) == -1) {
		printf("Error: box contains duplicate values in solution file\n");
		return INVALIDSOL;
	}
	else if (checkCage(ksData) == -1) {
		printf("Error: cage contains duplicate values in solution file\n");
		return INVALIDSOL;
	}
	else if (checkCageSum(ksData) == -1) {
		printf("Error: incorrect cage sum in solution file\n");
		return INVALIDSOL;
	}
	else
		return VALID;
}

int checkRowsColumns(KSData* ksData) {
	// check each column for duplicate numbers,
	// repeat for rows
	for (int checkCount = 0; checkCount < 2; checkCount++) {
		for (int a = 0; a < ksData->gridLength; a++) {

			bool numbersSeen[ksData->gridLength];
			for (int i = 0; i < ksData->gridLength; i++)
				numbersSeen[i] = false;

			for (int b = 0; b < ksData->gridLength; b++) {

				// this line changes if we are checking horizontally
				// or vertically
				int v = (checkCount == 0 ? ksData->grid[a][b] :
						ksData->grid[b][a])->value;

				if (v > 0 && v <= ksData->gridLength) {
					if (numbersSeen[v-1])
						return -1;
					else
						numbersSeen[v-1] = true;
				}
			}
		}
	}
	return 0;
}

int checkBoxes(KSData* ksData) {
	// check each box for duplicates
	for (int boxColumn = 0; boxColumn < ksData->boxLength; boxColumn++) {
		for (int boxRow = 0; boxRow < ksData->boxLength; boxRow++) {

			bool numbersSeen[ksData->gridLength];
			for (int i = 0; i < ksData->gridLength; i++)
				numbersSeen[i] = false;

			for (int x = 0; x < ksData->boxLength; x++) {
				for (int y = 0; y < ksData->boxLength; y++) {

					int v = ksData->grid \
							[boxColumn * ksData->boxLength + x] \
							[boxRow * ksData->boxLength + y] \
							->value;

					if (v > 0 && v <= ksData->gridLength) {
						if (numbersSeen[v-1])
							return -1;
						else
							numbersSeen[v-1] = true;
					}
				}
			}
		}
	}
	return 0;
}

int checkCage(KSData* ksData) {
	// check each cage for duplicates
	for (int cageCount = 0; cageCount < ksData->numberOfCages; cageCount++) {

		bool numbersSeen[ksData->gridLength];
		for (int i = 0; i < ksData->gridLength; i++)
			numbersSeen[i] = false;
		Cage* currentCage = ksData->cages[cageCount];

		// check each cell in the current cage
		for (int cellCount = 0; cellCount < currentCage->cageSize;
				cellCount++) {
			int v = currentCage->cells[cellCount]->value;

			if (v > 0 && v <= ksData->gridLength) {
				if (numbersSeen[v-1])
					return -1;
				else
					numbersSeen[v-1] = true;
			}
		}
	}
	return 0;
}

int checkCageSum(KSData* ksData) {
	// check each full cage equals the correct sum
	for (int cageCount = 0; cageCount < ksData->numberOfCages; cageCount++) {

		Cage* currentCage = ksData->cages[cageCount];

		int cageSum = 0;
		bool cageFilled = true;
		// check each cell in the current cage
		for (int cellCount = 0; cellCount < currentCage->cageSize;
				cellCount++) {
			Cell* currentCell = currentCage->cells[cellCount];

			// if we detect a cage that is not filled then
			// break and go to the next cage
			if (!currentCell->filled) {
				cageFilled = false;
				break;
			}

			// sum the value of the cells
			cageSum += currentCell->value;
		}

		// if the sum of a full cage is incorrect, return error
		if (cageFilled && currentCage->cageSum != cageSum)
			return -1;
	}
	return 0;
}
