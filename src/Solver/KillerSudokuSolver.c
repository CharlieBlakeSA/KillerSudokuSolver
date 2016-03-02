#include "../headers/KillerSudoku.h"

KSState solveSudoku(KSData* ksData);

int main(int argc, char *argv[]) {
	KSData ksDataStructure;

	KSState s = assessInputFiles(argc, argv, &ksDataStructure);
	switch(s) {

	case INCOMPLETE:
		printf("Attempting to solve sudoku...\n");
		KSState ss = solveSudoku(&ksDataStructure);
		if (ss == SOLVED) {
			printf("---%s---\n", stringFromState(ss));
			printSudoku(&ksDataStructure);
		} else
			printf("Sudoku could not be solved. Exiting...\n");
		break;


	case SOLVED:
		printf("---%s---\n", stringFromState(s));
		printSudoku(&ksDataStructure);
		break;

	default:
		printf("---%s---\n", stringFromState(s));
		printf("Sudoku could not be solved. Exiting...\n");
	}
}

KSState solveSudoku(KSData* ksData) {
	return INVALIDPROBLEM;
}
