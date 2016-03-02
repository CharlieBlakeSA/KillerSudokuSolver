#include "../headers/KillerSudokuChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage();
FILE* attemptOpen(char* filename);

int assessInputFiles(int argc, char *argv[]) {
	if (argc != 2 && argc != 3) usage();

	// create a KSData struct instance to hold info about the
	// puzzle
	KSData ksData;
	FILE* gridFile = attemptOpen(argv[1]);

	// open and parse the grid file
	if (parseGridFile(gridFile, &ksData) < 0) {
		printf("---Program terminated due to error in grid file---\n");
		return(-1);
	} else
		printf("Grid file syntax valid...\n");

	// if a solution file has been supplied
	if (argc == 3) {
		// open and parse the solution file
		FILE* solFile = attemptOpen(argv[2]);
		if (parseSolFile(solFile, &ksData) < 0) {
			printf("---Program terminated due to error in solution file---\n");
			return(-1);
		} else
			printf("Solution file syntax valid...\n");

		// check if the (partial) solution supplied is valid
		int r = checkInvalidSol(&ksData);
		if (r < 0) {
			printf("INVALIDSOL: ");
			switch(r) {
				case -2:
					printf("row/column contains duplicate values in solution file\n");
					break;
				case -3:
					printf("box contains duplicate values in solution file\n");
					break;
				case -4:
					printf("cage contains duplicate values in solution file\n");
					break;
				case -5:
					printf("incorrect cage sum in solution file\n");
					break;
			}
			printf("---Program terminated due to invalid solution file---\n");
			return (-1);
		}

		if (checkComplete(&ksData)) {
			printf("SOLVED\n");
			return 0;
		}
	}

	printf("INCOMPLETE\n");
	return 0;
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
