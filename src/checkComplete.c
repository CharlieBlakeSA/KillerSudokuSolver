#include "../headers/KillerSudokuChecker.h"
#include <stdbool.h>

bool checkComplete(KSData* ksData) {
	for (int x = 0; x < ksData->gridLength; x++)
		for (int y = 0; y < ksData->gridLength; y++)
			if (!ksData->grid[x][y]->filled)
				return false;
	return true;
}
