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

int parseGridFile(FILE* gridFile, char* filename, KSData* ksData);
int parseSolFile(FILE* solFile, char* filename, KSData* ksData);
void setupGridDimensions(int boxLength, int gridLength, int numberOfCells, KSData* ksData);
void setupCages(int numberOfCages, KSData* ksData);
Cage* createCage(int size, int sum, int cageCount, KSData* ksData);
void createCell(int x, int y, int cellCount, Cage* cage, KSData* ksData);
int checkInvalidSol(KSData* ksData);
