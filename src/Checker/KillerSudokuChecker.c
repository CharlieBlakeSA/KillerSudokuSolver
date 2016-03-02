#include "../headers/KillerSudoku.h"
#include "../headers/SudokuStates.h"

int main(int argc, char *argv[]) {
	// create a KSData struct instance to hold info
	// about the puzzle
	KSData ksDataStruct;

	KSState s = assessInputFiles(argc, argv, &ksDataStruct);
	printf("---%s---\n", stringFromState(s));
}
