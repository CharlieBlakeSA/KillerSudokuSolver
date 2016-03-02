#include "../headers/KillerSudokuChecker.h"
#include "../headers/SudokuStates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage();
FILE* attemptOpen(char* filename);

KSState assessInputFiles(int argc, char *argv[], KSData* ksData) {
	if (argc != 2 && argc != 3) usage();

	// open and parse the grid file
	FILE* gridFile = attemptOpen(argv[1]);
	KSState ks = parseGridFile(gridFile, ksData);
	if (ks != VALID) {
		return ks;
	} else
		printf("Grid file syntax valid...\n");

	// if a solution file has been supplied
	if (argc == 3) {
		// open and parse the solution file
		FILE* solFile = attemptOpen(argv[2]);
		if (parseSolFile(solFile, ksData) != VALID) {
			return INVALIDSYNTAX;
		} else
			printf("Solution file syntax valid...\n");

		// check if the (partial) solution supplied is valid
		if (checkInvalidSol(ksData) == INVALIDSOL)
			return INVALIDSOL;

		if (checkComplete(ksData))
			return SOLVED;
	}
	return INCOMPLETE;
}

void usage() {
	printf("usage: KillerSudokuChecker killer_sudoku_file [solution_file]\n");
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
