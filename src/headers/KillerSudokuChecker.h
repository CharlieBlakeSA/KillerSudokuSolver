#ifndef KS_CHECK_H
#define KS_CHECK_H

#include "../headers/SudokuStates.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int x;
	int y;
	int value;
	bool filled;
} Cell;

typedef struct {
	int cageSize;
	int cageSum;
	Cell** cells;
} Cage;

typedef struct {
	int boxLength;
	int gridLength;
	int numberOfCells;
	int numberOfCages;
	Cage** cages;
	Cell*** grid;
} KSData;

KSState assessInputFiles(int argc, char *argv[], KSData* ksData);
KSState parseGridFile(FILE* gridFile, KSData* ksData);
KSState parseSolFile(FILE* solFile, KSData* ksData);
void setupGridDimensions(int boxLength, int gridLength, int numberOfCells, KSData* ksData);
void setupCages(int numberOfCages, KSData* ksData);
Cage* createCage(int size, int sum, int cageCount, KSData* ksData);
void createCell(int x, int y, int cellCount, Cage* cage, KSData* ksData);
KSState checkInvalidSol(KSData* ksData);
bool checkComplete(KSData* ksData);

#endif
