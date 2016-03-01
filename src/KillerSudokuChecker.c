#include "../headers/KillerSudokuChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void usage();
FILE* attemptOpen(char* filename);
void checkSolFile(FILE* solFile, char* filename);

int main(int argc, char *argv[]) {
	if (argc != 3) usage();

	// create a KSData struct instance to hold info about the
	// puzzle
	KSData ksData;

	// attempts to treat args as filenames and opens
	FILE* gridFile = attemptOpen(argv[1]);
	FILE* solFile = attemptOpen(argv[2]);

	parseGridFile(gridFile, argv[1], &ksData);
	//checkSolFile(solFile, argv[2]);
}

void usage() {
	printf("usage: KillerSudokuChecker [killer sudoku file] [solution file]\n");
	exit(EXIT_FAILURE);
}

FILE* attemptOpen(char* filename) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Error: %s for file \"%s\"\n", strerror(errno), filename);
		usage();
	}
	return f;
}
