#include "../headers/KillerSudokuChecker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void usage();
FILE* attemptOpen(char* filename);

int main(int argc, char *argv[]) {
	if (argc != 2 && argc != 3) usage();

	// create a KSData struct instance to hold info about the
	// puzzle
	KSData ksData;
	FILE* gridFile = attemptOpen(argv[1]);

	if (parseGridFile(gridFile, argv[1], &ksData) < 0) {
		printf("---Program terminated due to error in grid file---\n");
		return(-1);
	} else
		printf("Grid file syntax valid...\n");

	if (argc == 3) {
		FILE* solFile = attemptOpen(argv[2]);
		if (parseSolFile(solFile, argv[2], &ksData) < 0) {
			printf("---Program terminated due to error in solution file---\n");
			return(-1);
		} else
			printf("Solution file syntax valid...\n");
	}

	if (checkInvalidSol(&ksData) < 0) {
		printf("INVALIDSOL: the supplied solution is not valid\n"
				"---Program terminated due to invalid solution file---\n");
		return (-1);
	}
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
