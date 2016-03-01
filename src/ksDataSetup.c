#include "../headers/KillerSudokuChecker.h"
#include <stdlib.h>
#include <stdbool.h>

void setupGridDimensions(int boxLength, int gridLength, int numberOfCells, KSData* ksData){
	ksData->boxLength = boxLength;
	ksData->gridLength = gridLength;
	ksData->numberOfCells = numberOfCells;
	ksData->grid = malloc(sizeof(Cell**) * gridLength);
	for (int i = 0; i < gridLength; i++)
		ksData->grid[i] = malloc(sizeof(Cell*) * gridLength);
}

void setupCages(int numberOfCages, KSData* ksData) {
	ksData->cages = malloc(sizeof(Cage*) * numberOfCages);
	ksData->numberOfCages = numberOfCages;
}

Cage* createCage(int size, int sum, int cageCount, KSData* ksData) {
	Cage* newCage = malloc(sizeof(Cage));
	newCage->cageSize = size;
	newCage->cageSum = sum;
	newCage->cells = malloc(sizeof(Cell*) * size);

	ksData->cages[cageCount] = newCage;

	return newCage;
}

void createCell(int x, int y, int cellCount, Cage* cage, KSData* ksData) {
	Cell* newCell = malloc(sizeof(Cell));
	newCell->x = x;
	newCell->y = y;
	newCell->filled = false;
	newCell->value = -1;

	cage->cells[cellCount] = newCell;
	ksData->grid[x-1][y-1] = newCell;
}
