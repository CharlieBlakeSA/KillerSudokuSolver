#include "../headers/KillerSudoku.h"
#include <stdio.h>
#include <stdbool.h>

KSState solveSudoku(KSData* ksData) {
	// for every possible value in every unfilled
	// cell, try filling the cell
	for(int col = 0; col < ksData->gridLength; col++) {
		for(int row = 0; row < ksData->gridLength; row++) {

			// skips filled cells
			Cell* currentCell = ksData->grid[col][row];
			if (currentCell->filled)
				continue;

			// for each possible value in the cell
			for(int val = 1; val <= ksData->gridLength; val++) {
				currentCell->value = val;
				currentCell->filled = true;

				// check if the newly added value is valid.
				// if not, undo and move on to the next possible value
				if (checkInvalidSol(ksData) == INVALIDSOL) {
					currentCell->value = -1;
					currentCell->filled = false;
					continue;
				}

				// check if the sodoku is complete. If so, return as such
				if (checkComplete(ksData))
					return SOLVED;

				// if not, recursively call this function on
				// the data struct.
				if (solveSudoku(ksData) == INVALIDSOL) {
					// if it is not solved, undo changes and move
					// on to the next possible value
					currentCell->value = -1;
					currentCell->filled = false;
					continue;
				} else
					return SOLVED;
			}

			// if, after having tried all possible values the current
			// cell is still not filled, the sodoku can't be completed
			if (!currentCell->filled)
				return INVALIDSOL;
		}
	}

	return INVALIDSOL;
}
