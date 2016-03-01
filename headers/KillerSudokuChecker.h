#include <stdbool.h>
#include <math.h>

typedef struct {
	int boxLength;
	int gridLength;
	int numberOfCells;
	int numberOfCages;
	Cage* cages;
	Cell** grid;
} KSData;

typedef struct {
	int cageSize;
	int cageSum;
	Cell* cells;
} Cage;

typedef struct {
	int x;
	int y;
	int value;
	bool filled;
} Cell;

void parseGridFile(FILE* gridFile, char* filename, KSData* ksData);
