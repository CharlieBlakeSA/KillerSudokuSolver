#include "../headers/KillerSudoku.h"
#include "../headers/SudokuStates.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage(char* programName);
FILE* attemptOpen(char* filename, char* programName);

KSState assessInputFiles(int argc, char *argv[], KSData* ksData) {
	if (argc != 2 && argc != 3) usage(argv[0]);

	// open and parse the grid file
	FILE* gridFile = attemptOpen(argv[1], argv[0]);
	KSState ks = parseGridFile(gridFile, ksData);
	if (ks != VALID) {
		return ks;
	} else
		printf("Grid file syntax valid...\n");

	// if a solution file has been supplied
	if (argc == 3) {
		// open and parse the solution file
		FILE* solFile = attemptOpen(argv[2], argv[0]);
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

void usage(char* programName) {
	printf("usage: %s killer_sudoku_file [solution_file]\n", programName);
	exit(EXIT_FAILURE);
}

FILE* attemptOpen(char* filename, char* programName) {
	FILE* f = fopen(filename, "r");
	if (!f) {
		printf("Error: %s for file \"%s\"\n", strerror(errno), filename);
		usage(programName);
	}
	return f;
}
